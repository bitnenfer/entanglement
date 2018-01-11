#ifndef _MATH_H_
#define _MATH_H_

#include "types.h"
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
            float32_t p_m, n, o, p;
        };
        float32_t data[16];
    };
};

/* mat2d */
struct mat2d* mat2d_identity(struct mat2d* p_out);
struct mat2d* mat2d_mul(struct mat2d* p_out, struct mat2d* p_m0, struct mat2d* p_m1);
struct vec2* mat2d_vec2_mul(struct vec2* p_out, struct mat2d* p_m0, struct vec2* p_v1);
struct mat2d* mat2d_translate(struct mat2d* p_out, struct mat2d* p_m, float32_t x, float32_t y);
struct mat2d* mat2d_scale(struct mat2d* p_out, struct mat2d* p_m, float32_t x, float32_t y);
struct mat2d* mat2d_rotate(struct mat2d* p_out, struct mat2d* p_m, float32_t radian);

/* mat4 */
struct mat4* mat4_identity(struct mat4* p_out);
struct mat4* mat4_mul(struct mat4* p_out, struct mat4* p_m0, struct mat4* p_m1);
struct vec3* mat4_vec3_mul(struct vec3* p_out, struct mat4* p_m0, struct vec3* p_v1);
struct mat4* mat4_transpose(struct mat4* p_out, struct mat4* p_m);
struct mat4* mat4_invert(struct mat4* p_out, struct mat4* p_m);
struct mat4* mat4_rotate_x(struct mat4* p_out, struct mat4* p_m, float32_t radian);
struct mat4* mat4_rotate_y(struct mat4* p_out, struct mat4* p_m, float32_t radian);
struct mat4* mat4_rotate_z(struct mat4* p_out, struct mat4* p_m, float32_t radian);
struct mat4* mat4_rotate(struct mat4* p_out, struct mat4* p_m, struct vec3* p_axis, float32_t radian);
struct mat4* mat4_scale(struct mat4* p_out, struct mat4* p_m, struct vec3* p_scale);
struct mat4* mat4_translate(struct mat4* p_out, struct mat4* p_m, struct vec3* p_translate);
struct mat4* mat4_frustum(struct mat4* p_out, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t frustum_near, float32_t frustum_far);
struct mat4* mat4_perspective(struct mat4* p_out, float32_t fov_y, float32_t aspect, float32_t persp_near, float32_t persp_far);
struct mat4* mat4_ortho(struct mat4* p_out, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t ortho_near, float32_t ortho_far);
struct mat4* mat4_look_at(struct mat4* p_out, struct vec3* p_eye, struct vec3* p_center, struct vec3* p_up);

/* vec2 */
struct vec2* vec2_add(struct vec2* p_out, struct vec2* p_v0, struct vec2* p_v1);
struct vec2* vec2_sub(struct vec2* p_out, struct vec2* p_v0, struct vec2* p_v1);
struct vec2* vec2_mul(struct vec2* p_out, struct vec2* p_v0, struct vec2* p_v1);
struct vec2* vec2_invert(struct vec2* p_out, struct vec2* p_v);
struct vec2* vec2_negate(struct vec2* p_out, struct vec2* p_v);
struct vec2* vec2_normalize(struct vec2* p_out, struct vec2* p_v);
int32_t vec2_equal(struct vec2* p_v0, struct vec2* p_v1);
struct vec3* vec2_cross(struct vec3* p_out, struct vec2* p_v0, struct vec2* p_v1);
float32_t vec2_distance(struct vec2* p_v0, struct vec2* p_v1);
float32_t vec2_dot(struct vec2* p_v0, struct vec2* p_v1);
float32_t vec2_length(struct vec2* p_v);
float32_t vec2_length2(struct vec2* p_v);
float32_t vec2_distance2(struct vec2* p_v0, struct vec2* p_v1);

/* vec3 */
struct vec3* vec3_add(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1);
struct vec3* vec3_sub(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1);
struct vec3* vec3_mul(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1);
struct vec3* vec3_invert(struct vec3* p_out, struct vec3* p_v);
struct vec3* vec3_negate(struct vec3* p_out, struct vec3* p_v);
struct vec3* vec3_normalize(struct vec3* p_out, struct vec3* p_v);
int32_t vec3_equal(struct vec3* p_v0, struct vec3* p_v1);
struct vec3* vec3_cross(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1);
float32_t vec3_distance(struct vec3* p_v0, struct vec3* p_v1);
float32_t vec3_dot(struct vec3* p_v0, struct vec3* p_v1);
float32_t vec3_length(struct vec3* p_v);
float32_t vec3_length2(struct vec3* p_v);
float32_t vec3_distance2(struct vec3* p_v0, struct vec3* p_v1);

/* quat */
struct quat* quat_identity(struct quat* p_out);
struct quat* quat_add(struct quat* p_out, struct quat* p_q0, struct quat* p_q1);
struct quat* quat_mul(struct quat* p_out, struct quat* p_q0, struct quat* p_q1);
struct quat* quat_set_axis_angle(struct quat* p_out, struct vec3* p_axis, float32_t radian);
struct quat* quat_rotate_x(struct quat* p_out, struct quat* p_q, float32_t radian);
struct quat* quat_rotate_y(struct quat* p_out, struct quat* p_q, float32_t radian);
struct quat* quat_rotate_z(struct quat* p_out, struct quat* p_q, float32_t radian);
struct quat* quat_calcw(struct quat* p_out, struct quat* p_q);
struct quat* quat_invert(struct quat* p_out, struct quat* p_q);
struct quat* quat_conjugate(struct quat* p_out, struct quat* p_q);
struct mat4* quat_to_mat4(struct mat4* p_out, struct quat* p_q);
float32_t quat_get_axis_angle(struct vec3* p_out_axis, struct quat* p_q);

/* Definition */
typedef struct quat quat_t;
typedef struct vec2 vec2_t;
typedef struct vec3 vec3_t;
typedef struct mat2d mat2d_t;
typedef struct mat4 mat4_t;

/* mat2d */
struct mat2d* mat2d_identity(struct mat2d* p_out)
{
    p_out->data[0] = 1.0f;
    p_out->data[1] = 0.0f;
    p_out->data[2] = 0.0f;
    p_out->data[3] = 1.0f;
    p_out->data[4] = 0.0f;
    p_out->data[5] = 0.0f;
    return p_out;
}
struct mat2d* mat2d_mul(struct mat2d* p_out, struct mat2d* p_m0, struct mat2d* p_m1)
{
    const float32_t* matrix_a = p_m0->data;
    const float32_t* matrix_b = p_m1->data;
    float32_t* matrix = p_out->data;

    float32_t a = matrix_a[0];
    float32_t b = matrix_a[1];
    float32_t c = matrix_a[2];
    float32_t d = matrix_a[3];
    float32_t tx = matrix_a[4];
    float32_t ty = matrix_a[5];

    float32_t a0 = matrix_b[0];
    float32_t b0 = matrix_b[1];
    float32_t c0 = matrix_b[2];
    float32_t d0 = matrix_b[3];
    float32_t tx0 = matrix_b[4];
    float32_t ty0 = matrix_b[5];

    matrix[0] = a * a0 + b * c0;
    matrix[1] = a * b0 + b * d0;
    matrix[2] = c * a0 + d * c0;
    matrix[3] = c * b0 + d * d0;
    matrix[4] = tx * a0 + ty * c0 + tx0;
    matrix[5] = tx * b0 + ty * d0 + ty0;

    return p_out;
}
struct vec2* mat2d_vec2_mul(struct vec2* p_out, struct mat2d* p_m0, struct vec2* p_v1)
{
    p_out->x = p_v1->x * p_m0->a + p_v1->y * p_m0->c + p_m0->tx;
    p_out->y = p_v1->x * p_m0->b + p_v1->y * p_m0->d + p_m0->ty;
    return p_out;
}
struct mat2d* mat2d_translate(struct mat2d* p_out, struct mat2d* p_m, float32_t x, float32_t y)
{
    p_out->data[4] = p_m->data[0] * x + p_m->data[2] * y + p_m->data[4];
    p_out->data[5] = p_m->data[1] * x + p_m->data[3] * y + p_m->data[5];
    return p_out;
}
struct mat2d* mat2d_scale(struct mat2d* p_out, struct mat2d* p_m, float32_t x, float32_t y)
{
    p_out->data[0] = p_m->data[0] * x;
    p_out->data[1] = p_m->data[1] * x;
    p_out->data[2] = p_m->data[2] * y;
    p_out->data[3] = p_m->data[3] * y;
    return p_out;
}
struct mat2d* mat2d_rotate(struct mat2d* p_out, struct mat2d* p_m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cs = cosf(radian);
    p_out->data[0] = cs * p_m->data[0] + -sn * p_m->data[2];
    p_out->data[1] = cs * p_m->data[1] + -sn * p_m->data[3];
    p_out->data[2] = sn * p_m->data[0] + cs * p_m->data[2];
    p_out->data[3] = sn * p_m->data[1] + cs * p_m->data[3];
    return p_out;
}

/* mat4 */
struct mat4* mat4_identity(struct mat4* p_out)
{
    p_out->data[0] = 1.0f;
    p_out->data[1] = 0.0f;
    p_out->data[2] = 0.0f;
    p_out->data[3] = 0.0f;
    p_out->data[4] = 0.0f;
    p_out->data[5] = 1.0f;
    p_out->data[6] = 0.0f;
    p_out->data[7] = 0.0f;
    p_out->data[8] = 0.0f;
    p_out->data[9] = 0.0f;
    p_out->data[10] = 1.0f;
    p_out->data[11] = 0.0f;
    p_out->data[12] = 0.0f;
    p_out->data[13] = 0.0f;
    p_out->data[14] = 0.0f;
    p_out->data[15] = 1.0f;
    return p_out;
}
struct mat4* mat4_mul(struct mat4* p_out, struct mat4* p_m0, struct mat4* p_m1)
{
    p_out->data[0] = p_m1->data[0] * p_m0->data[0] + p_m1->data[1] * p_m0->data[4] + p_m1->data[2] * p_m0->data[8] + p_m1->data[3] * p_m0->data[12];
    p_out->data[1] = p_m1->data[0] * p_m0->data[1] + p_m1->data[1] * p_m0->data[5] + p_m1->data[2] * p_m0->data[9] + p_m1->data[3] * p_m0->data[13];
    p_out->data[2] = p_m1->data[0] * p_m0->data[2] + p_m1->data[1] * p_m0->data[6] + p_m1->data[2] * p_m0->data[10] + p_m1->data[3] * p_m0->data[14];
    p_out->data[3] = p_m1->data[0] * p_m0->data[3] + p_m1->data[1] * p_m0->data[7] + p_m1->data[2] * p_m0->data[11] + p_m1->data[3] * p_m0->data[15];
    p_out->data[4] = p_m1->data[4] * p_m0->data[0] + p_m1->data[5] * p_m0->data[4] + p_m1->data[6] * p_m0->data[8] + p_m1->data[7] * p_m0->data[12];
    p_out->data[5] = p_m1->data[4] * p_m0->data[1] + p_m1->data[5] * p_m0->data[5] + p_m1->data[6] * p_m0->data[9] + p_m1->data[7] * p_m0->data[13];
    p_out->data[6] = p_m1->data[4] * p_m0->data[2] + p_m1->data[5] * p_m0->data[6] + p_m1->data[6] * p_m0->data[10] + p_m1->data[7] * p_m0->data[14];
    p_out->data[7] = p_m1->data[4] * p_m0->data[3] + p_m1->data[5] * p_m0->data[7] + p_m1->data[6] * p_m0->data[11] + p_m1->data[7] * p_m0->data[15];
    p_out->data[8] = p_m1->data[8] * p_m0->data[0] + p_m1->data[9] * p_m0->data[4] + p_m1->data[10] * p_m0->data[8] + p_m1->data[11] * p_m0->data[12];
    p_out->data[9] = p_m1->data[8] * p_m0->data[1] + p_m1->data[9] * p_m0->data[5] + p_m1->data[10] * p_m0->data[9] + p_m1->data[11] * p_m0->data[13];
    p_out->data[10] = p_m1->data[8] * p_m0->data[2] + p_m1->data[9] * p_m0->data[6] + p_m1->data[10] * p_m0->data[10] + p_m1->data[11] * p_m0->data[14];
    p_out->data[11] = p_m1->data[8] * p_m0->data[3] + p_m1->data[9] * p_m0->data[7] + p_m1->data[10] * p_m0->data[11] + p_m1->data[11] * p_m0->data[15];
    p_out->data[12] = p_m1->data[12] * p_m0->data[0] + p_m1->data[13] * p_m0->data[4] + p_m1->data[14] * p_m0->data[8] + p_m1->data[15] * p_m0->data[12];
    p_out->data[13] = p_m1->data[12] * p_m0->data[1] + p_m1->data[13] * p_m0->data[5] + p_m1->data[14] * p_m0->data[9] + p_m1->data[15] * p_m0->data[13];
    p_out->data[14] = p_m1->data[12] * p_m0->data[2] + p_m1->data[13] * p_m0->data[6] + p_m1->data[14] * p_m0->data[10] + p_m1->data[15] * p_m0->data[14];
    p_out->data[15] = p_m1->data[12] * p_m0->data[3] + p_m1->data[13] * p_m0->data[7] + p_m1->data[14] * p_m0->data[11] + p_m1->data[15] * p_m0->data[15];
    return p_out;
}
struct vec3* mat4_vec3_mul(struct vec3* p_out, struct mat4* p_m0, struct vec3* p_v1)
{
    p_out->x = p_m0->data[0] * p_v1->x + p_m0->data[4] * p_v1->y + p_m0->data[8] * p_v1->z + p_m0->data[12];
    p_out->y = p_m0->data[1] * p_v1->x + p_m0->data[5] * p_v1->y + p_m0->data[9] * p_v1->z + p_m0->data[13];
    p_out->z = p_m0->data[2] * p_v1->x + p_m0->data[6] * p_v1->y + p_m0->data[10] * p_v1->z + p_m0->data[14];
    return p_out;
}
struct mat4* mat4_transpose(struct mat4* p_out, struct mat4* p_m)
{
    p_out->data[0] = p_m->data[0];
    p_out->data[1] = p_m->data[4];
    p_out->data[2] = p_m->data[8];
    p_out->data[3] = p_m->data[12];
    p_out->data[4] = p_m->data[1];
    p_out->data[5] = p_m->data[5];
    p_out->data[6] = p_m->data[9];
    p_out->data[7] = p_m->data[13];
    p_out->data[8] = p_m->data[2];
    p_out->data[9] = p_m->data[6];
    p_out->data[10] = p_m->data[10];
    p_out->data[11] = p_m->data[14];
    p_out->data[12] = p_m->data[3];
    p_out->data[13] = p_m->data[7];
    p_out->data[14] = p_m->data[11];
    p_out->data[15] = p_m->data[15];
    return p_out;
}
struct mat4* mat4_invert(struct mat4* p_out, struct mat4* p_m)
{
    float32_t d0 = p_m->data[0] * p_m->data[5] - p_m->data[1] * p_m->data[4];
    float32_t d1 = p_m->data[0] * p_m->data[6] - p_m->data[2] * p_m->data[4];
    float32_t d2 = p_m->data[0] * p_m->data[7] - p_m->data[3] * p_m->data[4];
    float32_t d3 = p_m->data[1] * p_m->data[6] - p_m->data[2] * p_m->data[5];
    float32_t d4 = p_m->data[1] * p_m->data[7] - p_m->data[3] * p_m->data[5];
    float32_t d5 = p_m->data[2] * p_m->data[7] - p_m->data[3] * p_m->data[6];
    float32_t d6 = p_m->data[8] * p_m->data[13] - p_m->data[9] * p_m->data[12];
    float32_t d7 = p_m->data[8] * p_m->data[14] - p_m->data[10] * p_m->data[12];
    float32_t d8 = p_m->data[8] * p_m->data[15] - p_m->data[11] * p_m->data[12];
    float32_t d9 = p_m->data[9] * p_m->data[14] - p_m->data[10] * p_m->data[13];
    float32_t d10 = p_m->data[9] * p_m->data[15] - p_m->data[11] * p_m->data[13];
    float32_t d11 = p_m->data[10] * p_m->data[15] - p_m->data[11] * p_m->data[14];
    float32_t determinant = d0 * d11 - d1 * d10 + d2 * d9 + d3 * d8 - d4 * d7 + d5 * d6;

    if (determinant == 0.0f) return p_m;

    determinant = 1.0f / determinant;
    p_out->data[0] = (p_m->data[5] * d11 - p_m->data[6] * d10 + p_m->data[7] * d9) * determinant;
    p_out->data[1] = (p_m->data[2] * d10 - p_m->data[1] * d11 - p_m->data[3] * d9) * determinant;
    p_out->data[2] = (p_m->data[13] * d5 - p_m->data[14] * d4 + p_m->data[15] * d3) * determinant;
    p_out->data[3] = (p_m->data[10] * d4 - p_m->data[9] * d5 - p_m->data[11] * d3) * determinant;
    p_out->data[4] = (p_m->data[6] * d8 - p_m->data[4] * d11 - p_m->data[7] * d7) * determinant;
    p_out->data[5] = (p_m->data[0] * d11 - p_m->data[2] * d8 + p_m->data[3] * d7) * determinant;
    p_out->data[6] = (p_m->data[14] * d2 - p_m->data[12] * d5 - p_m->data[15] * d1) * determinant;
    p_out->data[7] = (p_m->data[8] * d5 - p_m->data[10] * d2 + p_m->data[11] * d1) * determinant;
    p_out->data[8] = (p_m->data[4] * d10 - p_m->data[5] * d8 + p_m->data[7] * d6) * determinant;
    p_out->data[9] = (p_m->data[1] * d8 - p_m->data[0] * d10 - p_m->data[3] * d6) * determinant;
    p_out->data[10] = (p_m->data[12] * d4 - p_m->data[13] * d2 + p_m->data[15] * d0) * determinant;
    p_out->data[11] = (p_m->data[9] * d2 - p_m->data[8] * d4 - p_m->data[11] * d0) * determinant;
    p_out->data[12] = (p_m->data[5] * d7 - p_m->data[4] * d9 - p_m->data[6] * d6) * determinant;
    p_out->data[13] = (p_m->data[0] * d9 - p_m->data[1] * d7 + p_m->data[2] * d6) * determinant;
    p_out->data[14] = (p_m->data[13] * d1 - p_m->data[12] * d3 - p_m->data[14] * d0) * determinant;
    p_out->data[15] = (p_m->data[8] * d3 - p_m->data[9] * d1 + p_m->data[10] * d0) * determinant;
    return p_out;
}
struct mat4* mat4_rotate_x(struct mat4* p_out, struct mat4* p_m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    p_out->data[0] = p_m->data[0];
    p_out->data[1] = p_m->data[1];
    p_out->data[2] = p_m->data[2];
    p_out->data[3] = p_m->data[3];
    p_out->data[12] = p_m->data[12];
    p_out->data[13] = p_m->data[13];
    p_out->data[14] = p_m->data[14];
    p_out->data[15] = p_m->data[15];
    p_out->data[4] = p_m->data[4] * cn + p_m->data[8] * sn;
    p_out->data[5] = p_m->data[5] * cn + p_m->data[9] * sn;
    p_out->data[6] = p_m->data[6] * cn + p_m->data[10] * sn;
    p_out->data[7] = p_m->data[7] * cn + p_m->data[11] * sn;
    p_out->data[8] = p_m->data[8] * cn - p_m->data[4] * sn;
    p_out->data[9] = p_m->data[9] * cn - p_m->data[5] * sn;
    p_out->data[10] = p_m->data[10] * cn - p_m->data[6] * sn;
    p_out->data[11] = p_m->data[11] * cn - p_m->data[7] * sn;
    return p_out;
}
struct mat4* mat4_rotate_y(struct mat4* p_out, struct mat4* p_m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    p_out->data[0] = p_m->data[0] * cn - p_m->data[8] * sn;
    p_out->data[1] = p_m->data[1] * cn - p_m->data[9] * sn;
    p_out->data[2] = p_m->data[2] * cn - p_m->data[10] * sn;
    p_out->data[3] = p_m->data[3] * cn - p_m->data[11] * sn;
    p_out->data[4] = p_m->data[4];
    p_out->data[5] = p_m->data[5];
    p_out->data[6] = p_m->data[6];
    p_out->data[7] = p_m->data[7];
    p_out->data[8] = p_m->data[0] * sn + p_m->data[8] * cn;
    p_out->data[9] = p_m->data[1] * sn + p_m->data[9] * cn;
    p_out->data[10] = p_m->data[2] * sn + p_m->data[10] * cn;
    p_out->data[11] = p_m->data[3] * sn + p_m->data[11] * cn;
    p_out->data[12] = p_m->data[12];
    p_out->data[13] = p_m->data[13];
    p_out->data[14] = p_m->data[14];
    p_out->data[15] = p_m->data[15];
    return p_out;
}
struct mat4* mat4_rotate_z(struct mat4* p_out, struct mat4* p_m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    p_out->data[0] = p_m->data[0] * cn + p_m->data[4] * sn;
    p_out->data[1] = p_m->data[1] * cn + p_m->data[5] * sn;
    p_out->data[2] = p_m->data[2] * cn + p_m->data[6] * sn;
    p_out->data[3] = p_m->data[3] * cn + p_m->data[7] * sn;
    p_out->data[4] = p_m->data[4] * cn - p_m->data[0] * sn;
    p_out->data[5] = p_m->data[5] * cn - p_m->data[1] * sn;
    p_out->data[6] = p_m->data[6] * cn - p_m->data[2] * sn;
    p_out->data[7] = p_m->data[7] * cn - p_m->data[3] * sn;
    p_out->data[8] = p_m->data[8];
    p_out->data[9] = p_m->data[9];
    p_out->data[10] = p_m->data[10];
    p_out->data[11] = p_m->data[11];
    p_out->data[12] = p_m->data[12];
    p_out->data[13] = p_m->data[13];
    p_out->data[14] = p_m->data[14];
    p_out->data[15] = p_m->data[15];
    return p_out;
}
struct mat4* mat4_rotate(struct mat4* p_out, struct mat4* p_m, struct vec3* axis, float32_t radian)
{
    float32_t length = vec3_length(axis);

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
    p_out->data[0] = p_m->data[0] * d0 + p_m->data[4] * d1 + p_m->data[8] * d2;
    p_out->data[1] = p_m->data[1] * d0 + p_m->data[5] * d1 + p_m->data[9] * d2;
    p_out->data[2] = p_m->data[2] * d0 + p_m->data[6] * d1 + p_m->data[10] * d2;
    p_out->data[3] = p_m->data[3] * d0 + p_m->data[7] * d1 + p_m->data[11] * d2;
    p_out->data[4] = p_m->data[0] * d3 + p_m->data[4] * d4 + p_m->data[8] * d5;
    p_out->data[5] = p_m->data[1] * d3 + p_m->data[5] * d4 + p_m->data[9] * d5;
    p_out->data[6] = p_m->data[2] * d3 + p_m->data[6] * d4 + p_m->data[10] * d5;
    p_out->data[7] = p_m->data[3] * d3 + p_m->data[7] * d4 + p_m->data[11] * d5;
    p_out->data[8] = p_m->data[0] * d6 + p_m->data[4] * d7 + p_m->data[8] * d8;
    p_out->data[9] = p_m->data[1] * d6 + p_m->data[5] * d7 + p_m->data[9] * d8;
    p_out->data[10] = p_m->data[2] * d6 + p_m->data[6] * d7 + p_m->data[10] * d8;
    p_out->data[11] = p_m->data[3] * d6 + p_m->data[7] * d7 + p_m->data[11] * d8;
    p_out->data[12] = p_m->data[12];
    p_out->data[13] = p_m->data[13];
    p_out->data[14] = p_m->data[14];
    p_out->data[15] = p_m->data[15];
    return p_out;
}
struct mat4* mat4_scale(struct mat4* p_out, struct mat4* p_m, struct vec3* scale)
{
    p_out->data[0] = p_m->data[0] * scale->x;
    p_out->data[1] = p_m->data[1] * scale->x;
    p_out->data[2] = p_m->data[2] * scale->x;
    p_out->data[3] = p_m->data[3] * scale->x;
    p_out->data[4] = p_m->data[4] * scale->y;
    p_out->data[5] = p_m->data[5] * scale->y;
    p_out->data[6] = p_m->data[6] * scale->y;
    p_out->data[7] = p_m->data[7] * scale->y;
    p_out->data[8] = p_m->data[8] * scale->z;
    p_out->data[9] = p_m->data[9] * scale->z;
    p_out->data[10] = p_m->data[10] * scale->z;
    p_out->data[11] = p_m->data[11] * scale->z;
    p_out->data[12] = p_m->data[12];
    p_out->data[13] = p_m->data[13];
    p_out->data[14] = p_m->data[14];
    p_out->data[15] = p_m->data[15];
    return p_out;
}
struct mat4* mat4_translate(struct mat4* p_out, struct mat4* p_m, struct vec3* translate)
{
    p_out->data[0] = p_m->data[0];
    p_out->data[1] = p_m->data[1];
    p_out->data[2] = p_m->data[2];
    p_out->data[3] = p_m->data[3];
    p_out->data[4] = p_m->data[4];
    p_out->data[5] = p_m->data[5];
    p_out->data[6] = p_m->data[6];
    p_out->data[7] = p_m->data[7];
    p_out->data[8] = p_m->data[8];
    p_out->data[9] = p_m->data[9];
    p_out->data[10] = p_m->data[10];
    p_out->data[11] = p_m->data[11];
    p_out->data[12] = p_m->data[0] * translate->x + p_m->data[4] * translate->y + p_m->data[8] * translate->z + p_m->data[12];
    p_out->data[13] = p_m->data[1] * translate->x + p_m->data[5] * translate->y + p_m->data[9] * translate->z + p_m->data[13];
    p_out->data[14] = p_m->data[2] * translate->x + p_m->data[6] * translate->y + p_m->data[10] * translate->z + p_m->data[14];
    p_out->data[15] = p_m->data[3] * translate->x + p_m->data[7] * translate->y + p_m->data[11] * translate->z + p_m->data[15];
    return p_out;
}
struct mat4* mat4_frustum(struct mat4* p_out, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t frustum_near, float32_t frustum_far)
{
    float32_t right_left = 1.0f / (right - left);
    float32_t top_bottom = 1.0f / (top - bottom);
    float32_t near_far = 1.0f / (frustum_near - frustum_far);
    p_out->data[0] = (frustum_near * 2.0f) * right_left;
    p_out->data[1] = 0.0f;
    p_out->data[2] = 0.0f;
    p_out->data[3] = 0.0f;
    p_out->data[4] = 0.0f;
    p_out->data[5] = (frustum_near * 2.0f) * top_bottom;
    p_out->data[6] = 0.0f;
    p_out->data[7] = 0.0f;
    p_out->data[8] = (right + left) * right_left;
    p_out->data[9] = (top + bottom) * top_bottom;
    p_out->data[10] = (frustum_far + frustum_near) * near_far;
    p_out->data[11] = -1.0f;
    p_out->data[12] = 0.0f;
    p_out->data[13] = 0.0f;
    p_out->data[14] = (frustum_far * frustum_near * 2.0f) * near_far;
    p_out->data[15] = 0.0f;
    return p_out;
}
struct mat4* mat4_perspective(struct mat4* p_out, float32_t fov_y, float32_t aspect, float32_t persp_near, float32_t persp_far)
{
    float32_t fov = 1.0f / tanf(fov_y / 2.0f);
    float32_t near_far = 1.0f / (persp_near - persp_far);
    p_out->data[0] = fov / aspect;
    p_out->data[1] = 0.0f;
    p_out->data[2] = 0.0f;
    p_out->data[3] = 0.0f;
    p_out->data[4] = 0.0f;
    p_out->data[5] = fov;
    p_out->data[6] = 0.0f;
    p_out->data[7] = 0.0f;
    p_out->data[8] = 0.0f;
    p_out->data[9] = 0.0f;
    p_out->data[10] = (persp_far + persp_near) * near_far;
    p_out->data[11] = -1.0f;
    p_out->data[12] = 0.0f;
    p_out->data[13] = 0.0f;
    p_out->data[14] = (2.0f * persp_far * persp_near) * near_far;
    p_out->data[15] = 0.0f;
    return p_out;
}
struct mat4* mat4_ortho(struct mat4* p_out, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t ortho_near, float32_t ortho_far)
{
    float32_t left_right = 1.0f / (left - right);
    float32_t bottom_top = 1.0f / (bottom - top);
    float32_t near_far = 1.0f / (ortho_near - ortho_far);
    p_out->data[0] = -2.0f * left_right;
    p_out->data[1] = 0.0f;
    p_out->data[2] = 0.0f;
    p_out->data[3] = 0.0f;
    p_out->data[4] = 0.0f;
    p_out->data[5] = -2.0f * bottom_top;
    p_out->data[6] = 0.0f;
    p_out->data[7] = 0.0f;
    p_out->data[8] = 0.0f;
    p_out->data[9] = 0.0f;
    p_out->data[10] = 2.0f * near_far;
    p_out->data[11] = 0.0f;
    p_out->data[12] = (left + right) * left_right;
    p_out->data[13] = (top + bottom) * bottom_top;
    p_out->data[14] = (ortho_far + ortho_near) * near_far;
    p_out->data[15] = 1.0f;
    return p_out;
}
struct mat4* mat4_look_at(struct mat4* p_out, struct vec3* eye, struct vec3* center, struct vec3* up)
{
    if (fabsf(eye->x - center->x) < 0.0000001f &&
        fabsf(eye->y - center->y) < 0.0000001f &&
        fabsf(eye->z - center->z) < 0.0000001f )
    {
        return mat4_identity(p_out);
    }
    float32_t z0 = eye->x - center->x;
    float32_t z1 = eye->y - center->y;
    float32_t z2 = eye->z - center->z;
    float32_t len = 1.0f / sqrtf(z0 * z0 + z1 * z1 + z2 * z2);
    z0 *= len;
    z1 *= len;
    z2 *= len;
    float32_t x0 = up->y * z2 - up->z * z1;
    float32_t x1 = up->z * z0 - up->x * z2;
    float32_t x2 = up->x * z1 - up->y * z0;
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
    p_out->data[0] = x0;
    p_out->data[1] = y0;
    p_out->data[2] = z0;
    p_out->data[3] = 0.0f;
    p_out->data[4] = x1;
    p_out->data[5] = y1;
    p_out->data[6] = z1;
    p_out->data[7] = 0.0f;
    p_out->data[8] = x2;
    p_out->data[9] = y2;
    p_out->data[10] = z2;
    p_out->data[11] = 0.0f;
    p_out->data[12] = -(x0 * eye->x + x1 * eye->y + x2 * eye->z);
    p_out->data[13] = -(y0 * eye->x + y1 * eye->y + y2 * eye->z);
    p_out->data[14] = -(z0 * eye->x + z1 * eye->y + z2 * eye->z);
    p_out->data[15] = 1.0f;
    return p_out;
}

/* vec2 */
struct vec2* vec2_add(struct vec2* p_out, struct vec2* p_v0, struct vec2* p_v1)
{
    p_out->x = p_v0->x + p_v1->x;
    p_out->y = p_v0->y + p_v1->y;
    return p_out;
}
struct vec2* vec2_sub(struct vec2* p_out, struct vec2* p_v0, struct vec2* p_v1)
{
    p_out->x = p_v0->x - p_v1->x;
    p_out->y = p_v0->y - p_v1->y;
    return p_out;
}
struct vec2* vec2_mul(struct vec2* p_out, struct vec2* p_v0, struct vec2* p_v1)
{
    p_out->x = p_v0->x * p_v1->x;
    p_out->y = p_v0->y * p_v1->y;
    return p_out;
}
struct vec2* vec2_invert(struct vec2* p_out, struct vec2* p_v)
{
    p_out->x = 1.0f / p_v->x;
    p_out->y = 1.0f / p_v->y;
    return p_out;
}
struct vec2* vec2_negate(struct vec2* p_out, struct vec2* p_v)
{
    p_out->x = p_v->x * -1.0f;
    p_out->y = p_v->y * -1.0f;
    return p_out;
}
struct vec2* vec2_normalize(struct vec2* p_out, struct vec2* p_v)
{
    float32_t l = p_v->x * p_v->x + p_v->y * p_v->y;
    if (l > 0.0f)
    {
        l = 1.0f / sqrtf(l);
        p_out->x = p_v->x * l;
        p_out->y = p_v->y * l;
    }
    return p_out;
}
int32_t vec2_equal(struct vec2* p_v0, struct vec2* p_v1)
{
    return (p_v0->x == p_v1->x && p_v0->y == p_v1->y);
}
struct vec3* vec2_cross(struct vec3* p_out, struct vec2* p_v0, struct vec2* p_v1)
{
    p_out->x = 0;
    p_out->y = 0;
    p_out->z = p_v0->x * p_v1->y - p_v0->y * p_v1->x;
    return p_out;
}
float32_t vec2_distance(struct vec2* p_v0, struct vec2* p_v1)
{
    float32_t x = p_v0->x - p_v1->x;
    float32_t y = p_v0->y - p_v1->y;
    return sqrtf(x * x + y * y);
}
float32_t vec2_dot(struct vec2* p_v0, struct vec2* p_v1)
{
    return p_v0->x * p_v1->x + p_v0->y * p_v1->y;
}
float32_t vec2_length(struct vec2* p_v)
{
    return sqrtf(p_v->x * p_v->x + p_v->y * p_v->y);
}
float32_t vec2_length2(struct vec2* p_v)
{
    return (p_v->x * p_v->x + p_v->y * p_v->y);
}
float32_t vec2_distance2(struct vec2* p_v0, struct vec2* p_v1)
{
    float32_t x = p_v0->x - p_v1->x;
    float32_t y = p_v0->y - p_v1->y;
    return (x * x + y * y);
}

/* vec3 */
struct vec3* vec3_add(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1)
{
    p_out->x = p_v0->x + p_v1->x;
    p_out->y = p_v0->y + p_v1->y;
    p_out->z = p_v0->z + p_v1->z;
    return p_out;
}
struct vec3* vec3_sub(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1)
{
    p_out->x = p_v0->x - p_v1->x;
    p_out->y = p_v0->y - p_v1->y;
    p_out->z = p_v0->z - p_v1->z;
    return p_out;
}
struct vec3* vec3_mul(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1)
{
    p_out->x = p_v0->x * p_v1->x;
    p_out->y = p_v0->y * p_v1->y;
    p_out->z = p_v0->z * p_v1->z;
    return p_out;
}
struct vec3* vec3_invert(struct vec3* p_out, struct vec3* p_v)
{
    p_out->x = 1.0f / p_v->x;
    p_out->y = 1.0f / p_v->y;
    p_out->z = 1.0f / p_v->z;
    return p_out;
}
struct vec3* vec3_negate(struct vec3* p_out, struct vec3* p_v)
{
    p_out->x = -1.0f * p_v->x;
    p_out->y = -1.0f * p_v->y;
    p_out->z = -1.0f * p_v->z;
    return p_out;
}
struct vec3* vec3_normalize(struct vec3* p_out, struct vec3* p_v)
{
    float32_t x = p_v->x;
    float32_t y = p_v->y;
    float32_t z = p_v->z;
    float32_t l = x * x + y * y + z * z;
    if (l > 0.0f)
    {
        l = 1.0f / sqrtf(l);
        p_out->x = x * l;
        p_out->y = y * l;
        p_out->z = z * l;
    }
    return p_out;
}
int32_t vec3_equal(struct vec3* p_v0, struct vec3* p_v1)
{
    return (p_v0->x == p_v1->x && p_v0->y == p_v1->y && p_v0->z == p_v1->z);
}
struct vec3* vec3_cross(struct vec3* p_out, struct vec3* p_v0, struct vec3* p_v1)
{
    float32_t lx = p_v0->x;
    float32_t ly = p_v0->y;
    float32_t lz = p_v0->z;
    float32_t rx = p_v1->x;
    float32_t ry = p_v1->y;
    float32_t rz = p_v1->z;

    p_out->x = ly * rz - lz * ry;
    p_out->y = lz * rx - lx * rz;
    p_out->z = lx * ry - ly * rx;

    return p_out;
}
float32_t vec3_distance(struct vec3* p_v0, struct vec3* p_v1)
{
    float32_t x = p_v0->x - p_v1->x;
    float32_t y = p_v0->y - p_v1->y;
    float32_t z = p_v0->z - p_v1->z;

    return sqrtf(x * x + y * y + z * z);
}
float32_t vec3_dot(struct vec3* p_v0, struct vec3* p_v1)
{
    return p_v0->x * p_v1->x + p_v0->y * p_v1->y + p_v0->z * p_v1->z;
}
float32_t vec3_length(struct vec3* p_v)
{
    float32_t x = p_v->x;
    float32_t y = p_v->y;
    float32_t z = p_v->z;
    return sqrtf(x * x + y * y + z * z);
}
float32_t vec3_length2(struct vec3* p_v)
{
    float32_t x = p_v->x;
    float32_t y = p_v->y;
    float32_t z = p_v->z;
    return (x * x + y * y + z * z);
}
float32_t vec3_distance2(struct vec3* p_v0, struct vec3* p_v1)
{
    float32_t x = p_v0->x - p_v1->x;
    float32_t y = p_v0->y - p_v1->y;
    float32_t z = p_v0->z - p_v1->z;

    return (x * x + y * y + z * z);
}

/* quat */
struct quat* quat_identity(struct quat* p_out)
{
    p_out->x = 0;
    p_out->y = 0;
    p_out->z = 0;
    p_out->w = 1;
    return p_out;
}
struct quat* quat_add(struct quat* p_out, struct quat* p_q0, struct quat* p_q1)
{
    p_out->w = p_q0->w + p_q1->w;
    p_out->x = p_q0->x + p_q1->x;
    p_out->y = p_q0->y + p_q1->y;
    p_out->z = p_q0->z + p_q1->z;
    return p_out;
}
struct quat* quat_mul(struct quat* p_out, struct quat* p_q0, struct quat* p_q1)
{
    p_out->x = p_q0->x * p_q1->w + p_q0->w * p_q1->x + p_q0->y * p_q1->z - p_q0->z * p_q1->y;
    p_out->y = p_q0->y * p_q1->w + p_q0->w * p_q1->y + p_q0->z * p_q1->x - p_q0->x * p_q1->z;
    p_out->z = p_q0->z * p_q1->w + p_q0->w * p_q1->z + p_q0->x * p_q1->y - p_q0->y * p_q1->x;
    p_out->w = p_q0->w * p_q1->w - p_q0->x * p_q1->x - p_q0->y * p_q1->y - p_q0->z * p_q1->z;
    return p_out;
}
struct quat* quat_set_axis_angle(struct quat* p_out, struct vec3* axis, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    p_out->x = sn * axis->x;
    p_out->y = sn * axis->y;
    p_out->z = sn * axis->z;
    p_out->w = cosf(radian * 0.5f);
    return p_out;
}
struct quat* quat_rotate_x(struct quat* p_out, struct quat* p_q, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    p_out->x = p_q->x * sn + p_q->w * cn;
    p_out->y = p_q->y * sn + p_q->z * cn;
    p_out->z = p_q->z * sn - p_q->y * cn;
    p_out->w = p_q->w * sn - p_q->x * cn;
    return p_out;
}
struct quat* quat_rotate_y(struct quat* p_out, struct quat* p_q, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    p_out->x = p_q->x * cn - p_q->z * sn;
    p_out->y = p_q->y * cn + p_q->w * sn;
    p_out->z = p_q->z * cn + p_q->x * sn;
    p_out->w = p_q->w * cn - p_q->y * sn;
    return p_out;
}
struct quat* quat_rotate_z(struct quat* p_out, struct quat* p_q, float32_t radian)
{
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    p_out->x = p_q->x * cn + p_q->y * sn;
    p_out->y = p_q->y * cn - p_q->x * sn;
    p_out->z = p_q->z * cn + p_q->w * sn;
    p_out->w = p_q->w * cn - p_q->z * sn;
    return p_out;
}
struct quat* quat_calcw(struct quat* p_out, struct quat* p_q)
{
    p_out->x = p_q->x;
    p_out->y = p_q->y;
    p_out->z = p_q->z;
    p_out->w = sqrtf(fabsf(1.0f - p_q->x * p_q->x - p_q->y * p_q->y - p_q->z * p_q->z));
    return p_out;
}
struct quat* quat_invert(struct quat* p_out, struct quat* p_q)
{
    float32_t dot = p_q->x * p_q->x + p_q->y * p_q->y + p_q->z * p_q->z + p_q->w * p_q->w;
    if (dot) dot = 1.0f / dot;
    p_out->x = -p_q->x * dot;
    p_out->y = -p_q->y * dot;
    p_out->z = -p_q->z * dot;
    p_out->w = p_q->w * dot;
    return p_out;
}
struct quat* quat_conjugate(struct quat* p_out, struct quat* p_q)
{
    p_out->x = -p_q->x;
    p_out->y = -p_q->y;
    p_out->z = -p_q->z;
    p_out->w = p_q->w;
    return p_out;
}
struct mat4* quat_to_mat4(struct mat4* p_out, struct quat* p_q)
{
    float32_t x2 = p_q->x + p_q->x;
    float32_t y2 = p_q->y + p_q->y;
    float32_t z2 = p_q->z + p_q->z;
    float32_t xx = p_q->x * x2;
    float32_t yx = p_q->y * x2;
    float32_t yy = p_q->y * y2;
    float32_t zx = p_q->z * x2;
    float32_t zy = p_q->z * y2;
    float32_t zz = p_q->z * z2;
    float32_t wx = p_q->w * x2;
    float32_t wy = p_q->w * y2;
    float32_t wz = p_q->w * z2;

    p_out->data[0] = 1.0f - yy - zz;
    p_out->data[1] = yx + wz;
    p_out->data[2] = zx - wy;
    p_out->data[3] = 0.0f;
    p_out->data[4] = yx - wz;
    p_out->data[5] = 1.0f - xx - zz;
    p_out->data[6] = zy + wx;
    p_out->data[7] = 0.0f;
    p_out->data[8] = zx + wy;
    p_out->data[9] = zy - wx;
    p_out->data[10] = 1.0f - xx - yy;
    p_out->data[11] = 0.0f;
    p_out->data[12] = 0.0f;
    p_out->data[13] = 0.0f;
    p_out->data[14] = 0.0f;
    p_out->data[15] = 1.0f;
    return p_out;
}
float32_t quat_get_axis_angle(struct vec3* p_out_axis, struct quat* p_q)
{
    float32_t radian = acosf(p_q->w) * 2.0f;
    float32_t sn = sinf(radian * 0.5f);
    if (sn != 0.0f)
    {
        p_out_axis->x = p_q->x / sn;
        p_out_axis->y = p_q->y / sn;
        p_out_axis->z = p_q->z / sn;
    }
    else
    {
        p_out_axis->x = 1.0f;
        p_out_axis->y = 0.0f;
        p_out_axis->z = 0.0f;
    }
    return radian;
}

#endif // !_MATH_H_
