#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/math/rect.hpp>

#include <SFML/Graphics.hpp>


namespace snc {

class Transform {
private:
    sf::Transform _transform{};

public:
    Transform()                     = default;
    Transform(const Transform&)     = default;
    Transform(Transform&&) noexcept = default;
    Transform& operator =(const Transform&)     = default;
    Transform& operator =(Transform&&) noexcept = default;

    Transform(float a00, float a01, float a02,
              float a10, float a11, float a12,
              float a20, float a21, float a22);

    explicit Transform(const sf::Transform&);
    explicit Transform(sf::Transform&&) noexcept;
    explicit operator sf::Transform&();
    explicit operator const sf::Transform&() const;

    auto matrix() const -> const float*;
    auto inverse() const -> Transform;
    auto transform_point(float x, float y) const -> Vec2f;
    auto transform_point(const Vec2f& point) const -> Vec2f;
    auto transform_rect(const FRect& rect) const -> FRect;
    auto combine(const Transform&) -> Transform&;
    auto translate(float, float) -> Transform&;
    auto translate(const Vec2f&) -> Transform&;
    auto rotate(float) -> Transform&;
    auto rotate(float, float, float) -> Transform&;
    auto rotate(float, const Vec2f&) -> Transform&;
    auto scale(float, float) -> Transform&;
    auto scale(float, float, float, float) -> Transform&;
    auto scale(const Vec2f&) -> Transform&;
    auto scale(const Vec2f&, const Vec2f&) -> Transform&;
};

inline Transform operator *(const Transform& lhs, const Transform& rhs) {
    return Transform(static_cast<sf::Transform>(lhs) * static_cast<sf::Transform>(rhs));
}

inline Transform& operator *=(Transform& lhs, const Transform& rhs) {
    static_cast<sf::Transform&>(lhs) *= static_cast<sf::Transform>(rhs);
    return lhs;
}

inline Vec2f operator *(const Transform& lhs, const Vec2f& rhs) {
    return Vec2f(static_cast<sf::Transform>(lhs) * static_cast<sf::Vector2f>(rhs));
}

inline bool operator ==(const Transform& lhs, const Transform& rhs) {
    return static_cast<sf::Transform>(lhs) == static_cast<sf::Transform>(rhs);
}

inline bool operator !=(const Transform& lhs, const Transform& rhs) {
    return !(lhs == rhs);
}

}
