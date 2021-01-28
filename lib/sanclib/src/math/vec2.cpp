#include <sanctuary/math/vec2.hpp>
#include <cstdlib>
#include <cmath>


namespace snc {

template<class T>
auto Vec2<T>::operator [](Vec2::size_type idx) -> Vec2::value_type& {
    return idx == 0 ? x : y;
}

template<class T>
auto Vec2<T>::operator [](Vec2::size_type idx) const -> Vec2::value_type {
    return idx == 0 ? x : y;
}

template<class T>
auto Vec2<T>::length() const -> float {
    return std::sqrt(x * x + y * y);
}

template<class T>
auto Vec2<T>::distance(const Vec2& other) const -> float {
    return Vec2{ other.x - x, other.y - y }.length();
}

template<class T>
auto Vec2<T>::dot(const Vec2& other) const -> float {
    return (x * other.x) + (y * other.y);
}

template<class T>
auto Vec2<T>::cross(const Vec2& other) const -> float {
    return (x * other.y) - (y * other.x);
}

template<class T>
auto Vec2<T>::truncate(T len) -> Vec2& {
    T angle = std::atan2(y, x);
    return *this = {
        len * std::cos(angle),
        len * std::sin(angle)
    };
}

template<class T>
auto Vec2<T>::rotate(float degrees) -> Vec2& {
    float theta = degrees / 180 * 3.14;
    float c = std::cos(theta);
    float s = std::sin(theta);
    return *this = {
        x * c - y * s,
        x * s + y * c
    };
}

template<class T>
auto Vec2<T>::normalize() -> Vec2& {
    return length() == 0
        ? *this
        : *this *= (1.f / length());
}

}
