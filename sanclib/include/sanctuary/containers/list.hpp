#pragma once
#include <vector>
#include <iostream>
#include <fstream>

#include <sanctuary/utility/algorithms.hpp>


namespace snc {

template<class T>
class List {
private:
    using wrapped_type = std::vector<T>;

    wrapped_type _buffer{};

public:
    using value_type       = wrapped_type::value_type;
    using size_type        = wrapped_type::size_type;
    using difference_type  = wrapped_type::difference_type;
    using iterator         = wrapped_type::iterator;
    using const_iterator   = wrapped_type::const_iterator;
    using reverse_iterator = wrapped_type::reverse_iterator;
    using const_reverse_iterator = wrapped_type::const_reverse_iterator;

    List()                = default;
    List(const List&)     = default;
    List(List&&) noexcept = default;
    List& operator =(const List&)     = default;
    List& operator =(List&&) noexcept = default;

    List(const T& value, size_type size)
        : _buffer(value, size)
    {}

    List(std::initializer_list<List::value_type> initializer)
        : _buffer(initializer)
    {}

    template<class InputIt>
    List(InputIt first, InputIt last)
        : _buffer(first, last)
    {}

    List(const std::vector<T>& other)
        : _buffer(other)
    {}

    List(std::vector<T>&& other) noexcept
        : _buffer(std::move(other))
    {}

    operator std::vector<T>&() {
        return _buffer;
    }

    operator const std::vector<T>&() const {
        return _buffer;
    }

    auto operator [](size_type index) -> value_type& {
        return _buffer[index];
    }

    auto operator [](size_type index) const  -> const value_type& {
        return _buffer[index];
    }

    auto at(size_type index) const -> const value_type& {
        return _buffer.at(index);
    }

    auto data() -> value_type* {
        return _buffer.data();
    }

    auto data() const -> const value_type* {
        return _buffer.data();
    }

    auto begin() -> iterator {
        return _buffer.begin();
    }

    auto begin() const -> const_iterator {
        return _buffer.cbegin();
    }

    auto cbegin() const -> const_iterator {
        return _buffer.cbegin();
    }

    auto end() -> iterator {
        return _buffer.end();
    }

    auto end() const -> const_iterator {
        return _buffer.cend();
    }

    auto cend() const -> const_iterator {
        return _buffer.cend();
    }

    auto rbegin() -> reverse_iterator {
        return _buffer.rbegin();
    }

    auto rend() -> reverse_iterator {
        return _buffer.rend();
    }

    auto find(const T& ele) -> iterator {
        return _buffer.find(ele);
    }

    auto find(const T& ele) const -> const_iterator {
        return _buffer.find(ele);
    }

    auto find_last(const T& ele) -> iterator {
        return _buffer.rfind(ele);
    }

    auto find_last(const T& ele) const -> const_iterator {
        return _buffer.rfind(ele);
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

    auto count(const T& ele) const -> size_type {
        return snc::count(_buffer, ele);
    }

    bool empty() const {
        return _buffer.empty();
    }

    bool compare(const List& other) const {
        return _buffer == other._buffer;
    }

    bool contains(const T& ele) const {
        return find(ele) != _buffer.cend();
    }

    template<class... Eles>
    bool contains_any(Eles&&... eles) const {
        return ((find(eles) != _buffer.cend()) || ...);
    }

    template<class... Eles>
    bool contains_all(Eles&&... eles) const {
        return ((find(eles) != _buffer.cend()) && ...);
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

    void swap(List<T>& other) {
        _buffer.swap(other._buffer);
    }

    void push_back(const T& ele) {
        _buffer.push_back(ele);
    }

    void pop_back() {
        _buffer.pop_back();
    }

    template<class... Args>
    T& emplace_back(Args&&... args) noexcept {
        return _buffer.emplace_back(std::forward<Args>(args)...);
    }

    auto insert(size_type pos, const T& ele) -> iterator {
        assert(_buffer.size() >= pos);
        return _buffer.insert(cbegin() + pos, ele);
    }

    auto insert(size_type from, size_type to, const T& ele) -> iterator {
        assert(_buffer.size() >= to);
        return _buffer.insert(cbegin() + from, cbegin() + to, ele);
    }

    auto insert(const_iterator pos, const T& ele) -> iterator {
        return _buffer.insert(pos, ele);
    }

    auto insert(const_iterator from, const_iterator to, const T& ele) -> iterator {
        return _buffer.insert(from, to, ele);
    }

    auto erase(size_type pos) -> iterator {
        return _buffer.erase(cbegin() + pos);
    }

    auto erase(size_type from, size_type to) -> iterator {
        return _buffer.erase(cbegin() + from, cbegin() + to);
    }

    auto erase(const_iterator pos) -> iterator {
        return _buffer.erase(pos);
    }

    auto erase(const_iterator from, const_iterator to) -> iterator{
        return _buffer.erase(from, to);
    }

    auto erase(const T& ele) -> iterator {
        if (auto it = _buffer.find(ele); it != end())
            return erase(it);
        return end();
    }

    template<class... Eles>
    auto erase_all(Eles&&... eles) -> iterator {
        return (erase(eles), ...);
    }

    auto front() -> T& {
        return _buffer.front();
    }

    auto front() const -> const T& {
        return _buffer.front();
    }

    auto back() -> T& {
        return _buffer.back();
    }

    auto back() const -> const T& {
        return _buffer.back();
    }

    auto reverse() -> List& {
        return snc::reverse(*this);
    }

    auto deduplicate() -> List& {
        return snc::unique(*this);
    }
};

template<class T>
bool operator ==(const List<T>& lhs, const List<T>& rhs) {
    return lhs.compare(rhs);
}

template<class T>
bool operator !=(const List<T>& lhs, const List<T>& rhs) {
    return !lhs.compare(rhs);
}

}
