#include <sanctuary/graphics/drawing/sprite.hpp>
#include <sanctuary/graphics/windowing/window.hpp>


namespace snc {

Sprite::Sprite(const Texture& texture)
    : _sprite(static_cast<const sf::Texture&>(texture))
{}

Sprite::Sprite(const Texture& texture, const IRect& rect)
   : _sprite(static_cast<const sf::Texture&>(texture), static_cast<sf::IntRect>(rect))
{}

Sprite::operator sf::Sprite&() {
    return _sprite;
}

Sprite::operator const sf::Sprite&() const {
    return _sprite;
}

auto Sprite::position() const -> Vec2f {
    return Vec2f(_sprite.getPosition());
}

auto Sprite::rotation() const -> float {
    return _sprite.getRotation();
}

auto Sprite::scale() const -> Vec2f {
    return Vec2f(_sprite.getScale());
}

auto Sprite::origin() const -> Vec2f {
    return Vec2f(_sprite.getOrigin());
}

auto Sprite::texture() const -> const Texture* {
    return reinterpret_cast<const Texture*>(_sprite.getTexture());
}

auto Sprite::color() const -> Color {
    return Color(_sprite.getColor());
}

auto Sprite::bounds() const -> FRect {
    return FRect(_sprite.getLocalBounds());
}

auto Sprite::global_bounds() const -> FRect {
    return FRect(_sprite.getGlobalBounds());
}

void Sprite::set_texture(const Texture& texture, bool reset) {
    _sprite.setTexture(static_cast<sf::Texture>(texture), reset);
}

void Sprite::set_texture_rect(const IRect& rect) {
    _sprite.setTextureRect(static_cast<sf::IntRect>(rect));
}

void Sprite::set_color(const Color& color) {
    _sprite.setColor(static_cast<sf::Color>(color));
}

void Sprite::set_position(float x, float y) {
    _sprite.setPosition(x, y);
}

void Sprite::set_position(const Vec2f& pos) {
    set_position(pos.x, pos.y);
}

void Sprite::set_rotation(float angle) {
    _sprite.setRotation(angle);
}

void Sprite::set_scale(float fx, float fy) {
    _sprite.setScale(fx, fy);
}

void Sprite::set_scale(const Vec2f& factors) {
    set_scale(factors.x, factors.y);
}

void Sprite::set_origin(float x, float y) {
    _sprite.setOrigin(x, y);
}

void Sprite::set_origin(const Vec2f& pos) {
    set_origin(pos);
}

void Sprite::move(float ox, float oy) {
    _sprite.move(ox, oy);
}

void Sprite::move(const Vec2f& offset) {
    move(offset.x, offset.y);
}

void Sprite::rotate(float degrees) {
    _sprite.rotate(degrees);
}

void Sprite::scale_by(float fx, float fy) {
    _sprite.scale(fx, fy);
}

void Sprite::scale_by(const Vec2f& factors) {
    scale_by(factors.x, factors.y);
}

void Sprite::draw(Window* window, const RenderState& state) const {
    window->draw(_sprite, static_cast<sf::RenderStates>(state));
}

}
