
int find_strictly_smaller(const float *arr, int n, float key) {
  int lo = 0, hi = n - 1;
  int result = -1; // index of the element just smaller

  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;

    if (*(arr + mid) < key) {
      result = mid; // candidate found
      lo = mid + 1; // look right for a larger valid one
    } else {
      hi = mid - 1; // too big, go left
    }
  }

  return result; // -1 if none smaller
}
