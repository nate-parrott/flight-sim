#include "meshmodel.h"
#include <gl.h>
#include <qdir.h>
#include <QImage>
#include <QGLWidget>
#include "final.h"

MeshModel::MeshModel() {

}

void MeshModel::load(const char* filename) {
    directory = QDir(QString::fromUtf8(filename));
    directory.makeAbsolute();
    directory.cdUp();
    //printf("Material: %s\n", (dir.absolutePath()+"/").toUtf8().constData());
    std::string error = tinyobj::LoadObj(shapes, filename, (const char*)(directory.absolutePath()+"/").toUtf8().constData());
    if (!error.empty()) printf("ERROR: '%s'\n", error.c_str());
    hasCachedBoundingBox = false;
}

void MeshModel::makeVBOs() {
    for (int i=0; i<shapes.size(); i++) {
        tinyobj::shape_t* shape = &shapes[i];
        tinyobj::mesh_t* mesh = &(shape->mesh);
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        int nVertices = mesh->positions.size()/3;
        float* data = new float[nVertices * 8];
        for (int v=0; v<nVertices; v++) {
            float* vertex = data + v*8;
            vertex[0] = mesh->positions[v*3];
            vertex[1] = mesh->positions[v*3+1];
            vertex[2] = mesh->positions[v*3+2];
            vertex[3] = mesh->normals[v*3];
            vertex[4] = mesh->normals[v*3+1];
            vertex[5] = mesh->normals[v*3+2];
            vertex[6] = mesh->texcoords[v*2];
            vertex[7] = mesh->texcoords[v*2+1];
        }
        glBufferData(GL_ARRAY_BUFFER, nVertices * 8 * sizeof(float), data, GL_STATIC_DRAW);
        delete[] data;
        vboIDs.push_back(vboID);

        GLuint eboID;
        glGenBuffers(1, &eboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size()*sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);
        eboIDs.push_back(eboID);
    }
}

void MeshModel::render(bool materials) {
    if (vboIDs.size()==0) makeVBOs();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    for (int i=0; i<shapes.size(); i++) {
        tinyobj::shape_t* shape = &shapes[i];
        if (materials) applyMaterial(&shape->material);
        glBindBuffer(GL_ARRAY_BUFFER, vboIDs[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIDs[i]);

        glVertexPointer(3, GL_FLOAT, sizeof(float)*8, (GLvoid*)0);
        glNormalPointer(GL_FLOAT, sizeof(float)*8, (GLvoid*)(sizeof(float)*3));
        glTexCoordPointer(2, GL_FLOAT, sizeof(float)*8, (GLvoid*)(sizeof(float)*6));
        glDrawElements(GL_TRIANGLES, shape->mesh.indices.size(), GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshModel::applyMaterial(tinyobj::material_t* material) {

    GLfloat color[] = {0,0,0,1};

    color[0] = material->specular[0];
    color[1] = material->specular[1];
    color[2] = material->specular[2];
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);

    glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

    color[0] = material->diffuse[0];
    color[1] = material->diffuse[1];
    color[2] = material->diffuse[2];
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

    color[0] = material->ambient[0];
    color[1] = material->ambient[1];
    color[2] = material->ambient[2];
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);

    if (!material->diffuse_texname.empty()) {
        color[0] = color[1] = color[2] = 1;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
        glEnable(GL_TEXTURE_2D);
        bindTextureWithName(material->diffuse_texname);
    }
}

void MeshModel::getBoundingBox(Vector3* minimum, Vector3* maximum) {
    if (!hasCachedBoundingBox) {
        bool firstVertex = true;
        for (int i=0; i<shapes.size(); i++) {
            tinyobj::mesh_t* mesh = &(shapes[i].mesh);
            for (int j=0; j<mesh->positions.size(); j+=3) {
                if (firstVertex) {
                    cachedMin = cachedMax = Vector3(mesh->positions[j], mesh->positions[j+1], mesh->positions[j+2]);
                    firstVertex = false;
                } else {
                    cachedMin.x = npmin(cachedMin.x, mesh->positions[j]);
                    cachedMax.x = npmax(cachedMax.x, mesh->positions[j]);
                    cachedMin.y = npmin(cachedMin.y, mesh->positions[j+1]);
                    cachedMax.y = npmax(cachedMax.y, mesh->positions[j+1]);
                    cachedMin.z = npmin(cachedMin.z, mesh->positions[j+2]);
                    cachedMax.z = npmax(cachedMax.z, mesh->positions[j+2]);
                }
            }
        }
        hasCachedBoundingBox = true;
    }
    *minimum = cachedMin;
    *maximum = cachedMax;
}

void MeshModel::bindTextureWithName(std::string name) {
    if (textures.find(name) == textures.end()) {
        QImage img;
        img.load(directory.absoluteFilePath(QString::fromStdString(name)));
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        img = QGLWidget::convertToGLFormat(img);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        textures[name] = id;
    }
    glBindTexture(GL_TEXTURE_2D, textures[name]);
}

MeshModel::~MeshModel() {
    for (auto it=textures.begin(); it!=textures.end(); it++) {
        GLuint name = it->second;
        glDeleteTextures(1, &name);
    }
}

