#ifndef SPRITE_H
#define SPRITE_H

#include "final.h"

class Sprite
{
public:
    Sprite();
    virtual void update(double dt);
    Vector3 position, velocity, heading, up;
    virtual void draw();
};

#endif // SPRITE_H
