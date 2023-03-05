//
// Created by tom on 03/03/23.
//

#ifndef RGINTERP_INTERPOLATIONSTRATEGY_H
#define RGINTERP_INTERPOLATIONSTRATEGY_H

#include "Axis.h"
#include <unsupported/Eigen/CXX11/Tensor>

enum InterpolationMethod {
    NearestNeighbour,
    Linear
};


template <enum InterpolationMethod, typename T>
struct Interpolate{
    T operator()(const InterpVertex<T>& v1, const InterpVertex<T>& v2, const InterpVertex<T>& v3, const T& fillValue, const Eigen::Tensor<T, 3>& data) const;
};


template<typename T>
struct Interpolate<NearestNeighbour, T> {
    T operator()(const InterpVertex<T>& v1, const InterpVertex<T>& v2, const InterpVertex<T>& v3, const T& fillValue, const Eigen::Tensor<T, 3>& data) const {
        ssize_t ix, iy, iz;
        if (!v1.inBounds or !v2.inBounds or !v3.inBounds) {
            return fillValue;
        }
        ix = v1.index;
        if (v1.normalizedDistance >= 0.5) {
            ++ix;
        }

        iy = v2.index;
        if (v2.normalizedDistance >= 0.5) {
            ++iy;
        }

        iz = v3.index;
        if (v3.normalizedDistance >= 0.5) {
            ++iz;
        }

        return data(ix, iy, iz);
    };
};

template <typename T> T interpolate_1d(T& v1, T& v2, T& x) { return v1 * (1 - x) + v2 * x; }

template <typename T> T interpolate_2d(T& v1, T& v2, T& v3, T& v4, T& x, T& y)
{
    T s = interpolate_1d(v1, v2, x);
    T t = interpolate_1d(v3, v4, x);
    return interpolate_1d(s, t, y);
}

template <typename T> T interpolate_3d(T& v1, T& v2, T& v3, T& v4, T& v5, T& v6, T& v7, T& v8, T& x, T& y, T& z)
{
    T s = interpolate_2d(v1, v2, v3, v4, x, y);
    T t = interpolate_2d(v5, v6, v7, v8, x, y);
    return interpolate_1d(s, t, z);
}

template<typename T>
struct Interpolate<Linear, T> {
    T operator()(const InterpVertex<T>& v1, const InterpVertex<T>& v2, const InterpVertex<T>& v3, const T& fillValue, const Eigen::Tensor<T, 3>& data) const {
        if (!v1.inBounds or !v2.inBounds or !v3.inBounds) {
            return fillValue;
        }
        auto ix = v1.index;
        auto iy = v2.index;
        auto iz = v3.index;

        const T d1 = data(ix, iy, iz);
        const T d2 = data(ix + 1, iy, iz);
        const T d3 = data(ix, iy + 1, iz);
        const T d4 = data(ix + 1, iy + 1, iz);
        const T d5 = data(ix, iy, iz + 1);
        const T d6 = data(ix + 1, iy, iz + 1);
        const T d7 = data(ix, iy + 1, iz + 1);
        const T d8 = data(ix + 1, iy + 1, iz + 1);
        return interpolate_3d(d1, d2, d3, d4, d5, d6, d7, d8, v1.normalizedDistance, v2.normalizedDistance, v3.normalizedDistance);
    };
};

#endif //RGINTERP_INTERPOLATIONSTRATEGY_H
