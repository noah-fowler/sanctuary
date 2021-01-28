#pragma once
#include <functional>
#include <memory>
#include <type_traits>

#include <sanctuary/math/vec2.hpp>
#include <sanctuary/graphics/windowing/render_state.hpp>
#include <sanctuary/graphics/interface/theme.hpp>


namespace snc {


class Window;
class Gui;


class Widget {
public:
    struct Event {
        enum Type {
            None = -1,
            Activated,
            Deactivated,
            Shown,
            Hidden,
            Pressed,
            Released,
            Hovered,
        };

        Type type{};
    };

    using Callback = std::function<void()>;

    Gui*   gui{ nullptr };
    size_t id{};
    bool active{ true };
    bool visible{ true };
    bool hovered{ false };
    bool clicked{ false };

private:
    struct WidgetInterface {
        virtual ~WidgetInterface() {}
        virtual WidgetInterface* clone() const = 0;
        virtual void* cast() = 0;
        virtual Vec2f position() const = 0;
        virtual Vec2f size() const = 0;
        virtual FRect bounds() const = 0;
        virtual FRect global_bounds() const = 0;
        virtual void set_position(float, float) = 0;
        virtual void set_size(float, float) = 0;
        virtual void set_theme(const Theme&) = 0;
        virtual void draw(Window*, const RenderState&) const = 0;
    };

    template<class T>
    struct WidgetImpl : WidgetInterface {
        T value;

        template<class U = T>
        WidgetImpl(T value, typename std::enable_if_t<std::is_reference_v<U>>* = 0)
            : value(value)
        {}

        template<class U = T>
        WidgetImpl(T value, typename std::enable_if_t<!std::is_reference_v<U>, int>* = 0)
            : value(std::move(value))
        {}

        virtual WidgetInterface* clone() const override {
            return new WidgetImpl(value);
        }

        virtual void* cast() override {
            return &value;
        }

        virtual Vec2f position() const override {
            return value.position();
        }

        virtual Vec2f size() const override {
            return value.size();
        }

        virtual FRect bounds() const override {
            return value.bounds();
        }

        virtual FRect global_bounds() const override {
            return value.global_bounds();
        }

        virtual void set_position(float x, float y) override {
            value.set_position(x, y);
        }

        virtual void set_size(float width, float height) override {
            value.set_size(width, height);
        }

        virtual void set_theme(const Theme& theme) override {
            value.set_theme(theme);
        }

        virtual void draw(Window* window, const RenderState& state) const override {
            value.draw(window, state);
        }
    };

    template<class T>
    struct WidgetImpl<std::reference_wrapper<T>> : WidgetImpl<T&> {
        WidgetImpl(std::reference_wrapper<T> ref)
            : WidgetImpl<T&>(ref.get())
        {}
    };

private:
    std::unique_ptr<WidgetInterface> _value;

public:
    Widget() = default;

    template<class T>
    Widget(T value)
        : _value(new WidgetImpl<typename std::remove_reference_t<T>>(std::move(value)))
    {}

    Widget(const Widget& other)
        : _value(other._value->clone())
    {}

    Widget(Widget&& other) noexcept
        : _value(std::move(other._value))
    {}

    template<class T>
    Widget& operator =(T rhs) {
        Widget temp(std::move(rhs));
        std::swap(temp, *this);
        return *this;
    }

    Widget& operator =(const Widget& rhs) {
        Widget temp(rhs);
        std::swap(temp, *this);
        return *this;
    }

    Widget& operator =(Widget&& rhs) noexcept {
        _value = std::move(rhs._value);
        return *this;
    }

    template<class T>
    T cast() {
        return *static_cast<T*>(_value->cast());
    }

    auto position() const -> Vec2f {
        return _value->position();
    }

    auto size() const -> Vec2f {
        return _value->size();
    }

    FRect bounds() const {
        return _value->bounds();
    }

    FRect global_bounds() const {
        return _value->global_bounds();
    }

    void set_position(float x, float y) {
        _value->set_position(x, y);
    }

    void set_position(const Vec2f& pos) {
        set_position(pos.x, pos.y);
    }

    void set_size(float width, float height) {
        _value->set_size(width, height);
    }

    void set_size(const Vec2f& size) {
        set_size(size.x, size.y);
    }

    void set_theme(const Theme& theme) {
        _value->set_theme(theme);
    }

    /**
     * Hooks a Widget::Callback to a Widget::Event::Type.
     *
     * @param event The event type to hook to
     * @param callback The Widget::Callback to hook
     */
    bool hook(Event::Type event, Callback&& callback) {
        if (!gui)
            return false;
        //gui->hook(static_cast<Window::Event::Type>(event), std::move(callback));
        return true;
    }

    /**
     * Draws widget.
     *
     * @param window The window to draw to
     * @param state The RenderState to draw with
     */
    void draw(Window* window, const RenderState& state) const {
        _value->draw(window, state);
    }
};


}
