#pragma once

class App
{
private:
    static bool running;

public:
    inline static void close() { App::running = false; };
    inline static bool is_running()  { return App::running; };
};