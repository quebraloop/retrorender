#include "ppm.h"

void ppm_out(FILE *file, int width, int height, void *ctx, void (*cb)(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b, void *ctx))
{
	int maxval = 255;

	fprintf(file, "P6 %d %d %d\n", width, height, maxval);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned char r, g, b;

			cb(x, y, &r, &g, &b, ctx);
			fputc(r, file);
			fputc(g, file);
			fputc(b, file);
		}
	}
}

