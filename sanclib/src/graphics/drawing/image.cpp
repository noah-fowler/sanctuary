#include <sanctuary/graphics/drawing/image.hpp>


namespace snc {

Image::Image(unsigned width, unsigned height, const Color& color) {
    _image.create(width, height, static_cast<sf::Color>(color));
}

Image::Image(const String& path, Logger* logger) {
    load(path, logger);
}

Image::Image(const sf::Image& other)
    : _image(other)
{}

Image::Image(sf::Image&& other) noexcept
    : _image(std::move(other))
{}

Image::operator sf::Image&() {
    return _image;
}

Image::operator const sf::Image&() const {
    return _image;
}

Image::operator bool() const {
    return !_error;
}

bool Image::load(const String& path, Logger* logger) {
    return {};
}

bool Image::save(const String& path, Logger* logger) {
    return {};
}

void Image::create(unsigned width, unsigned height, const Color& color) {
    _image.create(width, height, static_cast<sf::Color>(color));
}

}
