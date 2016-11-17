#ifndef PLANE_H
#define PLANE_H

#include "sprite.h"
#include "meshmodel.h"
#include <QGLFramebufferObject>

class Plane : public Sprite
{
public:
    Plane();
    void draw();
    MeshModel model;
    float getModelScale();
    float desiredSize;

    void pitch(float angle);
    void roll(float angle);
    void yaw(float angle);
    void transformPlane(Matrix4x4 mat);

    void update(double dt);

    float throttle;

    void renderSilhouette(float scale, QGLFramebufferObject** framebuffer);
};

#endif // PLANE_H
