// #pragma once

#include <gtest/gtest.h>
#include "../src/figure_vector.cpp"
#include "../src/triangle.cpp"
#include "../src/rectangle.cpp"
#include "../src/square.cpp"

TEST(Construction, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle tr;
    Rectangle rec;
    Square sq;
    ASSERT_TRUE((double(tr) - double(rec)) < test_eps);
    ASSERT_TRUE((double(sq) - double(rec)) < test_eps);
}

// -------------- Triangle -------------

TEST(Triangle, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    ASSERT_TRUE((double(tr) - 0.5) < test_eps);
}

TEST(Triangle, test_01)
{
    double test_eps = std::numeric_limits<double>::epsilon();

    std::stringstream ss, sss;
    Triangle tr;
    ss << "0 0 1 1 0 1";
    ss >> tr;
    sss << tr;
    EXPECT_EQ(sss.str(), "x  0, y  0\nx  1, y  1\nx  0, y  1\n");
}

TEST(Triangle, test_02)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Point p1(0.0, 1.0); 
    Point p2(0.0, 0.0);
    Point p3(1.0, 0.0);
    Triangle tr1(p1, p2, p3);
    ASSERT_TRUE((double(tr1) - 0.5) < test_eps);
}

TEST(Triangle, test_03)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle tr1(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    Triangle tr2(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    ASSERT_TRUE((double(tr1) - double(tr2)) < test_eps);
}

TEST(Triangle, test_04)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle tr1(Point(-1, 0), Point(1, 0), Point(0, 2));
    double y = double(2) / double(3);
    Point p(0, y);
    ASSERT_TRUE(Point(tr1.get_center() - p).x_ < test_eps);
    ASSERT_TRUE(Point(tr1.get_center() - p).y_ < test_eps);
}


TEST(Triangle, test_05)
{
    Triangle tr;
    Triangle tr1(Point(-1, 0), Point(1, 0), Point(0, 2));
    Triangle tr2(tr1);
    EXPECT_EQ(tr1, tr2);
    Triangle tr3 = std::move(tr2);
    EXPECT_EQ(tr3, tr1);
    EXPECT_EQ(tr, tr2);
}

// --------------- Rectangle -------------------------

TEST(Rectangle, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Rectangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0), Point(1, 1));
    ASSERT_TRUE((double(tr) - 1) < test_eps);
}

TEST(Rectangle, test_01)
{
    double test_eps = std::numeric_limits<double>::epsilon();

    std::stringstream ss, sss;
    Rectangle rec;
    ss << "0 0 0 1 1 1 1 0";
    ss >> rec;
    sss << rec;
    EXPECT_EQ(sss.str(), "x  0, y  0\nx  0, y  1\nx  1, y  1\nx  1, y  0\n");
}

TEST(Rectangle, test_02)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Point p1(0.0, 0); 
    Point p2(0.0, 1.0);
    Point p3(1.0, 1.0);
    Point p4(1.0, 0.0);
    Rectangle rec1(p1, p2, p3, p4);
    ASSERT_TRUE((double(rec1) - 1) < test_eps);
}

TEST(Rectangle, test_03)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Rectangle rec1(Point(0.0, 0.0), Point(0.0,1.0), Point(10.0, 1.0), Point(10, 0));
    Rectangle rec2(Point(0.0, 0.0), Point(0.0, 1.0), Point(5.0, 1), Point(5, 0));
    ASSERT_TRUE((double(rec1) - 2*double(rec2)) < test_eps);
}

TEST(Rectangle, test_04)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Rectangle rec1(Point(0.0, 0.0), Point(0.0, 1.0), Point(5.0, 1), Point(5, 0));
    Point p(2.5, 0.5);
    ASSERT_TRUE(Point(rec1.get_center() - p).x_ < test_eps);
    ASSERT_TRUE(Point(rec1.get_center() - p).y_ < test_eps);
}


TEST(Rectangle, test_05)
{
    Rectangle rec;
    Rectangle rec1(Point(0.0, 0.0), Point(0.0, 1.0), Point(5.0, 1), Point(5, 0));
    Rectangle rec2(rec1);
    EXPECT_EQ(rec1, rec2);
    Rectangle rec3 = std::move(rec2);
    EXPECT_EQ(rec3, rec1);
    EXPECT_EQ(rec, rec2);
}
// --------- Square --------

TEST(Square, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Square sq1(Point(0.0, 0.0), Point(0.0, 10), Point(10, 10), Point(10, 0));
    ASSERT_TRUE(double(sq1) - 100 < test_eps);
    Point p(5, 5);
    ASSERT_TRUE(Point(sq1.get_center() - p).x_ < test_eps);
    ASSERT_TRUE(Point(sq1.get_center() - p).y_ < test_eps);
}

TEST(Vector, test_03)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    FigureVector vec;
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));

    for (int i = 0; i < 10; ++i){
        vec.push_back(&tr);
    }
    ASSERT_TRUE(vec.size() == 10);
}

TEST(Vector, test_04)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    FigureVector vec;
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    // Rectangle rec(Point(0, 1), Point(1, 1), Point(1, 0), Point(0, 0));
    // std::cout << double(rec) << '\n';
    for (int i = 0; i < 10; ++i){
        vec.push_back(&tr);
    }
    for (int i = 0; i < 5; ++i){
        vec.remove(0);
    }
    ASSERT_TRUE(vec.size() == 5);
    for (int i = 0; i < 4; ++i){
        ASSERT_TRUE((double(*vec.get(i)) - double(*vec.get(i+1))) < test_eps);
    }
}

TEST(Vector, test_05)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    FigureVector vec;
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    // Rectangle rec(Point(0, 1), Point(1, 1), Point(1, 0), Point(0, 0));
    // std::cout << double(rec) << '\n';
    for (int i = 0; i < 10; ++i){
        vec.push_back(&tr);
    }
    for (int i = 0; i < 5; ++i){
        vec.remove(0);
    }
    ASSERT_TRUE(vec.size() == 5);
    for (int i = 0; i < 4; ++i){
        ASSERT_TRUE((double(*vec.get(i)) - double(*vec.get(i+1))) < test_eps);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}