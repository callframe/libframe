#include <limits.h>

#include "lf/bit.h"
#include "lf/macro.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

static void test_lf_ispow2_accepts_powers_of_two(void) {
  TEST_ASSERT_TRUE(lf_ispow2(1));
  TEST_ASSERT_TRUE(lf_ispow2(2));
  TEST_ASSERT_TRUE(lf_ispow2(1024));
}

static void test_lf_ispow2_rejects_zero_and_non_powers(void) {
  TEST_ASSERT_FALSE(lf_ispow2(0));
  TEST_ASSERT_FALSE(lf_ispow2(3));
  TEST_ASSERT_FALSE(lf_ispow2(12));
}

static void test_alignment_helpers_round_values_as_expected(void) {
  TEST_ASSERT_TRUE(lf_aligned_to(32, 8));
  TEST_ASSERT_FALSE(lf_aligned_to(34, 8));
  TEST_ASSERT_EQUAL_UINT64(40, lf_align_up(33, 8));
  TEST_ASSERT_EQUAL_UINT64(32, lf_align_down(39, 8));
}

static void test_bit_scan_helpers_handle_zero_and_non_zero_values(void) {
  const i32 bit_width = lf_cast(i32, sizeof(usize) * CHAR_BIT);

  TEST_ASSERT_EQUAL_INT(bit_width, lf_ctz(0));
  TEST_ASSERT_EQUAL_INT(bit_width, lf_clz(0));
  TEST_ASSERT_EQUAL_INT(3, lf_ctz(lf_cast(usize, 40)));
  TEST_ASSERT_EQUAL_INT(0, lf_clz(lf_cast(usize, 1) << (bit_width - 1)));
}

static void test_log2_helpers_round_toward_expected_boundaries(void) {
  TEST_ASSERT_EQUAL_UINT64(0, lf_log2floor(1));
  TEST_ASSERT_EQUAL_UINT64(0, lf_log2ceil(1));
  TEST_ASSERT_EQUAL_UINT64(3, lf_log2floor(15));
  TEST_ASSERT_EQUAL_UINT64(4, lf_log2ceil(15));
  TEST_ASSERT_EQUAL_UINT64(4, lf_log2floor(16));
  TEST_ASSERT_EQUAL_UINT64(4, lf_log2ceil(16));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_lf_ispow2_accepts_powers_of_two);
  RUN_TEST(test_lf_ispow2_rejects_zero_and_non_powers);
  RUN_TEST(test_alignment_helpers_round_values_as_expected);
  RUN_TEST(test_bit_scan_helpers_handle_zero_and_non_zero_values);
  RUN_TEST(test_log2_helpers_round_toward_expected_boundaries);

  return UNITY_END();
}
