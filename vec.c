#include "vec.h"

Vec3 vec3_make(float x, float y, float z)
{
	Vec3 ret = { x, y, z };
	return ret;
}

Vec3 vec3_scale(Vec3 v, float s)
{
	return vec3_make(v.x * s, v.y * s, v.z * s);
}

Vec3 vec3_add(Vec3 a, Vec3 b)
{
	return vec3_make(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3_sub(Vec3 a, Vec3 b)
{
	return vec3_make(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 vec3_mul(Vec3 a, Vec3 b)
{
	return vec3_make(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3 vec3_div(Vec3 a, Vec3 b)
{
	return vec3_make(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec4 vec4_make(float x, float y, float z, float w)
{
	Vec4 ret = { x, y, z, w };
	return ret;
}

Vec4 vec3_to_vec4(Vec3 v, float w)
{
	return vec4_make(v.x, v.y, v.z, w);
}

Vec4 vec4_scale(Vec4 v, float s)
{
	return vec4_make(v.x * s, v.y * s, v.z * s, v.w * s);
}

