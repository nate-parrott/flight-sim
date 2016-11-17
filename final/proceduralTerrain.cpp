#include "proceduralTerrain.h"

ProceduralTerrain::ProceduralTerrain()
{
}

float ProceduralTerrain::heightAtPos(Vector2 pos) {
    return 0;
}
Vector3 normalAtPos(Vector2 pos) {
    return Vector3(0, 1, 0);
}

void ProceduralTerrain::renderRectAtResolution(Vector2 start, Vector2 end, int intermediateSamples) {
    float dx = (end.x-start.x)/intermediateSamples;
    float dy = (end.y-start.y)/intermediateSamples;
    glColor3f(0.4, 0.7, 0.4);
    glBegin(GL_TRIANGLES);
    for (int y=0; y<intermediateSamples; y++) {
        for (int x=0; x<intermediateSamples; x++) {
            Vector2 p0 = Vector2(start.x + x*dx, start.y + y*dy);
            Vector2 p1 = Vector2(start.x + (x+1)*dx, start.y + y*dy);
            Vector2 p2 = Vector2(start.x + (x+1)*dx, start.y + (y+1)*dy);
            Vector2 p3 = Vector2(start.x + x*dx, start.y + (y+1)*dy);

            glNormal3f(0, 1, 0);
            glVertex3f(p0.x, heightAtPos(p0), p0.y);
            glNormal3f(0, 1, 0);
            glVertex3f(p1.x, heightAtPos(p1), p1.y);
            glNormal3f(0, 1, 0);
            glVertex3f(p2.x, heightAtPos(p2), p2.y);

            glNormal3f(0, 1, 0);
            glVertex3f(p2.x,  heightAtPos(p2), p2.y);
            glNormal3f(0, 1, 0);
            glVertex3f(p3.x, heightAtPos(p3), p3.y);
            glNormal3f(0, 1, 0);
            glVertex3f(p0.x, heightAtPos(p0), p0.y);
        }
    }
    glEnd();
}

void ProceduralTerrain::renderAroundPosition(Vector2 pos) {
    float dist = 400;
    renderRectAtResolution(Vector2(pos.x-dist, pos.y-dist), Vector2(pos.x+dist, pos.y+dist), 20);
}
