#include "sprite.h"
#include <gl.h>

Sprite::Sprite()
{
    up = Vector3(0, 1, 0);
}
void Sprite::draw() {

}
void Sprite::update(double dt) {
    position += velocity*dt;
}
