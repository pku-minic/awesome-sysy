/*
  Usage: ./mandelbrot <xmin> <xmax> <ymin> <ymax> <maxiter> <xres> > <out.ppm>

  Where <xmin>, <xmax>, <ymin>, <ymax> must be integers that reinterpreted by
  IEEE-754 single-precision floating point numbers.

  Example: echo 1049275610 1049280643 999820068 1000185140 500 1024 |
           ./mandelbrot > pic.ppm

  Reference: https://gist.github.com/andrejbauer/7919569
  Modified by MaxXing.
*/

int fp_add(int x, int y);
int fp_sub(int x, int y);
int fp_mul(int x, int y);
int fp_div(int x, int y);
int fp_lt(int x, int y);
int to_fp(int x);
int to_int(int x);

int main() {
  /* The window in the plane. */
  int xmin = getint(), xmax = getint();
  int ymin = getint(), ymax = getint();

  /* Maximum number of iterations */
  int maxiter = getint();

  /* Image size, width is given, height is computed. */
  int xres = getint();
  int yres = to_int(
      fp_div(fp_mul(to_fp(xres), fp_sub(ymax, ymin)), fp_sub(xmax, xmin)));

  /*write ASCII header to the file*/
  putch(80); putch(51); putch(10);
  putint(xres); putch(32); putint(yres); putch(10); putint(255); putch(10);

  int x, y; /* Coordinates of the current point in the complex plane. */
  int u, v; /* Coordinates of the iterated point. */
  int i, j; /* Pixel counters */
  int k;    /* Iteration counter */
  j = 0;
  while (j < yres) {
    y = fp_sub(ymax, fp_div(fp_mul(to_fp(j), fp_sub(ymax, ymin)), to_fp(yres)));
    i = 0;
    while (i < xres) {
      int u = 0, v = 0, u2 = 0, v2 = 0;
      x = fp_add(xmin,
                 fp_div(fp_mul(to_fp(i), fp_sub(xmax, xmin)), to_fp(xres)));
      /* iterate the point */
      k = 1;
      while (k < maxiter && fp_lt(fp_add(u2, v2), to_fp(4))) {
        v = fp_add(fp_mul(fp_mul(to_fp(2), u), v), y);
        u = fp_add(fp_sub(u2, v2), x);
        u2 = fp_mul(u, u);
        v2 = fp_mul(v, v);
        k = k + 1;
      }
      /* compute pixel color and write it to file */
      if (k >= maxiter) {
        /* interior */
        putint(0); putch(32); putint(0); putch(32); putint(0); putch(32);
      } else {
        int r = k * 128 / maxiter;
        int g = k * 192 / maxiter;
        int b = k * 255 / maxiter;
        putint(r); putch(32); putint(g); putch(32); putint(b); putch(32);
      }
      i = i + 1;
    }
    putch(10);
    j = j + 1;
  }
  return 0;
}
