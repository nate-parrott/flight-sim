#ifndef MESHMODEL2_H
#define MESHMODEL2_H

#include "obj_parser/objLoader.h"

class MeshModel2
{
    objLoader _loader;
public:
    MeshModel2();
    void load(const char* filename);
    void render();
    ~MeshModel2();
};

#endif // MESHMODEL2_H
