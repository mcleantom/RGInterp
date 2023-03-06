//
// Created by tom on 03/03/23.
//
#include "gtest/gtest.h"
#include "Interpolator.h"
#include <chrono>

inline float f(float x, float y, float z) {
    return 2 * pow(x, 3) + 3 * pow(y, 2) - z;
}

TEST(Interpolator3D, ScipyExample)
{
    CoordinateAxis<float> speed(1, 4, 11);
    CoordinateAxis<float> tws(4, 7, 22);
    CoordinateAxis<float> twa(7, 9, 33);
    Eigen::Tensor<float, 3> data(11, 22, 33);
    for (ssize_t i=0; i<11; ++i) {
        for (ssize_t j=0; j<22; ++j) {
            for (ssize_t k=0; k<33; ++k) {
                data(i, j, k) = f(speed.coordinateValue(i), tws.coordinateValue(j), twa.coordinateValue(k));
            }
        }
    }
    Grid3D<float, Linear> gridData(data, std::numeric_limits<float>::infinity(), "Data");
    Interpolator3D<float, float, float, Linear, float> interpolator(speed, tws, twa, gridData);
    ASSERT_FLOAT_EQ(interpolator.interpolate(2.1, 6.2, 8.3), 125.8047);
    ASSERT_FLOAT_EQ(interpolator.interpolate(3.3, 5.2, 7.1), 146.3007);
    ASSERT_FLOAT_EQ(interpolator.interpolate(0, 0, 0), std::numeric_limits<float>::infinity());
    ASSERT_FLOAT_EQ(interpolator.interpolate(1, 4, 7), data(0, 0, 0));
    ASSERT_FLOAT_EQ(interpolator.interpolate(4, 7, 9), data(10, 21, 32));

    auto res = interpolator.interpolate({2.1, 3.3}, {6.2, 5.2}, {8.3, 7.1});
    ASSERT_EQ(res.size(), 2);
    ASSERT_FLOAT_EQ(res[0], 125.8047);
    ASSERT_FLOAT_EQ(res[1], 146.3007);
}

std::vector<float> linspace(float start, float end, size_t points)
{
    std::vector<float> res(points);
    float step = (end - start) / (points - 1);
    size_t i = 0;
    for (auto& e : res)
    {
        e = start + step * i++;
    }
    return res;
}

TEST(Interpolator3D, Speed)
{
    CoordinateAxis<float> speed(1, 4, 11);
    CoordinateAxis<float> tws(4, 7, 22);
    CoordinateAxis<float> twa(7, 9, 33);
    Eigen::Tensor<float, 3> data(11, 22, 33);
    for (ssize_t i=0; i<11; ++i) {
        for (ssize_t j=0; j<22; ++j) {
            for (ssize_t k=0; k<33; ++k) {
                data(i, j, k) = f(speed.coordinateValue(i), tws.coordinateValue(j), twa.coordinateValue(k));
            }
        }
    }
    Grid3D<float, Linear> gridData(data, std::numeric_limits<float>::infinity(), "Data");
    Interpolator3D<float, float, float, Linear, float> interpolator(speed, tws, twa, gridData);
    size_t N = 1e7;
    auto x = linspace(1, 4, N);
    auto y = linspace(4, 7, N);
    auto z = linspace(7, 9, N);
    auto start = std::chrono::high_resolution_clock::now();
    auto res = interpolator.interpolate(x, y, z);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << duration.count() * 1e-6 << "s" << std::endl;
}