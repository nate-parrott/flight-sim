#ifndef IMAGETERRAIN_H
#define IMAGETERRAIN_H

#include "terrain.h"
#include <vector>
#include <map>
#include <QImage>
#include "CS123Algebra.h"
#include <QDir>
#include <QGLShaderProgram>
#include "plane.h"
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include "biomes.h"

const int levelsOfDetail = 6;
const float tileSize = 300;

struct TileKey {
    double x, y;
    int lod;
    bool operator<(const TileKey& other) const {
        if (x < other.x) return true;
        else if (x > other.x) return false;
        if (y < other.y) return true;
        else if (y > other.y) return false;
        return lod < other.lod;
    }
};

class PerlinTerrain;

struct HeightMap {
    enum {
        NotYetGenerated,
        Generated,
        BoundToVBO
    } state;

    TileKey key;

    void generate(PerlinTerrain* terrain);

    unsigned int numIndices;

    GLuint vboID, eboID;
    GLvoid *vboData, *eboData;
    GLuint vboSize, eboSize;

    void bind(); // binds to VBO
    ~HeightMap();
};

class TerrainGenerationWorker;

class PerlinTerrain : public Terrain
{
    friend class TerrainGenerationWorker;
    friend class HeightMap;

    void renderWater(Vector3 point);
    QGLShaderProgram* waterShader;

    float lodRadii[levelsOfDetail] = {-1, -1, -1, 3000, 4000, 8000};

    QGLShaderProgram* terrainShader;
    GLuint sandID, grassID, rockID, snowID;

    static inline float heightFunction(double x, double y);
    static inline Land terrainGenerationFunction(double x, double y);

    int tick;
    TerrainGenerationWorker* worker;
    QWaitCondition* workerWaitCondition;
    QMutex* terrainMutex;
    Vector3 userPosition;
    std::map<TileKey, HeightMap*> heightmapCache;
public:
    PerlinTerrain();
    void renderAroundPoint(Vector3 point);
    int waterLevel;
    Biomes biomes;
    Plane* plane;
};

class TerrainGenerationWorker : public QThread {
    //Q_OBJECT
public:
    void run();
    void deleteOldCachedTiles(float x, float y);

    PerlinTerrain* terrain;
};

#endif // IMAGETERRAIN_H
