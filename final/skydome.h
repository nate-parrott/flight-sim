#ifndef SKYDOME_H
#define SKYDOME_H

#include <gl.h>
#include <QImage>
#include "final.h"

class SkyDome
{
    GLuint textureID;
public:
    SkyDome();
    bool setupYet();
    void load(QImage &image);
    void render(Viewpoint viewpoint);
};

#endif // SKYDOME_H
