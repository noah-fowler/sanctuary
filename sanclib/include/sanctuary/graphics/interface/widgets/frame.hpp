#pragma once

#include <sanctuary/graphics/drawing/shapes/rectangle.hpp>


namespace snc {

class Frame : public Rectangle {
private:
public:
    using Rectangle::Rectangle;

    void set_theme(const Theme& theme) {
        set_color(theme.color);
        set_outline_color(theme.secondary_color);
        set_outline_thickness(theme.outline);
    }
};

}
