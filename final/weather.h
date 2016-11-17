#ifndef WEATHER_H
#define WEATHER_H

#include <vector>
#include <map>
#include "final.h"

const int particlesPerCloud = 15;
const float cloudSize = 500;

const float cloudTileSize = 500;

struct CloudParticle {
    float x, y, z, size, opacity;
};

struct CloudTileKey {
    double x, y;
    bool operator<(const CloudTileKey& other) const {
        if (x < other.x) return true;
        else if (x > other.x) return false;
        return y < other.y;
    }
};

struct Cloud {
    Vector3 center;
    CloudParticle particles[particlesPerCloud]; // in the space [-0.5, 0.5]
    void randomize();
};
#define NULL_CLOUD ((Cloud*)1)

class Weather
{
    std::map<CloudTileKey, Cloud*> cloudsForTiles;
    void updateCloudCache(Vector3 point, float viewDistance);
    void deleteOldCachedTiles(double x, double y, float distance);
public:
    Weather();
    void renderWeather(Vector3 point, Vector3 viewerPos, float viewDistance);
};

#endif // WEATHER_H
