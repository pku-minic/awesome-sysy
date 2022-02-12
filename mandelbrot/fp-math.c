// Floating point math functions for SysY programs.

int fp_add(int x, int y) {
  float ans = *(float *)&x + *(float *)&y;
  return *(int *)&ans;
}

int fp_sub(int x, int y) {
  float ans = *(float *)&x - *(float *)&y;
  return *(int *)&ans;
}

int fp_mul(int x, int y) {
  float ans = *(float *)&x * *(float *)&y;
  return *(int *)&ans;
}

int fp_div(int x, int y) {
  float ans = *(float *)&x / *(float *)&y;
  return *(int *)&ans;
}

int fp_lt(int x, int y) {
  int ans = *(float *)&x < *(float *)&y;
  return ans;
}

int to_fp(int x) {
  float ans = x;
  return *(int *)&ans;
}

int to_int(int x) {
  float ans = *(float *)&x;
  return ans;
}
