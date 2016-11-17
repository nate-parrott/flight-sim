#ifndef GAME_H
#define GAME_H

#include "sprite.h"
#include "plane.h"
#include "perlinterrain.h"
#include <QGLShaderProgram>
#include <vector>
#include "skydome.h"
#include "weather.h"
#include "remotecontrolreceiver.h"

class Game
{
public:
    Game();

    RemoteControlReceiver* remoteControlReceiver;

    Plane plane;
    PerlinTerrain terrain;
    SkyDome skyDome;
    Weather weather;

    void draw();
    void update(double dt);
};

#endif // GAME_H
