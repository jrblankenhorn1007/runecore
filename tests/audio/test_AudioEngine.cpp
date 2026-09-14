#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "audio/AudioEngine.hpp"

using Catch::Approx;

TEST_CASE("AudioEngine Procedural Sound Synthesis and Playback", "[audio][engine]") {
    AudioEngine audio;

    SECTION("Initial State and Configuration") {
        REQUIRE(audio.isInitialized() == false);
        REQUIRE(audio.getMasterVolume() == Approx(1.0f));
        REQUIRE(audio.getSFXVolume() == Approx(1.0f));

        audio.setMasterVolume(0.8f);
        REQUIRE(audio.getMasterVolume() == Approx(0.8f));
        audio.setSFXVolume(0.7f);
        REQUIRE(audio.getSFXVolume() == Approx(0.7f));
    }

    SECTION("Initialization (Headless or Audio Device)") {
        // Can initialize in headless mode or real audio stream
        bool ok = audio.init(true); // force headless/mock for deterministic test
        REQUIRE(ok == true);
        REQUIRE(audio.isInitialized() == true);
    }

    SECTION("Procedural Sound Synthesis Produces Valid PCM Samples") {
        audio.init(true);

        // Synthesize various SFX
        std::vector<float> slash = audio.synthesizeSound(SoundEffect::SwordSlash);
        REQUIRE(!slash.empty());
        // Verify samples are bounded within [-1.0, 1.0]
        for (float s : slash) {
            REQUIRE(s >= -1.0f);
            REQUIRE(s <= 1.0f);
        }

        std::vector<float> hit = audio.synthesizeSound(SoundEffect::HitImpact);
        REQUIRE(!hit.empty());

        std::vector<float> xp = audio.synthesizeSound(SoundEffect::XPPickup);
        REQUIRE(!xp.empty());

        std::vector<float> lvl = audio.synthesizeSound(SoundEffect::LevelUp);
        REQUIRE(!lvl.empty());
    }

    SECTION("Playing Sounds Enqueues Active Voices") {
        audio.init(true);

        REQUIRE(audio.getActiveVoiceCount() == 0);
        audio.playSound(SoundEffect::SwordSlash);
        REQUIRE(audio.getActiveVoiceCount() == 1);

        audio.playSound(SoundEffect::HitImpact);
        REQUIRE(audio.getActiveVoiceCount() == 2);

        // Update audio engine over time to decay active voices
        audio.update(0.5f);
        REQUIRE(audio.getActiveVoiceCount() <= 2);

        audio.stopAll();
        REQUIRE(audio.getActiveVoiceCount() == 0);
    }

    SECTION("Music Scenes Track Transitions") {
        audio.init(true);
        REQUIRE(audio.getMusicScene() == MusicScene::Exploration);
        audio.update(0.5f);
        REQUIRE(audio.getMusicSceneTime() == Approx(0.5f));
        audio.setMusicScene(MusicScene::Combat);
        REQUIRE(audio.getMusicScene() == MusicScene::Combat);
        REQUIRE(audio.getMusicSceneTime() == Approx(0.0f));
    }
}
