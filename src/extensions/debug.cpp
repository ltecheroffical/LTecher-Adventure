#include <raylib.h>

#if PRODUCTION_BUILD == 0
#include "debug.h"

void Debugger::on_render()
{
    DrawFPS(5, 5);
}
#endif