#ifndef VIEW_H
#define VIEW_H

#include <qgl.h>
#include <QTime>
#include <QTimer>
#include "game.h"
#include <set>
#include <QGLFramebufferObject>
const float keyActivationPeriod = 0.3;

#define VIEW_DISTANCE 6000

class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

    QTime gameTime;

    Game game;

    QGLFramebufferObject* currentFramebuffer;
private:
    QTime time;
    QTimer timer;

    void initializeGL();
    void paintGL();
    void renderGame(float xOffset=0);
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    std::set<int> pressedKeys;
    void updateKeyActivations(float dt);
    std::map<int, float> keyActivations;
    float getKeyActivation(int key);

private slots:
    void tick();
};

View* mainView();

#endif // VIEW_H

