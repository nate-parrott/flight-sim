#include "game.h"
#include <QDateTime>
#include "view.h"
#include <cstdlib>

Game::Game()
{
    srand(time(NULL));
    plane.position = Vector3(0, 20, 0);
    plane.heading = Vector3(0, 0, 1);
    plane.velocity = Vector3(0, 0, 40);
    //terrain.scale = 3;
    terrain.waterLevel = 0;
    terrain.plane = &plane;
}

void Game::draw() {

    float fallBehind = 15;
    float fallUp = 6;

    Viewpoint currentViewpoint;
    currentViewpoint.eye = plane.position-plane.heading*fallBehind+plane.up*fallUp;
    currentViewpoint.look = currentViewpoint.eye + plane.heading;
    currentViewpoint.up = plane.up;
    uint64_t time = QDateTime::currentMSecsSinceEpoch();
    currentViewpoint.millisecondTime = time;

    Viewpoint vp = currentViewpoint;

    gluLookAt(vp.eye.x, vp.eye.y, vp.eye.z, vp.look.x, vp.look.y, vp.look.z, vp.up.x, vp.up.y, vp.up.z);

    if (!skyDome.setupYet()) {
        QImage image;
        image.load(pathForResource("skydomes/sky.png"));
        skyDome.load(image);
    }
    skyDome.render(vp);

    GLfloat lightPos[] = {0, 1000000, 0, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    terrain.renderAroundPoint(plane.position);

    weather.renderWeather(plane.position, Vector3(vp.eye.x, vp.eye.y, vp.eye.z), VIEW_DISTANCE);

    plane.draw();
}

void Game::update(double dt) {
    if (!remoteControlReceiver) {
        remoteControlReceiver = new RemoteControlReceiver();
        remoteControlReceiver->start();
    }
    if (remoteControlReceiver->hasUpToDateData()) {
        plane.roll(remoteControlReceiver->roll / 180 * M_PI * dt);
        plane.pitch(remoteControlReceiver->pitch / 180 * M_PI * dt);
    }
    plane.update(dt);
}
