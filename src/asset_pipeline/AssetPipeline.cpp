#include "asset_pipeline/AssetPipeline.hpp"

#include <nlohmann/json.hpp>

#include <array>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <utility>

#ifdef __APPLE__
#include <Security/Security.h>
#endif

using json = nlohmann::json;

namespace asset_pipeline {
namespace {

std::string shellQuote(const std::string& value) {
    std::string quoted{"'"};
    for (char character : value) {
        if (character == '\'') quoted += "'\\''";
        else quoted += character;
    }
    quoted += '\'';
    return quoted;
}

std::filesystem::path temporaryPath(const std::string& suffix) {
    std::random_device random;
    std::ostringstream name;
    name << ".runecore_asset_pipeline_" << random() << suffix;
    return std::filesystem::temp_directory_path() / name.str();
}

std::string readHiddenLine(const char* prompt) {
    std::cout << prompt << std::flush;
    termios originalSettings{};
    if (tcgetattr(STDIN_FILENO, &originalSettings) != 0) {
        std::string fallback;
        std::getline(std::cin, fallback);
        return fallback;
    }

    termios hiddenSettings = originalSettings;
    hiddenSettings.c_lflag &= static_cast<unsigned long>(~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &hiddenSettings);
    std::string value;
    std::getline(std::cin, value);
    tcsetattr(STDIN_FILENO, TCSANOW, &originalSettings);
    std::cout << '\n';
    return value;
}

std::string base64Decode(const std::string& encoded) {
    static constexpr char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::array<int, 256> values{};
    values.fill(-1);
    for (int index = 0; alphabet[index] != '\0'; ++index) values[static_cast<unsigned char>(alphabet[index])] = index;

    std::string decoded;
    int accumulator = 0;
    int bits = -8;
    for (unsigned char character : encoded) {
        if (character == '=') break;
        if (values[character] < 0) continue;
        accumulator = (accumulator << 6) | values[character];
        bits += 6;
        if (bits >= 0) {
            decoded += static_cast<char>((accumulator >> bits) & 0xff);
            bits -= 8;
        }
    }
    return decoded;
}

bool writeText(const std::filesystem::path& path, const std::string& text, std::string& error) {
    std::ofstream output(path);
    if (!output) {
        error = "Unable to write " + path.string();
        return false;
    }
    output << text;
    return true;
}

std::string supportedGenerationSize(const GenerationRequest& request) {
    const float aspectRatio = static_cast<float>(request.width) / static_cast<float>(request.height);
    if (aspectRatio > 1.25f) return "1536x1024";
    if (aspectRatio < 0.8f) return "1024x1536";
    return "1024x1024";
}

} // namespace

std::string CredentialStore::read() {
    if (const char* environmentKey = std::getenv("OPENAI_API_KEY"); environmentKey && *environmentKey) {
        return environmentKey;
    }

#ifdef __APPLE__
    void* passwordData = nullptr;
    UInt32 passwordLength = 0;
    const OSStatus result = SecKeychainFindGenericPassword(
        nullptr, static_cast<UInt32>(std::strlen(serviceName)), serviceName,
        0, nullptr, &passwordLength, &passwordData, nullptr);
    if (result == errSecSuccess) {
        std::string key(static_cast<const char*>(passwordData), passwordLength);
        SecKeychainItemFreeContent(nullptr, passwordData);
        return key;
    }
#endif
    return {};
}

bool CredentialStore::save(const std::string& apiKey, std::string& error) {
    if (apiKey.empty()) {
        error = "The API key cannot be empty.";
        return false;
    }

#ifdef __APPLE__
    SecKeychainItemRef existingItem = nullptr;
    const OSStatus lookup = SecKeychainFindGenericPassword(
        nullptr, static_cast<UInt32>(std::strlen(serviceName)), serviceName,
        0, nullptr, nullptr, nullptr, &existingItem);
    if (lookup == errSecSuccess && existingItem) {
        const OSStatus update = SecKeychainItemModifyAttributesAndData(
            existingItem, nullptr, static_cast<UInt32>(apiKey.size()), apiKey.data());
        CFRelease(existingItem);
        if (update != errSecSuccess) {
            error = "Unable to update the OpenAI API key in the macOS Keychain.";
            return false;
        }
        return true;
    }

    const OSStatus add = SecKeychainAddGenericPassword(
        nullptr, static_cast<UInt32>(std::strlen(serviceName)), serviceName,
        0, nullptr, static_cast<UInt32>(apiKey.size()), apiKey.data(), nullptr);
    if (add != errSecSuccess) {
        error = "Unable to save the OpenAI API key in the macOS Keychain.";
        return false;
    }
    return true;
#else
    error = "Keychain storage is only available on macOS. Set OPENAI_API_KEY instead.";
    return false;
#endif
}

OpenAIImageProvider::OpenAIImageProvider(PipelineConfig config) : m_config(std::move(config)) {}

bool OpenAIImageProvider::generate(const GenerationRequest& request, const std::string& apiKey,
                                   const std::filesystem::path& outputPath, std::string& error) const {
    if (apiKey.empty()) {
        error = "No OpenAI API key found. Run `configure` or set OPENAI_API_KEY.";
        return false;
    }

    const std::string prompt = request.camera.empty()
        ? request.prompt
        : request.prompt + " Camera angle: " + request.camera + ".";
    json payload{
        {"model", m_config.model},
        {"prompt", prompt},
        {"size", supportedGenerationSize(request)},
        {"background", request.transparentBackground ? "transparent" : "opaque"},
        {"output_format", "png"}
    };
    const auto configPath = temporaryPath(".curl");
    const auto responsePath = temporaryPath(".json");
    const auto payloadPath = temporaryPath(".payload");
    std::error_code cleanupError;
    const std::string curlConfig =
        "url = \"" + m_config.apiUrl + "\"\n"
        "request = POST\n"
        "header = \"Authorization: Bearer " + apiKey + "\"\n"
        "header = \"Content-Type: application/json\"\n"
        "data-binary = \"@" + payloadPath.string() + "\"\n"
        "output = \"" + responsePath.string() + "\"\n"
        "silent\nshow-error\n";
    if (!writeText(configPath, curlConfig, error)) return false;
    if (!writeText(payloadPath, payload.dump(), error)) return false;
    chmod(configPath.c_str(), S_IRUSR | S_IWUSR);
    chmod(payloadPath.c_str(), S_IRUSR | S_IWUSR);

    const std::string command = "curl --config " + shellQuote(configPath.string());
    const int exitCode = std::system(command.c_str());
    std::ifstream response(responsePath);
    std::string responseText((std::istreambuf_iterator<char>(response)), std::istreambuf_iterator<char>());
    std::filesystem::remove(configPath, cleanupError);
    std::filesystem::remove(payloadPath, cleanupError);
    std::filesystem::remove(responsePath, cleanupError);
    if (exitCode != 0) {
        error = "OpenAI request failed (curl exit " + std::to_string(exitCode) + ").";
        if (!responseText.empty()) error += " Provider response: " + responseText;
        return false;
    }

    try {
        const json result = json::parse(responseText);
        if (!result.contains("data") || result["data"].empty() || !result["data"][0].contains("b64_json")) {
            error = "OpenAI returned no base64 image data: " + result.dump();
            return false;
        }
        const std::string image = base64Decode(result["data"][0]["b64_json"].get<std::string>());
        if (image.empty()) {
            error = "OpenAI returned an empty image.";
            return false;
        }
        if (!outputPath.parent_path().empty()) std::filesystem::create_directories(outputPath.parent_path());
        std::ofstream output(outputPath, std::ios::binary);
        output.write(image.data(), static_cast<std::streamsize>(image.size()));
        if (!output) {
            error = "Unable to write generated image " + outputPath.string();
            return false;
        }
        return validateGeneratedImage(outputPath, error);
    } catch (const std::exception& exception) {
        error = std::string("Unable to parse OpenAI response: ") + exception.what();
        return false;
    }
}

bool loadGenerationRequest(const std::filesystem::path& path, GenerationRequest& request, std::string& error) {
    std::ifstream input(path);
    if (!input) {
        error = "Unable to open request metadata " + path.string();
        return false;
    }
    try {
        const json data = json::parse(input);
        request.id = data.at("id").get<std::string>();
        request.category = data.value("category", "unknown");
        request.assetLabel = data.at("label").get<std::string>();
        request.prompt = data.at("prompt").get<std::string>();
        request.camera = data.value("camera", "");
        request.style = data.value("style", "runecore_hybrid_v1");
        request.presentationTier = data.value("presentation_tier", "pixel");
        request.width = data.value("width", 128);
        request.height = data.value("height", 128);
        request.transparentBackground = data.value("transparent_background", true);
        request.animationFrames = data.value("animation_frames", 1);
        request.intendedUse = data.value("intended_use", "");
        request.documentationPath = data.value("documentation", "");
        return true;
    } catch (const std::exception& exception) {
        error = std::string("Invalid request metadata: ") + exception.what();
        return false;
    }
}

bool writeGenerationRequest(const std::filesystem::path& path, const GenerationRequest& request, std::string& error) {
    json data{
        {"id", request.id}, {"category", request.category}, {"label", request.assetLabel},
        {"prompt", request.prompt},
        {"style", request.style}, {"camera", request.camera}, {"presentation_tier", request.presentationTier},
        {"width", request.width}, {"height", request.height},
        {"transparent_background", request.transparentBackground},
        {"animation_frames", request.animationFrames}, {"intended_use", request.intendedUse},
        {"documentation", request.documentationPath}
    };
    if (!path.parent_path().empty()) std::filesystem::create_directories(path.parent_path());
    return writeText(path, data.dump(2) + "\n", error);
}

bool validateGeneratedImage(const std::filesystem::path& path, std::string& error) {
    std::ifstream image(path, std::ios::binary);
    std::array<unsigned char, 8> signature{};
    image.read(reinterpret_cast<char*>(signature.data()), signature.size());
    static constexpr std::array<unsigned char, 8> pngSignature{0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
    if (!image || signature != pngSignature) {
        error = "Generated output is not a valid PNG: " + path.string();
        return false;
    }
    return true;
}

bool runPipeline(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: runecore_asset_pipeline <configure|generate|validate> [path]\n";
        return false;
    }
    const std::string command = argv[1];
    if (command == "configure") {
        std::string key = readHiddenLine("OpenAI API key (input hidden): ");
        if (key.rfind("OPENAI_API_KEY=", 0) == 0) key.erase(0, std::strlen("OPENAI_API_KEY="));
        if (key.size() >= 2 && key.front() == '\'' && key.back() == '\'') key = key.substr(1, key.size() - 2);
        std::string error;
        if (!CredentialStore::save(key, error)) {
            std::cerr << error << '\n';
            return false;
        }
        std::cout << "OpenAI credentials saved to the macOS Keychain.\n";
        return true;
    }

    if (argc < 3) {
        std::cerr << command << " requires a file path.\n";
        return false;
    }
    const std::filesystem::path path = argv[2];
    std::string error;
    if (command == "validate") {
        if (!validateGeneratedImage(path, error)) {
            std::cerr << error << '\n';
            return false;
        }
        std::cout << "Valid PNG: " << path << '\n';
        return true;
    }
    if (command == "generate") {
        GenerationRequest request;
        if (!loadGenerationRequest(path, request, error)) {
            std::cerr << error << '\n';
            return false;
        }
        const auto requestDirectory = path.parent_path();
        const bool isBiomeOrganizedEnemy = request.category == "enemies" &&
            requestDirectory.parent_path().parent_path().parent_path().filename() == "enemies";
        const bool isStandardAsset = requestDirectory.parent_path().parent_path().filename() == request.category;
        if (request.assetLabel.empty() || requestDirectory.filename() != request.assetLabel ||
            (!isStandardAsset && !isBiomeOrganizedEnemy)) {
            error = "Each request must live in assets/generated/<category>/<entity>/<label>/request.json, "
                "or assets/generated/enemies/<biome>/<entity>/<label>/request.json, with the request folder named exactly like label.";
            std::cerr << error << '\n';
            return false;
        }
        const auto output = requestDirectory / "source.png";
        OpenAIImageProvider provider(PipelineConfig{});
        if (!provider.generate(request, CredentialStore::read(), output, error)) {
            std::cerr << error << '\n';
            return false;
        }
        std::cout << "Generated asset: " << output << '\n';
        return true;
    }
    std::cerr << "Unknown command: " << command << '\n';
    return false;
}

} // namespace asset_pipeline