#pragma once

#include <sanctuary/math/transform.hpp>

#include <SFML/Graphics/RenderStates.hpp>


namespace snc {

/**
 * RenderState
 *
 * A class storing rendering information
 */
class RenderState {
private:
    sf::RenderStates _state; //!< Internal state

public:
    RenderState()                       = default;
    RenderState(const RenderState&)     = default;
    RenderState(RenderState&&) noexcept = default;
    RenderState& operator =(const RenderState&)     = default;
    RenderState& operator =(RenderState&&) noexcept = default;

    /**
     * Construct from a Transform.
     *
     * @param The transform
     */
    RenderState(const Transform&);

    explicit RenderState(const sf::RenderStates&);
    explicit RenderState(sf::RenderStates&&) noexcept;
    explicit operator sf::RenderStates&();
    explicit operator const sf::RenderStates&() const;
};


}
