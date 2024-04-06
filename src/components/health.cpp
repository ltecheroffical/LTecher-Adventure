#include "health.h"

Health::Health(float max) : max_health(max), health(max)
{
  
}

Health::Health(float max, float inital) : max_health(max), health(inital)
{
  
}

void Health::set_health(float health)
{
  this->health = health;
  this->on_health_changed.emit(this->health);
}

void Health::set_max(float max)
{
  this->max_health = max;
}

void Health::damage(float amount)
{
  this->health -= amount;
  this->on_health_damaged.emit(this->health);
  this->on_health_changed.emit(this->health);
}

void Health::heal(float amount)
{
  this->health += amount;
  this->on_health_healed.emit(this->health);
  this->on_health_changed.emit(this->health);
}

float Health::get_health(bool normalized)
{
  if (normalized)
  {
    return this->health / this->max_health;
  }

  return this->health; 
}

float Health::get_max()
{
  return this->max_health; 
}

bool Health::is_dead()
{
  return this->health <= 0;
}
