#ifndef MESHMODEL_H
#define MESHMODEL_H

#include <QString>
#include <vector>
#include <map>
#include "tiny_obj_loader.h"
#include <QDir>
#include <gl.h>
#include "CS123Algebra.h"

/*
 * MeshModel loads and renders .obj files and (some of) their associated .mtl data
 * Files must be exported by Blender with the options "include normals" and "keep vertex order" enabled
 */

class MeshModel
{
public:
    MeshModel();
    void load(const char* filename);
    void render(bool materials=true);
    std::map<std::string, GLuint> textures;
    void loadTexture(std::string str);
    ~MeshModel();
    void getBoundingBox(Vector3* minimum, Vector3* maximum);

private:
    QDir directory;
    void applyMaterial(tinyobj::material_t* material);
    std::vector<tinyobj::shape_t> shapes;
    void bindTextureWithName(std::string name);

    void makeVBOs();
    std::vector<GLuint> vboIDs;
    std::vector<GLuint> eboIDs;

    bool hasCachedBoundingBox = false;
    Vector3 cachedMin, cachedMax;
};

#endif // MESHMODEL_H
