#pragma once

#include <sanctuary/utility/string.hpp>
#include <sanctuary/utility/logger.hpp>
#include <sanctuary/graphics/drawing/color.hpp>

#include <SFML/Graphics/Image.hpp>


namespace snc {

class Image {
private:
    sf::Image _image;
    bool      _error{};

public:
    Image()                 = default;
    Image(const Image&)     = default;
    Image(Image&&) noexcept = default;
    Image& operator =(const Image&)     = default;
    Image& operator =(Image&&) noexcept = default;

    Image(unsigned, unsigned, const Color& = Color::Black);
    Image(const String&, Logger* = nullptr);

    explicit Image(const sf::Image&);
    explicit Image(sf::Image&&) noexcept;
    explicit operator sf::Image&();
    explicit operator const sf::Image&() const;

    operator bool() const;

    bool load(const String&, Logger* = nullptr);
    bool save(const String&, Logger* = nullptr);

    void create(unsigned, unsigned, const Color& = Color::Black);
};

}
