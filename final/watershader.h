#ifndef WATERSHADER_H
#define WATERSHADER_H

#include <QGLShaderProgram>

class WaterShader {
public:
    static QGLShaderProgram* makeWaterShader();
    static void bind(QGLShaderProgram* waterShader);
};

#endif // WATERSHADER_H
