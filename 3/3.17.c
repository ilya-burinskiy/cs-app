long lt_cnt = 0;
long gt_cnt = 0;

// A.
long gotodiff_se(long x, long y) {
  long result;
  if (x < y) {
    goto x_lt_y;
  }
  ++gt_cnt;
  result = x - y;
  goto done;
x_lt_y:
  ++lt_cnt;
  result = y - x;
done:
  return result;
}

// B.
