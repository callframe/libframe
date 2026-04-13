#include <stddef.h>

#include "lf/array.h"
#include "lf/macro.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

static void test_array_init_uses_requested_element_size_and_minimum_capacity(
    void) {
  struct lf_array array = lf_array_new(int);

  TEST_ASSERT_TRUE(lf_array_init_with_(int, &array, 0));

  TEST_ASSERT_NOT_NULL(array.elems);
  TEST_ASSERT_EQUAL_UINT64(sizeof(int), array.elem_size);
  TEST_ASSERT_EQUAL_UINT64(0, array.elems_len);
  TEST_ASSERT_EQUAL_UINT64(LF_ARRAY_INITIAL_CAPACITY, array.elems_cap);

  lf_array_deinit(&array);
}

static void test_array_push_grows_and_preserves_element_order(void) {
  struct lf_array array = lf_array_new(int);
  int values[] = {1, 2, 3, 4, 5, 6};

  TEST_ASSERT_TRUE(lf_array_init_with_(int, &array, 1));
  TEST_ASSERT_TRUE(lf_array_push_(&array, values, lf_countof(values)));

  TEST_ASSERT_EQUAL_UINT64(lf_countof(values), array.elems_len);
  TEST_ASSERT_TRUE(array.elems_cap >= array.elems_len);
  TEST_ASSERT_EQUAL_INT(1, *lf_array_at_(int*, &array, 0));
  TEST_ASSERT_EQUAL_INT(4, *lf_array_at_(int*, &array, 3));
  TEST_ASSERT_EQUAL_INT(6, *lf_array_at_(int*, &array, 5));

  lf_array_deinit(&array);
}

static void test_array_reserve_expands_capacity_without_changing_length(void) {
  struct lf_array array = lf_array_new(int);

  TEST_ASSERT_TRUE(lf_array_init_with_(int, &array, 2));
  TEST_ASSERT_TRUE(lf_array_reserve(&array, 9));

  TEST_ASSERT_EQUAL_UINT64(0, array.elems_len);
  TEST_ASSERT_TRUE(array.elems_cap >= 9);

  lf_array_deinit(&array);
}

static void test_array_pop_returns_last_element_and_updates_length(void) {
  struct lf_array array = lf_array_new(int);
  struct lf_array empty = lf_array_new(int);
  int values[] = {7, 8, 9};
  int popped = 0;

  TEST_ASSERT_TRUE(lf_array_init_with_(int, &array, 0));
  TEST_ASSERT_TRUE(lf_array_init_with_(int, &empty, 0));
  TEST_ASSERT_TRUE(lf_array_push_(&array, values, lf_countof(values)));
  TEST_ASSERT_TRUE(lf_array_pop_(&array, &popped));

  TEST_ASSERT_EQUAL_INT(9, popped);
  TEST_ASSERT_EQUAL_UINT64(2, array.elems_len);
  TEST_ASSERT_FALSE(lf_array_pop_(&empty, &popped));

  lf_array_deinit(&array);
  lf_array_deinit(&empty);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_array_init_uses_requested_element_size_and_minimum_capacity);
  RUN_TEST(test_array_push_grows_and_preserves_element_order);
  RUN_TEST(test_array_reserve_expands_capacity_without_changing_length);
  RUN_TEST(test_array_pop_returns_last_element_and_updates_length);

  return UNITY_END();
}
