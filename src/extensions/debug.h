#include <plugin.h>

#pragma once

#if PRODUCTION_BUILD == 0
class Debugger : public Plugin
{
public:
    Debugger() = default;
    ~Debugger() override = default;

    void on_render() override;
};
#endif
