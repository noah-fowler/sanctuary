#pragma once

#include <sanctuary/utility/string.hpp>
#include <sanctuary/utility/logger.hpp>

#include <SFML/Graphics/Font.hpp>


namespace snc {


class Font {
private:
    sf::Font _font;
    bool     _error{};

public:
    Font()                = default;
    Font(const Font&)     = default;
    Font(Font&&) noexcept = default;

    Font(const String& path, Logger* logger = nullptr) {
        load(path, logger);
    }

    explicit Font(const sf::Font& other)
        : _font(other)
    {}

    explicit Font(sf::Font&& other)
        : _font(std::move(other))
    {}

    explicit operator sf::Font&() {
        return _font;
    }

    explicit operator const sf::Font&() const {
        return _font;
    }

    operator bool() const {
        return !_error;
    }

    bool load(const String& path, Logger* logger = nullptr) {
        if (!_font.loadFromFile(static_cast<std::string>(path))) {
            if (logger)
                logger->error("Failed to load font: {}", path);
            _error = true;
            return false;
        }
        _error = false;
        return true;
    }
};


}
