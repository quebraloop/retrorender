#include "canvas.h"
#include "raster.h"
#include "ppm.h"

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

void cb(int x, int y, int u0, int u1, int u2, int det, void *ctx)
{
	uintptr_t *ptr = (uintptr_t *)ctx;
	Canvas *canvas = (Canvas *)ptr[0];
	uint32_t *color_gradient = ((uint32_t *)ptr[1]);

	float alpha = (float)u0 / (float)det;
	float beta = (float)u1 / (float)det;
	float gamma = (float)u2 / (float)det;

	unsigned char r = get_red_ch(color_gradient[0]) * alpha + get_red_ch(color_gradient[1]) * beta + get_red_ch(color_gradient[2]) * gamma;
	unsigned char g = get_green_ch(color_gradient[0]) * alpha + get_green_ch(color_gradient[1]) * beta + get_green_ch(color_gradient[2]) * gamma;
	unsigned char b = get_blue_ch(color_gradient[0]) * alpha + get_blue_ch(color_gradient[1]) * beta + get_blue_ch(color_gradient[2]) * gamma;

	uint32_t color = make_rgbx(r, g, b);

	canvas_set_pixel(canvas, x, y, color);
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

int main(void)
{
	Canvas canvas;
	uint32_t *pixels;

	pixels = malloc(sizeof(uint32_t) * width * height);

	canvas_init(&canvas, width, height, pixels);

	canvas_fill(&canvas, make_rgbx(0, 0, 0));

	srand((unsigned int)(uintptr_t)pixels);

	int x0 = 0.50f * width, y0 = 0.20f * height;
	int x1 = 0.25f * width, y1 = 0.80f * height;
	int x2 = 0.75f * width, y2 = 0.80f * height;

	uint32_t color_gradient[] = { rand_color(), rand_color(), rand_color() };

	uintptr_t ctx[] = { (uintptr_t)&canvas, (uintptr_t)color_gradient };

	raster_triangle(
		x0, y0,
		x1, y1,
		x2, y2,
		ctx,
		cb
		);

	ppm_out(stdout, width, height, &canvas, fetcher);

	free(pixels);

	return 0;
}

