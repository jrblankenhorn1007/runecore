#include "core/Random.hpp"
#include <algorithm>

Random::Random(uint32_t seed) : m_rng(seed) {}

void Random::setSeed(uint32_t seed) {
    m_rng.seed(seed);
}

int Random::rangeInt(int min, int max) {
    if (min >= max) return min;
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_rng);
}

float Random::rangeFloat(float min, float max) {
    if (min >= max) return min;
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_rng);
}

float Random::gaussian(float mean, float stddev, float minVal, float maxVal) {
    std::normal_distribution<float> dist(mean, stddev);
    float val = dist(m_rng);
    return std::clamp(val, minVal, maxVal);
}

bool Random::chance(float probability) {
    if (probability <= 0.0f) return false;
    if (probability >= 1.0f) return true;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(m_rng) < probability;
}
