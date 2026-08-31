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

void cb(int x, int y, void *ctx)
{
	uintptr_t *ptr = (uintptr_t *)ctx;
	Canvas *canvas = (Canvas *)ptr[0];
	uint32_t color = *((uint32_t *)ptr[1]);

	canvas_set_pixel(canvas, x, y, color);
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

	for (int i = 0; i < (1 << 16); i++) {
		int x0 = rand() % width;
		int y0 = rand() % height;

		int x1 = rand() % width;
		int y1 = rand() % height;

		unsigned char r = rand() % 256;
		unsigned char g = rand() % 256;
		unsigned char b = rand() % 256;

		uint32_t color = make_rgbx(r, g, b);
	
		uintptr_t ctx[] = { (uintptr_t)&canvas, (uintptr_t)&color };

		raster_line(
			x0, y0,
			x1, y1,
			ctx,
			cb
			);
	}

	ppm_out(stdout, width, height, &canvas, fetcher);

	free(pixels);

	return 0;
}

