#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>

struct canvas {
	int width;
	int height;
	uint32_t *pixels;
};
typedef struct canvas Canvas;

void canvas_init(Canvas *canvas, int width, int height, uint32_t *pixels);
void canvas_set_pixel(Canvas *canvas, int x, int y, uint32_t color);
uint32_t canvas_get_pixel(Canvas *canvas, int x, int y);
bool canvas_in_bounds(Canvas *canvas, int x, int y);
void canvas_fill(Canvas *canvas, uint32_t color);

#endif

