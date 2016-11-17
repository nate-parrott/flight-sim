#ifndef BIOMES_H
#define BIOMES_H

#include <QGLWidget>

struct TerrainTexture {
    GLubyte sand, grass, rock, snow;
};

struct Land {
    TerrainTexture texture;
    float height;
    float cloudProbability;
    Land();
};

class Biome {
public:
    Biome();
    float weight; // affects the size of the biome
    virtual Land generate(double x, double y, float seed) = 0;
};

class Desert : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
};

class Tundra : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
};

class Grassland : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
};

class Mountains : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
};

class Ocean : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
};

class Humid : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
};

class Swampland : public Biome {
public:
    virtual Land generate(double x, double y, float seed);
    Swampland();
};

class Biomes
{
public:
    Biomes();
    Biome** biomes;
    int numBiomes;
    void getBiomeCoefficients(float* coefficients, double x, double y, float seed);
    Land landAtPos(double x, double y);
};

#endif // BIOMES_H
