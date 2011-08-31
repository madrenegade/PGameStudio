#include "Math/Vector3.h"
#include "Math/DivideByZeroException.h"
#include <gtest/gtest.h>

using namespace Math;

TEST(Vector3Test, DefaultConstructorShouldCreateOrigin)
{
    Vector3 v;
    EXPECT_EQ(v.X, 0);
    EXPECT_EQ(v.Y, 0);
    EXPECT_EQ(v.Z, 0);
}

TEST(Vector3Test, ConstructorWith1_1_1)
{
    Vector3 v(1, 1, 1);
    EXPECT_EQ(v.X, 1);
    EXPECT_EQ(v.Y, 1);
    EXPECT_EQ(v.Z, 1);
}

TEST(Vector3Test, ConstructorWith10_Minus789_651)
{
    Vector3 v(10.12, -789.4, 651.99);
    EXPECT_EQ(v.X, 10.12);
    EXPECT_EQ(v.Y, -789.4);
    EXPECT_EQ(v.Z, 651.99);
}

TEST(Vector3test, CopyConstructor)
{
    Vector3 org(7, 12, -8.3);
    Vector3 copy(org);

    EXPECT_EQ(org.X, copy.X);
    EXPECT_EQ(org.Y, copy.Y);
    EXPECT_EQ(org.Z, copy.Z);
}

TEST(Vector3Test, AssignmentDivideByZeroShouldThrowDivideByZeroException)
{
    Vector3 v(1, 1, 1);

    ASSERT_THROW(v /= 0.0, DivideByZeroException);
}

TEST(Vector3Test, AssignmentDivide)
{
    Vector3 v(1, 1, 1);
    v /= 2.0;

    EXPECT_EQ(0.5, v.X);
    EXPECT_EQ(0.5, v.Y);
    EXPECT_EQ(0.5, v.Z);
}

TEST(Vector3Test, AssignmentAdd)
{
    Vector3 v;
    v += Vector3(1, 2, 3);
    
    EXPECT_EQ(1, v.X);
    EXPECT_EQ(2, v.Y);
    EXPECT_EQ(3, v.Z);
}

TEST(Vector3Test, AssignmentSub)
{
    Vector3 v;
    v -= Vector3(1, 2, 3);
    
    EXPECT_EQ(-1, v.X);
    EXPECT_EQ(-2, v.Y);
    EXPECT_EQ(-3, v.Z);
}

TEST(Vector3Test, Add)
{
    const Vector3 v;
    Vector3 result = v + Vector3(1, 2, 3);
    
    EXPECT_EQ(1, result.X);
    EXPECT_EQ(2, result.Y);
    EXPECT_EQ(3, result.Z);
}

TEST(Vector3Test, Sub)
{
    const Vector3 v;
    Vector3 result = v - Vector3(1, 2, 3);
    
    EXPECT_EQ(-1, result.X);
    EXPECT_EQ(-2, result.Y);
    EXPECT_EQ(-3, result.Z);
}

TEST(Vector3Test, Negate)
{
    const Vector3 v(1, 2, 3);
    Vector3 result(-v);
    
    EXPECT_EQ(-1, result.X);
    EXPECT_EQ(-2, result.Y);
    EXPECT_EQ(-3, result.Z);
}

TEST(Vector3Test, Multiply)
{
    const Vector3 lhs(1, 2, 3);
    Vector3 result(lhs * 5);
    
    EXPECT_EQ(5, result.X);
    EXPECT_EQ(10, result.Y);
    EXPECT_EQ(15, result.Z);
}

TEST(Vector3Test, FriendMultiply)
{
    const Vector3 rhs(1, 2, 3);
    Vector3 result(5 * rhs);
    
    EXPECT_EQ(5, result.X);
    EXPECT_EQ(10, result.Y);
    EXPECT_EQ(15, result.Z);
}

TEST(Vector3Test, Normalize)
{
    Vector3 v(1, 1, 1);
    
    ASSERT_NE(1, v.Length());
    v.Normalize();
    EXPECT_EQ(1, v.Length());
}

TEST(Vector3Test, Length1_0_0) 
{
    const Vector3 v(1, 0, 0);
    EXPECT_EQ(1, v.Length());
}

TEST(Vector3Test, Length0_4_0) 
{
    const Vector3 v(0, 4, 0);
    EXPECT_EQ(4, v.Length());
}

TEST(Vector3Test, Length0_0_Minus3) 
{
    const Vector3 v(0, 0, -3);
    EXPECT_EQ(3, v.Length());
}

TEST(Vector3Test, LenghtSquared1_0_0)
{
    const Vector3 v(1, 0, 0);
    EXPECT_EQ(1, v.LengthSquared());
}

TEST(Vector3Test, LenghtSquared0_4_0)
{
    const Vector3 v(0, 4, 0);
    EXPECT_EQ(16, v.LengthSquared());
}

TEST(Vector3Test, LenghtSquared0_0_Minus3)
{
    const Vector3 v(0, 0, -3);
    EXPECT_EQ(9, v.LengthSquared());
}

TEST(Vector3Test, CrossProduct)
{
    const Vector3 v1(3, -3, 1);
    const Vector3 v2(4, 9, 2);
    
    const Vector3 result(v1.Cross(v2));
    
    EXPECT_EQ(-15, result.X);
    EXPECT_EQ(-2, result.Y);
    EXPECT_EQ(39, result.Z);
}

TEST(Vector3Test, DotProduct)
{
    const Vector3 v1(10, 2, 30);
    const Vector3 v2(3, 9, 4);
    
    EXPECT_EQ(168, v1.Dot(v2));
}