#include "weather.h"
#include <gl.h>
#include "support.h"
#include "final.h"
#include <cstdlib>
#include "simplexnoise.h"
#include "view.h"

void Cloud::randomize() {
#define RAND_FLOAT ((rand()%1000)/1000.0 - 0.5)
    float avgSize = 1.0/particlesPerCloud * 1.5;
    particles[0].x = particles[0].y = particles[0].z = 0;
    particles[0].size = avgSize;
    for (int i=1; i<particlesPerCloud; i++) {
        CloudParticle neighbor = particles[rand()%i];
        particles[i].x = neighbor.x + RAND_FLOAT * avgSize;
        particles[i].y = neighbor.y + RAND_FLOAT * avgSize;
        particles[i].z = neighbor.z + RAND_FLOAT * avgSize;
        particles[i].size = avgSize * (1.0 + RAND_FLOAT*0.3);
        particles[i].opacity = RAND_FLOAT*0.5 + 0.5;
    }
}

Weather::Weather()
{

}
void Weather::updateCloudCache(Vector3 point, float viewDistance) {
    Vector2 tileOrigin = Vector2(round(point.x/cloudTileSize)*cloudTileSize, round(point.z/cloudTileSize)*cloudTileSize);
    int tileRadius = ceil(viewDistance / cloudTileSize);
    for (int x=-tileRadius; x<tileRadius; x++) {
        for (int y=-tileRadius; y<tileRadius; y++) {
            Vector2 tilePos = Vector2(tileOrigin.x + x * cloudTileSize, tileOrigin.y + y * cloudTileSize);
            CloudTileKey key;
            key.x = tilePos.x;
            key.y = tilePos.y;
            if (!cloudsForTiles[key]) {
                float cloudProbability = mainView()->game.terrain.biomes.landAtPos(point.x, point.z).cloudProbability;
                Vector3 center = Vector3(tilePos.x + cloudTileSize*RAND_FLOAT, 120 + RAND_FLOAT*20, tilePos.y + cloudTileSize*RAND_FLOAT);
                if (raw_noise_2d(center.x, center.z)*0.5 + 0.5 < cloudProbability) {
                    Cloud* c = new Cloud();
                    c->center = center;
                    c->randomize();
                    cloudsForTiles[key] = c;
                } else {
                    cloudsForTiles[key] = (Cloud*)NULL_CLOUD;
                }
            }
        }
    }
}

void Weather::renderWeather(Vector3 point, Vector3 viewerPos, float viewDistance) {
    static int tick = 0;
    if ((tick++)%100 == 0) {
        deleteOldCachedTiles(point.x, point.z, viewDistance + 100);
    }

    updateCloudCache(point, viewDistance);

    static GLuint cloudParticleTexture = 0;
    if (!cloudParticleTexture) {
        cloudParticleTexture = loadAndBindTexture(pathForResource("textures/cloud.png"));
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, cloudParticleTexture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    for (auto it=cloudsForTiles.begin(); it != cloudsForTiles.end(); it++) {
        Cloud* c = it->second;
        if (c==NULL || c==NULL_CLOUD) continue;
        glPushMatrix();
        glTranslatef(c->center.x, c->center.y, c->center.z);
        glScalef(2, 0.5, 2);
        for (int j=0; j<particlesPerCloud; j++) {
            CloudParticle p = c->particles[j];
            float particleSize = p.size * cloudSize;
            Vector3 relativeParticlePos = (Vector3(p.x, p.y, p.z)*cloudSize);
            Vector3 absoluteParticlePos = c->center + relativeParticlePos;
            glPushMatrix();
            glTranslatef(relativeParticlePos.x, relativeParticlePos.y, relativeParticlePos.z);
            glScalef(particleSize/2, particleSize/2, particleSize/2);
            Vector3 look = (viewerPos - absoluteParticlePos).getNormalized();
            Vector3 existing = Vector3(0, 0, 1);
            Vector3 axis = existing.cross(look);
            glRotatef(acos(existing.dot(look))*180/M_PI, axis.x, axis.y, axis.z);

            glColor4f(1,1,1,p.opacity);

            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-1, -1, 0);
            glTexCoord2f(1, 0);
            glVertex3f(1, -1, 0);
            glTexCoord2f(1, 1);
            glVertex3f(1, 1, 0);
            glTexCoord2f(0, 1);
            glVertex3f(-1, 1, 0);
            glEnd();

            glPopMatrix();
        }
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
}

void Weather::deleteOldCachedTiles(double x, double y, float maxDist) {
    std::vector<CloudTileKey> tilesToDelete;
    for (auto it=cloudsForTiles.begin(); it!=cloudsForTiles.end(); it++) {
        CloudTileKey key = it->first;
        double dist = sqrt(pow(key.x + cloudTileSize/2.0 - x, 2) + pow(key.y + cloudTileSize/2.0 - y, 2));
        if (dist > maxDist) {
            tilesToDelete.push_back(key);
        }
    }
    for (int i=0; i<tilesToDelete.size(); i++) {
        Cloud* c = cloudsForTiles[tilesToDelete[i]];
        if (c!=NULL && c!=NULL_CLOUD) {
            delete c;
        }
        cloudsForTiles.erase(tilesToDelete[i]);
    }
}
