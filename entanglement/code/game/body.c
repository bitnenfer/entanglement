#include "body.h"

bool32_t ldBodyImmediateOverlapCheck(body_t* LD_RESTRICT pBodyA, body_t* LD_RESTRICT pBodyB)
{
    return c2Collided((const void*)pBodyA, NULL, pBodyA->shapeType, (const void*)pBodyB, NULL, pBodyB->shapeType);
}

bool32_t ldBodyImmediateCollisionCheck(const body_t* LD_RESTRICT pBodyA, const body_t* LD_RESTRICT pBodyB, c2Manifold* LD_RESTRICT pCollisionInfo)
{
    c2Collide((const void*)pBodyA, NULL, pBodyA->shapeType, (const void*)pBodyB, NULL, pBodyB->shapeType, pCollisionInfo);
    return pCollisionInfo->count > 0;
}

bool32_t ldBodyImmediateCollisionSolve(body_t* LD_RESTRICT pBodyA, body_t* LD_RESTRICT pBodyB)
{
    c2Manifold collisionInfo = { 0 };
    if (ldBodyImmediateCollisionCheck(pBodyA, pBodyB, &collisionInfo))
    {
        float32_t px = collisionInfo.depths[0] * collisionInfo.n.x;
        float32_t py = collisionInfo.depths[0] * collisionInfo.n.y;
        float32_t avx = pBodyA->velocity.x;
        float32_t avy = pBodyA->velocity.y;
        float32_t bvx = pBodyB->velocity.x;
        float32_t bvy = pBodyB->velocity.y;

        if (!pBodyA->immovable && pBodyB->immovable)
        {
            pBodyA->position.x -= px;
            pBodyA->position.y -= py;
            pBodyA->velocity.x = (bvx - avx * pBodyA->elasticity) * collisionInfo.n.x;
            pBodyA->velocity.y = (bvy - avy * pBodyA->elasticity) * collisionInfo.n.y;
        }
        else if (pBodyA->immovable && !pBodyB->immovable)
        {
            pBodyB->position.x += px;
            pBodyB->position.y += py;
            pBodyB->velocity.x = (avx - bvx * pBodyB->elasticity) * collisionInfo.n.x;
            pBodyB->velocity.y = (avy - bvy * pBodyB->elasticity) * collisionInfo.n.y;
        }
        else 
        {
            px *= 0.5f;
            py *= 0.5f;
            
            pBodyA->position.x -= px;
            pBodyA->position.y -= py;


            pBodyA->velocity.x = (bvx - avx * pBodyA->elasticity) * collisionInfo.n.x;
            pBodyA->velocity.y = (bvy - avy * pBodyA->elasticity) * collisionInfo.n.y;
            
            pBodyB->position.x += px;
            pBodyB->position.y += py;
            
            pBodyB->velocity.x = (avx - bvx * pBodyB->elasticity) * collisionInfo.n.x;
            pBodyB->velocity.y = (avy - bvy * pBodyB->elasticity) * collisionInfo.n.y;
        }
        return LD_TRUE;
    }
    return LD_FALSE;
}

void ldBodyUpdateMotion(body_t* pBody, float32_t deltaT)
{
    
}
