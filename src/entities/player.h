#include <stdexcept>
#include <gameobject.h>

#pragma once

class Player : public GameObject
{
public:
    inline float get_health() { return health; };
    inline int   get_max_health() { return max_health; };

    inline void  set_health(int health) { this->health = health; };
    inline void  set_max_health(int max_health) { this->max_health = max_health; };

private:
    float health;
    int   max_health;

};
