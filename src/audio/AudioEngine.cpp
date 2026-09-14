#include "audio/AudioEngine.hpp"
#include <cmath>
#include <algorithm>
#include <random>

constexpr int SAMPLE_RATE = 44100;

AudioEngine::AudioEngine() = default;

AudioEngine::~AudioEngine() {
    shutdown();
}

bool AudioEngine::init(bool forceHeadless) {
    if (m_initialized) return true;

    m_headless = forceHeadless;

    if (!m_headless) {
        if (!SDL_Init(SDL_INIT_AUDIO)) {
            m_headless = true;
        } else {
            SDL_AudioSpec spec;
            spec.format = SDL_AUDIO_F32;
            spec.channels = 1;
            spec.freq = SAMPLE_RATE;

            m_audioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
            if (m_audioStream) {
                SDL_ResumeAudioStreamDevice(m_audioStream);
            } else {
                m_headless = true;
            }
        }
    }

    m_voices.resize(16); // 16 voice polyphony
    m_initialized = true;
    return true;
}

void AudioEngine::shutdown() {
    if (m_audioStream) {
        SDL_DestroyAudioStream(m_audioStream);
        m_audioStream = nullptr;
    }
    m_voices.clear();
    if (!m_headless) {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
    m_initialized = false;
}

void AudioEngine::setMasterVolume(float vol) {
    m_masterVolume = std::clamp(vol, 0.0f, 1.0f);
}

void AudioEngine::setSFXVolume(float vol) {
    m_sfxVolume = std::clamp(vol, 0.0f, 1.0f);
}

void AudioEngine::setMusicVolume(float vol) {
    m_musicVolume = std::clamp(vol, 0.0f, 1.0f);
}

void AudioEngine::setAmbienceVolume(float vol) {
    m_ambienceVolume = std::clamp(vol, 0.0f, 1.0f);
}

std::vector<float> AudioEngine::synthesizeSound(SoundEffect effect) const {
    std::vector<float> buf;

    auto makeEnvelope = [](float t, float dur, float attack, float decay) {
        if (t < attack) return t / std::max(0.001f, attack);
        float rel = (dur - t) / std::max(0.001f, dur - attack);
        return std::clamp(rel * rel, 0.0f, 1.0f);
    };

    switch (effect) {
        case SoundEffect::SwordSlash: {
            float dur = 0.15f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float freq = 800.0f - (t / dur) * 600.0f;
                float env = makeEnvelope(t, dur, 0.01f, 0.14f);
                float wave = std::sin(2.0f * 3.14159f * freq * t);
                buf[i] = std::clamp(wave * env * 0.6f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::HitImpact: {
            float dur = 0.12f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float env = std::exp(-25.0f * t);
                float wave = std::sin(2.0f * 3.14159f * 110.0f * t);
                buf[i] = std::clamp(wave * env * 0.8f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::CritHit: {
            float dur = 0.25f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float env = std::exp(-15.0f * t);
                float wave = 0.7f * std::sin(2.0f * 3.14159f * 1200.0f * t) +
                             0.3f * std::sin(2.0f * 3.14159f * 2400.0f * t);
                buf[i] = std::clamp(wave * env * 0.7f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::Gunshot: {
            float dur = 0.15f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            std::mt19937 rng(42);
            std::uniform_real_distribution<float> noise(-1.0f, 1.0f);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float env = std::exp(-30.0f * t);
                buf[i] = std::clamp(noise(rng) * env * 0.9f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::LaserShoot: {
            float dur = 0.12f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float freq = 1600.0f - (t / dur) * 1200.0f;
                float env = std::exp(-18.0f * t);
                float wave = std::sin(2.0f * 3.14159f * freq * t);
                buf[i] = std::clamp(wave * env * 0.6f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::Jump: {
            float dur = 0.12f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float freq = 220.0f + (t / dur) * 220.0f; // 220 -> 440 Hz
                float env = makeEnvelope(t, dur, 0.01f, 0.11f);
                float wave = std::sin(2.0f * 3.14159f * freq * t);
                buf[i] = std::clamp(wave * env * 0.5f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::DoubleJump: {
            float dur = 0.14f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float freq = 350.0f + (t / dur) * 350.0f; // 350 -> 700 Hz
                float env = makeEnvelope(t, dur, 0.01f, 0.13f);
                float wave = std::sin(2.0f * 3.14159f * freq * t);
                buf[i] = std::clamp(wave * env * 0.5f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::XPPickup: {
            float dur = 0.18f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float freq = (t < 0.09f) ? 523.25f : 659.25f; // C5 -> E5
                float env = std::exp(-10.0f * t);
                float wave = std::sin(2.0f * 3.14159f * freq * t);
                buf[i] = std::clamp(wave * env * 0.5f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::LevelUp: {
            float dur = 0.45f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            float notes[4] = {523.25f, 659.25f, 783.99f, 1046.50f}; // C5, E5, G5, C6
            float noteDur = dur / 4.0f;
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                int noteIdx = std::clamp(static_cast<int>(t / noteDur), 0, 3);
                float noteT = t - (noteIdx * noteDur);
                float env = std::exp(-8.0f * noteT);
                float wave = std::sin(2.0f * 3.14159f * notes[noteIdx] * t);
                buf[i] = std::clamp(wave * env * 0.7f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::EnemyDeath: {
            float dur = 0.28f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float envelope = std::max(0.0f, 1.0f - t * 4.0f);
                buf[i] = std::sin(2.0f * 3.14159f * (120.0f - 70.0f * t) * t) * envelope * 0.6f;
            }
            break;
        }
        case SoundEffect::MiningClink: {
            float dur = 0.15f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float env = std::exp(-28.0f * t);
                float wave = 0.6f * std::sin(2.0f * 3.14159f * 1500.0f * t) +
                             0.4f * std::sin(2.0f * 3.14159f * 3000.0f * t);
                buf[i] = std::clamp(wave * env * 0.6f, -1.0f, 1.0f);
            }
            break;
        }
        case SoundEffect::UI_Click:
        case SoundEffect::UI_Equip:
        default: {
            float dur = 0.05f;
            int total = static_cast<int>(dur * SAMPLE_RATE);
            buf.resize(total);
            for (int i = 0; i < total; ++i) {
                float t = static_cast<float>(i) / SAMPLE_RATE;
                float env = std::exp(-40.0f * t);
                float wave = std::sin(2.0f * 3.14159f * 800.0f * t);
                buf[i] = std::clamp(wave * env * 0.4f, -1.0f, 1.0f);
            }
            break;
        }
    }

    return buf;
}

void AudioEngine::playSound(SoundEffect effect, float volume) {
    if (!m_initialized) return;

    // Find free voice slot or oldest
    ActiveVoice* voice = nullptr;
    for (auto& v : m_voices) {
        if (!v.active) {
            voice = &v;
            break;
        }
    }
    if (!voice && !m_voices.empty()) {
        voice = &m_voices[0];
    }

    if (voice) {
        voice->effect = effect;
        voice->samples = synthesizeSound(effect);
        voice->cursor = 0;
        voice->volume = std::clamp(volume, 0.0f, 1.0f) * m_masterVolume * m_sfxVolume;
        voice->active = true;

        if (m_audioStream && !m_headless) {
            // Apply volume scaling and push to SDL3 stream
            std::vector<float> scaledSamples = voice->samples;
            for (float& s : scaledSamples) {
                s *= voice->volume;
            }
            SDL_PutAudioStreamData(m_audioStream, scaledSamples.data(), static_cast<int>(scaledSamples.size() * sizeof(float)));
        }
    }
}

void AudioEngine::update(float dt) {
    if (!m_initialized) return;

    m_musicSceneTime += std::max(0.0f, dt);
    size_t samplesAdvanced = static_cast<size_t>(dt * SAMPLE_RATE);
    for (auto& v : m_voices) {
        if (!v.active) continue;
        v.cursor += samplesAdvanced;
        if (v.cursor >= v.samples.size()) {
            v.active = false;
        }
    }
}

void AudioEngine::stopAll() {
    for (auto& v : m_voices) {
        v.active = false;
        v.cursor = 0;
    }

        if (m_audioStream && !m_headless) {
            SDL_ClearAudioStream(m_audioStream);
        }
    }

    void AudioEngine::setMusicScene(MusicScene scene) {
        if (m_musicScene == scene) return;
        m_musicScene = scene;
        m_musicSceneTime = 0.0f;
    }

size_t AudioEngine::getActiveVoiceCount() const {
    size_t count = 0;
    for (const auto& v : m_voices) {
        if (v.active) count++;
    }
    return count;
}
