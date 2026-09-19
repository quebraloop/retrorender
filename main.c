#include "canvas.h"
#include "raster.h"
#include "ppm.h"
#include "vec.h"
#include "mat.h"

#include <stdlib.h>

const int width = 1280;
const int height = 720;

uint32_t make_rgbx(unsigned char r, unsigned char g, unsigned char b)
{
	return r << 24 | g << 16 | b << 8 | 0xFF;
}

unsigned char get_red_ch(uint32_t color)
{
	return (color >> 24) & 0xFF;
}

unsigned char get_green_ch(uint32_t color)
{
	return (color >> 16) & 0xFF;
}

unsigned char get_blue_ch(uint32_t color)
{
	return (color >> 8) & 0xFF;
}

void cb(int x, int y, void *ctx)
{
	uintptr_t *ptr = (uintptr_t *)ctx;
	Canvas *canvas = (Canvas *)ptr[0];
	uint32_t color = *((uint32_t *)ptr[1]);

	if (canvas_in_bounds(canvas, x, y)) {
		canvas_set_pixel(canvas, x, y, color);
	}
}

uint32_t rand_color()
{
	return make_rgbx(rand() % 256, rand() % 256, rand() % 256);
}

void fetcher(
	int x, int y,
	unsigned char *r, unsigned char *g, unsigned char *b,
	void *ctx
	)
{
	Canvas *canvas = (Canvas *)ctx;
	uint32_t color = canvas_get_pixel(canvas, x, y);

	*r = get_red_ch(color);
	*g = get_green_ch(color);
	*b = get_blue_ch(color);
}

Vec4 viewport(Vec4 v)
{
	Vec4 ret = v;
	ret.x = (ret.x + 1.0f) * width * 0.5f;
	ret.y = (ret.y + 1.0f) * height * 0.5f;

	return ret;
}

const Vec3 cube_vertices[] = {
	{ 0.5f, 0.5f, 0.5f },
	{ -0.5f, 0.5f, 0.5f },
	{ -0.5f, -0.5f, 0.5f },
	{ 0.5f, -0.5f, 0.5f },

	{ 0.5f, 0.5f, -0.5f },
	{ -0.5f, 0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ 0.5f, -0.5f, -0.5f }
};

const int cube_edges[][2] = {
	{ 0, 1 }, { 0, 3 }, { 0, 4 },
	{ 1, 2 }, { 1, 5 },
	{ 2, 3 }, { 2, 6 },
	{ 3, 7 },
	{ 4, 5 }, { 4, 7 },
	{ 5, 6 },
	{ 6, 7 }
};

#define ARR_SIZE(arr) ( sizeof(arr) / sizeof(*(arr)) )

const float PI = 3.141593f;
const float FPS = 60.0f;
const float DUR = 10.0f; // in seconds

int main(void)
{
	Canvas canvas;
	uint32_t *pixels;

	pixels = malloc(sizeof(uint32_t) * width * height);

	canvas_init(&canvas, width, height, pixels);

	srand((unsigned int)(uintptr_t)pixels);

	float num_frames = FPS * DUR;
	float angle = 0.0f;
	uint32_t color = rand_color();

	for (int frame = 0; frame < num_frames; frame++) {
		canvas_fill(&canvas, make_rgbx(0, 0, 0));

		// Rotate around x, y and z axis and
		// translate the cube a little away to make sure it will fit in [-1, 1]
		Mat4 model = mat4_mul_mat4(
				mat4_translate(vec3_make(0.0f, 0.0f, 2.0f)),
				mat4_mul_mat4(
					mat4_rotate_z(angle * 0.1f),
					mat4_mul_mat4(
						mat4_rotate_y(angle * 1.5f), mat4_rotate_x(angle * 0.2f)))
				);

		size_t num_vertices = ARR_SIZE(cube_vertices);
		size_t num_edges = ARR_SIZE(cube_edges);
		Vec4 screen[num_vertices];

		for (size_t v = 0; v < num_vertices; v++) {
			screen[v] = mat4_mul_vec4(model, vec3_to_vec4(cube_vertices[v], 1.0f));
			screen[v] = vec4_scale(screen[v], 1.0f / screen[v].z);
			screen[v] = viewport(screen[v]);
		}

		for (size_t e = 0; e < num_edges; e++) {
			const int *edge = cube_edges[e];

			Vec4 v0 = screen[edge[0]];
			Vec4 v1 = screen[edge[1]];

			uintptr_t ctx[] = { (uintptr_t)&canvas, (uintptr_t)&color };

			raster_line(
				v0.x, v0.y,
				v1.x, v1.y,
				(void *)ctx,
				cb
				);
		}

		angle += 2.0f * PI / num_frames;
	
		ppm_out(stdout, width, height, &canvas, fetcher);
	}

	free(pixels);

	return 0;
}

