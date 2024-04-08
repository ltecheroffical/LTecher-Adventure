#include <gameobject.h>
#include <scene.h>

#include "app.h"

App::App()
{
  this->running = true;
  this->screen_tint = Color{ 0, 0, 0, 0 };
}
