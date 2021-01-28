#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include <sanctuary/utility/algorithms.hpp>
#include <sanctuary/containers/list.hpp>


namespace snc {

template<class Key, class Value>
class Map {
private:
    using wrapped_type = std::vector<std::pair<Key, Value>>;

    wrapped_type _buffer{};

public:
    using value_type             = wrapped_type::value_type;
    using key_type               = Key;
    using mapped_type            = Value;
    using size_type              = wrapped_type::size_type;
    using difference_type        = wrapped_type::difference_type;
    using iterator               = wrapped_type::iterator;
    using const_iterator         = wrapped_type::const_iterator;
    using reverse_iterator       = wrapped_type::reverse_iterator;
    using const_reverse_iterator = wrapped_type::const_reverse_iterator;

    Map()               = default;
    Map(const Map&)     = default;
    Map(Map&&) noexcept = default;
    Map& operator =(const Map&)     = default;
    Map& operator =(Map&&) noexcept = default;

    Map(std::initializer_list<value_type> init)
        : _buffer(init)
    {}

    Map(const std::map<Key, Value>& other)
        : _buffer(other.begin(), other.end())
    {}

    operator std::map<Key, Value>() const {
        return std::map(_buffer.begin(), _buffer.end());
    }

    auto operator [](const key_type& key) -> mapped_type& {
        if (auto res = snc::find_if(_buffer, [&key](auto& ele){ return ele.first == key; }); res != _buffer.end())
            return res->second;
        return _buffer.emplace_back(key, mapped_type{}).second;
    }

    auto data() -> value_type* {
        return _buffer.data();
    }

    auto data() const -> const value_type* {
        return _buffer.data();
    }

    auto begin() -> iterator { return _buffer.begin(); }
    auto begin() const -> const_iterator { return _buffer.cbegin(); }
    auto cbegin() const -> const_iterator { return _buffer.cbegin(); }
    auto end() -> iterator { return _buffer.end(); }
    auto end() const -> const_iterator { return _buffer.cend(); }
    auto cend() const -> const_iterator { return _buffer.cend(); }
    auto rbegin() -> reverse_iterator { return _buffer.rbegin(); }
    auto crbegin() -> const_reverse_iterator { return _buffer.crbegin(); }
    auto rend() -> reverse_iterator { return _buffer.rend(); }
    auto crend() -> const_reverse_iterator { return _buffer.crend(); }

    auto find(const key_type& key) -> iterator {
        return snc::find_if(_buffer, [&key](auto& ele){ return ele.first == key; });
    }

    auto find(const key_type& key) const -> const_iterator {
        return snc::find_if(_buffer, [&key](auto& ele){ return ele.first == key; });
    }

    auto find_value(const mapped_type& value) -> iterator {
        return snc::find_if(_buffer, [&value](auto& ele){ return ele.second == value; });
    }

    auto find_value(const mapped_type& value) const -> const_iterator {
        return snc::find_if(_buffer, [&value](auto& ele){ return ele.second == value; });
    }

    auto find_last_value(const mapped_type& value) -> iterator {
    }

    auto find_last_value(const mapped_type& value) const -> const_iterator {
    }

    auto size() const -> size_type {
        return _buffer.size();
    }

    auto max_size() const -> size_type {
        return _buffer.max_size();
    }

    auto capacity() const -> size_type {
        return _buffer.capacity();
    }

    auto count(const key_type& key) const -> unsigned {
        return snc::count_if(_buffer, [&key](const auto& ele){ return ele.first == key; });
    }

    auto count_value(const mapped_type& value) const -> unsigned {
        return snc::count_if(_buffer, [&value](const auto& ele){ return ele.second == value; });
    }

    bool empty() const {
        return _buffer.empty();
    }

    bool compare(const Map& other) const {
        return _buffer.compare(other._buffer);
    }

    bool contains(const key_type& key) const {
        return find(key) != cend();
    }

    bool contains_value(const mapped_type& value) const {
        return find_value() != cend();
    }

    void reserve(size_type size) {
        _buffer.reserve(size);
    }

    void resize(size_type size) {
        _buffer.resize(size);
    }

    void shrink_to_fit() {
        _buffer.shrink_to_fit();
    }

    void clear() {
        _buffer.clear();
    }

    void swap(Map& other) {
        _buffer.swap(other._buffer);
    }

    void push_back(const value_type& ele) {
        _buffer.push_back(ele);
    }

    void pop_back() {
        _buffer.pop_back();
    }

    auto& emplace_back(value_type&& ele) {
        return _buffer.emplace_back(ele);
    }

    auto front() -> value_type& {
        return _buffer.front();
    }

    auto front() const -> const value_type& {
        return _buffer.front();
    }

    auto back() -> value_type& {
        return _buffer.back();
    }

    auto back() const -> const value_type& {
        return _buffer.back();
    }
};

template<class Key, class Value>
bool operator ==(const Map<Key, Value>& lhs, const Map<Key, Value>& rhs) {
    return lhs.compare(rhs);
}

template<class Key, class Value>
bool operator !=(const Map<Key, Value>& lhs, const Map<Key, Value>& rhs) {
    return !lhs.compare(rhs);
}

}
