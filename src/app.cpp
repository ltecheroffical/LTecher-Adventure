#include "app.h"

bool App::running = true;

Color App::screen_tint = WHITE;

vec<std::shared_ptr<Plugin>> App::plugins;