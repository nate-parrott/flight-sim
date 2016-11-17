#include "support.h"
#include <QGLWidget>
#include <glu.h>

mat4<float> lookMatrix(Vector3 heading, Vector3 up) {
    Vector3 w = -heading.getNormalized();
    Vector3 u = up.cross(w).getNormalized();
    Vector3 v = w.cross(u);
    auto mat = mat4<float>(
                u.x, u.y, u.z, 0,
                v.x, v.y, v.z, 0,
                w.x, w.y, w.z, 0,
                0, 0, 0, 1
                );
    return mat;
}

Vector3 transformPoint(mat4<float> mat, Vector3 vec) {
    auto vecM = mat4<float>(
                vec.x,0,0,0,
                vec.y,0,0,0,
                vec.z,0,0,0,
                1,0,0,0
                );
    auto res = mat * vecM;
    Vector4 v = Vector4(res.data[0], res.data[4], res.data[8], res.data[12]);
    return Vector3(v.x/v.w, v.y/v.w, v.z/v.w);
}

GLuint loadAndBindTexture(QString path) {
    QImage img = QGLWidget::convertToGLFormat(QImage(path));
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, img.width(), img.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    return id;
}
