#pragma once
#include <functional>
#include <memory>
#include <type_traits>

#include <sanctuary/graphics/windowing/render_state.hpp>


namespace snc {


class Window;


class Drawable {
private:
    struct DrawableInterface {
        virtual ~DrawableInterface() {}
        virtual DrawableInterface* clone() const = 0;
        virtual void* cast() = 0;
        virtual void draw(Window*, const RenderState&) const = 0;
    };

    template<class T>
    struct DrawableImpl : DrawableInterface {
        T value;

        template<class U = T>
        DrawableImpl(T value, typename std::enable_if_t<std::is_reference_v<U>>* = 0)
            : value(value)
        {}

        template<class U = T>
        DrawableImpl(T value, typename std::enable_if_t<!std::is_reference_v<U>, int>* = 0)
            : value(std::move(value))
        {}

        virtual DrawableInterface* clone() const override {
            return new DrawableImpl(value);
        }

        virtual void* cast() override {
            return &value;
        }

        virtual void draw(Window* window, const RenderState& state) const override {
            value.draw(window, state);
        }
    };

    template<class T>
    struct DrawableImpl<std::reference_wrapper<T>> : DrawableImpl<T&> {
        DrawableImpl(std::reference_wrapper<T> ref)
            : DrawableImpl<T&>(ref.get())
        {}
    };

private:
    std::unique_ptr<DrawableInterface> _value;

public:
    Drawable() = default;

    template<class T>
    Drawable(T value)
        : _value(new DrawableImpl<typename std::remove_reference_t<T>>(std::move(value)))
    {}

    Drawable(const Drawable& other)
        : _value(other._value->clone())
    {}

    Drawable(Drawable&& other) noexcept
        : _value(std::move(other._value))
    {}

    template<class T>
    Drawable& operator =(T rhs) {
        Drawable temp(std::move(rhs));
        std::swap(temp, *this);
        return *this;
    }

    Drawable& operator =(const Drawable& rhs) {
        Drawable temp(rhs);
        std::swap(temp, *this);
        return *this;
    }

    Drawable& operator =(Drawable&& rhs) noexcept {
        _value = std::move(rhs._value);
        return *this;
    }

    template<class T>
    T cast() {
        return *static_cast<T*>(_value->cast());
    }

    void draw(Window* window, const RenderState& state) const {
        _value->draw(window, state);
    }
};


}
