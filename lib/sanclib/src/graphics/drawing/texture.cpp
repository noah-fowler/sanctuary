#include <sanctuary/graphics/drawing/texture.hpp>


namespace snc {

Texture::Texture(unsigned width, unsigned height) {
    create(width, height);
}

Texture::Texture(const String& path, Logger* logger) {
    load(path, logger);
}

Texture::Texture(const sf::Texture& other)
    : _texture(other)
{}

Texture::operator sf::Texture&() {
    return _texture;
}

Texture::operator const sf::Texture&() const {
    return _texture;
}

Texture::operator bool() const {
    return !_error;
}

Texture::operator sf::Texture*() {
    return &_texture;
}

Texture::operator const sf::Texture*() const {
    return &_texture;
}

bool Texture::load(const String& path, Logger* logger) {
    if (!_texture.loadFromFile(static_cast<std::string>(path))) {
        if (logger)
            logger->error("Failed to load texture: {}", path);
        _error = true;
        return false;
    }
    return true;
}

void Texture::create(unsigned width, unsigned height) {
    _texture.create(width, height);
}

}
