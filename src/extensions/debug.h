#include <plugin.h>

#pragma once

class Debugger : public Plugin
{
public:
    Debugger() = default;
    ~Debugger() override = default;
    
    static bool is_visible;
    
    void on_update(float delta) override;
    void on_render() override;
};
