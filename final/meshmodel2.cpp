#include "meshmodel2.h"
#include <gl.h>

MeshModel2::MeshModel2() {

}

void MeshModel2::load(const char* filename) {
    _loader.load((char*)filename);
}

void MeshModel2::render() {
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable ( GL_COLOR_MATERIAL );
    glColor4f(0, 0.2, 1, 1);
    for (int fi=0; fi<_loader.faceCount; fi++) {
        obj_face* face = _loader.faceList[fi];
        glBegin(face->vertex_count==4? GL_QUADS : GL_TRIANGLES);
        for (int vi=0; vi < face->vertex_count; vi++) {
            glNormal3dv((const double*)_loader.normalList[face->normal_index[vi]]);
            glVertex3dv((const double*)_loader.vertexList[face->vertex_index[vi]]);
        }
    }
}

MeshModel2::~MeshModel2() {

}
