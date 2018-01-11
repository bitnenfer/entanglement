#include  "camera.h"

static const vec3_t k_UpVector = { 0.0f, 1.0f, 0.0f };
static camera_t g_Camera;
static camera_t g_CameraOrigin;

void camera_init()
{
    mat4_identity();
    mat4_identity()
}
camera_t* camera_get();
mat4_t camera_get_mvp(mat4_t* p_model);
mat4_t camera_get_projection();
mat4_t camera_get_view();
void camera_set_perspective(float32_t fov_y, float32_t aspect, float32_t n, float32_t f);
void camera_set_ortho(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t n, float32_t f);
void camera_look_at(vec3_t point);
void camera_set_rotation(vec3_t rotation);
void camera_set_position(vec3_t position);
