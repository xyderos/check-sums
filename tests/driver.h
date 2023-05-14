#include <check.h>

#include "../src/crc/crc.h"
#include "../src/fletcher/fletcher.h"
#include "../src/xor/xor.h"
#include "../src/xor_per_block/xor_per_block.h"

START_TEST(VERIFY_CRC)
{
	int result = crc_16("data/trash", "data/trash.crc");

	ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(VERIFY_FLETCHER)
{
	int result = fletcher("data/trash", "data/trash.fletcher");

	ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(VERIFY_XOR)
{
	int result = xor("data/trash", "data/trash.xor");

	ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(VERIFY_XOR_PER_BLOCK)
{
	int result = xor_per_block("data/trash", "data/trash.xor_per_block");

	ck_assert_int_eq(result, 0);
}
END_TEST
