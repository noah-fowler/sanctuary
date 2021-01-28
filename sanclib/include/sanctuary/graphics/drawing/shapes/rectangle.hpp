#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/math/rect.hpp>
#include <sanctuary/math/transform.hpp>
#include <sanctuary/graphics/windowing/render_state.hpp>
#include <sanctuary/graphics/drawing/image.hpp>
#include <sanctuary/graphics/drawing/texture.hpp>


namespace snc {


class Window;


class Rectangle {
private:
    sf::RectangleShape _rect;

public:
    Rectangle() = default;
    Rectangle(const Rectangle&)     = default;
    Rectangle(Rectangle&&) noexcept = default;

    Rectangle(float width, float height, const Color& color = Color::White)
        : _rect({ width, height })
    {
        set_color(color);
    }

    Rectangle(float width, float height, float x, float y, const Color& color = Color::White)
        : _rect({ width, height })
    {
        set_position(x, y);
        set_color(color);
    }

    Rectangle(const Vec2f& size, const Color& color = Color::White)
        : _rect({ size.x, size.y })
    {
        set_color(color);
    }

    Rectangle(const Vec2f& size, const Vec2f& pos, const Color& color = Color::White)
        : _rect({ size.x, size.y })
    {
        set_position(pos);
        set_color(color);
    }

    const Texture* texture() const {
        return reinterpret_cast<const Texture*>(_rect.getTexture());
    }

    Vec2f origin() const {
        return Vec2f(_rect.getOrigin());
    }

    Vec2f position() const {
        return Vec2f(_rect.getPosition());
    }

    Vec2f size() const {
        return Vec2f(_rect.getSize());
    }

    float rotation() const {
        return _rect.getRotation();
    }

    Vec2f scale() const {
        return Vec2f(_rect.getScale());
    }

    IRect texture_rect() const {
        return IRect(_rect.getTextureRect());
    }

    Color color() const {
        return Color(_rect.getFillColor());
    }

    Color outline_color() const {
        return Color(_rect.getOutlineColor());
    }

    FRect bounds() const {
        return FRect(_rect.getLocalBounds());
    }

    FRect global_bounds() const {
        return FRect(_rect.getGlobalBounds());
    }

    Transform transform() const {
        return Transform(_rect.getTransform());
    }

    void set_origin(float x, float y) {
        _rect.setOrigin(x, y);
    }

    void set_origin(const Vec2f& pos) {
        set_origin(pos.x, pos.y);
    }

    void set_position(float x, float y) {
        _rect.setPosition(x, y);
    }

    void set_position(const Vec2f& pos) {
        set_position(pos.x, pos.y);
    }

    void set_size(float x, float y) {
        _rect.setSize({ x, y });
    }

    void set_size(const Vec2f& size) {
        set_size({ size.x, size.y });
    }

    void set_rotation(float angle) {
        _rect.setRotation(angle);
    }

    void set_scale(float x, float y) {
        _rect.setScale(x, y);
    }

    void set_scale(const Vec2f& factors) {
        set_scale(factors.x, factors.y);
    }

    void set_texture(const Texture& tex, bool reset_rect = false) {
        _rect.setTexture(static_cast<const sf::Texture*>(tex), reset_rect);
    }

    void set_texture_rect(const IRect& area) {
        _rect.setTextureRect(static_cast<sf::IntRect>(area));
    }

    void set_color(const Color& color) {
        _rect.setFillColor(static_cast<sf::Color>(color));
    }

    void set_outline_color(const Color& color) {
        _rect.setOutlineColor(static_cast<sf::Color>(color));
    }

    void set_outline_thickness(int thickness) {
        _rect.setOutlineThickness(thickness);
    }

    void move(float ox, float oy) {
        _rect.move(ox, oy);
    }

    void move(const Vec2f& off) {
        move(off.x, off.y);
    }

    void scale(float fx, float fy) {
        _rect.scale(fx, fy);
    }

    void scale(const Vec2f& facs) {
        scale(facs.x, facs.y);
    }

    void draw(Window* window, const RenderState& state = {}) const {
        window->draw(_rect, static_cast<sf::RenderStates>(state));
    }
};


}
