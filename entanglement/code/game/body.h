#ifndef _BODY_H_
#define _BODY_H_

#define TINYC2_IMPLEMENTATION

#include "../thirdparty/tinyc2.h"
#include "../math.h"

typedef struct body
{
    union shape
    {
        c2AABB aabb;
        c2Circle circle;
        c2Capsule capsule;
        c2Poly polygon;
    } shape;
    C2_TYPE shapeType;
    vec2_t position;
    vec2_t velocity;
    vec2_t acceleration;
    float32_t elasticity;
    bool32_t immovable;
} body_t;

bool32_t ldBodyImmediateOverlapCheck(const body_t* LD_RESTRICT pBodyA, const body_t* LD_RESTRICT pBodyB);
bool32_t ldBodyImmediateCollisionCheck(const body_t* LD_RESTRICT pBodyA, const body_t* LD_RESTRICT pBodyB, c2Manifold* LD_RESTRICT pCollisionInfo);
bool32_t ldBodyImmediateCollisionSolve(body_t* LD_RESTRICT pBodyA, body_t* LD_RESTRICT pBodyB);
void ldBodyUpdateMotion(body_t* pBody, float32_t deltaT);

#endif // !_BODY_H_
