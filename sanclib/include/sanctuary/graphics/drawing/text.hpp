#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/utility/string.hpp>
#include <sanctuary/graphics/drawing/color.hpp>
#include <sanctuary/graphics/drawing/font.hpp>

#include <SFML/Graphics/Text.hpp>


namespace snc {

class Text {
private:
    sf::Text _text;

public:
    Text()                = default;
    Text(const Text&)     = default;
    Text(Text&&) noexcept = default;
    Text& operator =(const Text&) = default;
    Text& operator =(Text&&)      = default;

    Text(const String& str, const Font& font, unsigned char_size = 30)
        : _text(static_cast<std::string>(str), static_cast<const sf::Font&>(font), 30)
    {}

    explicit Text(const sf::Text& other)
        : _text(other)
    {}

    explicit Text(sf::Text&& other)
        : _text(std::move(other))
    {}

    explicit operator sf::Text&() {
        return _text;
    }

    explicit operator const sf::Text&() const {
        return _text;
    }

    auto string() const -> String {
        return String(_text.getString());
    }

    const Font* font() const {
        return reinterpret_cast<const Font*>(_text.getFont());
    }

    void set_position(float x, float y) {
        _text.setPosition({ x, y });
    }

    void set_position(const Vec2f& pos) {
        set_position(pos.x, pos.y);
    }

    void set_string(const String& str) {
        _text.setString(static_cast<std::string>(str));
    }

    void set_font(const Font& font) {
        _text.setFont(static_cast<const sf::Font&>(font));
    }

    void set_color(const Color& color) {
        _text.setFillColor(static_cast<sf::Color>(color));
    }

    void set_outline_color(const Color& color) {
        _text.setOutlineColor(static_cast<sf::Color>(color));
    }

    void draw(Window* window, const RenderState& state = {}) const {
        window->draw(_text, static_cast<sf::RenderStates>(state));
    }
};

}
