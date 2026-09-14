#pragma once

class Metabolism {
public:
    Metabolism();

    float getHunger() const { return m_hunger; }
    float getThirst() const { return m_thirst; }
    float getBodyTemperature() const { return m_bodyTemp; }

    void setHunger(float val);
    void setThirst(float val);

    void eat(float hungerRestore);
    void drink(float thirstRestore);

    bool isStarving() const { return m_hunger <= 0.0f; }
    bool isDehydrated() const { return m_thirst <= 0.0f; }
    bool isHypothermic() const { return m_bodyTemp < 35.0f; }
    bool isHyperthermic() const { return m_bodyTemp > 40.0f; }

    // Returns damage dealt to health from extreme conditions (starvation, hypothermia)
    float update(float dt, float ambientTemperature);

private:
    float m_hunger{100.0f};   // 0 to 100
    float m_thirst{100.0f};   // 0 to 100
    float m_bodyTemp{37.0f};  // Degrees Celsius

    float m_hungerDrainRate{0.05f}; // per second (approx ~33 minutes to deplete)
    float m_thirstDrainRate{0.08f}; // per second (approx ~20 minutes to deplete)
};
