#include "perlinterrain.h"
#include <qdir.h>
#include <gl.h>
#include "final.h"
#include "view.h"
#include "watershader.h"
#include "simplexnoise.h"

GLuint TerrainTextureAttributeIndex = -1;

HeightMap::~HeightMap() {
    if (state == BoundToVBO) {
        glDeleteBuffers(1, &vboID);
        glDeleteBuffers(1, &eboID);
    } else if (state == Generated) {
        delete vboData;
        delete eboData;
    }
}

PerlinTerrain::PerlinTerrain() {
    waterLevel = 0;

    tick = 0;
    worker = new TerrainGenerationWorker();
    worker->terrain = this;
    terrainMutex = new QMutex();
    workerWaitCondition = new QWaitCondition();
    worker->start();
}

#define VERTEX_SIZE (sizeof(float)*3 + sizeof(float)*3 + sizeof(TerrainTexture))

void PerlinTerrain::renderAroundPoint(Vector3 point) {
    QGLFramebufferObject* shadow = NULL;
    float shadowScale = 20;
    plane->renderSilhouette(shadowScale, &shadow);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, shadow->texture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (!terrainShader) {
        terrainShader = new QGLShaderProgram(mainView()->context());
        terrainShader->addShaderFromSourceFile(QGLShader::Vertex, pathForResource("shaders/terrain.vert"));
        terrainShader->addShaderFromSourceFile(QGLShader::Fragment, pathForResource("shaders/terrain.frag"));
        if (!terrainShader->link()) {
            qDebug() << terrainShader->log();
        }
        sandID = loadAndBindTexture(pathForResource("textures/sand.jpg"));
        grassID = loadAndBindTexture(pathForResource("textures/grass.jpg"));
        rockID = loadAndBindTexture(pathForResource("textures/rock.jpg"));
        snowID = loadAndBindTexture(pathForResource("textures/snow.jpg"));
        TerrainTextureAttributeIndex = terrainShader->attributeLocation("terrainTextureAttribute");
    }
    terrainShader->bind();
    userPosition = point;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sandID);
    terrainShader->setUniformValue("sand", 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, grassID);
    terrainShader->setUniformValue("grass", 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, rockID);
    terrainShader->setUniformValue("rock", 2);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, snowID);
    terrainShader->setUniformValue("snow", 3);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, shadow->texture());
    terrainShader->setUniformValue("shadow", 4);
    terrainShader->setUniformValue("shadowPos", QVector2D(plane->position.x, plane->position.z));
    terrainShader->setUniformValue("shadowSize", QVector2D(shadow->width()/shadowScale, shadow->height()/shadowScale));

    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableVertexAttribArray(TerrainTextureAttributeIndex);

    terrainMutex->lock();
    for (auto it=heightmapCache.begin(); it!=heightmapCache.end(); it++) {
        HeightMap* heightMap = it->second;

        if (heightMap->state == HeightMap::Generated) {
            heightMap->bind();
        }
        if (heightMap->state == HeightMap::BoundToVBO) {
            glBindBuffer(GL_ARRAY_BUFFER, heightMap->vboID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, heightMap->eboID);

            glVertexPointer(3, GL_FLOAT, VERTEX_SIZE, (GLvoid*)0);
            glNormalPointer(GL_FLOAT, VERTEX_SIZE, (GLvoid*)(sizeof(float)*3));
            glVertexAttribPointer(TerrainTextureAttributeIndex, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (GLvoid*)(sizeof(float)*6));
            glDrawElements(GL_TRIANGLE_STRIP, heightMap->numIndices, GL_UNSIGNED_INT, 0);
        }
    }
    terrainMutex->unlock();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableVertexAttribArray(TerrainTextureAttributeIndex);
    glPopMatrix();


    terrainShader->release();
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete shadow;
    glActiveTexture(GL_TEXTURE0);

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderWater(point);
    glDisable(GL_BLEND);
    glPopMatrix();

    if ((tick++)%30) {
        workerWaitCondition->wakeAll();
    }
}
inline float PerlinTerrain::heightFunction(double x, double y) {
    float scales[] = {1000, 400, 200, 40};
    int nscales = sizeof(scales) / sizeof(scales[0]);
    float totalWeights = 0.0;
    float weight = 1.0;
    float height = 0;
    float offset = 0;
    float bumpiness = 1;
    for (int i=0; i<nscales; i++) {
        height += raw_noise_2d(x/scales[i]+offset, y/scales[i]+offset) * bumpiness * weight;
        totalWeights += weight;
        offset += 17;
        bumpiness = raw_noise_2d(x/scales[i]+offset, y/scales[i]+offset);
        bumpiness = npmax(0, bumpiness);
        offset += 13;
        weight /= 2;
    }
    height /= totalWeights;

    float normal = height * 1.5;
    float desert = height*height*1.6;
    float mix = raw_noise_2d(x/3000, y/3000)/2 + 0.5;

    return normal*mix + desert * (1-mix);
}
inline Land PerlinTerrain::terrainGenerationFunction(double x, double y) {
    float height = heightFunction(x, y);
    Land l;
    l.height = height;
    l.texture.sand = l.texture.grass = l.texture.rock = l.texture.snow = 0;
    if (height < 0.1) {
        l.texture.sand = 250;
    } else if (height < 0.5) {
        l.texture.grass = 250;
    } else if (height < 0.7) {
        l.texture.rock = 250;
    } else {
        l.texture.snow = 250;
    }
    return l;
}

void PerlinTerrain::renderWater(Vector3 point) {
    if (!waterShader) {
        waterShader = WaterShader::makeWaterShader();
    }

    WaterShader::bind(waterShader);

    glBegin(GL_QUADS);
    float d = 6000;
    glNormal3f(0, 1, 0);
    glVertex3f(point.x-d, waterLevel, point.z-d);
    glNormal3f(0, 1, 0);
    glVertex3f(point.x-d, waterLevel, point.z+d);
    glNormal3f(0, 1, 0);
    glVertex3f(point.x+d, waterLevel, point.z+d);
    glNormal3f(0, 1, 0);
    glVertex3f(point.x+d, waterLevel, point.z-d);
    glEnd();
    waterShader->release();

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_1D, 0);
}

void TerrainGenerationWorker::run() {
    forever {
        terrain->terrainMutex->lock();
        terrain->workerWaitCondition->wait(terrain->terrainMutex);

        Vector3 userPos = terrain->userPosition;

        std::vector<HeightMap*> newMaps;
        int tilesAround = ceil(terrain->lodRadii[levelsOfDetail-1]/tileSize);
        Vector2 originTilePos = Vector2(round(userPos.x/tileSize)*tileSize, round(userPos.z/tileSize)*tileSize);
        for (int tileX=-tilesAround; tileX<tilesAround; tileX++) {
            for (int tileY=-tilesAround; tileY<tilesAround; tileY++) {
                Vector2 tileOrigin = originTilePos + Vector2(tileSize*tileX, tileSize*tileY);
                Vector2 tileEnd = tileOrigin + Vector2(tileSize, tileSize);
                float dist = sqrt(pow(tileEnd.x*0.5 + tileOrigin.x*0.5 - originTilePos.x, 2) + pow(tileEnd.y*0.5 + tileOrigin.y*0.5 - originTilePos.y, 2));
                int lod = levelsOfDetail-1;
                if (dist > terrain->lodRadii[lod]) continue;
                while (lod > 0 && dist < terrain->lodRadii[lod-1]) lod--;

                TileKey key;
                key.lod = lod;
                key.x = tileOrigin.x;
                key.y = tileOrigin.y;

                if (terrain->heightmapCache.find(key) == terrain->heightmapCache.end()) {
                    HeightMap* hm = new HeightMap();
                    hm->state = HeightMap::NotYetGenerated;
                    hm->key = key;
                    terrain->heightmapCache[key] = hm;
                    newMaps.push_back(hm);
                }
            }
        }

        deleteOldCachedTiles(userPos.x, userPos.z);

        terrain->terrainMutex->unlock();

        for (int i=0; i<newMaps.size(); i++) {
            newMaps[i]->generate(terrain);
        }
    }
}

void TerrainGenerationWorker::deleteOldCachedTiles(float x, float y) {
    float maxDist = terrain->lodRadii[levelsOfDetail-1];
    std::vector<TileKey> tilesToDelete;
    for (auto it=terrain->heightmapCache.begin(); it!=terrain->heightmapCache.end(); it++) {
        TileKey key = it->first;
        double dist = sqrt(pow(key.x + tileSize/2.0 - x, 2) + pow(key.y + tileSize/2.0 - y, 2));
        if (dist > maxDist && terrain->heightmapCache[key]->state == HeightMap::Generated) {
            tilesToDelete.push_back(key);
        }
    }
    for (int i=0; i<tilesToDelete.size(); i++) {
        delete terrain->heightmapCache[tilesToDelete[i]];
        terrain->heightmapCache.erase(tilesToDelete[i]);
    }
}

void HeightMap::generate(PerlinTerrain* terrain) {
    Vector2 tileOrigin = Vector2(key.x, key.y);
    int size = tileSize/pow(2, key.lod);

    // make a vertex buffer:
    int nVertices = size * size;
    GLubyte* data = new GLubyte[nVertices * VERTEX_SIZE];
    for (int i=0; i<nVertices; i++) {
        double x = tileOrigin.x + ((i%size)*1.0)/(size-1) * tileSize;
        double y = tileOrigin.y + ((i/size)*1.0)/(size-1) * tileSize;
        //double height = heightFunction(x, y);
        double pixelSize = 1.0/(size-1) * tileSize;
        //double dx = (PerlinTerrain::heightFunction(x+pixelSize, y) - PerlinTerrain::heightFunction(x-pixelSize, y))/2;
        //double dy = (PerlinTerrain::heightFunction(x, y+pixelSize) - PerlinTerrain::heightFunction(x, y-pixelSize))/2;
        double dx = (terrain->biomes.landAtPos(x+pixelSize, y).height - terrain->biomes.landAtPos(x-pixelSize, y).height)/2;
        double dy = (terrain->biomes.landAtPos(x, y+pixelSize).height - terrain->biomes.landAtPos(x, y-pixelSize).height)/2;
        Vector3 normal = Vector3(dx, pixelSize, dy);
        normal.normalize();

        Land land = terrain->biomes.landAtPos(x, y);//PerlinTerrain::terrainGenerationFunction(x, y);

        float* vertex = (float*)(data + i * VERTEX_SIZE);
        vertex[0] = x;
        vertex[1] = land.height;
        vertex[2] = y;
        vertex[3] = normal.x;
        vertex[4] = normal.y;
        vertex[5] = normal.z;
        TerrainTexture* terrainTex = (TerrainTexture*)(data + i * VERTEX_SIZE + sizeof(float)*6);
        *terrainTex = land.texture;
    }
    vboData = data;
    vboSize = nVertices * VERTEX_SIZE;

    // make an index buffer:
    numIndices = (size-1)*size*2;
    unsigned int* indices = new unsigned int[numIndices];
    int i=0;
    for (int x=0; x<size-1; x++) {
        // render triangle strips in alternating directions so the endpoints don't screw things up
        if (x%2) {
            for (int y=0; y<size; y++) {
                indices[i++] = y*size + x;
                indices[i++] = y*size + x+1;
            }
        } else {
            for (int y=size-1; y>=0; y--) {
                indices[i++] = y*size + x;
                indices[i++] = y*size + x+1;
            }
        }
    }
    eboData = indices;
    eboSize = sizeof(unsigned int)*numIndices;

    state = Generated;
}

void HeightMap::bind() {
    glGenBuffers(1, &(vboID));
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vboSize, vboData, GL_STATIC_DRAW);

    glGenBuffers(1, &(eboID));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, eboData, GL_STATIC_DRAW);

    state = BoundToVBO;
    delete[] vboData;
    delete[] eboData;
}
