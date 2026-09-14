#pragma once
#include <random>
#include <cstdint>

class Random {
public:
    explicit Random(uint32_t seed = 1337);

    void setSeed(uint32_t seed);
    int rangeInt(int min, int max);
    float rangeFloat(float min, float max);
    float gaussian(float mean, float stddev, float minVal, float maxVal);
    bool chance(float probability);

private:
    std::mt19937 m_rng;
};
