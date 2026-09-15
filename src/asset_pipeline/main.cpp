#include "asset_pipeline/AssetPipeline.hpp"

int main(int argc, char* argv[]) {
    return asset_pipeline::runPipeline(argc, argv) ? 0 : 1;
}