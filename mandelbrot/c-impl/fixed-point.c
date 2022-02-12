/*
  Usage: ./mandelbrot <xmin> <xmax> <ymin> <ymax> <maxiter> <xres> > <out.ppm>

  Where <xmin>, <xmax>, <ymin>, <ymax> must be fixed point numbers with scalling
  factor 10000000.

  Example: ./mandelbrot 2708500 2710000 46400 48100 500 1024 > pic.ppm

  Reference: https://gist.github.com/andrejbauer/7919569
  Modified by MaxXing.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int64_t SCALE = 10000000;

typedef int64_t fixed_t;

fixed_t fixed_add(fixed_t a, fixed_t b) { return a + b; }

fixed_t fixed_sub(fixed_t a, fixed_t b) { return a - b; }

fixed_t fixed_mul(fixed_t a, fixed_t b) {
  int64_t tmp = (int64_t)a * (int64_t)b;
  return (fixed_t)(tmp / SCALE);
}

fixed_t fixed_div(fixed_t a, fixed_t b) {
  int64_t tmp = (int64_t)a * SCALE;
  return (fixed_t)(tmp / b);
}

fixed_t to_fixed(int a) { return (fixed_t)(a * SCALE); }

int to_int(fixed_t a) { return (int)(a / SCALE); }

int main(int argc, char* argv[]) {
  /* The window in the plane. */
  const fixed_t xmin = atoi(argv[1]);
  const fixed_t xmax = atoi(argv[2]);
  const fixed_t ymin = atoi(argv[3]);
  const fixed_t ymax = atoi(argv[4]);

  /* Maximum number of iterations, at most 65535. */
  const uint16_t maxiter = (unsigned short)atoi(argv[5]);

  /* Image size, width is given, height is computed. */
  const int xres = atoi(argv[6]);
  const int yres = to_int(fixed_div(
      fixed_mul(to_fixed(xres), fixed_sub(ymax, ymin)), fixed_sub(xmax, xmin)));

  /*write ASCII header to the file*/
  printf("P3\n%d %d\n%d\n", xres, yres, 255);

  fixed_t x, y; /* Coordinates of the current point in the complex plane. */
  fixed_t u, v; /* Coordinates of the iterated point. */
  int i, j;     /* Pixel counters */
  int k;        /* Iteration counter */
  for (j = 0; j < yres; j++) {
    y = fixed_sub(ymax, fixed_div(fixed_mul(to_fixed(j), fixed_sub(ymax, ymin)),
                                  to_fixed(yres)));
    for (i = 0; i < xres; i++) {
      fixed_t u = 0, v = 0, u2 = 0, v2 = 0;
      x = fixed_add(xmin,
                    fixed_div(fixed_mul(to_fixed(i), fixed_sub(xmax, xmin)),
                              to_fixed(xres)));
      /* iterate the point */
      for (k = 1; k < maxiter && (fixed_add(u2, v2) < to_fixed(4)); k++) {
        v = fixed_add(fixed_mul(fixed_mul(to_fixed(2), u), v), y);
        u = fixed_add(fixed_sub(u2, v2), x);
        u2 = fixed_mul(u, u);
        v2 = fixed_mul(v, v);
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
