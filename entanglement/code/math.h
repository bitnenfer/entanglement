#ifndef _MATH_H_
#define _MATH_H_

#include "types.h"
#include "platform.h"
#include <math.h>

struct quat
{
    float32_t x, y, z, w;
};

struct vec2
{
    float32_t x;
    float32_t y;
};

struct vec3
{
    union
    {
        struct
        {
            float32_t x;
            float32_t y;
            float32_t z;
        };
    };
};

struct mat2d
{
    union
    {
        struct
        {
            float32_t a, b, c;
            float32_t d, tx, ty;
        };
        float32_t data[6];
    };
};

struct mat4
{
    union
    {
        struct
        {
            float32_t a, b, c, d;
            float32_t e, f, g, h;
            float32_t i, j, k, l;
            float32_t pM, n, o, p;
        };
        float32_t data[16];
    };
};

/* mat2d */
struct mat2d* ldMat2dIdent(struct mat2d* LD_RESTRICT pOut);
struct mat2d* ldMat2dMul(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM0, struct mat2d* LD_RESTRICT pM1);
struct vec2* ldMat2DVec2Mul(struct vec2*  LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM0, struct vec2* LD_RESTRICT pV1);
struct mat2d* ldMat2DTranslate(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM, float32_t x, float32_t y);
struct mat2d* ldMat2DScale(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM, float32_t x, float32_t y);
struct mat2d* ldMat2DRotate(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM, float32_t radian);

/* mat4 */
struct mat4* ldMat4Ident(struct mat4* LD_RESTRICT pOut);
struct mat4* ldMat4Mul(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM0, struct mat4* LD_RESTRICT pM1);
struct vec3* ldMat4Vec3Mul(struct vec3* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM0, struct vec3* LD_RESTRICT pV1);
struct mat4* ldMat4Transpose(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM);
struct mat4* ldMat4Invert(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM);
struct mat4* ldMat4RotateX(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, float32_t radian);
struct mat4* ldMat4RotateY(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, float32_t radian);
struct mat4* ldMat4RotateZ(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, float32_t radian);
struct mat4* ldMat4Rotate(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, struct vec3* LD_RESTRICT pAxis, float32_t radian);
struct mat4* ldMat4Scale(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, struct vec3* LD_RESTRICT pScale);
struct mat4* ldMat4Translate(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, struct vec3* LD_RESTRICT pTranslate);
struct mat4* ldMat4Frustum(struct mat4* LD_RESTRICT pOut, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t frustumNear, float32_t frustumFar);
struct mat4* ldMat4Perspective(struct mat4* LD_RESTRICT pOut, float32_t fovY, float32_t aspect, float32_t perspNear, float32_t perspFar);
struct mat4* ldMat4Orthographic(struct mat4* LD_RESTRICT pOut, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t orthoNear, float32_t orthoFar);
struct mat4* ldMat4LookAt(struct mat4* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pEye, struct vec3* LD_RESTRICT pCenter, struct vec3* LD_RESTRICT pUp);

/* vec2 */
struct vec2* ldVec2Add(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
struct vec2* ldVec2Sub(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
struct vec2* ldVec2Mul(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
struct vec2* ldVec2Invert(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV);
struct vec2* ldVec2Negate(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV);
struct vec2* ldVec2Normalize(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV);
int32_t ldVec2Equal(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
struct vec3* ldVec2Cross(struct vec3* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
float32_t ldVec2Distance(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
float32_t ldVec2Dot(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);
float32_t ldVec2Length(struct vec2* LD_RESTRICT pV);
float32_t ldVec2Length2(struct vec2* LD_RESTRICT pV);
float32_t ldVec2Distance2(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1);

/* vec3 */
struct vec3* ldVec3Add(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
struct vec3* ldVec3Sub(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
struct vec3* ldVec3Mul(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
struct vec3* ldVec3Invert(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV);
struct vec3* ldVec3Negate(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV);
struct vec3* ldVec3Normalize(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV);
int32_t ldVec3Equal(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
struct vec3* ldVec3Cross(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
float32_t ldVec3Distance(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
float32_t ldVec3Dot(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);
float32_t ldVec3Length(struct vec3* LD_RESTRICT pV);
float32_t ldVec3Length2(struct vec3* LD_RESTRICT pV);
float32_t ldVec3Distance2(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1);

/* quat */
struct quat* ldQuatIdent(struct quat* LD_RESTRICT pOut);
struct quat* ldQuatAdd(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ0, struct quat* LD_RESTRICT pQ1);
struct quat* ldQuatMul(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ0, struct quat* LD_RESTRICT pQ1);
struct quat* ldQuatSetAxisAngle(struct quat* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pAxis, float32_t radian);
struct quat* ldQuatRotateX(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ, float32_t radian);
struct quat* ldQuatRotateY(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ, float32_t radian);
struct quat* ldQuatRotateZ(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ, float32_t radian);
struct quat* ldQuatCalcW(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ);
struct quat* ldQuatInvert(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ);
struct quat* ldQuatConjugate(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ);
struct mat4* ldQuatToMat4(struct mat4* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ);
float32_t ldQuatGetAxisAngle(struct vec3* LD_RESTRICT pOutAxis, struct quat* LD_RESTRICT pQ);

/* Definition */
typedef struct quat quat_t;
typedef struct vec2 vec2_t;
typedef struct vec3 vec3_t;
typedef struct mat2d mat2d_t;
typedef struct mat4 mat4_t;

/* mat2d */
struct mat2d* ldMat2dIdent(struct mat2d* LD_RESTRICT pOut)
{
    pOut->data[0] = 1.0f;
    pOut->data[1] = 0.0f;
    pOut->data[2] = 0.0f;
    pOut->data[3] = 1.0f;
    pOut->data[4] = 0.0f;
    pOut->data[5] = 0.0f;
    return pOut;
}
struct mat2d* ldMat2dMul(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM0, struct mat2d* LD_RESTRICT pM1)
{
    const float32_t* matrixA = pM0->data;
    const float32_t* matrixB = pM1->data;
    float32_t* matrix = pOut->data;

    float32_t a = matrixA[0];
    float32_t b = matrixA[1];
    float32_t c = matrixA[2];
    float32_t d = matrixA[3];
    float32_t tx = matrixA[4];
    float32_t ty = matrixA[5];

    float32_t a0 = matrixB[0];
    float32_t b0 = matrixB[1];
    float32_t c0 = matrixB[2];
    float32_t d0 = matrixB[3];
    float32_t tx0 = matrixB[4];
    float32_t ty0 = matrixB[5];

    matrix[0] = a * a0 + b * c0;
    matrix[1] = a * b0 + b * d0;
    matrix[2] = c * a0 + d * c0;
    matrix[3] = c * b0 + d * d0;
    matrix[4] = tx * a0 + ty * c0 + tx0;
    matrix[5] = tx * b0 + ty * d0 + ty0;

    return pOut;
}
struct vec2* ldMat2DVec2Mul(struct vec2* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM0, struct vec2* LD_RESTRICT pV1)
{
    pOut->x = pV1->x * pM0->a + pV1->y * pM0->c + pM0->tx;
    pOut->y = pV1->x * pM0->b + pV1->y * pM0->d + pM0->ty;
    return pOut;
}
struct mat2d* ldMat2DTranslate(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM, float32_t x, float32_t y)
{
    pOut->data[4] = pM->data[0] * x + pM->data[2] * y + pM->data[4];
    pOut->data[5] = pM->data[1] * x + pM->data[3] * y + pM->data[5];
    return pOut;
}
struct mat2d* ldMat2DScale(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM, float32_t x, float32_t y)
{
    pOut->data[0] = pM->data[0] * x;
    pOut->data[1] = pM->data[1] * x;
    pOut->data[2] = pM->data[2] * y;
    pOut->data[3] = pM->data[3] * y;
    return pOut;
}
struct mat2d* ldMat2DRotate(struct mat2d* LD_RESTRICT pOut, struct mat2d* LD_RESTRICT pM, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cs = cosf(radian);
    pOut->data[0] = cs * pM->data[0] + sn * pM->data[2];
    pOut->data[1] = cs * pM->data[1] + sn * pM->data[3];
    pOut->data[2] = -sn * pM->data[0] + cs * pM->data[2];
    pOut->data[3] = -sn * pM->data[1] + cs * pM->data[3];
    return pOut;
}

/* mat4 */
struct mat4* ldMat4Ident(struct mat4* LD_RESTRICT pOut)
{
    pOut->data[0] = 1.0f;
    pOut->data[1] = 0.0f;
    pOut->data[2] = 0.0f;
    pOut->data[3] = 0.0f;
    pOut->data[4] = 0.0f;
    pOut->data[5] = 1.0f;
    pOut->data[6] = 0.0f;
    pOut->data[7] = 0.0f;
    pOut->data[8] = 0.0f;
    pOut->data[9] = 0.0f;
    pOut->data[10] = 1.0f;
    pOut->data[11] = 0.0f;
    pOut->data[12] = 0.0f;
    pOut->data[13] = 0.0f;
    pOut->data[14] = 0.0f;
    pOut->data[15] = 1.0f;
    return pOut;
}
struct mat4* ldMat4Mul(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM0, struct mat4* LD_RESTRICT pM1)
{
    pOut->data[0] = pM1->data[0] * pM0->data[0] + pM1->data[1] * pM0->data[4] + pM1->data[2] * pM0->data[8] + pM1->data[3] * pM0->data[12];
    pOut->data[1] = pM1->data[0] * pM0->data[1] + pM1->data[1] * pM0->data[5] + pM1->data[2] * pM0->data[9] + pM1->data[3] * pM0->data[13];
    pOut->data[2] = pM1->data[0] * pM0->data[2] + pM1->data[1] * pM0->data[6] + pM1->data[2] * pM0->data[10] + pM1->data[3] * pM0->data[14];
    pOut->data[3] = pM1->data[0] * pM0->data[3] + pM1->data[1] * pM0->data[7] + pM1->data[2] * pM0->data[11] + pM1->data[3] * pM0->data[15];
    pOut->data[4] = pM1->data[4] * pM0->data[0] + pM1->data[5] * pM0->data[4] + pM1->data[6] * pM0->data[8] + pM1->data[7] * pM0->data[12];
    pOut->data[5] = pM1->data[4] * pM0->data[1] + pM1->data[5] * pM0->data[5] + pM1->data[6] * pM0->data[9] + pM1->data[7] * pM0->data[13];
    pOut->data[6] = pM1->data[4] * pM0->data[2] + pM1->data[5] * pM0->data[6] + pM1->data[6] * pM0->data[10] + pM1->data[7] * pM0->data[14];
    pOut->data[7] = pM1->data[4] * pM0->data[3] + pM1->data[5] * pM0->data[7] + pM1->data[6] * pM0->data[11] + pM1->data[7] * pM0->data[15];
    pOut->data[8] = pM1->data[8] * pM0->data[0] + pM1->data[9] * pM0->data[4] + pM1->data[10] * pM0->data[8] + pM1->data[11] * pM0->data[12];
    pOut->data[9] = pM1->data[8] * pM0->data[1] + pM1->data[9] * pM0->data[5] + pM1->data[10] * pM0->data[9] + pM1->data[11] * pM0->data[13];
    pOut->data[10] = pM1->data[8] * pM0->data[2] + pM1->data[9] * pM0->data[6] + pM1->data[10] * pM0->data[10] + pM1->data[11] * pM0->data[14];
    pOut->data[11] = pM1->data[8] * pM0->data[3] + pM1->data[9] * pM0->data[7] + pM1->data[10] * pM0->data[11] + pM1->data[11] * pM0->data[15];
    pOut->data[12] = pM1->data[12] * pM0->data[0] + pM1->data[13] * pM0->data[4] + pM1->data[14] * pM0->data[8] + pM1->data[15] * pM0->data[12];
    pOut->data[13] = pM1->data[12] * pM0->data[1] + pM1->data[13] * pM0->data[5] + pM1->data[14] * pM0->data[9] + pM1->data[15] * pM0->data[13];
    pOut->data[14] = pM1->data[12] * pM0->data[2] + pM1->data[13] * pM0->data[6] + pM1->data[14] * pM0->data[10] + pM1->data[15] * pM0->data[14];
    pOut->data[15] = pM1->data[12] * pM0->data[3] + pM1->data[13] * pM0->data[7] + pM1->data[14] * pM0->data[11] + pM1->data[15] * pM0->data[15];
    return pOut;
}
struct vec3* ldMat4Vec3Mul(struct vec3* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM0, struct vec3* LD_RESTRICT pV1)
{
    pOut->x = pM0->data[0] * pV1->x + pM0->data[4] * pV1->y + pM0->data[8] * pV1->z + pM0->data[12];
    pOut->y = pM0->data[1] * pV1->x + pM0->data[5] * pV1->y + pM0->data[9] * pV1->z + pM0->data[13];
    pOut->z = pM0->data[2] * pV1->x + pM0->data[6] * pV1->y + pM0->data[10] * pV1->z + pM0->data[14];
    return pOut;
}
struct mat4* ldMat4Transpose(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM)
{
    pOut->data[0] = pM->data[0];
    pOut->data[1] = pM->data[4];
    pOut->data[2] = pM->data[8];
    pOut->data[3] = pM->data[12];
    pOut->data[4] = pM->data[1];
    pOut->data[5] = pM->data[5];
    pOut->data[6] = pM->data[9];
    pOut->data[7] = pM->data[13];
    pOut->data[8] = pM->data[2];
    pOut->data[9] = pM->data[6];
    pOut->data[10] = pM->data[10];
    pOut->data[11] = pM->data[14];
    pOut->data[12] = pM->data[3];
    pOut->data[13] = pM->data[7];
    pOut->data[14] = pM->data[11];
    pOut->data[15] = pM->data[15];
    return pOut;
}
struct mat4* ldMat4Invert(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM)
{
    float32_t d0 = pM->data[0] * pM->data[5] - pM->data[1] * pM->data[4];
    float32_t d1 = pM->data[0] * pM->data[6] - pM->data[2] * pM->data[4];
    float32_t d2 = pM->data[0] * pM->data[7] - pM->data[3] * pM->data[4];
    float32_t d3 = pM->data[1] * pM->data[6] - pM->data[2] * pM->data[5];
    float32_t d4 = pM->data[1] * pM->data[7] - pM->data[3] * pM->data[5];
    float32_t d5 = pM->data[2] * pM->data[7] - pM->data[3] * pM->data[6];
    float32_t d6 = pM->data[8] * pM->data[13] - pM->data[9] * pM->data[12];
    float32_t d7 = pM->data[8] * pM->data[14] - pM->data[10] * pM->data[12];
    float32_t d8 = pM->data[8] * pM->data[15] - pM->data[11] * pM->data[12];
    float32_t d9 = pM->data[9] * pM->data[14] - pM->data[10] * pM->data[13];
    float32_t d10 = pM->data[9] * pM->data[15] - pM->data[11] * pM->data[13];
    float32_t d11 = pM->data[10] * pM->data[15] - pM->data[11] * pM->data[14];
    float32_t determinant = d0 * d11 - d1 * d10 + d2 * d9 + d3 * d8 - d4 * d7 + d5 * d6;

    if (determinant == 0.0f) return pM;

    determinant = 1.0f / determinant;
    pOut->data[0] = (pM->data[5] * d11 - pM->data[6] * d10 + pM->data[7] * d9) * determinant;
    pOut->data[1] = (pM->data[2] * d10 - pM->data[1] * d11 - pM->data[3] * d9) * determinant;
    pOut->data[2] = (pM->data[13] * d5 - pM->data[14] * d4 + pM->data[15] * d3) * determinant;
    pOut->data[3] = (pM->data[10] * d4 - pM->data[9] * d5 - pM->data[11] * d3) * determinant;
    pOut->data[4] = (pM->data[6] * d8 - pM->data[4] * d11 - pM->data[7] * d7) * determinant;
    pOut->data[5] = (pM->data[0] * d11 - pM->data[2] * d8 + pM->data[3] * d7) * determinant;
    pOut->data[6] = (pM->data[14] * d2 - pM->data[12] * d5 - pM->data[15] * d1) * determinant;
    pOut->data[7] = (pM->data[8] * d5 - pM->data[10] * d2 + pM->data[11] * d1) * determinant;
    pOut->data[8] = (pM->data[4] * d10 - pM->data[5] * d8 + pM->data[7] * d6) * determinant;
    pOut->data[9] = (pM->data[1] * d8 - pM->data[0] * d10 - pM->data[3] * d6) * determinant;
    pOut->data[10] = (pM->data[12] * d4 - pM->data[13] * d2 + pM->data[15] * d0) * determinant;
    pOut->data[11] = (pM->data[9] * d2 - pM->data[8] * d4 - pM->data[11] * d0) * determinant;
    pOut->data[12] = (pM->data[5] * d7 - pM->data[4] * d9 - pM->data[6] * d6) * determinant;
    pOut->data[13] = (pM->data[0] * d9 - pM->data[1] * d7 + pM->data[2] * d6) * determinant;
    pOut->data[14] = (pM->data[13] * d1 - pM->data[12] * d3 - pM->data[14] * d0) * determinant;
    pOut->data[15] = (pM->data[8] * d3 - pM->data[9] * d1 + pM->data[10] * d0) * determinant;
    return pOut;
}
struct mat4* ldMat4RotateX(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    pOut->data[0] = pM->data[0];
    pOut->data[1] = pM->data[1];
    pOut->data[2] = pM->data[2];
    pOut->data[3] = pM->data[3];
    pOut->data[12] = pM->data[12];
    pOut->data[13] = pM->data[13];
    pOut->data[14] = pM->data[14];
    pOut->data[15] = pM->data[15];
    pOut->data[4] = pM->data[4] * cn + pM->data[8] * sn;
    pOut->data[5] = pM->data[5] * cn + pM->data[9] * sn;
    pOut->data[6] = pM->data[6] * cn + pM->data[10] * sn;
    pOut->data[7] = pM->data[7] * cn + pM->data[11] * sn;
    pOut->data[8] = pM->data[8] * cn - pM->data[4] * sn;
    pOut->data[9] = pM->data[9] * cn - pM->data[5] * sn;
    pOut->data[10] = pM->data[10] * cn - pM->data[6] * sn;
    pOut->data[11] = pM->data[11] * cn - pM->data[7] * sn;
    return pOut;
}
struct mat4* ldMat4RotateY(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    pOut->data[0] = pM->data[0] * cn - pM->data[8] * sn;
    pOut->data[1] = pM->data[1] * cn - pM->data[9] * sn;
    pOut->data[2] = pM->data[2] * cn - pM->data[10] * sn;
    pOut->data[3] = pM->data[3] * cn - pM->data[11] * sn;
    pOut->data[4] = pM->data[4];
    pOut->data[5] = pM->data[5];
    pOut->data[6] = pM->data[6];
    pOut->data[7] = pM->data[7];
    pOut->data[8] = pM->data[0] * sn + pM->data[8] * cn;
    pOut->data[9] = pM->data[1] * sn + pM->data[9] * cn;
    pOut->data[10] = pM->data[2] * sn + pM->data[10] * cn;
    pOut->data[11] = pM->data[3] * sn + pM->data[11] * cn;
    pOut->data[12] = pM->data[12];
    pOut->data[13] = pM->data[13];
    pOut->data[14] = pM->data[14];
    pOut->data[15] = pM->data[15];
    return pOut;
}
struct mat4* ldMat4RotateZ(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    pOut->data[0] = pM->data[0] * cn + pM->data[4] * sn;
    pOut->data[1] = pM->data[1] * cn + pM->data[5] * sn;
    pOut->data[2] = pM->data[2] * cn + pM->data[6] * sn;
    pOut->data[3] = pM->data[3] * cn + pM->data[7] * sn;
    pOut->data[4] = pM->data[4] * cn - pM->data[0] * sn;
    pOut->data[5] = pM->data[5] * cn - pM->data[1] * sn;
    pOut->data[6] = pM->data[6] * cn - pM->data[2] * sn;
    pOut->data[7] = pM->data[7] * cn - pM->data[3] * sn;
    pOut->data[8] = pM->data[8];
    pOut->data[9] = pM->data[9];
    pOut->data[10] = pM->data[10];
    pOut->data[11] = pM->data[11];
    pOut->data[12] = pM->data[12];
    pOut->data[13] = pM->data[13];
    pOut->data[14] = pM->data[14];
    pOut->data[15] = pM->data[15];
    return pOut;
}
struct mat4* ldMat4Rotate(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, struct vec3* LD_RESTRICT axis, float32_t radian)
{
    float32_t length = ldVec3Length(axis);

    if (fabsf(length) < 0.0000001f) return NULL;

    length = 1 / length;
    axis->x *= length;
    axis->y *= length;
    axis->z *= length;
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    float32_t theta = 1 - cn;
    float32_t d0 = axis->x * axis->x * theta + cn;
    float32_t d4 = axis->y * axis->y * theta + cn;
    float32_t d8 = axis->z * axis->z * theta + cn;
    float32_t d1 = axis->y * axis->x * theta + axis->z * sn;
    float32_t d2 = axis->z * axis->x * theta - axis->y * sn;
    float32_t d3 = axis->x * axis->y * theta - axis->z * sn;
    float32_t d5 = axis->z * axis->y * theta + axis->x * sn;
    float32_t d6 = axis->x * axis->z * theta + axis->y * sn;
    float32_t d7 = axis->y * axis->z * theta - axis->x * sn;
    pOut->data[0] = pM->data[0] * d0 + pM->data[4] * d1 + pM->data[8] * d2;
    pOut->data[1] = pM->data[1] * d0 + pM->data[5] * d1 + pM->data[9] * d2;
    pOut->data[2] = pM->data[2] * d0 + pM->data[6] * d1 + pM->data[10] * d2;
    pOut->data[3] = pM->data[3] * d0 + pM->data[7] * d1 + pM->data[11] * d2;
    pOut->data[4] = pM->data[0] * d3 + pM->data[4] * d4 + pM->data[8] * d5;
    pOut->data[5] = pM->data[1] * d3 + pM->data[5] * d4 + pM->data[9] * d5;
    pOut->data[6] = pM->data[2] * d3 + pM->data[6] * d4 + pM->data[10] * d5;
    pOut->data[7] = pM->data[3] * d3 + pM->data[7] * d4 + pM->data[11] * d5;
    pOut->data[8] = pM->data[0] * d6 + pM->data[4] * d7 + pM->data[8] * d8;
    pOut->data[9] = pM->data[1] * d6 + pM->data[5] * d7 + pM->data[9] * d8;
    pOut->data[10] = pM->data[2] * d6 + pM->data[6] * d7 + pM->data[10] * d8;
    pOut->data[11] = pM->data[3] * d6 + pM->data[7] * d7 + pM->data[11] * d8;
    pOut->data[12] = pM->data[12];
    pOut->data[13] = pM->data[13];
    pOut->data[14] = pM->data[14];
    pOut->data[15] = pM->data[15];
    return pOut;
}
struct mat4* ldMat4Scale(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, struct vec3* LD_RESTRICT scale)
{
    pOut->data[0] = pM->data[0] * scale->x;
    pOut->data[1] = pM->data[1] * scale->x;
    pOut->data[2] = pM->data[2] * scale->x;
    pOut->data[3] = pM->data[3] * scale->x;
    pOut->data[4] = pM->data[4] * scale->y;
    pOut->data[5] = pM->data[5] * scale->y;
    pOut->data[6] = pM->data[6] * scale->y;
    pOut->data[7] = pM->data[7] * scale->y;
    pOut->data[8] = pM->data[8] * scale->z;
    pOut->data[9] = pM->data[9] * scale->z;
    pOut->data[10] = pM->data[10] * scale->z;
    pOut->data[11] = pM->data[11] * scale->z;
    pOut->data[12] = pM->data[12];
    pOut->data[13] = pM->data[13];
    pOut->data[14] = pM->data[14];
    pOut->data[15] = pM->data[15];
    return pOut;
}
struct mat4* ldMat4Translate(struct mat4* LD_RESTRICT pOut, struct mat4* LD_RESTRICT pM, struct vec3* LD_RESTRICT translate)
{
    pOut->data[0] = pM->data[0];
    pOut->data[1] = pM->data[1];
    pOut->data[2] = pM->data[2];
    pOut->data[3] = pM->data[3];
    pOut->data[4] = pM->data[4];
    pOut->data[5] = pM->data[5];
    pOut->data[6] = pM->data[6];
    pOut->data[7] = pM->data[7];
    pOut->data[8] = pM->data[8];
    pOut->data[9] = pM->data[9];
    pOut->data[10] = pM->data[10];
    pOut->data[11] = pM->data[11];
    pOut->data[12] = pM->data[0] * translate->x + pM->data[4] * translate->y + pM->data[8] * translate->z + pM->data[12];
    pOut->data[13] = pM->data[1] * translate->x + pM->data[5] * translate->y + pM->data[9] * translate->z + pM->data[13];
    pOut->data[14] = pM->data[2] * translate->x + pM->data[6] * translate->y + pM->data[10] * translate->z + pM->data[14];
    pOut->data[15] = pM->data[3] * translate->x + pM->data[7] * translate->y + pM->data[11] * translate->z + pM->data[15];
    return pOut;
}
struct mat4* ldMat4Frustum(struct mat4* LD_RESTRICT pOut, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t frustumNear, float32_t frustumFar)
{
    float32_t rightLeft = 1.0f / (right - left);
    float32_t topBottom = 1.0f / (top - bottom);
    float32_t nearFar = 1.0f / (frustumNear - frustumFar);
    pOut->data[0] = (frustumNear * 2.0f) * rightLeft;
    pOut->data[1] = 0.0f;
    pOut->data[2] = 0.0f;
    pOut->data[3] = 0.0f;
    pOut->data[4] = 0.0f;
    pOut->data[5] = (frustumNear * 2.0f) * topBottom;
    pOut->data[6] = 0.0f;
    pOut->data[7] = 0.0f;
    pOut->data[8] = (right + left) * rightLeft;
    pOut->data[9] = (top + bottom) * topBottom;
    pOut->data[10] = (frustumFar + frustumNear) * nearFar;
    pOut->data[11] = -1.0f;
    pOut->data[12] = 0.0f;
    pOut->data[13] = 0.0f;
    pOut->data[14] = (frustumFar * frustumNear * 2.0f) * nearFar;
    pOut->data[15] = 0.0f;
    return pOut;
}
struct mat4* ldMat4Perspective(struct mat4* LD_RESTRICT pOut, float32_t fovY, float32_t aspect, float32_t perspNear, float32_t perspFar)
{
    float32_t fov = 1.0f / tanf(fovY / 2.0f);
    float32_t nearFar = 1.0f / (perspNear - perspFar);
    pOut->data[0] = fov / aspect;
    pOut->data[1] = 0.0f;
    pOut->data[2] = 0.0f;
    pOut->data[3] = 0.0f;
    pOut->data[4] = 0.0f;
    pOut->data[5] = fov;
    pOut->data[6] = 0.0f;
    pOut->data[7] = 0.0f;
    pOut->data[8] = 0.0f;
    pOut->data[9] = 0.0f;
    pOut->data[10] = (perspFar + perspNear) * nearFar;
    pOut->data[11] = -1.0f;
    pOut->data[12] = 0.0f;
    pOut->data[13] = 0.0f;
    pOut->data[14] = (2.0f * perspFar * perspNear) * nearFar;
    pOut->data[15] = 0.0f;
    return pOut;
}
struct mat4* ldMat4Orthographic(struct mat4* LD_RESTRICT pOut, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t orthoNear, float32_t orthoFar)
{
    float32_t leftRight = 1.0f / (left - right);
    float32_t bottomTop = 1.0f / (bottom - top);
    float32_t nearFar = 1.0f / (orthoNear - orthoFar);
    pOut->data[0] = -2.0f * leftRight;
    pOut->data[1] = 0.0f;
    pOut->data[2] = 0.0f;
    pOut->data[3] = 0.0f;
    pOut->data[4] = 0.0f;
    pOut->data[5] = -2.0f * bottomTop;
    pOut->data[6] = 0.0f;
    pOut->data[7] = 0.0f;
    pOut->data[8] = 0.0f;
    pOut->data[9] = 0.0f;
    pOut->data[10] = 2.0f * nearFar;
    pOut->data[11] = 0.0f;
    pOut->data[12] = (left + right) * leftRight;
    pOut->data[13] = (top + bottom) * bottomTop;
    pOut->data[14] = (orthoFar + orthoNear) * nearFar;
    pOut->data[15] = 1.0f;
    return pOut;
}
struct mat4* ldMat4LookAt(struct mat4* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pEye, struct vec3* LD_RESTRICT pCenter, struct vec3* LD_RESTRICT pUp)
{
    if (fabsf(pEye->x - pCenter->x) < 0.0000001f &&
        fabsf(pEye->y - pCenter->y) < 0.0000001f &&
        fabsf(pEye->z - pCenter->z) < 0.0000001f )
    {
        return ldMat4Ident(pOut);
    }
    float32_t z0 = pEye->x - pCenter->x;
    float32_t z1 = pEye->y - pCenter->y;
    float32_t z2 = pEye->z - pCenter->z;
    float32_t len = 1.0f / sqrtf(z0 * z0 + z1 * z1 + z2 * z2);
    z0 *= len;
    z1 *= len;
    z2 *= len;
    float32_t x0 = pUp->y * z2 - pUp->z * z1;
    float32_t x1 = pUp->z * z0 - pUp->x * z2;
    float32_t x2 = pUp->x * z1 - pUp->y * z0;
    len = sqrtf(x0 * x0 + x1 * x1 + x2 * x2);
    if (!len)
    {
        x0 = 0.0f;
        x1 = 0.0f;
        x2 = 0.0f;
    }
    else
    {
        len = 1.0f / len;
        x0 *= len;
        x1 *= len;
        x2 *= len;
    }
    float32_t y0 = z1 * x2 - z2 * x1;
    float32_t y1 = z2 * x0 - z0 * x2;
    float32_t y2 = z0 * x1 - z1 * x0;
    len = sqrtf(y0 * y0 + y1 * y1 + y2 * y2);
    if (!len)
    {
        y0 = 0.0f;
        y1 = 0.0f;
        y2 = 0.0f;
    }
    else
    {
        len = 1.0f / len;
        y0 *= len;
        y1 *= len;
        y2 *= len;
    }
    pOut->data[0] = x0;
    pOut->data[1] = y0;
    pOut->data[2] = z0;
    pOut->data[3] = 0.0f;
    pOut->data[4] = x1;
    pOut->data[5] = y1;
    pOut->data[6] = z1;
    pOut->data[7] = 0.0f;
    pOut->data[8] = x2;
    pOut->data[9] = y2;
    pOut->data[10] = z2;
    pOut->data[11] = 0.0f;
    pOut->data[12] = -(x0 * pEye->x + x1 * pEye->y + x2 * pEye->z);
    pOut->data[13] = -(y0 * pEye->x + y1 * pEye->y + y2 * pEye->z);
    pOut->data[14] = -(z0 * pEye->x + z1 * pEye->y + z2 * pEye->z);
    pOut->data[15] = 1.0f;
    return pOut;
}

/* vec2 */
struct vec2* ldVec2Add(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    pOut->x = pV0->x + pV1->x;
    pOut->y = pV0->y + pV1->y;
    return pOut;
}
struct vec2* ldVec2Sub(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    pOut->x = pV0->x - pV1->x;
    pOut->y = pV0->y - pV1->y;
    return pOut;
}
struct vec2* ldVec2Mul(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    pOut->x = pV0->x * pV1->x;
    pOut->y = pV0->y * pV1->y;
    return pOut;
}
struct vec2* ldVec2Invert(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV)
{
    pOut->x = 1.0f / pV->x;
    pOut->y = 1.0f / pV->y;
    return pOut;
}
struct vec2* ldVec2Negate(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV)
{
    pOut->x = pV->x * -1.0f;
    pOut->y = pV->y * -1.0f;
    return pOut;
}
struct vec2* ldVec2Normalize(struct vec2* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV)
{
    float32_t l = pV->x * pV->x + pV->y * pV->y;
    if (l > 0.0f)
    {
        l = 1.0f / sqrtf(l);
        pOut->x = pV->x * l;
        pOut->y = pV->y * l;
    }
    return pOut;
}
int32_t ldVec2Equal(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    return (pV0->x == pV1->x && pV0->y == pV1->y);
}
struct vec3* ldVec2Cross(struct vec3* LD_RESTRICT pOut, struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    pOut->x = 0;
    pOut->y = 0;
    pOut->z = pV0->x * pV1->y - pV0->y * pV1->x;
    return pOut;
}
float32_t ldVec2Distance(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    float32_t x = pV0->x - pV1->x;
    float32_t y = pV0->y - pV1->y;
    return sqrtf(x * x + y * y);
}
float32_t ldVec2Dot(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    return pV0->x * pV1->x + pV0->y * pV1->y;
}
float32_t ldVec2Length(struct vec2* LD_RESTRICT pV)
{
    return sqrtf(pV->x * pV->x + pV->y * pV->y);
}
float32_t ldVec2Length2(struct vec2* LD_RESTRICT pV)
{
    return (pV->x * pV->x + pV->y * pV->y);
}
float32_t ldVec2Distance2(struct vec2* LD_RESTRICT pV0, struct vec2* LD_RESTRICT pV1)
{
    float32_t x = pV0->x - pV1->x;
    float32_t y = pV0->y - pV1->y;
    return (x * x + y * y);
}

/* vec3 */
struct vec3* ldVec3Add(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    pOut->x = pV0->x + pV1->x;
    pOut->y = pV0->y + pV1->y;
    pOut->z = pV0->z + pV1->z;
    return pOut;
}
struct vec3* ldVec3Sub(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    pOut->x = pV0->x - pV1->x;
    pOut->y = pV0->y - pV1->y;
    pOut->z = pV0->z - pV1->z;
    return pOut;
}
struct vec3* ldVec3Mul(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    pOut->x = pV0->x * pV1->x;
    pOut->y = pV0->y * pV1->y;
    pOut->z = pV0->z * pV1->z;
    return pOut;
}
struct vec3* ldVec3Invert(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV)
{
    pOut->x = 1.0f / pV->x;
    pOut->y = 1.0f / pV->y;
    pOut->z = 1.0f / pV->z;
    return pOut;
}
struct vec3* ldVec3Negate(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV)
{
    pOut->x = -1.0f * pV->x;
    pOut->y = -1.0f * pV->y;
    pOut->z = -1.0f * pV->z;
    return pOut;
}
struct vec3* ldVec3Normalize(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV)
{
    float32_t x = pV->x;
    float32_t y = pV->y;
    float32_t z = pV->z;
    float32_t l = x * x + y * y + z * z;
    if (l > 0.0f)
    {
        l = 1.0f / sqrtf(l);
        pOut->x = x * l;
        pOut->y = y * l;
        pOut->z = z * l;
    }
    return pOut;
}
int32_t ldVec3Equal(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    return (pV0->x == pV1->x && pV0->y == pV1->y && pV0->z == pV1->z);
}
struct vec3* ldVec3Cross(struct vec3* LD_RESTRICT pOut, struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    float32_t lx = pV0->x;
    float32_t ly = pV0->y;
    float32_t lz = pV0->z;
    float32_t rx = pV1->x;
    float32_t ry = pV1->y;
    float32_t rz = pV1->z;

    pOut->x = ly * rz - lz * ry;
    pOut->y = lz * rx - lx * rz;
    pOut->z = lx * ry - ly * rx;

    return pOut;
}
float32_t ldVec3Distance(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    float32_t x = pV0->x - pV1->x;
    float32_t y = pV0->y - pV1->y;
    float32_t z = pV0->z - pV1->z;

    return sqrtf(x * x + y * y + z * z);
}
float32_t ldVec3Dot(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    return pV0->x * pV1->x + pV0->y * pV1->y + pV0->z * pV1->z;
}
float32_t ldVec3Length(struct vec3* LD_RESTRICT pV)
{
    float32_t x = pV->x;
    float32_t y = pV->y;
    float32_t z = pV->z;
    return sqrtf(x * x + y * y + z * z);
}
float32_t ldVec3Length2(struct vec3* LD_RESTRICT pV)
{
    float32_t x = pV->x;
    float32_t y = pV->y;
    float32_t z = pV->z;
    return (x * x + y * y + z * z);
}
float32_t ldVec3Distance2(struct vec3* LD_RESTRICT pV0, struct vec3* LD_RESTRICT pV1)
{
    float32_t x = pV0->x - pV1->x;
    float32_t y = pV0->y - pV1->y;
    float32_t z = pV0->z - pV1->z;

    return (x * x + y * y + z * z);
}

/* quat */
struct quat* ldQuatIdent(struct quat* LD_RESTRICT pOut)
{
    pOut->x = 0;
    pOut->y = 0;
    pOut->z = 0;
    pOut->w = 1;
    return pOut;
}
struct quat* ldQuatAdd(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ0, struct quat* LD_RESTRICT pQ1)
{
    pOut->w = pQ0->w + pQ1->w;
    pOut->x = pQ0->x + pQ1->x;
    pOut->y = pQ0->y + pQ1->y;
    pOut->z = pQ0->z + pQ1->z;
    return pOut;
}
struct quat* ldQuatMul(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ0, struct quat* LD_RESTRICT pQ1)
{
    pOut->x = pQ0->x * pQ1->w + pQ0->w * pQ1->x + pQ0->y * pQ1->z - pQ0->z * pQ1->y;
    pOut->y = pQ0->y * pQ1->w + pQ0->w * pQ1->y + pQ0->z * pQ1->x - pQ0->x * pQ1->z;
    pOut->z = pQ0->z * pQ1->w + pQ0->w * pQ1->z + pQ0->x * pQ1->y - pQ0->y * pQ1->x;
    pOut->w = pQ0->w * pQ1->w - pQ0->x * pQ1->x - pQ0->y * pQ1->y - pQ0->z * pQ1->z;
    return pOut;
}
struct quat* ldQuatSetAxisAngle(struct quat* LD_RESTRICT pOut, struct vec3* LD_RESTRICT axis, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    pOut->x = sn * axis->x;
    pOut->y = sn * axis->y;
    pOut->z = sn * axis->z;
    pOut->w = cosf(radian * 0.5f);
    return pOut;
}
struct quat* ldQuatRotateX(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    pOut->x = pQ->x * sn + pQ->w * cn;
    pOut->y = pQ->y * sn + pQ->z * cn;
    pOut->z = pQ->z * sn - pQ->y * cn;
    pOut->w = pQ->w * sn - pQ->x * cn;
    return pOut;
}
struct quat* ldQuatRotateY(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    pOut->x = pQ->x * cn - pQ->z * sn;
    pOut->y = pQ->y * cn + pQ->w * sn;
    pOut->z = pQ->z * cn + pQ->x * sn;
    pOut->w = pQ->w * cn - pQ->y * sn;
    return pOut;
}
struct quat* ldQuatRotateZ(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    pOut->x = pQ->x * cn + pQ->y * sn;
    pOut->y = pQ->y * cn - pQ->x * sn;
    pOut->z = pQ->z * cn + pQ->w * sn;
    pOut->w = pQ->w * cn - pQ->z * sn;
    return pOut;
}
struct quat* ldQuatCalcW(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ)
{
    pOut->x = pQ->x;
    pOut->y = pQ->y;
    pOut->z = pQ->z;
    pOut->w = sqrtf(fabsf(1.0f - pQ->x * pQ->x - pQ->y * pQ->y - pQ->z * pQ->z));
    return pOut;
}
struct quat* ldQuatInvert(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ)
{
    float32_t dot = pQ->x * pQ->x + pQ->y * pQ->y + pQ->z * pQ->z + pQ->w * pQ->w;
    if (dot) dot = 1.0f / dot;
    pOut->x = -pQ->x * dot;
    pOut->y = -pQ->y * dot;
    pOut->z = -pQ->z * dot;
    pOut->w = pQ->w * dot;
    return pOut;
}
struct quat* ldQuatConjugate(struct quat* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ)
{
    pOut->x = -pQ->x;
    pOut->y = -pQ->y;
    pOut->z = -pQ->z;
    pOut->w = pQ->w;
    return pOut;
}
struct mat4* ldQuatToMat4(struct mat4* LD_RESTRICT pOut, struct quat* LD_RESTRICT pQ)
{
    float32_t x2 = pQ->x + pQ->x;
    float32_t y2 = pQ->y + pQ->y;
    float32_t z2 = pQ->z + pQ->z;
    float32_t xx = pQ->x * x2;
    float32_t yx = pQ->y * x2;
    float32_t yy = pQ->y * y2;
    float32_t zx = pQ->z * x2;
    float32_t zy = pQ->z * y2;
    float32_t zz = pQ->z * z2;
    float32_t wx = pQ->w * x2;
    float32_t wy = pQ->w * y2;
    float32_t wz = pQ->w * z2;

    pOut->data[0] = 1.0f - yy - zz;
    pOut->data[1] = yx + wz;
    pOut->data[2] = zx - wy;
    pOut->data[3] = 0.0f;
    pOut->data[4] = yx - wz;
    pOut->data[5] = 1.0f - xx - zz;
    pOut->data[6] = zy + wx;
    pOut->data[7] = 0.0f;
    pOut->data[8] = zx + wy;
    pOut->data[9] = zy - wx;
    pOut->data[10] = 1.0f - xx - yy;
    pOut->data[11] = 0.0f;
    pOut->data[12] = 0.0f;
    pOut->data[13] = 0.0f;
    pOut->data[14] = 0.0f;
    pOut->data[15] = 1.0f;
    return pOut;
}
float32_t ldQuatGetAxisAngle(struct vec3* LD_RESTRICT pOutAxis, struct quat* LD_RESTRICT pQ)
{
    float32_t radian = acosf(pQ->w) * 2.0f;
    float32_t sn = sinf(radian * 0.5f);
    if (sn != 0.0f)
    {
        pOutAxis->x = pQ->x / sn;
        pOutAxis->y = pQ->y / sn;
        pOutAxis->z = pQ->z / sn;
    }
    else
    {
        pOutAxis->x = 1.0f;
        pOutAxis->y = 0.0f;
        pOutAxis->z = 0.0f;
    }
    return radian;
}

#endif // !_MATH_H_
