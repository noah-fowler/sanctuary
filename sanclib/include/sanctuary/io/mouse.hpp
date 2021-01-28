#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/graphics/windowing/window.hpp>

#include <SFML/Window/Mouse.hpp>


namespace snc {

struct Mouse {
    enum class Button {
        Left,
        Right,
        Middle,
        X1,
        X2,
    };

    static bool button_pressed(Button button) {
        return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }

    static Vec2i position() {
        const auto pos = sf::Mouse::getPosition();
        return { pos.x, pos.y };
    }

    static Vec2i position(const Window& relative) {
        const auto pos = sf::Mouse::getPosition(static_cast<const sf::RenderWindow&>(relative));
        return { pos.x, pos.y };
    }
};

}
