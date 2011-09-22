#include "Math/Matrix4.h"
#include <gtest/gtest.h>
#include <glog/log_severity.h>

#include "Utilities/StopWatch.h"
#include <boost/scoped_array.hpp>

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

TEST(Matrix4Test, testMultiplyPerformance)
{
    const unsigned int NUM_MATRIXES = 10000000;
    boost::scoped_array<Math::Matrix4> m(new Math::Matrix4[NUM_MATRIXES]);
    Math::Matrix4 res;
    
    Utilities::StopWatch sw("Matrix4 Multiply");
    
    for(unsigned int i = 0; i < NUM_MATRIXES; ++i)
    {
        res = res * m[i];
    }
}
