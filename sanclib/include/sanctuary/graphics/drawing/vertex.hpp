#pragma once
#include <sanctuary/math/vec2.hpp>
#include <sanctuary/graphics/drawing/color.hpp>

#include <SFML/Graphics/Vertex.hpp>


namespace snc {

enum class Primitive {
    Points        = sf::Points,
    Lines         = sf::Lines,
    Triangles     = sf::Triangles,
    LineStrip     = sf::LineStrip,
    TriangleStrip = sf::TriangleStrip,
    TriangleFan   = sf::TriangleFan
};


class Vertex {
private:
    sf::Vertex _vertex;

public:
    Vertex()                  = default;
    Vertex(const Vertex&)     = default;
    Vertex(Vertex&&) noexcept = default;
    Vertex& operator =(const Vertex&)     = default;
    Vertex& operator =(Vertex&&) noexcept = default;

    Vertex(const Vec2f& pos)
        : _vertex({ pos.x, pos.y })
    {}

    Vertex(float x, float y, const Color& color)
        : _vertex({ x, y }, static_cast<sf::Color>(color))
    {}

    Vertex(const Vec2f& pos, const Color& color)
        : _vertex({ pos.x, pos.y }, static_cast<sf::Color>(color))
    {}

    Vertex(const Vec2f& pos, const Vec2f tex_coord)
        : _vertex({ pos.x, pos.y }, { tex_coord.x, tex_coord.y })
    {}

    Vertex(const Vec2f& pos, const Color& color, const Vec2f tex_coord)
        : _vertex({ pos.x, pos.y }, static_cast<sf::Color>(color), { tex_coord.x, tex_coord.y })
    {}

    explicit Vertex(const sf::Vertex& other)
        : _vertex(other)
    {}

    explicit Vertex(sf::Vertex&& other) noexcept
        : _vertex(std::move(other))
    {}

    explicit operator sf::Vertex&() {
        return _vertex;
    }

    explicit operator const sf::Vertex&() const {
        return _vertex;
    }

    Vec2f position() const {
        return Vec2f(_vertex.position);
    }

    Color color() const {
        return Color(_vertex.color);
    }

    Vec2f tex_coords() const {
        return Vec2f(_vertex.texCoords);
    }

    void set_position(const Vec2f& pos) {
        _vertex.position = { pos.x, pos.y };
    }

    void set_color(const Color& color) {
        _vertex.color = static_cast<sf::Color>(color);
    }

    void set_tex_coords(const Vec2f& coords) {
        _vertex.texCoords = { coords.x, coords.y };
    }
};


}
