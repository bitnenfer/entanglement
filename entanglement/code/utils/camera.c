#include  "camera.h"

static vec3_t k_UpVector = { 0.0f, 1.0f, 0.0f };
static camera_t g_Camera;
static camera_t g_CameraOrigin;

void camera_init()
{
    mat4_identity(&g_Camera.view);
    mat4_identity(&g_Camera.projection);
    mat4_identity(&g_CameraOrigin.view);
    mat4_identity(&g_CameraOrigin.projection);
}
camera_t* camera_get()
{
    return &g_Camera;
}
mat4_t camera_get_mvp(mat4_t* p_model)
{
    mat4_t mvp;

    mat4_mul(&mvp, &g_Camera.projection, &g_Camera.view);
    mat4_mul(&mvp, &mvp, p_model);

    return mvp;
}
mat4_t* camera_get_projection()
{
    return &g_Camera.projection;
}
mat4_t* camera_get_view()
{
    return &g_Camera.view;
}
void camera_set_perspective(float32_t fov_y, float32_t aspect, float32_t n, float32_t f)
{
    mat4_perspective(&g_Camera.projection, fov_y, aspect, n, f);
}
void camera_set_ortho(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t n, float32_t f)
{
    mat4_ortho(&g_Camera.projection, left, right, bottom, top, n, f);
}
void camera_look_at(vec3_t* p_point)
{
    mat4_look_at(&g_Camera.view, &g_Camera.position, p_point, &k_UpVector);
}
void camera_set_rotation(vec3_t* p_rotation)
{
    mat4_rotate_x(&g_Camera.view, &g_CameraOrigin.view, p_rotation->x);
    mat4_rotate_y(&g_Camera.view, &g_Camera.view, p_rotation->y);
    mat4_rotate_z(&g_Camera.view, &g_Camera.view, p_rotation->z);
}
void camera_set_position(vec3_t* p_position)
{
    g_Camera.position.x = p_position->x;
    g_Camera.position.y = p_position->y;
    g_Camera.position.z = p_position->z;
    mat4_translate(&g_Camera.view, &g_CameraOrigin.view, &g_Camera.position);
}
