#pragma once

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/math/rect.hpp>
#include <sanctuary/math/transform.hpp>

#include <SFML/Graphics/View.hpp>


namespace snc {

/**
 * View
 *
 * A class storing viewport information
 */
class View {
private:
    sf::View _view{};

public:
    View()                = default;
    View(const View&)     = default;
    View(View&&) noexcept = default;
    View& operator =(const View&)     = default;
    View& operator =(View&&) noexcept = default;

    /**
     * Construct from a Rect<float>
     *
     * @param The FRect
     */
    View(const FRect&);

    /**
     * Construct from a position and size
     *
     * @param The position
     * @param The size
     */
    View(const Vec2f&, const Vec2f&);

    explicit View(const sf::View&);
    explicit View(sf::View&&) noexcept;
    explicit operator sf::View&();
    explicit operator const sf::View&() const;

    /**
     * Returns the center position.
     */
    auto center() const -> Vec2f;

    /**
     * Returns the size
     */
    auto size() const -> Vec2f;

    /**
     * Returns the rotation
     */
    auto rotation() const -> float;

    /**
     * Returns the viewport
     */
    auto viewport() const -> FRect;

    /**
     * Returns the transform
     */
    auto transform() const -> Transform;

    /**
     * Returns the inverse transform
     */
    auto inverse_transform() const -> Transform;

    /**
     * Sets the center position.
     */
    void set_center(float, float);
    void set_center(const Vec2f&);

    /**
     * Sets the size
     */
    void set_size(float, float);
    void set_size(const Vec2f&);

    /**
     * Sets the rotation
     */
    void set_rotation(float);

    /**
     * Sets the viewport
     */
    void set_viewport(const FRect&);

    /**
     * Resets the viewport
     */
    void reset(const FRect&);

    void move(float, float);
    void move(const Vec2f&);
    void rotate(float);
    void zoom(float);
};

}
