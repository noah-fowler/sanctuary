#include <sanctuary/math/transform.hpp>


namespace snc {

Transform::Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22)
    : _transform(a00, a01, a02, a10, a11, a12, a20, a21, a22)
{}

Transform::Transform(const sf::Transform& other)
    : _transform(other)
{}

Transform::Transform(sf::Transform&& other) noexcept
    : _transform(std::move(other))
{}

Transform::operator sf::Transform&() {
    return _transform;
}

Transform::operator const sf::Transform&() const {
    return _transform;
}

auto Transform::matrix() const -> const float* {
    return _transform.getMatrix();
}

auto Transform::inverse() const -> Transform {
    return Transform(_transform.getInverse());
}

auto Transform::transform_point(float x, float y) const -> Vec2f {
    return Vec2f(_transform.transformPoint(x, y));
}

auto Transform::transform_point(const Vec2f& point) const -> Vec2f {
    return transform_point(point.x, point.y);
}

auto Transform::transform_rect(const FRect& rect) const -> FRect {
    return FRect(_transform.transformRect(static_cast<sf::FloatRect>(rect)));
}

auto Transform::combine(const Transform& other) -> Transform& {
    _transform.combine(static_cast<sf::Transform>(other));
    return *this;
}

auto Transform::translate(float x, float y) -> Transform& {
    _transform.translate(x, y);
    return *this;
}

auto Transform::translate(const Vec2f& offset) -> Transform& {
    _transform.translate(offset.x, offset.y);
    return *this;
}

auto Transform::rotate(float degrees) -> Transform& {
    _transform.rotate(degrees);
    return *this;
}

auto Transform::rotate(float degrees, float cx, float cy) -> Transform& {
    _transform.rotate(degrees, cx, cy);
    return *this;
}

auto Transform::rotate(float degrees, const Vec2f& center) -> Transform& {
    return rotate(degrees, center.x, center.y);
}

auto Transform::scale(float x, float y) -> Transform& {
    _transform.scale(x, y);
    return *this;
}

auto Transform::scale(float x, float y, float cx, float cy) -> Transform& {
    _transform.scale(x, y, cx, cy);
    return *this;
}

auto Transform::scale(const Vec2f& factors) -> Transform& {
    return scale(factors.x, factors.y);
}

auto Transform::scale(const Vec2f& factors, const Vec2f& center) -> Transform& {
    return scale(factors.x, factors.y, center.x, center.y);
}

}
