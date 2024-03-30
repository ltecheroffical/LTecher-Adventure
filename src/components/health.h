#pragma once

class Health
{
public:
    explicit Health(float max);
    Health(float max, float inital);
    ~Health() = default;

    float health;
    float max_health;

    /*
    * Sets the current health
    *
    * @param health The health to set to
    */
    void set_health(float health);
    /*
    * Sets the max health
    *
    * @param health The max health to set to
    */
    void set_max(float max);

    /*
    * Damages the health by an amount
    * 
    * @param amount The amount of health to subtract
    */
    void damage(float amount);
    /*
    * Health the health by an amount
    * 
    * @param amount The amount of health to add
    */
    void heal(float amount);

    /*
    * Gets the current health
    * 
    * @param normalized Sets if the health value is between 0 and 1
    * 
    * @returns The health value
    */
    float get_health(bool normalized = false);
    /*
    * Gets the max health
    * 
    * @returns The max health value
    */
    float get_max();

    /*
    * Returns if the health value <= 0
    * 
    * @returns A bool that tracks if health is zero
    */
    bool is_dead();
};
