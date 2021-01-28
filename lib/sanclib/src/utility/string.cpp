#include <sanctuary/utility/string.hpp>


namespace snc {

String::String(const char* other)
    : _string(other)
{}

String::String(const std::string& other)
    : _string(other)
{}

String::String(std::string&& other) noexcept
    : _string(std::move(other))
{}

String::operator std::string&() {
    return _string;
}

String::operator const std::string&() const {
    return _string;
}

std::ostream& operator <<(std::ostream& stream, const String& str) {
    stream << static_cast<std::string>(str);
    return stream;
}

std::ofstream& operator <<(std::ofstream& stream, const String& str) {
    stream << static_cast<std::string>(str);
    return stream;
}

auto String::begin() -> String::iterator {
    return _string.begin();
}

auto String::begin() const -> String::const_iterator {
    return _string.cbegin();
}

auto String::cbegin() const -> String::const_iterator {
    return _string.cbegin();
}

auto String::end() -> String::iterator {
    return _string.end();
}

auto String::end() const -> String::const_iterator {
    return _string.cend();
}

auto String::cend() const -> String::const_iterator {
    return _string.cend();
}

void String::reserve(String::size_type size) {
    _string.reserve(size);
}

void String::resize(String::size_type size) {
    _string.resize(size);
}

void String::clear() {
    _string.clear();
}

auto String::length() const -> String::size_type {
    return _string.length();
}

auto String::capacity() const -> String::size_type{
    return _string.capacity();
}

auto String::match(const String& other, String::size_type offset) const -> String::String::size_type {
    return _string.find(other._string, offset);
}

auto String::match_last(const String& other, String::size_type offset) const -> String::String::size_type {
    return _string.rfind(other._string, offset);
}

auto String::mismatch(const String& other, String::size_type offset) const -> String::String::size_type {
    return _string.find_first_not_of(other._string, offset);
}

bool String::empty() const {
    return _string.empty();
}

bool String::compare(const String& other) const {
    return _string == other._string;
}

bool String::contains(const String& other) const {
    return match(other) != String::npos;
}

template<class... Others>
bool String::contains_any(Others&&... others) const {
    return (contains(others) || ...);
}

template<class... Others>
bool String::contains_all(Others&&... others) const {
    return (contains(others) && ...);
}

bool String::starts_with(const String& other) const {
    return match(other) == 0U;
}

template<class... Others>
bool String::starts_with_any(Others&&... others) const {
    return (starts_with(others) || ...);
}

bool String::ends_with(const String& other) const {
    return match_last(other) == length() - other.length();
}

template<class... Others>
bool String::ends_with_any(Others&&... others) const {
    return (ends_with(others) || ...);
}

auto String::substr(String::size_type start, String::size_type end) const -> String{
    return String(_string.substr(start, end));
}

void String::push_back(char chr) {
    _string.push_back(chr);
}

void String::pop_back() {
    _string.pop_back();
}

auto String::append(const String& other) -> String& {
    _string.append(other._string);
    return *this;
}

}
