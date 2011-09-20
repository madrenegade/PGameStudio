#include "Math/Matrix4.h"
#include <gtest/gtest.h>

using namespace Math;

TEST(Matrix4Test, createTranslationPosition)
{
    Vector4 v(0, 0, 0, 1);
    
    Matrix4 m = Matrix4::CreateTranslation(Vector3(1, 2, 3));
    v *= m;
    
    EXPECT_EQ(v.X, 1);
    EXPECT_EQ(v.Y, 2);
    EXPECT_EQ(v.Z, 3);
}

TEST(Matrix4Test, createTranslationDirection)
{
    Vector4 v(0, 0, 0, 0);
    
    Matrix4 m = Matrix4::CreateTranslation(Vector3(1, 2, 3));
    v *= m;
    
    EXPECT_EQ(v.X, 0);
    EXPECT_EQ(v.Y, 0);
    EXPECT_EQ(v.Z, 0);
}
