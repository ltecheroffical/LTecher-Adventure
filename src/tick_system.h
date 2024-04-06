#include <event.h>

#pragma once

class TickSystem
{
public:
  static TickSystem& singleton() { 
    static TickSystem instance;
    return instance; 
  };
  
  /*
   * Gets the number of ticks
   */
  int get_ticks() { return this->ticks; };
  /*
   * Gets a pointer to the number of ticks
   */
  int *ticks_ptr() { return &this->ticks; };

  /*
   * Emitted every tick
   */
  Event<> on_tick;

private:
  TickSystem();

  int ticks = 0;
  float tick_time = 0.0f;
};
