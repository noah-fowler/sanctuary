#pragma once

#include <sanctuary/utility/string.hpp>
#include <sanctuary/utility/logger.hpp>

#include <SFML/Graphics/Texture.hpp>


namespace snc {

class Texture {
private:
    sf::Texture _texture;
    bool        _error{};

public:
    Texture()               = default;
    Texture(const Texture&) = default;
    Texture& operator =(const Texture&) = default;

    Texture(unsigned, unsigned);
    Texture(const String&, Logger* = nullptr);

    explicit Texture(const sf::Texture&);
    explicit operator sf::Texture&();
    explicit operator const sf::Texture&() const;
    explicit operator sf::Texture*();
    explicit operator const sf::Texture*() const;

    operator bool() const;

    bool load(const String&, Logger* = nullptr);
    void create(unsigned, unsigned);
};

}
