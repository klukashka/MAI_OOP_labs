#include <gtest/gtest.h>
#include "../include/number_is_clear.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(123456)==true);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(0)==true);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(-1)==true);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(-123432)==false);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(9999)==true);
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(10)==false);
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(number_is_clear(-12334)==true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}