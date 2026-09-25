#pragma once

#include <filesystem>
#include <string>

namespace asset_pipeline {

struct GenerationRequest {
    std::string id;
    std::string category;
    std::string assetLabel;
    std::string prompt;
    std::string camera;
    std::string style{"runecore_hybrid_v1"};
    std::string presentationTier{"pixel"};
    int width{128};
    int height{128};
    bool transparentBackground{true};
    int animationFrames{1};
    std::string intendedUse;
    std::string documentationPath;
    std::string referenceImage;
};

struct PipelineConfig {
    std::filesystem::path rootDirectory{"assets"};
    std::string model{"gpt-image-1"};
    std::string apiUrl{"https://api.openai.com/v1/images/generations"};
};

class CredentialStore {
public:
    static constexpr const char* serviceName = "runecore.asset-pipeline.openai";

    static std::string read();
    static bool save(const std::string& apiKey, std::string& error);
};

class OpenAIImageProvider {
public:
    explicit OpenAIImageProvider(PipelineConfig config);

    bool generate(const GenerationRequest& request, const std::string& apiKey,
                  const std::filesystem::path& outputPath, std::string& error) const;

private:
    PipelineConfig m_config;
};

bool loadGenerationRequest(const std::filesystem::path& path,
                           GenerationRequest& request, std::string& error);
bool writeGenerationRequest(const std::filesystem::path& path,
                            const GenerationRequest& request, std::string& error);
bool validateGeneratedImage(const std::filesystem::path& path, std::string& error);
bool runPipeline(int argc, char* argv[]);

}