#ifndef FINAL_H
#define FINAL_H

#include <gl.h>
#include <glu.h>
#include "CS123Algebra.h"
#include "QString.h"
#include "support.h"

const float backgroundColor[] = {0.5, 0.7, 0.9, 1.0};
QString pathForResource(const char* resource);

#define npmax(a,b) (a>b? a : b)
#define npmin(a,b) (a<b? a : b)

struct Viewpoint {
    Vector3 eye, look, up;
    uint64_t millisecondTime;
};


#endif // FINAL_H
