#include "lf/allocator.h"

#include <stddef.h>
#include <stdlib.h>

#include "lf/assert.h"
#include "lf/bit.h"
#include "lf/macro.h"

static u8* lf_allocate_default(u8* self, usize size, usize align) {
  lf_unused(self);
  lf_assert(lf_ispow2(align));
  lf_assert(size != 0 && size % align == 0);

  return aligned_alloc(align, size);
}

static void lf_deallocate_default(u8* self, u8* p) {
  lf_unused(self);
  free(p);
}

static const struct lf_allocator LF_ALLOCATOR_DEFAULT = {
    .self = NULL,
    .allocate = lf_allocate_default,
    .deallocate = lf_deallocate_default,
};

_Thread_local const struct lf_allocator* LF_ALLOCATOR = &LF_ALLOCATOR_DEFAULT;

const struct lf_allocator* lf_allocator_default(void) {
  return &LF_ALLOCATOR_DEFAULT;
}

u8* lf_allocate(usize size, usize align) {
  lf_assert(LF_ALLOCATOR != NULL);
  return LF_ALLOCATOR->allocate(LF_ALLOCATOR->self, size, align);
}

void lf_deallocate(u8* p) {
  lf_assert(LF_ALLOCATOR != NULL);
  LF_ALLOCATOR->deallocate(LF_ALLOCATOR->self, p);
}
