#pragma once

enum class WeatherType {
    Clear,
    Rain,
    Blizzard,
    FalloutStorm
};

class DayNightCycle {
public:
    explicit DayNightCycle(float fullCycleSeconds = 1440.0f);

    void update(float dt);
    void setTimeOfDay(float seconds);
    float getTimeOfDay() const { return m_timeOfDay; }

    float getAmbientDarkness() const; // 0.0 (noon bright) to 0.85 (midnight dark)
    bool isNight() const;

    WeatherType getWeather() const { return m_weather; }
    void setWeather(WeatherType weather) { m_weather = weather; }

private:
    float m_fullCycle{1440.0f};
    float m_timeOfDay{720.0f}; // starts at noon (720s)
    WeatherType m_weather{WeatherType::Clear};
};
