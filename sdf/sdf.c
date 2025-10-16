const int positive = 0;
const int negative = 1;

// #region Fixed-point number operation

// Fixed-point number representation
// fp[0] = integer part
// fp[1] = fractional part (out of SCALE)
// fp[2] = sign (0 for positive, 1 for negative)
// #define SCALE 10000 // 4 decimal places of precision
const int SCALE = 10000; // 4 decimal places of precision

// Add two fixed-point numbers, result = a + b
void fp_add(int a[], int b[], int result[]) {
  int temp[3];
  if (a[2] == b[2]) {
    // both positive or both negative
    result[2] = a[2];
    result[1] = a[1] + b[1];
    result[0] = a[0] + b[0];
    if (result[1] >= SCALE) {
      result[0] = result[0] + 1;
      result[1] = result[1] - SCALE;
    }
    return;
  }

  int temp1[3] = {a[0], a[1], a[2]};
  int temp2[3] = {b[0], b[1], b[2]};
  if (temp2[2] == positive) {
    // swap temp1 temp2
    // let temp1 is positive, temp2 is negative
    temp[0] = temp1[0];
    temp[1] = temp1[1];
    temp[2] = temp1[2];
    temp1[0] = temp2[0];
    temp1[1] = temp2[1];
    temp1[2] = temp2[2];
    temp2[0] = temp[0];
    temp2[1] = temp[1];
    temp2[2] = temp[2];
  }
  // temp1 is positive, b is negative
  if (temp1[0] > temp2[0] || (temp1[0] == temp2[0] && temp1[1] >= temp2[1])) {
    // temp1 is greater than b
    result[2] = positive;
    result[0] = temp1[0] - temp2[0];
    result[1] = temp1[1] - temp2[1];
    if (result[1] < 0) {
      result[0] = result[0] - 1;
      result[1] = result[1] + SCALE;
    }
  } else {
    result[2] = negative;
    result[0] = temp2[0] - temp1[0];
    result[1] = temp2[1] - temp1[1];
    if (result[1] < 0) {
      result[0] = result[0] - 1;
      result[1] = result[1] + SCALE;
    }
  }
}

// Subtract b from a, result = a - b
void fp_sub(int a[], int b[], int result[]) {
  if (a[2] == positive && a[2] == b[2]) {
    // both positive
    if (a[0] > b[0] || (a[0] == b[0] && a[1] >= b[1])) {
      // a is greater than b
      result[2] = positive;
      result[0] = a[0] - b[0];
      result[1] = a[1] - b[1];
      if (result[1] < 0) {
        result[0] = result[0] - 1;
        result[1] = result[1] + SCALE;
      }
    } else {
      result[2] = negative;
      result[0] = b[0] - a[0];
      result[1] = b[1] - a[1];
      if (result[1] < 0) {
        result[0] = result[0] - 1;
        result[1] = result[1] + SCALE;
      }
    }
    return;
  }

  if (a[2] == negative && a[2] == b[2]) {
    // both negative
    if (a[0] > b[0] || (a[0] == b[0] && a[1] >= b[1])) {
      // a is less than b
      result[2] = negative;
      result[0] = a[0] - b[0];
      result[1] = a[1] - b[1];
      if (result[1] < 0) {
        result[0] = result[0] - 1;
        result[1] = result[1] + SCALE;
      }
    } else {
      result[2] = positive;
      result[0] = b[0] - a[0];
      result[1] = b[1] - a[1];
      if (result[1] < 0) {
        result[0] = result[0] - 1;
        result[1] = result[1] + SCALE;
      }
    }
    return;
  }

  result[2] = a[2];
  result[0] = a[0] + b[0];
  result[1] = a[1] + b[1];
  if (result[1] >= SCALE) {
    result[0] = result[0] + 1;
    result[1] = result[1] - SCALE;
  }
  return;
}

// Multiply two integers with modulo (avoid overflow)
// (a * b) % mod
int mod_mult(int a, int b, int mod) {
  int result = 0;
  while (b > 0) {
    if ((b % 2) == 1) {
      result = (result + a) % mod;
    }
    a = (a * 2) % mod;
    b = b / 2;
  }
  return result;
}

// Multiply two fixed-point numbers, result = a * b
void fp_mul(int a[], int b[], int result[]) {
  // (a1 + a2) * (b1 + b2) = a1 * b1 + a1 * b2 + a2 * b1 + a2 * b2
  int part1 = a[0] * b[0];
  int int_part2 = 0;
  int frac_part2 = 0;
  int part2 = a[0] * b[1];
  // 214769 = (2 ** 32 - 1) / 9999
  if (a[0] > 214769) {
    // handle overflow
    int_part2 = a[0] / SCALE * b[1];
    frac_part2 = mod_mult(a[0], b[1], SCALE);
  } else {
    int_part2 = part2 / SCALE;
    frac_part2 = part2 % SCALE;
  }

  int int_part3 = 0;
  int frac_part3 = 0;
  int part3 = a[1] * b[0];
  if (b[0] > 214769) {
    // handle overflow
    int_part3 = b[0] / SCALE * a[1];
    frac_part3 = mod_mult(b[0], a[1], SCALE);
  } else {
    int_part3 = part3 / SCALE;
    frac_part3 = part3 % SCALE;
  }
  int part4 = a[1] * b[1] / SCALE;

  result[0] = part1 + int_part2 + int_part3;
  result[1] = frac_part2 + frac_part3 + part4;
  if (result[1] >= SCALE) {
    result[0] = result[0] + (result[1] / SCALE);
    result[1] = result[1] % SCALE;
  }

  if (a[2] == b[2]) {
    result[2] = positive;
  } else {
    result[2] = negative;
  }
}

// Divide two fixed-point numbers, result = a / b
void fp_div(int a[], int b[], int result[]) {
  if (a[0] == b[0] && a[1] == b[1] && a[2] == b[2]) {
    result[0] = 1;
    result[1] = 0;
    result[2] = positive;
    return;
  }
  if (a[2] == b[2]) {
    result[2] = positive;
  } else {
    result[2] = negative;
  }
  if (b[0] == 0 && b[1] == 0) {
    result[0] = 0;
    result[1] = 0;
    return;
  }
  if (b[0] == 0) {
    result[0] = a[0] * SCALE / b[1];
    result[1] = a[1] * SCALE / b[1];
    if (result[1] >= SCALE) {
      result[0] = result[0] + (result[1] / SCALE);
      result[1] = result[1] % SCALE;
    }
    return;
  }

  // use absolute value for calculation
  int ta[3], tb[3];
  ta[0] = a[0];
  ta[1] = a[1];
  ta[2] = positive;
  tb[0] = b[0];
  tb[1] = b[1];
  tb[2] = positive;

  int int_part = ta[0] / (tb[0] + 1);
  int temp1[3], remaining[3];
  temp1[0] = tb[0] * int_part;
  temp1[1] = tb[1] * int_part;
  temp1[2] = positive;
  if (temp1[1] >= SCALE) {
    temp1[0] = temp1[0] + (temp1[1] / SCALE);
    temp1[1] = temp1[1] % SCALE;
  }
  fp_sub(ta, temp1, remaining);

  while (remaining[0] > tb[0] ||
         (remaining[0] == tb[0] && remaining[1] >= tb[1])) {
    int_part = int_part + 1;
    fp_sub(remaining, tb, temp1);
    remaining[0] = temp1[0];
    remaining[1] = temp1[1];
    remaining[2] = temp1[2];
  }

  result[0] = int_part;

  int frac_part = 0;
  int i = 0;
  int base[3] = {10, 0, positive};
  while (i < 4) {
    i = i + 1;
    fp_mul(remaining, base, temp1);
    remaining[0] = temp1[0];
    remaining[1] = temp1[1];
    remaining[2] = temp1[2];
    frac_part = frac_part * 10;
    while (remaining[0] > tb[0] ||
           (remaining[0] == tb[0] && remaining[1] >= b[1])) {
      frac_part = frac_part + 1;
      fp_sub(remaining, tb, temp1);
      remaining[0] = temp1[0];
      remaining[1] = temp1[1];
      remaining[2] = temp1[2];
    }
  }
  result[1] = frac_part;
}

/* Calculates x^y where x is fixed-point and y is a regular integer (y >= 0) */
void fp_pow(int x[], int y, int result[]) {
  // Special cases
  if (x[0] == 0 && x[1] == 0) {
    // 0^y = 0, except 0^0 which is undefined (returning 1 in this case)
    if (y == 0) {
      result[0] = 1;
      result[1] = 0;
    } else {
      result[0] = 0;
      result[1] = 0;
    }
    return;
  }

  if (y == 0) {
    // Anything^0 = 1
    result[0] = 1;
    result[1] = 0;
    return;
  }

  // For positive exponents: Exponentiation by squaring algorithm
  result[0] = 1;
  result[1] = 0;

  int base[3] = {x[0], x[1], positive};
  int power = y;
  int temp[3];

  while (power > 0) {
    if (power % 2 == 1) {
      // If power is odd, multiply result by base
      fp_mul(result, base, temp);
      result[0] = temp[0];
      result[1] = temp[1];
    }

    // Square the base
    fp_mul(base, base, temp);
    base[0] = temp[0];
    base[1] = temp[1];

    power = power / 2;
  }

  if (y % 2 == 0) {
    result[2] = positive;
  } else {
    result[2] = x[2];
  }
}

/* Calculate square root of a fixed-point number using Newton-Raphson method */
void fp_sqrt(int x[], int result[]) {
  result[2] = positive;
  // Handle special cases
  if (x[0] < 0 || (x[0] == 0 && x[1] < 0)) {
    // Cannot take square root of negative number
    // Setting result to 0 to indicate error
    result[0] = 0;
    result[1] = 0;
    return;
  }

  if (x[0] == 0 && x[1] == 0) {
    // sqrt(0) = 0
    result[0] = 0;
    result[1] = 0;
    return;
  }

  // Initial guess: a reasonable approximation to sqrt(x)
  int guess[3] = {x[0], x[1], positive};
  int two[3] = {2, 0, positive};
  int n_exp = 10;
  if (x[0] > SCALE) {
    // x is very large: start with 10^(log10(x)/2)
    while ((n_exp * n_exp <= x[0]) && (n_exp < 100000)) {
      n_exp = 10 * n_exp;
    }
    guess[0] = n_exp;
    guess[1] = 0;
  } else if (x[0] > 1 || (x[0] == 1 && x[1] > 0)) {
    // x > 1: start with x/2
    fp_div(x, two, guess);
  } else {
    // x < 1: start with x
  }

  // Newton-Raphson iteration: next = (guess + x/guess) / 2
  // We'll perform several iterations for accuracy
  // Usually 5-10 iterations is enough for good precision
  int temp1[3], temp2[3], next[3];
  int i = 0;
  while (i < 10) {
    i = i + 1;
    // Calculate x/guess
    fp_div(x, guess, temp1);

    // Calculate guess + x/guess
    fp_add(guess, temp1, temp2);

    // Calculate (guess + x/guess)/2
    int two[3] = {0, 5000, positive};
    fp_mul(temp2, two, next);

    // Update guess for next iteration
    guess[0] = next[0];
    guess[1] = next[1];
    guess[2] = next[2];
  }

  result[0] = guess[0];
  result[1] = guess[1];
}

/* Calculate sine of a fixed-point number using Taylor series approximation */
void fp_sin(int x[], int result[]) {
  // Normalize angle to [-π, π] range
  // First, create a 2π constant
  int two_pi[3] = {6, 2832, positive}; // 6.2832 is approximately 2π

  // Create temporary variables
  int temp1[3], temp2[3], normalized[3];

  // Copy input to normalized
  normalized[0] = x[0];
  normalized[1] = x[1];
  normalized[2] = x[2];

  // If abs(x) > π, subtract 2π until abs(x) <= π
  int pi[3] = {3, 1416, positive}; // 3.1416 is approximately π
  while (normalized[0] > pi[0] ||
         (normalized[0] == pi[0] && normalized[1] > pi[1])) {
    fp_sub(normalized, two_pi, temp1);
    normalized[0] = temp1[0];
    normalized[1] = temp1[1];
    normalized[2] = temp1[2];
  }

  // Taylor series for sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
  // We'll use the first 4 terms of the series for a reasonable approximation

  // First term: x
  result[0] = normalized[0];
  result[1] = normalized[1];
  result[2] = normalized[2];

  // x^3/3!
  int x3[3], term[3];
  fp_pow(normalized, 3, x3);
  int factorial3[3] = {6, 0, positive}; // 3! = 6
  fp_div(x3, factorial3, term);
  fp_sub(result, term, temp1);

  // x^5/5!
  int x5[3];
  fp_pow(normalized, 5, x5);
  int factorial5[3] = {120, 0, positive}; // 5! = 120
  fp_div(x5, factorial5, term);
  fp_add(temp1, term, temp2);

  // x^7/7!
  int x7[3];
  fp_pow(normalized, 7, x7);
  int factorial7[3] = {5040, 0, positive}; // 7! = 5040
  fp_div(x7, factorial7, term);
  fp_sub(temp2, term, result);
}

/* Calculate cosine of a fixed-point number using Taylor series approximation */
void fp_cos(int x[], int result[]) {
  // cos(x) = sin(x + π/2)
  int pi_over_2[3] = {1, 5708, positive}; // 1.5708 is approximately π/2
  int temp[3];
  fp_add(x, pi_over_2, temp);
  fp_sin(temp, result);
}

// Initialize a fixed-point number
void fp_init(int a[], int whole, int frac) {
  a[0] = whole;
  a[1] = frac;
  a[2] = positive;
}

// #endregion

// Safe hypotenuse calculation to avoid overflow
// sqrt(x^2 + y^2) = larger * sqrt(1 + (smaller/larger)^2)
void safe_hypot(int x[], int y[], int result[]) {
  int temp1[3], temp2[3], one[3] = {1, 0, positive};
  int larger[3], smaller[3];
  if (x[0] > y[0] || (x[0] == y[0] && x[1] >= y[1])) {
    larger[0] = x[0];
    larger[1] = x[1];
    larger[2] = positive;
    smaller[0] = y[0];
    smaller[1] = y[1];
    smaller[2] = positive;
  } else {
    larger[0] = y[0];
    larger[1] = y[1];
    larger[2] = positive;
    smaller[0] = x[0];
    smaller[1] = x[1];
    smaller[2] = positive;
  }

  int ratio[3];
  fp_div(smaller, larger, ratio);
  fp_mul(ratio, ratio, temp1);
  fp_add(temp1, one, temp2);
  fp_sqrt(temp2, temp1);
  fp_mul(larger, temp1, result);
}

// Safe hypotenuse calculation for 3D coordinates
// sqrt(x^2 + y^2 + z^2) =
//     larger * sqrt((x/larger)^2 + (y/larger)^2 + (z/larger)^2)
void safe_hypot3(int x[], int y[], int z[], int result[]) {
  int temp1[3], temp2[3], temp3[3];
  int larger[3] = {x[0], x[1], positive};
  if (y[0] > larger[0] || (y[0] == larger[0] && y[1] >= larger[1])) {
    larger[0] = y[0];
    larger[1] = y[1];
  }
  if (z[0] > larger[0] || (z[0] == larger[0] && z[1] >= larger[1])) {
    larger[0] = z[0];
    larger[1] = z[1];
  }

  int norm_x[3], norm_y[3], norm_z[3];
  fp_div(x, larger, norm_x);
  fp_div(y, larger, norm_y);
  fp_div(z, larger, norm_z);

  fp_mul(norm_x, norm_x, temp1);
  fp_mul(norm_y, norm_y, temp2);
  fp_mul(norm_z, norm_z, temp3);

  int temp4[3];
  fp_add(temp1, temp2, temp4);
  fp_add(temp4, temp3, temp1);

  fp_sqrt(temp1, temp4);
  fp_mul(larger, temp4, result);
}

void donut(int x[], int y[], int z[], int result[]) {
  int radius[3] = {0, 4000, positive};
  int thickness[3] = {0, 1500, positive};
  int temp1[3];
  int temp2[3];

  // math.sqrt(x**2 + y**2)
  safe_hypot(x, y, temp1);

  // t - radius
  fp_sub(temp1, radius, result);
  temp1[0] = result[0];
  temp1[1] = result[1];

  // math.sqrt(t**2 + z**2)
  safe_hypot(temp1, z, temp2);

  // result - thickness
  fp_sub(temp2, thickness, result);
}

void normal(int x[], int y[], int z[], int rx[], int ry[], int rz[]) {
  int e[3] = {0, 10, positive};
  int temp1[3], temp2[3], temp3[3];
  int n_x[3], n_y[3], n_z[3];

  // n_x = donut(x + ε, y, z) - donut(x - ε, y, z)
  fp_add(x, e, temp1);
  donut(temp1, y, z, temp2);
  fp_sub(x, e, temp1);
  donut(temp1, y, z, temp3);
  fp_sub(temp2, temp3, n_x);

  // n_y = donut(x, y + ε, z) - donut(x, y - ε, z)
  fp_add(y, e, temp1);
  donut(x, temp1, z, temp2);
  fp_sub(y, e, temp1);
  donut(x, temp1, z, temp3);
  fp_sub(temp2, temp3, n_y);

  // n_z = donut(x, y, z + ε) - donut(x, y, z - ε)
  fp_add(z, e, temp1);
  donut(x, y, temp1, temp2);
  fp_sub(z, e, temp1);
  donut(x, y, temp1, temp3);
  fp_sub(temp2, temp3, n_z);

  // norm = math.sqrt(n_x**2 + n_y**2 + n_z**2)
  int norm[3];
  safe_hypot3(n_x, n_y, n_z, norm);

  // rx = n_x / norm
  fp_div(n_x, norm, rx);
  // ry = n_y / norm
  fp_div(n_y, norm, ry);
  // rz = n_z / norm
  fp_div(n_z, norm, rz);
}

int sample(int x[], int y[], int ts[]) {
  int cos_v[3], sin_v[3];

  fp_cos(ts, cos_v);
  fp_sin(ts, sin_v);

  int t_x[3], t_z[3], d[3];
  int temp1[3], temp2[3];
  int nt_x[3], nt_y[3], nt_z[3];
  int is_lit = 0, is_frosted = 0;
  int i = 0;
  int z[3] = {10, 0, negative};
  while (i < 30) {
    i = i + 1;
    // t_x = x * cos - z * sin
    fp_mul(x, cos_v, temp1);
    fp_mul(z, sin_v, temp2);
    fp_sub(temp1, temp2, t_x);
    // t_z = x * sin + z * cos
    fp_mul(x, sin_v, temp1);
    fp_mul(z, cos_v, temp2);
    fp_add(temp1, temp2, t_z);
    // d = donut(t_x, y, t_z)
    donut(t_x, y, t_z, d);

    // d <= 0.01
    if (d[0] < 0 || (d[0] == 0 && d[1] < 100)) {
      is_lit = 0;
      is_frosted = 0;
      normal(t_x, y, t_z, nt_x, nt_y, nt_z);
      // is_lit = nt_y < -0.15
      if (nt_y[2] == negative &&
          (nt_y[0] > 0 || (nt_y[0] == 0 && nt_y[1] >= 1500))) {
        is_lit = 1;
      }
      // is_frosted = nt_z < -0.5
      if (nt_z[2] == negative &&
          (nt_z[0] > 0 || (nt_z[0] == 0 && nt_z[1] >= 5000))) {
        is_frosted = 1;
      }
      if (is_frosted == 1) {
        if (is_lit == 1) {
          return 64; // '@'
        } else {
          return 35; // '#'
        }
      } else {
        if (is_lit == 1) {
          return 61; // '='
        } else {
          return 46; // '.'
        }
      }
    } else {
      fp_add(z, d, temp1);
      z[0] = temp1[0];
      z[1] = temp1[1];
      z[2] = temp1[2];
    }
  }
  return 32; // ' '
}

int frame_chars[1620] = {};

void loop(int ts[]) {
  int fp_x[3], fp_y[3];
  int temp1[3];
  int remapped_x[3], remapped_y[3];
  int forty[3] = {40, 0, positive};
  int one[3] = {1, 0, positive};
  int half[3] = {0, 5000, positive};
  int twenty[3] = {20, 0, positive};

  int c;
  int x = 0, y = 0;
  int i = 0;
  while (y < 20) {
    x = 0;
    while (x < 80) {
      // remapped_x = x / 80 * 2 - 1
      //            = x / 40 - 1
      fp_init(fp_x, x, 0);
      fp_div(fp_x, forty, temp1);
      fp_sub(temp1, one, remapped_x);
      // remapped_y = (y / 20 * 2 - 1) * (2 * 20 / 80)
      //            = (y / 10 - 1) * 0.5
      //            = y / 20 - 0.5
      fp_init(fp_y, y, 0);
      fp_div(fp_y, twenty, temp1);
      fp_sub(temp1, half, remapped_y);
      c = sample(remapped_x, remapped_y, ts);
      frame_chars[i] = c;
      i = i + 1;
      x = x + 1;
    }
    y = y + 1;
    frame_chars[i] = 10;
    i = i + 1;
  }

  // \033[2J
  putch(27); // '\033'
  putch(91); // '['
  putch(50); // '2'
  putch(74); // 'J'
  i = 0;
  while (i < 1620) {
    i = i + 1;
    putch(frame_chars[i]);
  }
}

void loop_forever() {
  int ts[3] = {2, 0, positive};
  int dt[3] = {0, 2500, positive};
  int temp1[3];

  while (1) {

    loop(ts);
    fp_add(ts, dt, temp1);
    ts[0] = temp1[0];
    ts[1] = temp1[1];
    ts[2] = temp1[2];
  }
}

int main() {
  loop_forever();
  return 0;
}