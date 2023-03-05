//
// Created by tom on 03/03/23.
//

#ifndef RGINTERP_AXIS_H
#define RGINTERP_AXIS_H

#include <algorithm>

template<typename T>
struct InterpVertex {
    ssize_t index;
    T normalizedDistance;
    bool inBounds;
};

template <typename T> class CoordinateAxis {
public:
    CoordinateAxis(T min, T max, size_t numberOfPoints)
    : m_Size(numberOfPoints - 1)
    , m_Min(min)
    , m_Max(max)
    , m_dx((m_Max - m_Min)/m_Size)
    , m_InvDx(1/m_dx) {

    };
    InterpVertex<T> findInterpVertex(const T& coordinate)  const {
        auto rtn = InterpVertex<T>();
        rtn.index = findIndex(coordinate);
        rtn.inBounds = inBounds(coordinate);
        rtn.index = std::max<ssize_t>(rtn.index, 0);
        rtn.index = std::min<ssize_t>(rtn.index, m_Size-1);
        auto x1 = coordinateValue(rtn.index);
        auto x2 = coordinateValue(rtn.index + 1);
        rtn.normalizedDistance = (coordinate-x1)/(x2-x1);
        return rtn;
    };
    ssize_t findIndex(const T& coordinate) const {
        return (coordinate - m_Min) * m_InvDx;
    }
    bool inBounds(const T& coordinate) const {
        return ((coordinate>=m_Min) and (coordinate<=m_Max));
    }
    T coordinateValue(const size_t index)  const {
        return m_Min + index * m_dx;
    }
    T getMin() { return m_Min; }
    T getMax() { return m_Max; }
    T getdX() const { return m_dx; }
private:
    const size_t m_Size;
    const T m_Min;
    const T m_Max;
    const T m_dx;
    const T m_InvDx;
};

#endif //RGINTERP_AXIS_H
