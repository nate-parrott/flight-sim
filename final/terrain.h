#ifndef TERRAIN_H
#define TERRAIN_H

#include "CS123Algebra.h"

class Terrain
{
public:
    Terrain();

    virtual void renderAroundPoint(Vector3 point) = 0;
};

#endif // TERRAIN_H
