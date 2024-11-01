// #pragma once

#include <gtest/gtest.h>
#include "../src/figure_vector.cpp"
#include "../src/figure.cpp"
#include "../src/triangle.cpp"
#include "../src/rectangle.cpp"
#include "../src/square.cpp"
#include "../src/point.cpp"


// -------------- double -------------------------
TEST(Construction, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle<double> tr;
    Rectangle<double> rec;
    Square<double> sq;
    ASSERT_TRUE((double(tr) - double(rec)) < test_eps);
    ASSERT_TRUE((double(sq) - double(rec)) < test_eps);
}

// -------------- Triangle -------------

TEST(Triangle, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle<double> tr(
        Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    ASSERT_TRUE((double(tr) - 0.5) < test_eps);
}

TEST(Triangle, test_01)
{
    double test_eps = std::numeric_limits<double>::epsilon();

    std::stringstream ss, sss;
    Triangle<double> tr;
    ss << "0 0 1 1 0 1";
    ss >> tr;
    sss << tr;
    EXPECT_EQ(sss.str(), "x  0, y  0\nx  1, y  1\nx  0, y  1\n");
}

TEST(Triangle, test_02)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Point<double> p1(0.0, 1.0); 
    Point<double> p2(0.0, 0.0);
    Point<double> p3(1.0, 0.0);
    Triangle<double> tr1(p1, p2, p3);
    ASSERT_TRUE((double(tr1) - 0.5) < test_eps);
}

TEST(Triangle, test_03)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle<double> tr1(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    Triangle<double> tr2(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    ASSERT_TRUE((double(tr1) - double(tr2)) < test_eps);
}

TEST(Triangle, test_04)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Triangle<double> tr1(Point<double>(-1, 0), Point<double>(1, 0), Point<double>(0, 2));
    double y = double(2) / double(3);
    Point<double> p(0, y);
    Point<double> center = tr1.get_center();
    Point<double> nil;
    ASSERT_TRUE((center - p) <= nil);
}


TEST(Triangle, test_05)
{
    Triangle<double> tr;
    Triangle<double> tr1(Point<double>(-1, 0), Point<double>(1, 0), Point<double>(0, 2));
    Triangle<double> tr2(tr1);
    EXPECT_EQ(tr1, tr2);
    Triangle<double> tr3 = std::move(tr2);
    EXPECT_EQ(tr3, tr1);
    EXPECT_EQ(tr, tr2);
}

// --------------- Rectangle -------------------------

TEST(Rectangle, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Rectangle<double> tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0));
    ASSERT_TRUE((double(tr) - 1) < test_eps);
}

TEST(Rectangle, test_01)
{
    double test_eps = std::numeric_limits<double>::epsilon();

    std::stringstream ss, sss;
    Rectangle<double> rec;
    ss << "0 0 0 1 1 1 1 0";
    ss >> rec;
    sss << rec;
    EXPECT_EQ(sss.str(), "x  0, y  0\nx  0, y  1\nx  1, y  1\nx  1, y  0\n");
}

TEST(Rectangle, test_02)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Point<double> p1(0.0, 0); 
    Point<double> p2(0.0, 1.0);
    Point<double> p3(1.0, 1.0);
    Point<double> p4(1.0, 0.0);
    Rectangle<double> rec1(p1, p2, p3, p4);
    ASSERT_TRUE((double(rec1) - 1) < test_eps);
}

TEST(Rectangle, test_03)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Rectangle<double> rec1(Point(0.0, 0.0), Point(0.0,1.0), Point(10.0, 1.0), Point(10.0, 0.0));
    Rectangle<double> rec2(Point(0.0, 0.0), Point(0.0, 1.0), Point(5.0, 1.0), Point(5.0, 0.0));
    ASSERT_TRUE((double(rec1) - 2*double(rec2)) < test_eps);
}

TEST(Rectangle, test_04)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Rectangle rec1(Point(0.0, 0.0), Point(0.0, 1.0), Point(5.0, 1.0), Point(5.0, 0.0));
    Point p(2.5, 0.5);
    Point<double> center = rec1.get_center();
    Point<double> nil;
    ASSERT_TRUE((center - p) <= nil);
    ASSERT_TRUE((center - p) <= nil);
}


TEST(Rectangle, test_05)
{
    Rectangle<double> rec;
    Rectangle<double> rec1(Point(0.0, 0.0), Point(0.0, 1.0), Point(5.0, 1.0), Point(5.0, 0.0));
    Rectangle<double> rec2(rec1);
    EXPECT_EQ(rec1, rec2);
    Rectangle<double> rec3 = std::move(rec2);
    EXPECT_EQ(rec3, rec1);
    EXPECT_EQ(rec, rec2);
}
// --------- Square --------

TEST(Square, test_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    Square<double> sq1(Point(0.0, 0.0), Point(0.0, 10.0), Point(10.0, 10.0), Point(10.0, 0.0));
    ASSERT_TRUE(double(sq1) - 100 < test_eps);
    Point<double> p(5.0, 5.0);
    ASSERT_TRUE(Point(sq1.get_center() - p) <= Point<double>());
}

TEST(Vector, test_03)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    FigureVector<double> vec;
    Triangle tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));

    for (int i = 0; i < 10; ++i){
        vec.push_back(&tr);
    }
    ASSERT_TRUE(vec.size() == 10);
}

TEST(Vector, test_04)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    FigureVector<double> vec;
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
    FigureVector<double> vec;
    Triangle<double> tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
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

// ------------------- int ------------------------

// -------------- triangle -------------

TEST(Triangle, test_int_00)
{
    int test_eps = 0;
    Triangle<int> tr1(Point<int>(-1, 0), Point<int>(1, 0), Point<int>(0, 2));
    int y = int(2) / int(3);
    Point<int> p(0, y);
    Point<int> center = tr1.get_center();
    Point<int> nil;
    ASSERT_TRUE((center - p) <= nil);
}

TEST(Triangle, test_int_01)
{
    Triangle<int> tr;
    Triangle<int> tr1(Point<int>(-1, 0), Point<int>(1, 0), Point<int>(0, 2));
    Triangle<int> tr2(tr1);
    EXPECT_EQ(tr1, tr2);
    Triangle<int> tr3 = std::move(tr2);
    EXPECT_EQ(tr3, tr1);
    EXPECT_EQ(tr, tr2);
}

TEST(Triangle, test_int_02)
{
    int test_eps = 0;
    Point<int> p1(0.0, 1.0); 
    Point<int> p2(0.0, 0.0);
    Point<int> p3(1.0, 0.0);
    Triangle<int> tr1(p1, p2, p3);
    ASSERT_TRUE((double(tr1) - 0.5) <= test_eps);
}

// --------------- rectangle ------------------

TEST(Rectangle, test_int_00)
{
    std::stringstream ss, sss;
    Rectangle<int> rec;
    ss << "0 0 0 1 1 1 1 0";
    ss >> rec;
    sss << rec;
    EXPECT_EQ(sss.str(), "x  0, y  0\nx  0, y  1\nx  1, y  1\nx  1, y  0\n");
}

TEST(Rectangle, test_int_01)
{
    int test_eps = 0;
    Rectangle<int> rec1(Point(0, 0), Point(0,1), Point(10, 1), Point(10, 0));
    Rectangle<int> rec2(Point(0, 0), Point(0, 1), Point(5, 1), Point(5, 0));
    ASSERT_TRUE((double(rec1) - 2*double(rec2)) <= test_eps);
}

// ------------ square ----------

TEST(Square, test_int_00)
{
    int test_eps = 0;
    Square<int> sq1(Point(0, 0), Point(0, 10), Point(10, 10), Point(10, 0));
    ASSERT_TRUE(double(sq1) - 100 <= test_eps);
    Point<int> p(5.0, 5.0);
    ASSERT_TRUE(Point(sq1.get_center() - p) <= Point<int>());
}

// ------------ vector ------------------

TEST(Vector, test_int_00)
{
    double test_eps = std::numeric_limits<double>::epsilon();
    FigureVector<double> vec_d;
    Triangle<double> tr(Point(0.0, 1.0), Point(0.0, 0.0), Point(1.0, 0.0));
    for (int i = 0; i < 10; ++i){
        vec_d.push_back(&tr);
    }
    for (int i = 0; i < 5; ++i){
        vec_d.remove(0);
    }
    ASSERT_TRUE(vec_d.size() == 5);
    for (int i = 0; i < 4; ++i){
        ASSERT_TRUE((double(*vec_d.get(i)) - double(*vec_d.get(i+1))) <= test_eps);
    }
}

TEST(Vector, test_int_01)
{
    int test_eps = 0;
    Rectangle<int> rec(Point(0, 1), Point(1, 1), Point(1, 0), Point(0, 0));
    FigureVector<int> vec_i;
    for (int i = 0; i < 10; ++i){
        vec_i.push_back(&rec);
    }
    for (int i = 0; i < 5; ++i){
        vec_i.remove(0);
    }
    ASSERT_TRUE(vec_i.size() == 5);
    for (int i = 0; i < 4; ++i){
        ASSERT_TRUE((double(*vec_i.get(i)) - double(*vec_i.get(i+1))) <= test_eps);
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}