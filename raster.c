#include "raster.h"

#define ABS(x) ( (x) >= 0 ? (x) : -(x) )
#define SIGN(a) ( ( (a) > 0 ) - ( (a) < 0 ) )

void raster_line(
		int x0, int y0,
		int x1, int y1,
		void *ctx,
		void (*cb)(int x, int y, void *ctx)
		)
{
	int *major_coord, *minor_coord;
	int major_sign, minor_sign;
	int major_delta, minor_delta;

	int diff_x, diff_y;
	int dx, dy;
	int x, y;

	diff_x = x1 - x0;
	diff_y = y1 - y0;

	dx = ABS(diff_x);
	dy = ABS(diff_y);

	x = x0;
	y = y0;

	if (dx > dy) {
		major_coord = &x;
		minor_coord = &y;

		major_sign = SIGN(diff_x);
		minor_sign = SIGN(diff_y);

		major_delta = dx;
		minor_delta = dy;
	} else {
		major_coord = &y;
		minor_coord = &x;

		major_sign = SIGN(diff_y);
		minor_sign = SIGN(diff_x);

		major_delta = dy;
		minor_delta = dx;
	}

	int err = 2 * minor_delta - major_delta;

	for (int i = 0; i <= major_delta; i++) {
		cb(x, y, ctx);

		if (err >= 0) {
			err -= 2 * major_delta;
			(*minor_coord) += minor_sign;
		}

		err += 2 * minor_delta;
		(*major_coord) += major_sign;
	}
}

