#include <app.h>

#include "tick_system.h"

TickSystem::TickSystem()
{
  App::singleton().on_update.subscribe([this](float delta) {
    if (this->tick_time >= 0.25f)
    {
      this->ticks++;
      this->on_tick.emit();

      this->tick_time = 0.0f;
    }
    else
    {
      this->tick_time += delta;
    }
  });
}
