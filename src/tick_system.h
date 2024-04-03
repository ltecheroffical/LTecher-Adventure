#include <event.h>

#pragma once

class TickSystem
{
  public:

    static TickSystem& singleton() { 
      static TickSystem instance;
      return instance; 
    };
    
    Event<> on_tick;

  private:
    TickSystem();

    int ticks = 0;
    float tick_time = 0.0f;
};
