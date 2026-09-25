#include <catch2/catch_test_macros.hpp>

#include "asset_pipeline/AssetPipeline.hpp"

#include <filesystem>
#include <fstream>

namespace {

const std::filesystem::path testDirectory = "asset_pipeline_test_data";

}

TEST_CASE("Asset pipeline request metadata round trips", "[asset_pipeline]") {
    const auto path = testDirectory / "slime.json";
    asset_pipeline::GenerationRequest expected;
    expected.id = "enemy_slime_01";
    expected.category = "enemy";
    expected.assetLabel = "sprite";
    expected.prompt = "A hostile cave slime with a glowing rune core";
    expected.presentationTier = "pixel";
    expected.width = 128;
    expected.height = 128;
    expected.animationFrames = 4;
    expected.documentationPath = "docs/enemies/subterranean-caverns/rune-core-cave-slime.md";
    expected.referenceImage = "assets/generated/enemies/subterranean-caverns/slime_01/sprite/source.png";

    std::string error;
    REQUIRE(asset_pipeline::writeGenerationRequest(path, expected, error));

    asset_pipeline::GenerationRequest actual;
    REQUIRE(asset_pipeline::loadGenerationRequest(path, actual, error));
    REQUIRE(actual.id == expected.id);
    REQUIRE(actual.assetLabel == expected.assetLabel);
    REQUIRE(actual.prompt == expected.prompt);
    REQUIRE(actual.width == expected.width);
    REQUIRE(actual.animationFrames == expected.animationFrames);
    REQUIRE(actual.documentationPath == expected.documentationPath);
    REQUIRE(actual.referenceImage == expected.referenceImage);

    std::filesystem::remove_all(testDirectory);
}

TEST_CASE("Asset pipeline accepts PNG signatures and rejects other files", "[asset_pipeline]") {
    const auto pngPath = testDirectory / "valid.png";
    const auto textPath = testDirectory / "invalid.png";
    std::filesystem::create_directories(testDirectory);
    {
        std::ofstream png(pngPath, std::ios::binary);
        const unsigned char signature[]{0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
        png.write(reinterpret_cast<const char*>(signature), sizeof(signature));
    }
    {
        std::ofstream text(textPath);
        text << "not an image";
    }

    std::string error;
    REQUIRE(asset_pipeline::validateGeneratedImage(pngPath, error));
    REQUIRE_FALSE(asset_pipeline::validateGeneratedImage(textPath, error));
    std::filesystem::remove_all(testDirectory);
}