#include "mat.h"
#include <math.h>

Mat4 mat4_mul_mat4(Mat4 a, Mat4 b)
{
	Mat4 ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;

			for (int k = 0; k < 4; k++) {
				sum += a.m[i][k] * b.m[k][j];
			}

			ret.m[i][j] = sum;
		}
	}

	return ret;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v)
{
	float arr[4];
	float *ptr[] = { &v.x, &v.y, &v.z, &v.w };

	for (int i = 0; i < 4; i++) {
		float sum = 0.0f;

		for (int k = 0; k < 4; k++) {
			sum += m.m[i][k] * (*ptr[k]);
		}

		arr[i] = sum;
	}

	return vec4_make(arr[0], arr[1], arr[2], arr[3]);
}

Mat4 mat4_rotate_x(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	Mat4 ret = {
		.m = {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, c, -s, 0.0f },
			{ 0.0f, s, c, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}
	};

	return ret;
}

Mat4 mat4_rotate_y(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	Mat4 ret = {
		.m = {
			{ c, 0.0f, s, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ -s, 0.0f, c, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}
	};

	return ret;
}

Mat4 mat4_rotate_z(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);

	Mat4 ret = {
		.m = {
			{ c, -s, 0.0f, 0.0f },
			{ s, c, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}
	};

	return ret;
}

Mat4 mat4_translate(Vec3 t)
{
	Mat4 ret = {
		.m = {
			{ 1.0f, 0.0f, 0.0f, t.x },
			{ 0.0f, 1.0f, 0.0f, t.y },
			{ 0.0f, 0.0f, 1.0f, t.z },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}
	};

	return ret;
}

Mat4 mat4_scale(Vec3 s)
{
	Mat4 ret = {
		.m = {
			{ s.x, 0.0f, 0.0f, 0.0f },
			{ 0.0f, s.y, 0.0f, 0.0f },
			{ 0.0f, 0.0f, s.z, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		}
	};

	return ret;
}

