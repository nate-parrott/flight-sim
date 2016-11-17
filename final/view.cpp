#include "view.h"
#include <QApplication>
#include <QKeyEvent>
#include <glu.h>
#include "final.h"
#include <cstdlib>

View* _sharedView = NULL;
View* mainView() {
    return _sharedView;
}


View::View(QWidget *parent) : QGLWidget(parent)
{
    _sharedView = this;
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    setCursor(Qt::BlankCursor);

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));

    QGLFormat currentFormat = format();
    currentFormat.setSampleBuffers(true);
    currentFormat.setSamples(2);
    setFormat(currentFormat);

   }

View::~View()
{
}

void View::initializeGL()
{

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);

    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    time.start();
    timer.start(1000 / 60);

    gameTime.start();

    // Center the mouse, which is explained more in mouseMoveEvent() below.
    // This needs to be done here because the mouse may be initially outside
    // the fullscreen window and will not automatically receive mouse move
    // events. This occurs if there are two monitors and the mouse is on the
    // secondary monitor.
    //QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
}
QString showNum(int num, int length) {
    QString s = QString::number(num);
    while (s.length() < length) {
        s = QString(" ")+s;
    }
    if (s.length() > length) {
        s.truncate(length);
    }
    return s;
}
QString makeGauge(int length, float fill) {
    QString s("");
    for (int i=0; i<length; i++) {
        if (fill > i*1.0/length) {
            s += QString("|");
        } else {
            s += QString(" ");
        }
    }
    return s;
}

void View::paintGL()
{
    bool stereo = false;
    if (stereo) {
        const float parallax = 1.2;
        QGLFramebufferObject left(size(), QGLFramebufferObject::Depth);
        currentFramebuffer = &left;
        left.bind();
        renderGame(-parallax/2);
        left.release();
        QGLFramebufferObject right(size(), QGLFramebufferObject::Depth);
        currentFramebuffer = &right;
        right.bind();
        renderGame(parallax/2);
        right.release();

        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_LIGHTING);
        for (int i=0; i<2; i++) {
            if (i==0) {
                glColor3f(1,0,0);
            } else {
                glColor3f(0,1,1);
            }
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_DEPTH_TEST);
            glBindTexture(GL_TEXTURE_2D, i==0? left.texture() : right.texture());
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(-1, -1, 1);
            glTexCoord2f(1, 0);
            glVertex3f(1, -1, 1);
            glTexCoord2f(1, 1);
            glVertex3f(1, 1, 1);
            glTexCoord2f(0, 1);
            glVertex3f(-1, 1, 1);
            glEnd();
        }
    } else {
        currentFramebuffer = NULL;
        renderGame();
    }

    int speed = game.plane.velocity.getMagnitude();
    int alt = game.plane.position.y;
    float throttle = game.plane.throttle;
    QString text = QString("SPEED [%1] ALT [%2] THROTTLE [%3]").arg(showNum(speed, 5), showNum(alt, 5), makeGauge(8, throttle));
    if (game.remoteControlReceiver && !game.remoteControlReceiver->connectionKey.isEmpty()) {
        text += QString(" CONNECT at ") + game.remoteControlReceiver->connectionKey;
        /*if (game.remoteControlReceiver->hasUpToDateData()) {
            text += " [receiving]";
        }*/
    }
    glColor3f(1,1,1);
    QFont font("Courier", 20);
    font.setStyleHint(QFont::Monospace);
    font.setBold(true);
    renderText(5, height()-5, text, font);
}
void View::renderGame(float xOffset) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, width()*1.0/height(), 1, VIEW_DISTANCE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-xOffset, 0, 0);

    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE, GL_ZERO);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glPushMatrix();
    game.draw();
    glPopMatrix();
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

/*
void View::drawShadow() {

    GLdouble projection[16], modelview[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

    int viewport[] = {0, 0, width(), height()};

    int npixels = width()*height();
    unsigned char* bytes = new unsigned char[npixels*3];
    glReadPixels(0, 0, width(), height(), GL_RGB, GL_UNSIGNED_BYTE, bytes);
    float* depth = new float[npixels];
    glReadPixels(0, 0, width(), height(), GL_DEPTH_COMPONENT, GL_FLOAT, depth);

    for (int i=0; i<npixels; i++) {
        GLdouble x,y,z;
        gluUnProject(i%width(), i/width(), depth[i], modelview, projection, viewport, &x, &y, &z);
        bytes[i*3] = x/1000;
    }

    glDrawPixels(width(), height(), GL_RGB, GL_UNSIGNED_BYTE, bytes);

    delete[] bytes;
    delete[] depth;
}*/

void View::mousePressEvent(QMouseEvent *event)
{
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    // This starter code implements mouse capture, which gives the change in
    // mouse position since the last mouse movement. The mouse needs to be
    // recentered after every movement because it might otherwise run into
    // the edge of the screen, which would stop the user from moving further
    // in that direction. Note that it is important to check that deltaX and
    // deltaY are not zero before recentering the mouse, otherwise there will
    // be an infinite loop of mouse move events.
    int deltaX = event->x() - width() / 2;
    int deltaY = event->y() - height() / 2;
    if (!deltaX && !deltaY) return;
    //QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    // TODO: Handle mouse movements here
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) QApplication::quit();

    pressedKeys.insert(event->key());
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys.erase(event->key());
}

void View::tick()
{    
    const float rollDegreesPerSecond = 40;
    const float pitchDegreesPerSecond = 40;
    const float throttlePerSecond = 0.26;

    // Get the number of seconds since the last tick (variable update rate)
    float seconds = time.restart() * 0.001f;

    updateKeyActivations(seconds);

    float rollAngle = (getKeyActivation(Qt::Key_Right) - getKeyActivation(Qt::Key_Left))*rollDegreesPerSecond*seconds;
    game.plane.roll(rollAngle/180*M_PI);

    float rotateAngle = (getKeyActivation(Qt::Key_Down) - getKeyActivation(Qt::Key_Up))*pitchDegreesPerSecond*seconds;
    game.plane.pitch(rotateAngle/180*M_PI);

    float dthrottle = (getKeyActivation(Qt::Key_X) - getKeyActivation(Qt::Key_Z))*throttlePerSecond*seconds;
    game.plane.throttle = npmin(1.0, npmax(0.0, game.plane.throttle+dthrottle));

    game.update(seconds);

    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}
void View::updateKeyActivations(float dt) {
    for (auto it=pressedKeys.begin(); it!=pressedKeys.end(); it++) {
        int key = *it;
        if (pressedKeys.find(key)!=pressedKeys.end()) {
            float newActivation = getKeyActivation(key) + dt/keyActivationPeriod;
            if (newActivation > 1) newActivation = 1;
            keyActivations[key] = newActivation;
        }
    }
    for (auto it=keyActivations.begin(); it!=keyActivations.end(); it++) {
        int key = it->first;
        if (pressedKeys.find(key) == pressedKeys.end()) { // this is an unpressed key that needs its activation decreased
            float newActivation = getKeyActivation(key) - dt/keyActivationPeriod;
            if (newActivation > 0) {
                keyActivations[key] = newActivation;
            } else {
                keyActivations.erase(key);
            }
        }
    }
}
float View::getKeyActivation(int key) {
    if (keyActivations.find(key) == keyActivations.end()) {
        return 0;
    } else {
        return keyActivations[key];
    }
}
