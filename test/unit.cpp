#include <gtest/gtest.h>
#include "../include/binary.hpp"

// -------- constructors ----------

TEST(Constructors, test_01)
{
    Binary bin1("100"), bin(4);
    ASSERT_TRUE( bin1 == bin );
}

TEST(Constructors, test_02)
{
    Binary bin1(3, '1'), bin(7);
    ASSERT_TRUE( bin1 == bin );
}

TEST(Constructors, test_03)
{
    Binary bin1(3, '1'), bin(7);
    ASSERT_TRUE( bin1 == bin );
}

TEST(Constructors, test_04)
{
    Binary bin1(3, '1'), bin(7);
    ASSERT_TRUE( bin1 == bin );
}

TEST(Constructors, test_05)
{
    Binary bin1(3, '1'), bin{'1', '1', '1'};
    ASSERT_TRUE( bin1 == bin );
}

TEST(Constructors, test_06)
{
    Binary bin1(4, '0'), bin{"000"};
    ASSERT_TRUE( bin1 == bin );
}

TEST(Constructors, test_07)
{
    Binary bin(7);
    Binary binh(3, '1');
    Binary bin1;
    Binary t;
    bin1 = std::move(bin);
    ASSERT_TRUE( bin1 == binh );
    ASSERT_TRUE( bin == t );
}

TEST(Constructors, test_08)
{
    Binary bin(0);
    Binary bin1;
    Binary bin2("0");
    bin1 = std::move(bin);
    ASSERT_TRUE(bin1 != bin);
    ASSERT_TRUE(bin1 == bin2);
}

TEST(Constructors, test_09)
{
    Binary bin(1);
    Binary bin1;
    Binary bin2("0001");
    bin1 = std::move(bin);
    ASSERT_TRUE(bin1 != bin);
    ASSERT_TRUE(bin1 == bin2);
}

// ----------- comparison ---------------

TEST(Comparison, test_01)
{
    Binary bin1("000010"), bin("010");
    ASSERT_TRUE(bin1 == bin);
}

TEST(Comparison, test_02)
{
    Binary bin1("10"), bin("101");
    ASSERT_TRUE(bin1 != bin);
}

TEST(Comparison, test_03)
{
    Binary bin1(4), bin(2);
    ASSERT_TRUE(bin1 > bin);
}

TEST(Comparison, test_04)
{
    Binary bin1(0), bin(1);
    ASSERT_TRUE(bin1 <= bin);
}

TEST(Comparison, test_05)
{
    Binary bin1(1, '1'), bin("1111");
    ASSERT_TRUE(bin1 <= bin);
}

TEST(Comparison, test_06)
{
    Binary bin1(1, '1'), bin("1111");
    ASSERT_TRUE(bin1 <= bin);
}

TEST(Comparison, test_07)
{
    Binary bin(3, '1');
    Binary bin1;
    bin1 = bin;
    std::cout << bin << " " << bin1 << '\n';
    ASSERT_TRUE(bin1 == bin);
}

TEST(Comparison, test_08)
{
    Binary bin(3, '1');
    Binary binh(3, '1');
    Binary bin1;
    Binary t;
    bin1 = std::move(bin);
    ASSERT_TRUE(bin1 == binh);
    ASSERT_TRUE(bin == t);
}

// ---------- arithmetic ----------

TEST(Arithmetic, test_01)
{
    Binary bin(0), bin1(2030), bin2(1000), bin3(1030);
    ASSERT_TRUE((bin1 - bin2 - bin3) == bin);
}

TEST(Arithmetic, test_02)
{
    Binary bin(1030), bin1(2030), bin2(1000);
    ASSERT_TRUE(bin1 - bin2 == bin);
}

TEST(Arithmetic, test_03)
{
    Binary bin(0), bin1(10), bin2(2), bin3(8);
    ASSERT_TRUE(bin1 - bin2 - bin3 == bin);
}

TEST(Arithmetic, test_04)
{
    Binary bin("111"), bin1(13), bin2(6);
    ASSERT_TRUE(bin1 - bin2 == bin);
}

TEST(Arithmetic, test_05)
{
    Binary bin(0), bin1("00000"), bin2("0000001"), bin3(1);
    ASSERT_TRUE(bin1 + bin + bin2 - bin3 == bin);
}

TEST(Arithmetic, test_06)
{
    Binary bin1(7), bin(15);
    Binary bins(22);
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_07)
{
    Binary bin1("110"), bin("11");
    Binary bins("1001");
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_08)
{
    Binary bin1("00000"), bin("100");
    Binary bins;
    bins = bin1 + bin;
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_09)
{
    Binary bin1("0"), bin("100");
    Binary bins;
    bins = bin1 + bin;
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_10)
{
    Binary bin1("10"), bin("100");
    Binary bins("110");
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_11)
{
    Binary bin1("110"), bin("11");
    Binary bins("1001");
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_12)
{
    Binary bin1(4, '1'), bin("100");
    Binary bins("10011");
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_13)
{
    Binary bin1("100"), bin("0");
    Binary bins;
    bins = bin1 - bin;
    ASSERT_TRUE(bin1 - bin == bins);
}

TEST(Arithmetic, test_14)
{
    Binary bin1("110"), bin("10");
    Binary bins("100");
    ASSERT_TRUE(bin1 - bin == bins);
}

TEST(Arithmetic, test_15)
{
    Binary bin1("0"), bin("0");
    Binary bins("0");
    ASSERT_TRUE(bin1 - bin == bins);
}

TEST(Arithmetic, test_16)
{
    Binary bin1(4,'1'), bin("1011");
    Binary bins("100");
    ASSERT_TRUE(bin1 - bin == bins);
}

TEST(Arithmetic, test_17)
{
    Binary bin1(4,'1'), bin;
    Binary bins("1111");
    ASSERT_TRUE(bin1 - bin == bins);
}

TEST(Arithmetic, test_18)
{
    Binary bin1(4,'1'), bin;
    Binary bins("1111");
    ASSERT_TRUE(bin1 + bin == bins);
}

TEST(Arithmetic, test_19)
{
    Binary bin1(7), bin("101");
    Binary bins(12);
    ASSERT_TRUE(bin1 + bin == bins);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}