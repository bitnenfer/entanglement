#ifndef _UTILS_CAMERA_H_
#define _UTILS_CAMERA_H_

#include "../math.h"

struct camera
{
    mat4_t view;
    mat4_t projection;
    vec3_t position;
    quat_t rotation;
};

typedef struct camera camera_t;


void camera_init();
camera_t* camera_get();
mat4_t camera_get_mvp(mat4_t* p_model);
mat4_t* camera_get_projection();
mat4_t* camera_get_view();
void camera_set_perspective(float32_t fov_y, float32_t aspect, float32_t n, float32_t f);
void camera_set_ortho(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t n, float32_t f);
void camera_look_at(vec3_t* p_point);
void camera_set_rotation(vec3_t* p_rotation);
void camera_set_position(vec3_t* p_position);

#endif // !_UTILS_CAMERA_H_
