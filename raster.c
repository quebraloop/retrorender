#include "raster.h"

#define ABS(x) ( (x) >= 0 ? (x) : -(x) )
#define SIGN(a) ( ( (a) > 0 ) - ( (a) < 0 ) )
#define MIN(a, b) ( (a) < (b) ? (a) : (b) )
#define MAX(a, b) ( (a) > (b) ? (a) : (b) )

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

int signed_double_area(
		int x0, int y0,
		int x1, int y1,
		int x2, int y2
		)
{
	return ( x0 - x2 ) * ( y1 - y2 ) - ( x1 - x2 ) * ( y0 - y2 );
}

void raster_triangle(
		int x0, int y0,
		int x1, int y1,
		int x2, int y2,
		void *ctx,
		void (*cb)(int x, int y, int u0, int u1, int u2, int det, void *ctx)
		)
{
	int min_x = MIN(MIN(x0, x1), x2);
	int min_y = MIN(MIN(y0, y1), y2);
	int max_x = MAX(MAX(x0, x1), x2);
	int max_y = MAX(MAX(y0, y1), y2);

	int det = signed_double_area(x0, y0, x1, y1, x2, y2);

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			int u0 = signed_double_area(x, y, x1, y1, x2, y2);
			int u1 = signed_double_area(x, y, x2, y2, x0, y0);
			int u2 = signed_double_area(x, y, x0, y0, x1, y1);

			int in =
				( SIGN(u0) == SIGN(det) || u0 == 0 ) &&
				( SIGN(u1) == SIGN(det) || u1 == 0 ) &&
				( SIGN(u2) == SIGN(det) || u2 == 0 );

			if (in) {
				cb(x, y, u0, u1, u2, det, ctx);
			}
		}
	}
}

