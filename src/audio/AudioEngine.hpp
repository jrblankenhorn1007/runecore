#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <SDL3/SDL.h>

enum class SoundEffect {
    SwordSlash,
    HitImpact,
    CritHit,
    Gunshot,
    LaserShoot,
    Jump,
    DoubleJump,
    XPPickup,
    LevelUp,
    EnemyDeath,
    MiningClink,
    UI_Click,
    UI_Equip
};

enum class MusicScene {
    Exploration,
    Mining,
    Environment,
    Combat,
    Boss,
    Silence
};

struct ActiveVoice {
    SoundEffect effect{SoundEffect::UI_Click};
    std::vector<float> samples;
    size_t cursor{0};
    float volume{1.0f};
    bool active{false};
};

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    bool init(bool forceHeadless = false);
    void shutdown();

    void playSound(SoundEffect effect, float volume = 1.0f);
    void update(float dt);
    void stopAll();
    void setMusicScene(MusicScene scene);
    MusicScene getMusicScene() const { return m_musicScene; }
    float getMusicSceneTime() const { return m_musicSceneTime; }

    void setMasterVolume(float vol);
    void setSFXVolume(float vol);
    void setMusicVolume(float vol);
    void setAmbienceVolume(float vol);
    float getMasterVolume() const { return m_masterVolume; }
    float getSFXVolume() const { return m_sfxVolume; }
    float getMusicVolume() const { return m_musicVolume; }
    float getAmbienceVolume() const { return m_ambienceVolume; }

    bool isInitialized() const { return m_initialized; }
    size_t getActiveVoiceCount() const;

    std::vector<float> synthesizeSound(SoundEffect effect) const;

private:
    bool m_initialized{false};
    bool m_headless{false};
    float m_masterVolume{1.0f};
    float m_sfxVolume{1.0f};
    float m_musicVolume{1.0f};
    float m_ambienceVolume{1.0f};
    MusicScene m_musicScene{MusicScene::Exploration};
    float m_musicSceneTime{0.0f};

    SDL_AudioStream* m_audioStream{nullptr};
    std::vector<ActiveVoice> m_voices;
};
