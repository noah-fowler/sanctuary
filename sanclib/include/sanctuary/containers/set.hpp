#pragma once
#include <set>


namespace snc {

template<class T>
class Set {
private:
    using wrapped_type = std::set<T>;
    wrapped_type _buffer{};

public:
    using value_type  = wrapped_type::value_type;
    using size_type   = wrapped_type::size_type;

    Set()               = default;
    Set(const Set&)     = default;
    Set(Set&&) noexcept = default;

    auto size() const -> size_type {
        return _buffer.size();
    }

    auto max_size() const -> size_type {
        return _buffer.max_size();
    }

    bool empty() const {
        return _buffer.empty();
    }

    void clear() {
        _buffer.clear();
    }
};

}
