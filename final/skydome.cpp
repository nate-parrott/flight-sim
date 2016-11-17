#include "skydome.h"
#include <QGLWidget>
#include "final.h"

SkyDome::SkyDome() {

}

bool SkyDome::setupYet() {
    return textureID != 0;
}

void SkyDome::load(QImage &image) {
    QImage img = QGLWidget::convertToGLFormat(image);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.constBits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void SkyDome::render(Viewpoint viewpoint) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDisable(GL_LIGHTING);
    float size = 500;
    int levels = 5;
    int slices = 14;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0,0,0,viewpoint.look.x-viewpoint.eye.x,viewpoint.look.y-viewpoint.eye.y,viewpoint.look.z-viewpoint.eye.z,viewpoint.up.x,viewpoint.up.y,viewpoint.up.z);
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1,1,1);
    for (int level=-2; level<levels; level++) {
        for (int slice=0; slice<=slices; slice++) {
            for (int dy=0; dy<2; dy++) {
                int dx = 0;
                glTexCoord2f(0.5 + cos(slice*1.0/slices*M_PI*2)*0.5*(1-(level+dy)*1.0/levels), 0.5 + sin(slice*1.0/slices*M_PI*2)*0.5*(1-(level+dy)*1.0/levels));
                glVertex3f(cos((slice+dx)*1.0/slices*M_PI*2) * cos((level+dy)*1.0/levels*M_PI/2) * size, sin((level+dy)*1.0/levels*M_PI/2)*size, sin((slice+dx)*1.0/slices*M_PI*2) * cos((level+dy)*1.0/levels*M_PI/2) * size);
            }
        }
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}
