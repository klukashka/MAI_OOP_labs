#include <gtest/gtest.h>
#include "../include/binary.hpp"

TEST(Comparison, test_01)
{
    Binary bin1("100"), bin("100");
    ASSERT_TRUE( bin1 == bin );
}

TEST(Comparison, test_02)
{
    Binary bin1("10"), bin("101");
    ASSERT_FALSE( bin1 == bin );
}

TEST(Comparison, test_03)
{
    Binary bin1("100"), bin("10");
    ASSERT_TRUE( bin1 > bin );
}

TEST(Comparison, test_04)
{
    Binary bin1("0"), bin = {'1','0','0'};
    ASSERT_TRUE( bin1 < bin );
}

TEST(Comparison, test_05)
{
    Binary bin1(4, '1'), bin("1111");
    ASSERT_TRUE( bin1 == bin );
}

TEST(Comparison, test_06)
{
    Binary bin("100");
    Binary bin1;
    bin1 = bin;
    ASSERT_TRUE( bin1 == bin );
}

TEST(Comparison, test_07)
{
    Binary bin(3, '1');
    Binary bin1;
    bin1 = bin;
    ASSERT_TRUE( bin1 == bin );
}

TEST(Comparison, test_08)
{
    Binary bin(3, '1');
    Binary binh(3, '1');
    Binary bin1;
    Binary t;
    bin1 = std::move(bin);
    ASSERT_TRUE( bin1 == binh );
    ASSERT_TRUE( bin == t );
}

TEST(Arithmetic, test_09)
{
    Binary bin1("0"), bin("100");
    Binary bins;
    bins = bin1 + bin;
    ASSERT_TRUE( bin1 + bin == bins );
}

TEST(Arithmetic, test_10)
{
    Binary bin1("10"), bin("100");
    Binary bins("110");
    ASSERT_TRUE( bin1 + bin == bins );
}

TEST(Arithmetic, test_11)
{
    Binary bin1("110"), bin("11");
    Binary bins("1001");
    ASSERT_TRUE( bin1 + bin == bins );
}

TEST(Arithmetic, test_12)
{
    Binary bin1(4, '1'), bin("100");
    Binary bins("10011");
    ASSERT_TRUE( bin1 + bin == bins );
}

TEST(Arithmetic, test_13)
{
    Binary bin1("100"), bin("0");
    Binary bins;
    bins = bin1 - bin;
    ASSERT_TRUE( bin1 - bin == bins );
}

TEST(Arithmetic, test_14)
{
    Binary bin1("110"), bin("10");
    Binary bins("100");
    ASSERT_TRUE( bin1 - bin == bins );
}

TEST(Arithmetic, test_15)
{
    Binary bin1("0"), bin("0");
    Binary bins("0");
    ASSERT_TRUE( bin1 - bin == bins );
}

TEST(Arithmetic, test_16)
{
    Binary bin1(4,'1'), bin("1011");
    Binary bins("100");
    ASSERT_TRUE( bin1 - bin == bins );
}

TEST(Arithmetic, test_17)
{
    Binary bin1(4,'1'), bin;
    Binary bins("1111");
    ASSERT_TRUE( bin1 - bin == bins );
}

TEST(Arithmetic, test_18)
{
    Binary bin1(4,'1'), bin;
    Binary bins("1111");
    ASSERT_TRUE( bin1 + bin == bins );
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}