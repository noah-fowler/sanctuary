#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/graphics/window.hpp>

#include <SFML/Window/Touch.hpp>


namespace snc::touchpad {

inline bool pressed(unsigned finger) {
    return sf::Touch::isDown(finger);
}

inline Vec2i position(unsigned finger) {
    return sf::Touch::getPosition(finger);
}

inline Vec2i position(unsigned finger, const Window& relative) {
    return sf::Touch::getPosition(finger, static_cast<const sf::Window&>(relative));
}

}
