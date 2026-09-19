#ifndef VEC_H
#define VEC_H

struct vec3 {
	float x, y, z;
};
typedef struct vec3 Vec3;

struct vec4 {
	float x, y, z, w;
};
typedef struct vec4 Vec4;

Vec3 vec3_make(float x, float y, float z);
Vec3 vec3_scale(Vec3 v, float s);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 a, Vec3 b);
Vec3 vec3_div(Vec3 a, Vec3 b);

Vec4 vec4_make(float x, float y, float z, float w);
Vec4 vec3_to_vec4(Vec3 v, float w);
Vec4 vec4_scale(Vec4 v, float s);

#endif

