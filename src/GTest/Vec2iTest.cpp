//
// Created by pierre on 18-5-2.
//
#include "Vec2.hpp"
#include <gtest/gtest.h>
class Vec2iTest : public testing::TestWithParam<Vec2i>{
};

TEST_P(Vec2iTest,IsEqual){
	Vec2i point = GetParam();
	EXPECT_EQ(Vec2i(1,2),point);
};

INSTANTIATE_TEST_CASE_P(IsEqual,Vec2iTest,testing::Values(Vec2i(1,2)));
