#pragma once
#include <any>


namespace snc {

struct Any {
private:
    std::any _buffer;

public:
    Any()               = default;
    Any(const Any&)     = default;
    Any(Any&&) noexcept = default;
    Any& operator =(const Any&)     = default;
    Any& operator =(Any&&) noexcept = default;

    template<class T>
    Any(T value) noexcept
        : _buffer(std::move(value))
    {}

    template<class T>
    Any(T&& value) noexcept
        : _buffer(std::move(value))
    {}

    template<class T>
    T cast() {
        return std::any_cast<T>(_buffer);
    }
};

}
