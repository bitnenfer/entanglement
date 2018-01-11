#ifndef _MATH_H_
#define _MATH_H_

#include "types.h"

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
        struct
        {
            struct vec2 vec2;
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
            float32_t m, n, o, p;
        };
        float32_t data[16];
    };
};

/* mat2d */
struct mat2d* mat2d_identity(struct mat2d* p_out);
struct mat2d* mat2d_mul(struct mat2d* p_out, struct mat2d* m0, struct mat2d* m1);
struct vec2* mat2d_vec2_mul(struct vec2* p_out, struct mat2d* m0, struct vec2* v1);
struct mat2d* mat2d_translate(struct mat2d* p_out, struct mat2d* m, float32_t x, float32_t y);
struct mat2d* mat2d_scale(struct mat2d* p_out, struct mat2d* m, float32_t x, float32_t y);
struct mat2d* mat2d_rotate(struct mat2d* p_out, struct mat2d* m, float32_t radian);

/* mat4 */
struct mat4* mat4_identity(struct mat4* p_out);
struct mat4* mat4_mul(struct mat4* p_out, struct mat4* m0, struct mat4* m1);
struct vec3* mat4_vec3_mul(struct vec3* p_out, struct mat4* m0, struct vec3* v1);
struct mat4* mat4_transpose(struct mat4* p_out, struct mat4* m);
struct mat4* mat4_invert(struct mat4* p_out, struct mat4* m);
struct mat4* mat4_rotate_x(struct mat4* p_out, struct mat4* m, float32_t radian);
struct mat4* mat4_rotate_y(struct mat4* p_out, struct mat4* m, float32_t radian);
struct mat4* mat4_rotate_z(struct mat4* p_out, struct mat4* m, float32_t radian);
struct mat4* mat4_rotate(struct mat4* p_out, struct mat4* m, struct vec3* axis, float32_t radian);
struct mat4* mat4_scale(struct mat4* p_out, struct mat4* m, struct vec3* scale);
struct mat4* mat4_translate(struct mat4* p_out, struct mat4* m, struct vec3* translate);
struct mat4* mat4_frustum(struct mat4* p_out, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t frustum_near, float32_t frustum_far);
struct mat4* mat4_perspective(struct mat4* p_out, float32_t fov_y, float32_t aspect, float32_t persp_near, float32_t persp_far);
struct mat4* mat4_ortho(struct mat4* p_out, float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t ortho_near, float32_t ortho_far);
struct mat4* mat4_look_at(struct mat4* p_out, struct vec3* eye, struct vec3* center, struct vec3* up);

/* vec2 */
struct vec2 vec2_add(struct vec2 v0, struct vec2 v1);
struct vec2 vec2_sub(struct vec2 v0, struct vec2 v1);
struct vec2 vec2_mul(struct vec2 v0, struct vec2 v1);
struct vec2 vec2_invert(struct vec2 v);
struct vec2 vec2_negate(struct vec2 v);
struct vec2 vec2_normalize(struct vec2 v);
int32_t vec2_equal(struct vec2 v0, struct vec2 v1);
struct vec3 vec2_cross(struct vec2 v0, struct vec2 v1);
float32_t vec2_distance(struct vec2 v0, struct vec2 v1);
float32_t vec2_dot(struct vec2 v0, struct vec2 v1);
float32_t vec2_length(struct vec2 v);
float32_t vec2_length2(struct vec2 v);
float32_t vec2_distance2(struct vec2 v0, struct vec2 v1);

/* vec3 */
struct vec3 vec3_add(struct vec3 v0, struct vec3 v1);
struct vec3 vec3_sub(struct vec3 v0, struct vec3 v1);
struct vec3 vec3_mul(struct vec3 v0, struct vec3 v1);
struct vec3 vec3_invert(struct vec3 v);
struct vec3 vec3_negate(struct vec3 v);
struct vec3 vec3_normalize(struct vec3 v);
int32_t vec3_equal(struct vec3 v0, struct vec3 v1);
struct vec3 vec3_cross(struct vec3 v0, struct vec3 v1);
float32_t vec3_distance(struct vec3 v0, struct vec3 v1);
float32_t vec3_dot(struct vec3 v0, struct vec3 v1);
float32_t vec3_length(struct vec3 v);
float32_t vec3_length2(struct vec3 v);
float32_t vec3_distance2(struct vec3 v0, struct vec3 v1);

/* quat */
struct quat quat_identity();
struct quat quat_add(struct quat q0, struct quat q1);
struct quat quat_mul(struct quat q0, struct quat q1);
struct quat quat_set_axis_angle(struct vec3 axis, float32_t radian);
struct quat quat_rotate_x(struct quat q, float32_t radian);
struct quat quat_rotate_y(struct quat q, float32_t radian);
struct quat quat_rotate_z(struct quat q, float32_t radian);
struct quat quat_calcw(struct quat q);
struct quat quat_invert(struct quat q);
struct quat quat_conjugate(struct quat q);
struct mat4 quat_to_mat4(struct quat q);
float32_t quat_get_axis_angle(struct vec3* p_out_axis, struct quat q);

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
struct mat2d* mat2d_mul(struct mat2d* p_out, struct mat2d* m0, struct mat2d* m1)
{
    const float32_t* matrix_a = m0->data;
    const float32_t* matrix_b = m1->data;
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
struct vec2* mat2d_vec2_mul(struct vec2* p_out, struct mat2d* m0, struct vec2* v1)
{
    struct vec2 v;
    p_out->x = v1->x * m0->a + v1->y * m0->c + m0->tx;
    p_out->y = v1->x * m0->b + v1->y * m0->d + m0->ty;
    return p_out;
}
struct mat2d* mat2d_translate(struct mat2d* p_out, struct mat2d* m, float32_t x, float32_t y)
{
    p_out->data[4] = m->data[0] * x + m->data[2] * y + m->data[4];
    p_out->data[5] = m->data[1] * x + m->data[3] * y + m->data[5];
    return p_out;
}
struct mat2d* mat2d_scale(struct mat2d* p_out, struct mat2d* m, float32_t x, float32_t y)
{
    p_out->data[0] = m->data[0] * x;
    p_out->data[1] = m->data[1] * x;
    p_out->data[2] = m->data[2] * y;
    p_out->data[3] = m->data[3] * y;
    return p_out;
}
struct mat2d* mat2d_rotate(struct mat2d* p_out, struct mat2d* m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cs = cosf(radian);
    p_out->data[0] = cs * m->data[0] + -sn * m->data[2];
    p_out->data[1] = cs * m->data[1] + -sn * m->data[3];
    p_out->data[2] = sn * m->data[0] + cs * m->data[2];
    p_out->data[3] = sn * m->data[1] + cs * m->data[3];
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
struct mat4* mat4_mul(struct mat4* p_out, struct mat4* m0, struct mat4* m1)
{
    p_out->data[0] = m1->data[0] * m0->data[0] + m1->data[1] * m0->data[4] + m1->data[2] * m0->data[8] + m1->data[3] * m0->data[12];
    p_out->data[1] = m1->data[0] * m0->data[1] + m1->data[1] * m0->data[5] + m1->data[2] * m0->data[9] + m1->data[3] * m0->data[13];
    p_out->data[2] = m1->data[0] * m0->data[2] + m1->data[1] * m0->data[6] + m1->data[2] * m0->data[10] + m1->data[3] * m0->data[14];
    p_out->data[3] = m1->data[0] * m0->data[3] + m1->data[1] * m0->data[7] + m1->data[2] * m0->data[11] + m1->data[3] * m0->data[15];
    p_out->data[4] = m1->data[4] * m0->data[0] + m1->data[5] * m0->data[4] + m1->data[6] * m0->data[8] + m1->data[7] * m0->data[12];
    p_out->data[5] = m1->data[4] * m0->data[1] + m1->data[5] * m0->data[5] + m1->data[6] * m0->data[9] + m1->data[7] * m0->data[13];
    p_out->data[6] = m1->data[4] * m0->data[2] + m1->data[5] * m0->data[6] + m1->data[6] * m0->data[10] + m1->data[7] * m0->data[14];
    p_out->data[7] = m1->data[4] * m0->data[3] + m1->data[5] * m0->data[7] + m1->data[6] * m0->data[11] + m1->data[7] * m0->data[15];
    p_out->data[8] = m1->data[8] * m0->data[0] + m1->data[9] * m0->data[4] + m1->data[10] * m0->data[8] + m1->data[11] * m0->data[12];
    p_out->data[9] = m1->data[8] * m0->data[1] + m1->data[9] * m0->data[5] + m1->data[10] * m0->data[9] + m1->data[11] * m0->data[13];
    p_out->data[10] = m1->data[8] * m0->data[2] + m1->data[9] * m0->data[6] + m1->data[10] * m0->data[10] + m1->data[11] * m0->data[14];
    p_out->data[11] = m1->data[8] * m0->data[3] + m1->data[9] * m0->data[7] + m1->data[10] * m0->data[11] + m1->data[11] * m0->data[15];
    p_out->data[12] = m1->data[12] * m0->data[0] + m1->data[13] * m0->data[4] + m1->data[14] * m0->data[8] + m1->data[15] * m0->data[12];
    p_out->data[13] = m1->data[12] * m0->data[1] + m1->data[13] * m0->data[5] + m1->data[14] * m0->data[9] + m1->data[15] * m0->data[13];
    p_out->data[14] = m1->data[12] * m0->data[2] + m1->data[13] * m0->data[6] + m1->data[14] * m0->data[10] + m1->data[15] * m0->data[14];
    p_out->data[15] = m1->data[12] * m0->data[3] + m1->data[13] * m0->data[7] + m1->data[14] * m0->data[11] + m1->data[15] * m0->data[15];
    return p_out;
}
struct vec3* mat4_vec3_mul(struct vec3* p_out, struct mat4* m0, struct vec3* v1)
{
    p_out->x = m0->data[0] * v1->x + m0->data[4] * v1->y + m0->data[8] * v1->z + m0->data[12];
    p_out->y = m0->data[1] * v1->x + m0->data[5] * v1->y + m0->data[9] * v1->z + m0->data[13];
    p_out->z = m0->data[2] * v1->x + m0->data[6] * v1->y + m0->data[10] * v1->z + m0->data[14];
    return p_out;
}
struct mat4* mat4_transpose(struct mat4* p_out, struct mat4* m)
{
    p_out->data[0] = m->data[0];
    p_out->data[1] = m->data[4];
    p_out->data[2] = m->data[8];
    p_out->data[3] = m->data[12];
    p_out->data[4] = m->data[1];
    p_out->data[5] = m->data[5];
    p_out->data[6] = m->data[9];
    p_out->data[7] = m->data[13];
    p_out->data[8] = m->data[2];
    p_out->data[9] = m->data[6];
    p_out->data[10] = m->data[10];
    p_out->data[11] = m->data[14];
    p_out->data[12] = m->data[3];
    p_out->data[13] = m->data[7];
    p_out->data[14] = m->data[11];
    p_out->data[15] = m->data[15];
    return p_out;
}
struct mat4* mat4_invert(struct mat4* p_out, struct mat4* m)
{
    float32_t d0 = m->data[0] * m->data[5] - m->data[1] * m->data[4];
    float32_t d1 = m->data[0] * m->data[6] - m->data[2] * m->data[4];
    float32_t d2 = m->data[0] * m->data[7] - m->data[3] * m->data[4];
    float32_t d3 = m->data[1] * m->data[6] - m->data[2] * m->data[5];
    float32_t d4 = m->data[1] * m->data[7] - m->data[3] * m->data[5];
    float32_t d5 = m->data[2] * m->data[7] - m->data[3] * m->data[6];
    float32_t d6 = m->data[8] * m->data[13] - m->data[9] * m->data[12];
    float32_t d7 = m->data[8] * m->data[14] - m->data[10] * m->data[12];
    float32_t d8 = m->data[8] * m->data[15] - m->data[11] * m->data[12];
    float32_t d9 = m->data[9] * m->data[14] - m->data[10] * m->data[13];
    float32_t d10 = m->data[9] * m->data[15] - m->data[11] * m->data[13];
    float32_t d11 = m->data[10] * m->data[15] - m->data[11] * m->data[14];
    float32_t determinant = d0 * d11 - d1 * d10 + d2 * d9 + d3 * d8 - d4 * d7 + d5 * d6;

    if (determinant == 0.0f) return m;

    determinant = 1.0f / determinant;
    p_out->data[0] = (m->data[5] * d11 - m->data[6] * d10 + m->data[7] * d9) * determinant;
    p_out->data[1] = (m->data[2] * d10 - m->data[1] * d11 - m->data[3] * d9) * determinant;
    p_out->data[2] = (m->data[13] * d5 - m->data[14] * d4 + m->data[15] * d3) * determinant;
    p_out->data[3] = (m->data[10] * d4 - m->data[9] * d5 - m->data[11] * d3) * determinant;
    p_out->data[4] = (m->data[6] * d8 - m->data[4] * d11 - m->data[7] * d7) * determinant;
    p_out->data[5] = (m->data[0] * d11 - m->data[2] * d8 + m->data[3] * d7) * determinant;
    p_out->data[6] = (m->data[14] * d2 - m->data[12] * d5 - m->data[15] * d1) * determinant;
    p_out->data[7] = (m->data[8] * d5 - m->data[10] * d2 + m->data[11] * d1) * determinant;
    p_out->data[8] = (m->data[4] * d10 - m->data[5] * d8 + m->data[7] * d6) * determinant;
    p_out->data[9] = (m->data[1] * d8 - m->data[0] * d10 - m->data[3] * d6) * determinant;
    p_out->data[10] = (m->data[12] * d4 - m->data[13] * d2 + m->data[15] * d0) * determinant;
    p_out->data[11] = (m->data[9] * d2 - m->data[8] * d4 - m->data[11] * d0) * determinant;
    p_out->data[12] = (m->data[5] * d7 - m->data[4] * d9 - m->data[6] * d6) * determinant;
    p_out->data[13] = (m->data[0] * d9 - m->data[1] * d7 + m->data[2] * d6) * determinant;
    p_out->data[14] = (m->data[13] * d1 - m->data[12] * d3 - m->data[14] * d0) * determinant;
    p_out->data[15] = (m->data[8] * d3 - m->data[9] * d1 + m->data[10] * d0) * determinant;
    return p_out;
}
struct mat4* mat4_rotate_x(struct mat4* p_out, struct mat4* m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    p_out->data[0] = m->data[0];
    p_out->data[1] = m->data[1];
    p_out->data[2] = m->data[2];
    p_out->data[3] = m->data[3];
    p_out->data[12] = m->data[12];
    p_out->data[13] = m->data[13];
    p_out->data[14] = m->data[14];
    p_out->data[15] = m->data[15];
    p_out->data[4] = m->data[4] * cn + m->data[8] * sn;
    p_out->data[5] = m->data[5] * cn + m->data[9] * sn;
    p_out->data[6] = m->data[6] * cn + m->data[10] * sn;
    p_out->data[7] = m->data[7] * cn + m->data[11] * sn;
    p_out->data[8] = m->data[8] * cn - m->data[4] * sn;
    p_out->data[9] = m->data[9] * cn - m->data[5] * sn;
    p_out->data[10] = m->data[10] * cn - m->data[6] * sn;
    p_out->data[11] = m->data[11] * cn - m->data[7] * sn;
    return p_out;
}
struct mat4* mat4_rotate_y(struct mat4* p_out, struct mat4* m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    p_out->data[0] = m->data[0] * cn - m->data[8] * sn;
    p_out->data[1] = m->data[1] * cn - m->data[9] * sn;
    p_out->data[2] = m->data[2] * cn - m->data[10] * sn;
    p_out->data[3] = m->data[3] * cn - m->data[11] * sn;
    p_out->data[4] = m->data[4];
    p_out->data[5] = m->data[5];
    p_out->data[6] = m->data[6];
    p_out->data[7] = m->data[7];
    p_out->data[8] = m->data[0] * sn + m->data[8] * cn;
    p_out->data[9] = m->data[1] * sn + m->data[9] * cn;
    p_out->data[10] = m->data[2] * sn + m->data[10] * cn;
    p_out->data[11] = m->data[3] * sn + m->data[11] * cn;
    p_out->data[12] = m->data[12];
    p_out->data[13] = m->data[13];
    p_out->data[14] = m->data[14];
    p_out->data[15] = m->data[15];
    return p_out;
}
struct mat4* mat4_rotate_z(struct mat4* p_out, struct mat4* m, float32_t radian)
{
    float32_t sn = sinf(radian);
    float32_t cn = cosf(radian);
    p_out->data[0] = m->data[0] * cn + m->data[4] * sn;
    p_out->data[1] = m->data[1] * cn + m->data[5] * sn;
    p_out->data[2] = m->data[2] * cn + m->data[6] * sn;
    p_out->data[3] = m->data[3] * cn + m->data[7] * sn;
    p_out->data[4] = m->data[4] * cn - m->data[0] * sn;
    p_out->data[5] = m->data[5] * cn - m->data[1] * sn;
    p_out->data[6] = m->data[6] * cn - m->data[2] * sn;
    p_out->data[7] = m->data[7] * cn - m->data[3] * sn;
    p_out->data[8] = m->data[8];
    p_out->data[9] = m->data[9];
    p_out->data[10] = m->data[10];
    p_out->data[11] = m->data[11];
    p_out->data[12] = m->data[12];
    p_out->data[13] = m->data[13];
    p_out->data[14] = m->data[14];
    p_out->data[15] = m->data[15];
    return p_out;
}
struct mat4* mat4_rotate(struct mat4* p_out, struct mat4* m, struct vec3* axis, float32_t radian)
{
    float32_t length = vec3_length(*axis);

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
    p_out->data[0] = m->data[0] * d0 + m->data[4] * d1 + m->data[8] * d2;
    p_out->data[1] = m->data[1] * d0 + m->data[5] * d1 + m->data[9] * d2;
    p_out->data[2] = m->data[2] * d0 + m->data[6] * d1 + m->data[10] * d2;
    p_out->data[3] = m->data[3] * d0 + m->data[7] * d1 + m->data[11] * d2;
    p_out->data[4] = m->data[0] * d3 + m->data[4] * d4 + m->data[8] * d5;
    p_out->data[5] = m->data[1] * d3 + m->data[5] * d4 + m->data[9] * d5;
    p_out->data[6] = m->data[2] * d3 + m->data[6] * d4 + m->data[10] * d5;
    p_out->data[7] = m->data[3] * d3 + m->data[7] * d4 + m->data[11] * d5;
    p_out->data[8] = m->data[0] * d6 + m->data[4] * d7 + m->data[8] * d8;
    p_out->data[9] = m->data[1] * d6 + m->data[5] * d7 + m->data[9] * d8;
    p_out->data[10] = m->data[2] * d6 + m->data[6] * d7 + m->data[10] * d8;
    p_out->data[11] = m->data[3] * d6 + m->data[7] * d7 + m->data[11] * d8;
    p_out->data[12] = m->data[12];
    p_out->data[13] = m->data[13];
    p_out->data[14] = m->data[14];
    p_out->data[15] = m->data[15];
    return p_out;
}
struct mat4* mat4_scale(struct mat4* p_out, struct mat4* m, struct vec3* scale)
{
    p_out->data[0] = m->data[0] * scale->x;
    p_out->data[1] = m->data[1] * scale->x;
    p_out->data[2] = m->data[2] * scale->x;
    p_out->data[3] = m->data[3] * scale->x;
    p_out->data[4] = m->data[4] * scale->y;
    p_out->data[5] = m->data[5] * scale->y;
    p_out->data[6] = m->data[6] * scale->y;
    p_out->data[7] = m->data[7] * scale->y;
    p_out->data[8] = m->data[8] * scale->z;
    p_out->data[9] = m->data[9] * scale->z;
    p_out->data[10] = m->data[10] * scale->z;
    p_out->data[11] = m->data[11] * scale->z;
    p_out->data[12] = m->data[12];
    p_out->data[13] = m->data[13];
    p_out->data[14] = m->data[14];
    p_out->data[15] = m->data[15];
    return p_out;
}
struct mat4* mat4_translate(struct mat4* p_out, struct mat4* m, struct vec3* translate)
{
    p_out->data[0] = m->data[0];
    p_out->data[1] = m->data[1];
    p_out->data[2] = m->data[2];
    p_out->data[3] = m->data[3];
    p_out->data[4] = m->data[4];
    p_out->data[5] = m->data[5];
    p_out->data[6] = m->data[6];
    p_out->data[7] = m->data[7];
    p_out->data[8] = m->data[8];
    p_out->data[9] = m->data[9];
    p_out->data[10] = m->data[10];
    p_out->data[11] = m->data[11];
    p_out->data[12] = m->data[0] * translate->x + m->data[4] * translate->y + m->data[8] * translate->z + m->data[12];
    p_out->data[13] = m->data[1] * translate->x + m->data[5] * translate->y + m->data[9] * translate->z + m->data[13];
    p_out->data[14] = m->data[2] * translate->x + m->data[6] * translate->y + m->data[10] * translate->z + m->data[14];
    p_out->data[15] = m->data[3] * translate->x + m->data[7] * translate->y + m->data[11] * translate->z + m->data[15];
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
struct vec2 vec2_add(struct vec2* v0, struct vec2* v1)
{
    struct vec2 v;
    v.x = v0->x + v1->x;
    v.y = v0->y + v1->y;
    return v;
}
struct vec2 vec2_sub(struct vec2* v0, struct vec2* v1)
{
    struct vec2 v;
    v.x = v0.x - v1->x;
    v.y = v0.y - v1->y;
    return v;
}
struct vec2 vec2_mul(struct vec2* v0, struct vec2* v1)
{
    struct vec2 v;
    v.x = v0.x * v1->x;
    v.y = v0.y * v1->y;
    return v;
}
struct vec2 vec2_invert(struct vec2* v)
{
    struct vec2 o;
    o.x = 1.0f / v.x;
    o.y = 1.0f / v.y;
    return o;
}
struct vec2 vec2_negate(struct vec2* v)
{
    struct vec2 o;
    o.x = v.x * -1.0f;
    o.y = v.y * -1.0f;
    return o;
}
struct vec2 vec2_normalize(struct vec2* v)
{
    struct vec2 o = v;
    float32_t l = v.x * v.x + v.y * v.y;
    if (l > 0.0f)
    {
        l = 1.0f / sqrtf(l);
        o.x = v.x * l;
        o.y = v.y * l;
    }
    return o;
}
int32_t vec2_equal(struct vec2* v0, struct vec2* v1)
{
    return (v0.x == v1->x && v0.y == v1->y);
}
struct vec3 vec2_cross(struct vec2* v0, struct vec2* v1)
{
    struct vec3 v;
    v.x = 0;
    v.y = 0;
    v.z = v0.x * v1->y - v0.y * v1->x;
    return v;
}
float32_t vec2_distance(struct vec2* v0, struct vec2* v1)
{
    float32_t x = v0.x - v1->x;
    float32_t y = v0.y - v1->y;
    return sqrtf(x * x + y * y);
}
float32_t vec2_dot(struct vec2* v0, struct vec2* v1)
{
    return v0.x * v1->x + v0.y * v1->y;
}
float32_t vec2_length(struct vec2* v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}
float32_t vec2_length2(struct vec2* v)
{
    return (v.x * v.x + v.y * v.y);
}
float32_t vec2_distance2(struct vec2* v0, struct vec2* v1)
{
    float32_t x = v0.x - v1->x;
    float32_t y = v0.y - v1->y;
    return (x * x + y * y);
}

/* vec3 */
struct vec3 vec3_add(struct vec3* v0, struct vec3* v1)
{
    struct vec3 v;
    v.x = v0.x + v1->x;
    v.y = v0.y + v1->y;
    v.z = v0.z + v1->z;
    return v;
}
struct vec3 vec3_sub(struct vec3* v0, struct vec3* v1)
{
    struct vec3 v;
    v.x = v0.x - v1->x;
    v.y = v0.y - v1->y;
    v.z = v0.z - v1->z;
    return v;
}
struct vec3 vec3_mul(struct vec3* v0, struct vec3* v1)
{
    struct vec3 v;
    v.x = v0.x * v1->x;
    v.y = v0.y * v1->y;
    v.z = v0.z * v1->z;
    return v;
}
struct vec3 vec3_invert(struct vec3* v)
{
    struct vec3 o;
    o.x = 1.0f / v.x;
    o.y = 1.0f / v.y;
    o.z = 1.0f / v.z;
    return o;
}
struct vec3 vec3_negate(struct vec3* v)
{
    struct vec3 o;
    o.x = -1.0f * v.x;
    o.y = -1.0f * v.y;
    o.z = -1.0f * v.z;
    return o;
}
struct vec3 vec3_normalize(struct vec3* v)
{
    struct vec3 o = v;
    float32_t x = v.x;
    float32_t y = v.y;
    float32_t z = v.z;
    float32_t l = x * x + y * y + z * z;
    if (l > 0.0f)
    {
        l = 1.0f / sqrtf(l);
        o.x = x * l;
        o.y = y * l;
        o.z = z * l;
    }
    return o;
}
int32_t vec3_equal(struct vec3* v0, struct vec3* v1)
{
    return (v0.x == v1->x && v0.y == v1->y && v0.z == v1->z);
}
struct vec3 vec3_cross(struct vec3* v0, struct vec3* v1)
{
    struct vec3 v;
    float32_t lx = v0.x;
    float32_t ly = v0.y;
    float32_t lz = v0.z;
    float32_t rx = v1->x;
    float32_t ry = v1->y;
    float32_t rz = v1->z;

    v.x = ly * rz - lz * ry;
    v.y = lz * rx - lx * rz;
    v.z = lx * ry - ly * rx;

    return v;
}
float32_t vec3_distance(struct vec3* v0, struct vec3* v1)
{
    float32_t x = v0.x - v1->x;
    float32_t y = v0.y - v1->y;
    float32_t z = v0.z - v1->z;

    return sqrtf(x * x + y * y + z * z);
}
float32_t vec3_dot(struct vec3* v0, struct vec3* v1)
{
    return v0.x * v1->x + v0.y * v1->y + v0.z * v1->z;
}
float32_t vec3_length(struct vec3* v)
{
    float32_t x = v.x;
    float32_t y = v.y;
    float32_t z = v.z;
    return sqrtf(x * x + y * y + z * z);
}
float32_t vec3_length2(struct vec3* v)
{
    float32_t x = v.x;
    float32_t y = v.y;
    float32_t z = v.z;
    return (x * x + y * y + z * z);
}
float32_t vec3_distance2(struct vec3* v0, struct vec3* v1)
{
    float32_t x = v0.x - v1->x;
    float32_t y = v0.y - v1->y;
    float32_t z = v0.z - v1->z;

    return (x * x + y * y + z * z);
}

/* quat */
struct quat quat_identity()
{
    struct quat q;
    q.x = 0;
    q.y = 0;
    q.z = 0;
    q.w = 1;
    return q;
}
struct quat quat_add(struct quat q0, struct quat q1)
{
    struct quat q;
    q.w = q0.w + q1.w;
    q.x = q0.x + q1.x;
    q.y = q0.y + q1.y;
    q.z = q0.z + q1.z;
    return q;
}
struct quat quat_mul(struct quat q0, struct quat q1)
{
    struct quat q;
    q.x = q0.x * q1.w + q0.w * q1.x + q0.y * q1.z - q0.z * q1.y;
    q.y = q0.y * q1.w + q0.w * q1.y + q0.z * q1.x - q0.x * q1.z;
    q.z = q0.z * q1.w + q0.w * q1.z + q0.x * q1.y - q0.y * q1.x;
    q.w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
    return q;
}
struct quat quat_set_axis_angle(struct vec3 axis, float32_t radian)
{
    struct quat q;
    float32_t sn = sinf(radian * 0.5f);
    q.x = sn * axis.x;
    q.y = sn * axis.y;
    q.z = sn * axis.z;
    q.w = cosf(radian * 0.5f);
    return q;
}
struct quat quat_rotate_x(struct quat q, float32_t radian)
{
    struct quat o;
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    o.x = q.x * sn + q.w * cn;
    o.y = q.y * sn + q.z * cn;
    o.z = q.z * sn - q.y * cn;
    o.w = q.w * sn - q.x * cn;
    return o;
}
struct quat quat_rotate_y(struct quat q, float32_t radian)
{
    struct quat o;
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    o.x = q.x * cn - q.z * sn;
    o.y = q.y * cn + q.w * sn;
    o.z = q.z * cn + q.x * sn;
    o.w = q.w * cn - q.y * sn;
    return o;
}
struct quat quat_rotate_z(struct quat q, float32_t radian)
{
    struct quat o;
    float32_t sn = sinf(radian * 0.5f);
    float32_t cn = cosf(radian * 0.5f);
    o.x = q.x * cn + q.y * sn;
    o.y = q.y * cn - q.x * sn;
    o.z = q.z * cn + q.w * sn;
    o.w = q.w * cn - q.z * sn;
    return o;
}
struct quat quat_calcw(struct quat q)
{
    struct quat o;
    o.x = q.x;
    o.y = q.y;
    o.z = q.z;
    o.w = sqrtf(fabsf(1.0f - q.x * q.x - q.y * q.y - q.z * q.z));
    return o;
}
struct quat quat_invert(struct quat q)
{
    struct quat o;
    float32_t dot = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (dot) dot = 1.0f / dot;
    o.x = -q.x * dot;
    o.y = -q.y * dot;
    o.z = -q.z * dot;
    o.w = q.w * dot;
    return o;
}
struct quat quat_conjugate(struct quat q)
{
    struct quat o;
    o.x = -q.x;
    o.y = -q.y;
    o.z = -q.z;
    o.w = q.w;
    return o;
}
struct mat4 quat_to_mat4(struct quat q)
{
    struct mat4 m;
    float32_t x2 = q.x + q.x;
    float32_t y2 = q.y + q.y;
    float32_t z2 = q.z + q.z;
    float32_t xx = q.x * x2;
    float32_t yx = q.y * x2;
    float32_t yy = q.y * y2;
    float32_t zx = q.z * x2;
    float32_t zy = q.z * y2;
    float32_t zz = q.z * z2;
    float32_t wx = q.w * x2;
    float32_t wy = q.w * y2;
    float32_t wz = q.w * z2;

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
    return m;
}
float32_t quat_get_axis_angle(struct vec3* p_out_axis, struct quat q)
{
    float32_t radian = acosf(q.w) * 2.0f;
    float32_t sn = sinf(radian * 0.5f);
    if (sn != 0.0f)
    {
        p_out_axis->x = q.x / sn;
        p_out_axis->y = q.y / sn;
        p_out_axis->z = q.z / sn;
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
