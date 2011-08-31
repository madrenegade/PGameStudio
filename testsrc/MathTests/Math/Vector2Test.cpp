#include "Math/Vector2.h"
#include <gtest/gtest.h>

using namespace Math;

TEST(Vector2Test, DefaultConstructorShouldCreateOrigin)
{
    Vector2 v;
    EXPECT_EQ(v.X, 0);
    EXPECT_EQ(v.Y, 0);
}

TEST(Vector2Test, ConstructorWith1_1)
{
    Vector2 v(1, 1);
    EXPECT_EQ(v.X, 1);
    EXPECT_EQ(v.Y, 1);
}

TEST(Vector2Test, ConstructorWith10_Minus789)
{
    Vector2 v(10.12, -789.4);
    EXPECT_EQ(v.X, 10.12);
    EXPECT_EQ(v.Y, -789.4);
}