//
// Created by tom on 03/03/23.
//
#include "gtest/gtest.h"
#include "Axis.h"

TEST(PolarInterpolator, Axis) {
    CoordinateAxis<float> axis(0, 10, 11);
    EXPECT_EQ(axis.getMin(), 0);
    EXPECT_EQ(axis.getMax(), 10);
    EXPECT_EQ(axis.getdX(), 1);

    auto interp_point = axis.findInterpVertex(0);
    EXPECT_EQ(interp_point.index, 0);
    EXPECT_EQ(interp_point.normalizedDistance, 0);
    EXPECT_EQ(interp_point.inBounds, true);

    interp_point = axis.findInterpVertex(0.5);
    EXPECT_EQ(interp_point.index, 0);
    EXPECT_EQ(interp_point.normalizedDistance, 0.5);
    EXPECT_EQ(interp_point.inBounds, true);

    interp_point = axis.findInterpVertex(9.5);
    EXPECT_EQ(interp_point.index, 9);
    EXPECT_EQ(interp_point.normalizedDistance, 0.5);
    EXPECT_EQ(interp_point.inBounds, true);

    interp_point = axis.findInterpVertex(10);
    EXPECT_EQ(interp_point.index, 9);
    EXPECT_EQ(interp_point.normalizedDistance, 1);
    EXPECT_EQ(interp_point.inBounds, true);

    interp_point = axis.findInterpVertex(10.5);
    EXPECT_EQ(interp_point.index, 9);
    EXPECT_EQ(interp_point.normalizedDistance, 1.5);
    EXPECT_EQ(interp_point.inBounds, false);

    interp_point = axis.findInterpVertex(-0.5);
    EXPECT_EQ(interp_point.index, 0);
    EXPECT_EQ(interp_point.normalizedDistance, -0.5);
    EXPECT_EQ(interp_point.inBounds, false);
}