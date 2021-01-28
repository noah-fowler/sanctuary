#pragma once
#include <cstddef>

#include <SFML/System/Vector2.hpp>


namespace snc {

template<class T>
struct Vec2 {
    using size_type  = size_t;
    using value_type = T;

    value_type x{};
    value_type y{};

    Vec2()                = default;
    Vec2(const Vec2&)     = default;
    Vec2(Vec2&&) noexcept = default;
    Vec2& operator =(const Vec2&)     = default;
    Vec2& operator =(Vec2&&) noexcept = default;

    Vec2(value_type x, value_type y)
        : x(x)
        , y(y)
    {}

    explicit Vec2(const sf::Vector2<value_type>& other)
        : x(other.x)
        , y(other.y)
    {}

    explicit operator sf::Vector2<value_type>() const {
        return { x, y };
    }

    auto operator [](size_type idx) -> value_type&;
    auto operator [](size_type idx) const -> value_type;

    auto length() const -> float;
    auto distance(const Vec2& other) const -> float;

    auto dot(const Vec2& other) const -> float;
    auto cross(const Vec2& other) const -> float;

    auto truncate(T len) -> Vec2&;
    auto rotate(float degrees) -> Vec2&;
    auto normalize() -> Vec2&;
};

using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

template<class T>
float dot(const Vec2<T>& first, const Vec2<T>& second) {
    return first.dot(second);
}

template<class T>
float cross(const Vec2<T>& first, const Vec2<T>& second) {
    return first.cross(second);
}

template<class T>
Vec2<T>& operator ==(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

template<class T>
Vec2<T>& operator !=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(lhs == rhs);
}

template<class T>
Vec2<T>& operator +=(Vec2<T>& lhs, const Vec2<T>& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template<class T>
Vec2<T>& operator -=(Vec2<T>& lhs, const Vec2<T>& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

template<class T>
Vec2<T>& operator *=(Vec2<T>& lhs, T scalar) {
    lhs.x *= scalar;
    lhs.y *= scalar;
    return lhs;
}

template<class T>
Vec2<T>& operator /=(Vec2<T>& lhs, T scalar) {
    lhs.x /= scalar;
    lhs.y /= scalar;
    return lhs;
}

template<class T>
Vec2<T> operator +(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs += rhs;
}

template<class T>
Vec2<T> operator -(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs -= rhs;
}

template<class T>
Vec2<T> operator *(const Vec2<T>& lhs, T scalar) {
    return lhs *= scalar;
}

template<class T>
Vec2<T> operator /(const Vec2<T>& lhs, T scalar) {
    return lhs /= scalar;
}

}
