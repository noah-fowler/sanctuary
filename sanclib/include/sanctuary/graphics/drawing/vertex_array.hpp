#pragma once
#include <sanctuary/math/transform.hpp>
#include <sanctuary/graphics/windowing/render_state.hpp>
#include <sanctuary/graphics/drawing/vertex.hpp>


namespace snc {


class Window;


class VertexArray {
private:
    sf::VertexArray _vertices;

public:
    Primitive primitive;

    VertexArray()                       = default;
    VertexArray(const VertexArray&)     = default;
    VertexArray(VertexArray&&) noexcept = default;

    VertexArray(Primitive primitive, size_t count = 0)
        : _vertices(static_cast<sf::PrimitiveType>(primitive), count)
    {}

    explicit VertexArray(const sf::VertexArray& other)
        : _vertices(other)
    {}

    explicit VertexArray(sf::VertexArray&& other) noexcept
        : _vertices(std::move(other))
    {}

    explicit operator sf::VertexArray&() {
        return _vertices;
    }

    explicit operator const sf::VertexArray&() const {
        return _vertices;
    }

    Vertex& operator [](size_t idx) {
        return reinterpret_cast<Vertex&>(_vertices[idx]);
    }

    const sf::Vertex& operator [](size_t idx) const {
        return _vertices[idx];
    }

    size_t size() const {
        return _vertices.getVertexCount();
    }

    void append(Vertex vertex) {
        _vertices.append(static_cast<sf::Vertex>(vertex));
    }

    void clear() {
        _vertices.clear();
    }

    void resize(size_t count) {
        _vertices.resize(count);
    }

    void draw(Window* window, const RenderState& state = {}) const {
        window->draw(_vertices, static_cast<sf::RenderStates>(state));
    }
};


}
