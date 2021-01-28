#pragma once
#include <SFML/Graphics.hpp>


namespace snc {

struct Color {
    uint8_t r{};
    uint8_t g{};
    uint8_t b{};
    uint8_t a{};

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}

    explicit Color(const sf::Color& other)
        : r(other.r)
        , g(other.g)
        , b(other.b)
        , a(other.a)
    {}

    explicit operator sf::Color() const {
        return { r, g, b, a };
    }

    uint32_t as_int() const {
        return sf::Color{ r, g, b, a }.toInteger();
    }

    static Color Clear;
    static Color White;
    static Color Black;
    static Color Gray;
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Yellow;
    static Color Cyan;
    static Color Magenta;
};

inline Color Color::Clear = {   0,   0,   0,   0 };
inline Color Color::White = { 255, 255, 255, 255 };
inline Color Color::Black = {   0,   0,   0, 255 };
inline Color Color::Gray  = { 128, 128, 128, 255 };

inline Color Color::Red   = { 255,   0,   0, 255 };
inline Color Color::Green = {   0, 255,   0, 255 };
inline Color Color::Blue  = {   0,   0, 255, 255 };

inline Color Color::Yellow  = { 255, 255,   0, 255 };
inline Color Color::Cyan    = {   0, 255, 255, 255 };
inline Color Color::Magenta = { 255,   0, 255, 255 };

}
