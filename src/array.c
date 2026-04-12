#include "lf/array.h"

#include <stddef.h>
#include <string.h>

#include "lf/allocator.h"
#include "lf/assert.h"

static inline usize lf_array_next_cap(usize curr_cap, usize min_size) {
  curr_cap = curr_cap == 0 ? LF_ARRAY_INITIAL_CAPACITY : curr_cap;
  while (min_size > curr_cap) curr_cap = curr_cap * LF_ARRAY_GROWTH_FACTOR;
  return curr_cap;
}

void lf_array_deinit(struct lf_array* array) { lf_deallocate(array->elems); }

void lf_array_resize(struct lf_array* array, usize new_cap) {
  lf_assert(new_cap >= array->elems_len);

  usize size = lf_align_up(new_cap * array->elem_size, _Alignof(max_align_t));
  u8* new_elems = lf_allocate(size, _Alignof(max_align_t));
  memcpy(new_elems, array->elems, array->elem_size * array->elems_len);
  lf_deallocate(array->elems);

  array->elems = new_elems;
  array->elems_cap = new_cap;
}

void lf_array_reserve(struct lf_array* array, usize min_len) {
  if (array->elems_cap >= min_len) return;

  usize new_cap = lf_array_next_cap(array->elems_len, min_len);
  lf_array_resize(array, new_cap);
}

void lf_array_push(struct lf_array* array, const u8* elems, usize elems_len) {
  lf_assert(elems != NULL);

  lf_array_reserve(array, array->elems_len + elems_len);
  u8* at = lf_array_at(array, array->elems_len);
  memcpy(at, elems, array->elem_size * elems_len);
  array->elems_len += elems_len;
}

void lf_array_pop(struct lf_array* array, u8* out_elem) {
  lf_assert(array->elems_len > 0);

  u8* at = lf_array_at(array, array->elems_len - 1);
  memcpy(out_elem, at, array->elem_size);
  array->elems_len -= 1;
}

u8* lf_array_at(const struct lf_array* array, usize index) {
  lf_assert(array->elems_cap > index);
  return array->elems + array->elem_size * index;
}
