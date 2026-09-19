#ifndef MAT_H
#define MAT_H

#include "vec.h"

struct mat4 {
	float m[4][4];
};
typedef struct mat4 Mat4;

Mat4 mat4_mul_mat4(Mat4 a, Mat4 b);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);

Mat4 mat4_rotate_x(float angle);
Mat4 mat4_rotate_y(float angle);
Mat4 mat4_rotate_z(float angle);

Mat4 mat4_translate(Vec3 t);

Mat4 mat4_scale(Vec3 s);

#endif

