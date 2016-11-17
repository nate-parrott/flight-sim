#include "biomes.h"
#include "simplexnoise.h"
#include <cstdlib>
#include "final.h"
#include <QDebug>

const float TerrainSeed = 718;

const float BiomeDistance = 8000;

#define noise(period) (raw_noise_2d(x/period + (seed+=13), y/period + (seed+=13)))

#define roughness(period) (noise(period)*0.5 + 0.5)

Biome::Biome() {
    weight = 1;
}

Land::Land() {
    height = 0.0;
    cloudProbability = 0.5;
    texture.sand = texture.grass = texture.rock = texture.snow = 0;
}

Land Desert::generate(double x, double y, float seed) {
    Land l;
    l.texture.sand = 255;
    l.height += noise(900)*40 + 37;
    l.height += (noise(200)*20 + 10) * roughness(500);

    float shoots = roughness(900)*roughness(900);
    shoots = npmax(shoots-0.7, 0);
    l.height += (noise(60)*70 + 35)*shoots;

    l.cloudProbability = 0.1;
    return l;
}

Land Grassland::generate(double x, double y, float seed) {
    Land l;
    l.texture.grass = 100;
    l.height += noise(700)*40 + 20;
    float rockiness = roughness(200);
    rockiness = npmax(0, rockiness-0.7);
    l.height += (noise(20) * 20)*rockiness;
    l.texture.rock = rockiness * 200;
    return l;
}

Land Mountains::generate(double x, double y, float seed) {
    Land l;
    // slopes:
    l.height += noise(1200) * 20 + 30; // [10 - 50]
    // peaks:
    l.height += (noise(400) * 150 + 150)*roughness(900); // [0 - 300]
    // crags:
    l.height += noise(120) * 20 * roughness(270); // [-20 - 20]
    // small crags:
    l.height += noise(20) * 10 * roughness(120); // [-10 - 10]
    // texture:
    float temp = l.height + (noise(120)*50 + 50);
    float snow = temp > 200? npmin(1, (temp-200)/100 * 1.4) : 0;
    l.texture.rock = 100*(1-snow);
    l.texture.snow = 100*snow;
    l.texture.sand += pow(noise(100), 2)*30 + 30;
    return l;
}

Land Tundra::generate(double x, double y, float seed) {
    Land l;
    l.texture.snow = 100;
    l.texture.rock = roughness(100);
    l.height += noise(600)*50 + 50;
    l.height += noise(40)*10 * roughness(200);
    l.cloudProbability = 0.2;
    return l;
}

Land Humid::generate(double x, double y, float seed) {
    Land l;
    l.texture.grass = 100;
    l.texture.sand = 50;

    l.height += noise(1200) * 20 + 7;
    l.height += (noise(200) * 100 + 90)*roughness(500);
    l.height += (noise(15)*7 + 7) * roughness(60);

    l.texture.rock = noise(150)*100 + 100;

    l.cloudProbability = 0.9;
    return l;
}

Land Swampland::generate(double x, double y, float seed) {
    Land l;
    l.texture.grass = 100;
    l.texture.rock = noise(200) * 50 + 50;
    l.texture.sand = noise(200) * 50 + 50;

    l.height = noise(300)*10 + 2;
    l.cloudProbability = 1.0;

    return l;
}
Swampland::Swampland() {
    weight = 0.7;
}

Land Ocean::generate(double x, double y, float seed) {
    Land l;
    l.texture.sand = 255;
    l.height += noise(500) * 40 - 50;
    l.height += noise(16) * roughness(40) * 10;
    return l;
}

Biomes::Biomes() {
    numBiomes = 7;
    biomes = new Biome*[numBiomes];
    biomes[0] = new Humid();
    biomes[1] = new Grassland();
    biomes[2] = new Mountains();
    biomes[3] = new Desert();
    biomes[4] = new Ocean();
    biomes[5] = new Swampland();
    biomes[6] = new Tundra();
}
void ceilCoefficients(float* vals, int count) {
    int highest = 0;
    for (int i=1; i<count; i++) if (vals[i] > vals[highest]) highest = i;
    float cutoff = vals[highest]*0.8;
    for (int i=0; i<count; i++) vals[i] = npmax(0, vals[i]-cutoff);
    // normalize:
    float total = 0;
    for (int i=0; i<count; i++) total += vals[i];
    for (int i=0; i<count; i++) vals[i] /= total;
}
void Biomes::getBiomeCoefficients(float* coefficients, double x, double y, float seed) {
    for (int i=0; i<numBiomes; i++) {
        float score = raw_noise_3d(x/BiomeDistance + seed, y/BiomeDistance + seed, i * 10 + seed)*0.5 + 0.5;
        float weight = biomes[i]->weight;
        coefficients[i] = score * weight;
    }
    ceilCoefficients(coefficients, numBiomes);
}

Land Biomes::landAtPos(double x, double y) {
    //Land l = (new Tundra())->generate(x, y, 0);
    //return l;

    double seed = TerrainSeed;
    float* ks = new float[numBiomes];
    getBiomeCoefficients(ks, x, y, seed);
    Land cumulative;
    cumulative.cloudProbability = 0;
    for (int i=0; i<numBiomes; i++) {
        seed += 17;
        if (ks[i]==0) continue;
        Land l = biomes[i]->generate(x, y, seed);
        cumulative.height += l.height * ks[i];
        cumulative.cloudProbability += l.cloudProbability * ks[i];
        cumulative.texture.grass += l.texture.grass * ks[i];
        cumulative.texture.sand += l.texture.sand * ks[i];
        cumulative.texture.rock += l.texture.rock * ks[i];
        cumulative.texture.snow += l.texture.snow * ks[i];
    }
    //cumulative.height = 1;
    return cumulative;
}
