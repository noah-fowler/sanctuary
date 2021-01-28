#pragma once

#include <sanctuary/math/vec2.hpp>

#include <SFML/Graphics.hpp>


namespace snc {

template<class T = float>
struct Rect {
    using size_type   = size_t;
    using value_type  = T;
    using vector_type = Vec2<T>;

    value_type top{};
    value_type left{};
    value_type width{};
    value_type height{};

    Rect()                = default;
    Rect(const Rect&)     = default;
    Rect(Rect&&) noexcept = default;
    Rect& operator =(const Rect&)     = default;
    Rect& operator =(Rect&&) noexcept = default;

    Rect(value_type top, value_type left, value_type width, value_type height)
        : top(top)
        , left(left)
        , width(width)
        , height(height)
    {}

    Rect(const vector_type& pos, const vector_type& size)
        : top(pos.x)
        , left(pos.y)
        , width(size.x)
        , height(size.y)
    {}

    Rect(const sf::Rect<value_type>& other)
        : top(other.top)
        , left(other.left)
        , width(other.width)
        , height(other.height)
    {}

    operator sf::Rect<value_type>() const {
        return { top, left, width, height };
    }

    auto operator [](size_type idx) -> value_type& {
        switch (idx) {
            case 0: return top;    break;
            case 1: return left;   break;
            case 2: return width;  break;
            case 3: return height; break;
        }
        return top;
    }

    auto operator [](size_type idx) const -> const value_type& {
        switch (idx) {
            case 0: return top;    break;
            case 1: return left;   break;
            case 2: return width;  break;
            case 3: return height; break;
        }
        return top;
    }

    auto size() const -> vector_type {
        return { width, height };
    }

    auto position() const -> vector_type {
        return { top, left };
    }

    bool contains(value_type x, value_type y) const {
        return static_cast<sf::Rect<value_type>>(*this).contains(x, y);
    }

    bool contains(const vector_type& point) const {
        return contains(point.x, point.y);
    }
};

using IRect = Rect<int>;
using FRect = Rect<float>;
using URect = Rect<unsigned>;
using DRect = Rect<double>;
using LRect = Rect<long>;

}
