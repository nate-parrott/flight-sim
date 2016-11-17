#ifndef SUPPORT_H
#define SUPPORT_H

#include "CS123Algebra.h"
#include <QImage>
#include <gl.h>

mat4<float> lookMatrix(Vector3 heading, Vector3 up);
Vector3 transformPoint(mat4<float> mat, Vector3 vec);

GLuint loadAndBindTexture(QString path);

#endif // SUPPORT_H
