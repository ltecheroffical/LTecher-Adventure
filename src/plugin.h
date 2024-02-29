#pragma once

class Plugin
{
public:
    Plugin() = default;
    virtual ~Plugin() = default;

    /*
    * Called when the game starts
    * NOTE: This is a virutal function  
    */
    virtual void on_game_start() { /* Override to listen to event */ };

    /*
    * Called every frame while the game is running
    * NOTE: This is a virutal function  
    *    
    * @param delta The time since the last frame was rendered to now
    */
    virtual void on_update(float delta) { /* Override to listen to event */ };
    /*
    * Called when the objects are rendering
    */
    virtual void on_render() { /* Override to listen to event */ };

    /*
    * Called when the game exits
    * NOTE: This is a virutal function  
    */
    virtual void on_game_exits() { /* Override to listen to event */ };
};