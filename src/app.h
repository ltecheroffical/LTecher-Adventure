#pragma once

class App
{
private:
    static bool running;

public:
    static const int DEFAULT_SCREEN_WIDTH = 800;
    static const int DEFAULT_SCREEN_HEIGHT = 450;

    inline static void close() { App::running = false; };
    inline static bool is_running()  { return App::running; };
};