#pragma once
#include <unordered_map>
#include <typeindex>

#include <sanctuary/graphics/drawing/color.hpp>
#include <sanctuary/graphics/drawing/texture.hpp>
#include <sanctuary/graphics/drawing/font.hpp>


namespace snc {

/**
 * Theme
 *
 * A class storing color, outline, padding, texture, and font information
 * to be applied to widgets
 */
struct Theme {
    Color color{ snc::Color::Black };           //!< Primary color
    Color secondary_color{ snc::Color::White }; //!< Secondary color
    Color tertiary_color{ snc::Color::Gray };   //!< Tertiary color

    int outline{ -2 }; //!< Outline thickness, in pixels
    int padding{ 4 };  //!< Padding thickness, in pixels

    Texture* texture{ nullptr };        //!< Default texture
    Texture* border_texture{ nullptr }; //!< Default border texture
    Font*    font{ nullptr };           //!< Default font
};

}
