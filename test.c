#include "lf/array.h"
#include "lf/macro.h"
#include "lf/assert.h"

int main(void) {
  struct lf_array array = lf_array_new(u16);

  u16 val = 400;
  lf_array_push_(&array, &val, 1);
  val = 100;
  lf_array_pop_(&array, &val);
  lf_assert(val == 400);

  lf_array_deinit(&array);
}
