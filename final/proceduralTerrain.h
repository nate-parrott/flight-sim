#ifndef TERRAIN_H
#define TERRAIN_H

#include "final.h"

class ProceduralTerrain
{
public:
    ProceduralTerrain();

    float heightAtPos(Vector2 pos);
    Vector3 normalAtPos(Vector2 pos);
    void renderRectAtResolution(Vector2 start, Vector2 end, int intermediateSamples);
    void renderAroundPosition(Vector2 pos);
};

#endif // TERRAIN_H
