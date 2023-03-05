//
// Created by tom on 03/03/23.
//

#ifndef RGINTERP_GRID_H
#define RGINTERP_GRID_H
#include "InterpolationStrategy.h"
#include <unsupported/Eigen/CXX11/Tensor>

template<typename T, enum InterpolationMethod InterpMethod>
class Grid3D {
public:
    Grid3D(Eigen::Tensor<T, 3> data, T fillValue, std::string_view name)
    : m_Data(data), m_FillValue(fillValue), m_Name(name) {};
    T interpolate(const InterpVertex<T>& v1, const InterpVertex<T>& v2, const InterpVertex<T>& v3) const {
        return m_InterpolationMethod(v1, v2, v3, m_FillValue, m_Data);
    };
private:
    const Interpolate<InterpMethod, T> m_InterpolationMethod = Interpolate<InterpMethod, T>();
    const Eigen::Tensor<T, 3> m_Data;
    const T m_FillValue;
    const std::string_view m_Name;
};

#endif //RGINTERP_GRID_H
