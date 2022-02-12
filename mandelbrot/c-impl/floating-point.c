/*
  Usage: ./mandelbrot <xmin> <xmax> <ymin> <ymax> <maxiter> <xres> > <out.ppm>

  Example: ./mandelbrot 0.27085 0.27100 0.00464 0.00481 500 1024 > pic.ppm

  Reference: https://gist.github.com/andrejbauer/7919569
  Modified by MaxXing.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  /* The window in the plane. */
  const float xmin = atof(argv[1]);
  const float xmax = atof(argv[2]);
  const float ymin = atof(argv[3]);
  const float ymax = atof(argv[4]);

  /* Maximum number of iterations, at most 65535. */
  const uint16_t maxiter = (unsigned short)atoi(argv[5]);

  /* Image size, width is given, height is computed. */
  const int xres = atoi(argv[6]);
  const int yres = (xres * (ymax - ymin)) / (xmax - xmin);

  /*write ASCII header to the file*/
  printf("P3\n%d %d\n%d\n", xres, yres, 255);

  /* Precompute pixel width and height. */
  float dx = (xmax - xmin) / xres;
  float dy = (ymax - ymin) / yres;

  float x, y; /* Coordinates of the current point in the complex plane. */
  float u, v; /* Coordinates of the iterated point. */
  int i, j;   /* Pixel counters */
  int k;      /* Iteration counter */
  for (j = 0; j < yres; j++) {
    y = ymax - j * dy;
    for (i = 0; i < xres; i++) {
      float u = 0, v = 0, u2 = 0, v2 = 0;
      x = xmin + i * dx;
      /* iterate the point */
      for (k = 1; k < maxiter && (u2 + v2 < 4); k++) {
        v = 2 * u * v + y;
        u = u2 - v2 + x;
        u2 = u * u;
        v2 = v * v;
      }
      /* compute pixel color and write it to file */
      if (k >= maxiter) {
        /* interior */
        printf("%d %d %d ", 0, 0, 0);
      } else {
        int r = k * 128 / maxiter;
        int g = k * 192 / maxiter;
        int b = k * 255 / maxiter;
        printf("%d %d %d ", r, g, b);
      }
    }
    printf("\n");
  }
  return 0;
}
