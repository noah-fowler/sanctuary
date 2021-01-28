#include <sanctuary/graphics/windowing/render_state.hpp>


namespace snc {

RenderState::RenderState(const Transform& transform)
    : _state(static_cast<const sf::Transform&>(transform))
{}

RenderState::RenderState(const sf::RenderStates& other)
    : _state(other)
{}

RenderState::RenderState(sf::RenderStates&& other) noexcept
    : _state(std::move(other))
{}

RenderState::operator sf::RenderStates&() {
    return _state;
}

RenderState::operator const sf::RenderStates&() const {
    return _state;
}

}
