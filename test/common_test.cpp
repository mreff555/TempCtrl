#include <gtest/gtest.h>
#include <common.hpp>

TEST(Common, getMin)
{
  ParameterLimits params(0, 212, 100);
  EXPECT_EQ(params.getMin(), 0);
  EXPECT_NE(params.getMin(), -1);
  EXPECT_EQ(params.getMin(), 0.0);
}


TEST(Common, getMax)
{
  ParameterLimits params(0, 212, 100);
  EXPECT_EQ(params.getMax(), 212);
  EXPECT_NE(params.getMax(), 213);
  EXPECT_EQ(params.getMax(), 212.0);
}

TEST(Common, getDefault)
{
  ParameterLimits params(0, 212, 100);
  EXPECT_EQ(params.getDefault(), 100);
  EXPECT_NE(params.getDefault(), 99);
  EXPECT_EQ(params.getDefault(), 100.0);
}

TEST(Common, validate)
{
  ParameterLimits params(0, 212, 100);
  EXPECT_EQ(params.validate(35), 35);
  EXPECT_EQ(params.validate(212), 212);
  EXPECT_EQ(params.validate(0), 0 );
  EXPECT_FLOAT_EQ(params.validate(24.3), 24.3);
  EXPECT_FLOAT_EQ(params.validate(97.24), 97.24);
  EXPECT_FLOAT_EQ(params.validate(39.184), 39.184);
  EXPECT_FLOAT_EQ(params.validate(-31.184), params.getDefault());
  EXPECT_EQ(params.validate(400), params.getDefault());
  EXPECT_EQ(params.validate(params.getDefault()), params.getDefault());
}
