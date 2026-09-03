#ifndef RASTER_H
#define RASTER_H

void raster_line(
		int x0, int y0,
		int x1, int y1,
		void *ctx,
		void (*cb)(int x, int y, void *ctx)
		);

void raster_triangle(
		int x0, int y0,
		int x1, int y1,
		int x2, int y2,
		void *ctx,
		void (*cb)(int x, int y, int u0, int u1, int u2, int det, void *ctx)
		);

#endif

