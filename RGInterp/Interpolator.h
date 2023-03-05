//
// Created by tom on 03/03/23.
//

#ifndef RGINTERP_INTERPOLATOR_H
#define RGINTERP_INTERPOLATOR_H

#include "Axis.h"
#include "Grid.h"
#include "InterpolationStrategy.h"
#include "RGIThreads.h"

template<typename T1, typename T2, typename T3, enum InterpolationMethod IM, typename T>
class Interpolator3D {
public:
    Interpolator3D(
        CoordinateAxis<T1> axis1,
        CoordinateAxis<T2> axis2,
        CoordinateAxis<T3> axis3,
        Grid3D<T, IM> grid
    )
    : m_Axis1(axis1)
    , m_Axis2(axis2)
    , m_Axis3(axis3)
    , m_Grid(grid) {};
    std::vector<T> interpolate(const std::vector<T1>& x, const std::vector<T2>& y, const std::vector<T3>& z) const {
        if (x.size() != y.size() or y.size() != z.size()) {
            throw std::runtime_error("The size of x, y and z must be the same.");
        }
        std::vector<T> result(x.size());
        auto f = [&](const size_t& start, const size_t& end) {
            for (size_t i=start; i<end; ++i) {
                result[i] = interpolate(x[i], y[i], z[i]);
            }
        };
        dispatch(f, x.size(), 0);
        return result;
    }
    T interpolate(const T1& x, const T2& y, const T3& z) const {
        const auto p1 = m_Axis1.findInterpVertex(x);
        const auto p2 = m_Axis2.findInterpVertex(y);
        const auto p3 = m_Axis3.findInterpVertex(z);
        return m_Grid.interpolate(p1, p2, p3);
    }
private:
    const CoordinateAxis<T1> m_Axis1;
    const CoordinateAxis<T2> m_Axis2;
    const CoordinateAxis<T3> m_Axis3;
    const Grid3D<T, IM> m_Grid;
};

#endif //RGINTERP_INTERPOLATOR_H
