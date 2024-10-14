#include <gtest/gtest.h>
#include "../src/figure_vector.cpp"
#include "../src/triangle.cpp"
#include "../src/rectangle.cpp"
// #include "../src/square.cpp"

TEST(Test, test_00)
{
    double eps = std::numeric_limits<double>::epsilon();
    Triangle tr;
    Rectangle rec;
    ASSERT_TRUE((double(tr) - double(rec)) < eps);
}

TEST(Test, test_01)
{
    double eps = std::numeric_limits<double>::epsilon();
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    ASSERT_TRUE((double(tr) - 0.5) < eps);
}

TEST(Test, test_02)
{
    double eps = std::numeric_limits<double>::epsilon();
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    Rectangle rec(Point(0, 1), Point(2, 1), Point(2, 0), Point(0, 0));
    std::cout << double(tr) << ' ' << double(rec) << '\n';
    ASSERT_TRUE((4*double(tr) - double(rec)) < eps);
}

TEST(Test, test_03)
{
    double eps = std::numeric_limits<double>::epsilon();
    FigureVector vec;
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    // Rectangle rec(Point(0, 1), Point(1, 1), Point(1, 0), Point(0, 0));
    // std::cout << double(rec) << '\n';
    for (int i = 0; i < 10; i++){
        vec.push_back(&tr);
    }
    ASSERT_TRUE(vec.size() == 10);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}