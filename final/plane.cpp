#include "plane.h"
#include "CS123Algebra.h"
#include <QDir>
#include <view.h>

Plane::Plane()
{
    throttle = 0.7;
    // from http://tf3dm.com/3d-model/cessna-7555.html
    model.load(pathForResource("planes/c5.obj").toUtf8().constData());
    desiredSize = 8;
}

void Plane::draw() {
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    /*float yaw = atan2(heading.z, heading.x);
    glRotatef(-yaw*180/M_PI - 90, 0, 1, 0);
    float pitch = atan2(heading.y, heading.z);
    glRotatef(pitch*180/M_PI, 1, 0, 0);
    float roll = atan2(heading.y, heading.x);
    glRotatef(roll*180/M_PI, 0, 0, 1);*/
    auto mat = lookMatrix(heading, up);
    glMultMatrixf(mat.getInverse().getTranspose().data);

    float scale = getModelScale();
    glScalef(scale, scale, scale);
    model.render();

    glPopMatrix();
}

float Plane::getModelScale() {
    Vector3 minCoord, maxCoord;
    model.getBoundingBox(&minCoord, &maxCoord);
    float scale = npmin(desiredSize/(maxCoord.x-minCoord.x), npmin(desiredSize/(maxCoord.y-minCoord.y), desiredSize/(maxCoord.z-minCoord.z)));
    return scale;
}

void Plane::transformPlane(Matrix4x4 mat) {
    heading = transformPoint(mat, heading);
    velocity = transformPoint(mat, velocity);
    up = transformPoint(mat, up);
}

void Plane::pitch(float angle) {
    Vector3 axis = heading.cross(up);
    transformPlane(getRotMat(Vector4(0,0,0,0), Vector4(axis.x, axis.y, axis.z, 0), angle));
}

void Plane::roll(float angle) {
    Vector3 axis = heading;
    transformPlane(getRotMat(Vector4(0,0,0,0), Vector4(axis.x, axis.y, axis.z, 0), angle));
}

void Plane::yaw(float angle) {
    Vector3 axis = up;
    transformPlane(getRotMat(Vector4(0,0,0,0), Vector4(axis.x, axis.y, axis.z, 0), angle));
}
void Plane::update(double dt) {
    const float kdrag = 1;
    const float kthrust = 50;
    const float klift = 0.008;
    const float kgrav = 10;

    float forwardSpeed = velocity.dot(heading) / heading.getMagnitude();

    Vector3 lift = up * pow(forwardSpeed, 2) * klift;
    Vector3 accel = heading * throttle * kthrust;
    Vector3 gravity = Vector3(0, -1, 0)*kgrav;
    Vector3 airResistance = (-velocity.getNormalized()) * sqrt(velocity.dot(velocity))*kdrag;

    Vector3 acceleration = (lift+accel+gravity+airResistance);

    velocity += acceleration*dt;

    const float beginBoundaryAltitude = 300;
    const float endBoundaryAltitude = 400;
    if (position.y > beginBoundaryAltitude && velocity.y > 0) {
        velocity.y *= 1-(position.y-beginBoundaryAltitude)/(endBoundaryAltitude-beginBoundaryAltitude);
    }

    Sprite::update(dt);

    float roll = asin((heading.cross(Vector3(0,1,0))).dot(up))*180/M_PI;
    float yawPerDegreeOfRoll = 0.01;
    float yaw = -roll*yawPerDegreeOfRoll*dt;

    //yaw(-roll*yawPerDegreeOfRoll*dt);
    Vector3 axis = Vector3(0,1,0);
    transformPlane(getRotMat(Vector4(0,0,0,0), Vector4(axis.x, axis.y, axis.z, 0), yaw));



}

void Plane::renderSilhouette(float scale, QGLFramebufferObject** framebuffer) {

    QSize size = QSize(desiredSize*scale*1.2, desiredSize*scale*1.2);
    int oldViewport[4];
    glGetIntegerv(GL_VIEWPORT, oldViewport);
    glViewport(0,0,size.width(),size.height());
    *framebuffer = new QGLFramebufferObject(size, QGLFramebufferObject::NoAttachment,
                                            GL_TEXTURE_2D, GL_RGBA8);
    (*framebuffer)->bind();
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-size.width()/2, size.width()/2, -size.height()/2, size.height()/2, -1000, 1000);

    glMatrixMode(GL_MODELVIEW);


    glPushMatrix();
    glLoadIdentity();

    glScalef(getModelScale()*scale, getModelScale()*scale, getModelScale()*scale);

    glRotatef(-90, 1, 0, 0);

    auto mat = lookMatrix(heading, up);
    glMultMatrixf(mat.getInverse().getTranspose().data);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glColor3f(0.4,0.4,0.4);
    glDisable(GL_LIGHTING);

    model.render(false);

    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glFlush();

    (*framebuffer)->release();
    if (mainView()->currentFramebuffer) {
        mainView()->currentFramebuffer->bind();
    }

    glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
}
