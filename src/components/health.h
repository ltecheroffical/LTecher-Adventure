#include <components/component.h>

#include <event.h>

#pragma once

class Health : public Component
{
public:
  Health(float max);
  ~Health() = default;

  /*
   * Emitted when the current health has changed
   */
  Event<float> on_health_changed;
  
  /*
   * Emitted when the health is healed
   */
  Event<float> on_health_healed;
  /*
   * Emitted when the health is damaged
   */
  Event<float> on_health_damaged;

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

  /*
   * Returns a pointer to the health value
   *
   * @returns A pointer to the health
   */
  inline float *cur_health_ptr() { return &this->health; };
  /*
   * Returns a pointer to the max health value
   *
   * @returns A pointer to the max health
   */
  inline float *max_health_ptr() { return &this->max_health; };

private:
  float health;
  float max_health;
};
