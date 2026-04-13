#include "lf/array.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "lf/assert.h"
#include "lf/bit.h"
#include "lf/macro.h"

static inline usize lf_array_next_cap(usize curr_cap, usize min_size) {
  curr_cap = curr_cap == 0 ? LF_ARRAY_INITIAL_CAPACITY : curr_cap;
  while (min_size > curr_cap) curr_cap = curr_cap * LF_ARRAY_GROWTH_FACTOR;
  return curr_cap;
}

bool lf_array_init_with(struct lf_array* array, usize elem_size,
                        usize initial_cap) {
  lf_zerout(*array, 1);

  usize new_cap = lf_array_next_cap(0, initial_cap);
  usize size = lf_align_up(new_cap * elem_size, _Alignof(max_align_t));

  u8* new_elems = malloc(size);
  if (new_elems == NULL) return false;
  lf_zerout(*new_elems, size);

  array->elems = new_elems;
  array->elems_cap = new_cap;
  array->elem_size = elem_size;
  return true;
}

void lf_array_deinit(struct lf_array* array) {
  free(array->elems);
  lf_zerout(*array, 1);
}

bool lf_array_resize(struct lf_array* array, usize new_cap) {
  lf_assert(new_cap >= array->elems_len);

  struct lf_array temp = {0};
  if (!lf_array_init_with(&temp, array->elem_size, new_cap)) return false;

  memcpy(temp.elems, array->elems, array->elem_size * array->elems_len);
  temp.elems_len = array->elems_len;
  free(array->elems);

  *array = temp;
  return true;
}

bool lf_array_reserve(struct lf_array* array, usize min_len) {
  if (array->elems_cap >= min_len) return true;

  usize new_cap = lf_array_next_cap(array->elems_len, min_len);
  return lf_array_resize(array, new_cap);
}

bool lf_array_push(struct lf_array* array, const u8* elems, usize elems_len) {
  lf_assert(elems != NULL || elems_len == 0);

  if (!lf_array_reserve(array, array->elems_len + elems_len)) return false;
  u8* at = lf_array_at(array, array->elems_len);
  memcpy(at, elems, array->elem_size * elems_len);
  array->elems_len += elems_len;
  return true;
}

bool lf_array_pop(struct lf_array* array, u8* out_elem) {
  lf_assert(out_elem != NULL);
  if (array->elems_len == 0) return false;

  u8* at = lf_array_at(array, array->elems_len - 1);
  memcpy(out_elem, at, array->elem_size);
  array->elems_len -= 1;
  return true;
}

u8* lf_array_at(const struct lf_array* array, usize index) {
  lf_assert(array->elems_cap > index);
  return array->elems + array->elem_size * index;
}
