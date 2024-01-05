#include <raylib.h>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/*
* The base class for all objects in a `Scene` class
* 
* @name GameObject
*/
class GameObject
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    /*
    * The position at where the gameobject is rendered
    */
    Vector2 position = { 0, 0 };
    /*
    * The rotation of the gameobject
    */
    float rotation = 0;
    /*
    * The scale as the size multiplier
    */
    float scale = 1;
    /*
    * If the rendering of the gameobject is skipped
    */
    bool visible = true;

    /*
    * Called once the object enters the scene
    */
    virtual void on_start() { /* Override to listen to event */ };

    /*
    * Called every frame while the game is running
    * NOTE: This is a virutal function  
    *    
    * @param delta The time since the last frame was rendered to now
    */
    virtual void on_update(float delta) { /* Override to listen to event */ };
    /*
    * Called every frame when the gameobject should render
    */
    virtual void on_render() { /* Override to listen to event */ };

    /*
    * Called when the object is about to exit the scene
    */
    virtual void on_exit() { /* Override to listen to event */ };
};
#endif