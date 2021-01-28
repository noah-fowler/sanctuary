#include <sanctuary/graphics/windowing/view.hpp>


namespace snc {

View::View(const FRect& rect)
    : _view(static_cast<sf::FloatRect>(rect))
{}

View::View(const Vec2f& center, const Vec2f& size)
    : _view(static_cast<sf::Vector2f>(center), static_cast<sf::Vector2f>(size))
{}

View::View(const sf::View& other)
    : _view(other)
{}

View::View(sf::View&& other) noexcept
    : _view(std::move(other))
{}

View::operator sf::View&() {
    return _view;
}

View::operator const sf::View&() const {
    return _view;
}

auto View::center() const -> Vec2f {
    return Vec2f(_view.getCenter());
}

auto View::size() const -> Vec2f {
    return Vec2f(_view.getSize());
}

auto View::rotation() const -> float {
    return _view.getRotation();
}

auto View::viewport() const -> FRect {
    return FRect(_view.getViewport());
}

auto View::transform() const -> Transform {
    return Transform(_view.getTransform());
}

auto View::inverse_transform() const -> Transform {
    return Transform(_view.getInverseTransform());
}

void View::set_center(float x, float y) {
    _view.setCenter(x, y);
}

void View::set_center(const Vec2f& pos) {
    set_center(pos.x, pos.y);
}

void View::set_size(float width, float height) {
    _view.setSize(width, height);
}

void View::set_size(const Vec2f& size) {
    set_size(size.x, size.y);
}

void View::set_rotation(float degrees) {
    _view.setRotation(degrees);
}

void View::set_viewport(const FRect& rect) {
    _view.setViewport(static_cast<sf::FloatRect>(rect));
}

void View::reset(const FRect& rect) {
    _view.reset(static_cast<sf::FloatRect>(rect));
}

void View::move(float ox, float oy) {
    _view.move(ox, oy);
}

void View::move(const Vec2f& offset) {
    move(offset.x, offset.y);
}

void View::rotate(float angle) {
    _view.rotate(angle);
}

void View::zoom(float factor) {
    _view.zoom(factor);
}

}
