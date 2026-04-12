#pragma once

#include <stddef.h>

#include "lf/bit.h"

enum {
  LF_ARRAY_INITIAL_CAPACITY = 4,
  LF_ARRAY_GROWTH_FACTOR = 2,
};

struct lf_array {
  u8* elems;
  usize elems_len, elems_cap;
  usize elem_size;
};

// Raw Api

void lf_array_init_with(struct lf_array* array, usize elem_size,
                        usize initial_cap);
void lf_array_deinit(struct lf_array* array);

void lf_array_resize(struct lf_array* array, usize new_cap);
void lf_array_reserve(struct lf_array* array, usize min_len);

void lf_array_push(struct lf_array* array, const u8* elems, usize elems_len);
void lf_array_pop(struct lf_array* array, u8* out_elem);

u8* lf_array_at(const struct lf_array* array, usize index);

// Type wrapper

#define lf_array_new(T) ((struct lf_array){NULL, 0, 0, sizeof(T)})

#define lf_array_init_with_(T, array, initial) \
  lf_array_init_with((array), sizeof(T), initial)

#define lf_array_push_(array, elems, elems_len) \
  lf_array_push((array), lf_cast(const u8*, (elems)), (elems_len))

#define lf_array_pop_(array, elem) lf_array_pop((array), lf_cast(u8*, (elem)))
#define lf_array_at_(T, array, index) lf_cast(T, lf_array_at((array), (index)))
