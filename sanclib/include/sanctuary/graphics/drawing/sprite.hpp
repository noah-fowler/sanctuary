#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/math/rect.hpp>
#include <sanctuary/math/transform.hpp>
#include <sanctuary/utility/string.hpp>
#include <sanctuary/graphics/windowing/render_state.hpp>
#include <sanctuary/graphics/drawing/color.hpp>
#include <sanctuary/graphics/drawing/texture.hpp>

#include <SFML/Graphics/Sprite.hpp>


namespace snc {

class Window;


class Sprite {
private:
    sf::Sprite _sprite;

public:
    Sprite() = default;
    Sprite(const Sprite&) = default;
    Sprite& operator =(const Sprite&) = default;

    Sprite(const Texture&);
    Sprite(const Texture&, const IRect&);

    explicit operator sf::Sprite&();
    explicit operator const sf::Sprite&() const;

    auto position() const -> Vec2f;
    auto rotation() const -> float;
    auto scale() const -> Vec2f;
    auto origin() const -> Vec2f;
    auto texture() const -> const Texture*;
    auto color() const -> Color;

    auto bounds() const -> FRect;
    auto global_bounds() const -> FRect;

    void set_texture(const Texture&, bool = false);
    void set_texture_rect(const IRect&);
    void set_color(const Color&);

    void set_position(float, float);
    void set_position(const Vec2f&);
    void set_rotation(float);
    void set_scale(float, float);
    void set_scale(const Vec2f&);
    void set_origin(float, float);
    void set_origin(const Vec2f&);

    void move(float, float);
    void move(const Vec2f&);
    void rotate(float);
    void scale_by(float, float);
    void scale_by(const Vec2f&);
    void draw(Window* window, const RenderState& = {}) const;
};

}
