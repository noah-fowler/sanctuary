#pragma once
#include <sanctuary/math/vec2.hpp>
#include <sanctuary/utility/string.hpp>
#include <sanctuary/containers/list.hpp>
#include <sanctuary/graphics/windowing/view.hpp>
#include <sanctuary/graphics/windowing/render_state.hpp>
#include <sanctuary/graphics/drawing/drawable.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace snc {

auto screen_size() -> Vec2u;
auto fullscreen_sizes() -> List<Vec2u>;


class Window {
public:
    struct Event {
        enum Type {
            None         = -1,
            Closed       = sf::Event::Closed,
            Resized      = sf::Event::Resized,
            FocusGained  = sf::Event::GainedFocus,
            FocusLost    = sf::Event::LostFocus,
            KeyPressed     = sf::Event::KeyPressed,
            KeyReleased   = sf::Event::KeyReleased,
            MouseMoved    = sf::Event::MouseMoved,
            MouseEntered = sf::Event::MouseEntered,
            MouseLeft    = sf::Event::MouseLeft,
            MousePressed   = sf::Event::MouseButtonPressed,
            MouseReleased = sf::Event::MouseButtonReleased,
            MouseScrolled  = sf::Event::MouseWheelScrolled,
            TouchBegan   = sf::Event::TouchBegan,
            TouchEnded   = sf::Event::TouchEnded,
            TouchMoved   = sf::Event::TouchMoved,
        };

        struct MouseEvent {
            int x{};
            int y{};

            operator Vec2i() const {
                return { x, y };
            }
        };

        struct MouseButtonEvent {
            int x{};
            int y{};

            operator Vec2i() const {
                return { x, y };
            }
        };

        struct KeyboardEvent {
            bool alt{};
            bool ctrl{};
            bool shift{};
            bool system{};
        };

        struct TouchEvent {
            unsigned finger{};
            int x{};
            int y{};
        };

        Type type{ None };
        union {
            MouseEvent       mouse;
            MouseButtonEvent button;
            KeyboardEvent    keyboard;
            TouchEvent       touch;
        };
    };

private:
    sf::RenderWindow _window {};
    String           _title  {};

public:
    Window() = default;

    Window(const String& title, unsigned width, unsigned height);
    Window(const String& title, const Vec2u& size);

    explicit operator sf::RenderWindow&();
    explicit operator const sf::RenderWindow&() const;

    bool is_open() const;
    void open(const String& title, unsigned width, unsigned height);
    void open(const String& title, const Vec2u& size);
    void close();

    auto size() const -> Vec2u;
    auto position() const -> Vec2i;
    auto title() const -> String;

    auto view() const -> View;
    auto default_view() const -> View;
    auto viewport(const View& view) const -> IRect;

    void set_size(unsigned x, unsigned y);
    void set_size(const Vec2u& new_size);
    void set_position(int x, int y);
    void set_position(const Vec2i& new_position);

    void set_title(const String& new_title);
    void set_visible(bool = true);

    void set_fps(unsigned = 30);
    void set_vsync(bool = true);

    void set_cursor_visible(bool = true);
    void set_cursor_grabbed(bool = true);
    void set_active(bool = true);
    void set_view(const View& view);

    void request_focus();
    bool has_focus() const;

    bool poll(Event& event);
    bool wait(Event& event);

    void clear();
    void display();
    void draw(const Drawable& drawable, const RenderState& = {});
    void draw(const sf::Drawable& drawable, const sf::RenderStates& = sf::RenderStates::Default);
};

}
