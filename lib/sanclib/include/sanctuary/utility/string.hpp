#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <fmt/ostream.h>


namespace snc {

class String {
private:
    using wrapped_type = std::string;

    wrapped_type _string{};

public:
    using value_type             = wrapped_type::value_type;
    using size_type              = wrapped_type::size_type;
    using iterator               = wrapped_type::iterator;
    using const_iterator         = wrapped_type::const_iterator;
    using reverse_iterator       = wrapped_type::reverse_iterator;
    using const_reverse_iterator = wrapped_type::const_reverse_iterator;

    inline static size_type npos = wrapped_type::npos;

    String()                  = default;
    String(const String&)     = default;
    String(String&&) noexcept = default;
    String& operator =(const String&)     = default;
    String& operator =(String&&) noexcept = default;

    String(const char* other);

    explicit String(const std::string&);
    explicit String(std::string&&) noexcept;
    explicit operator std::string&();
    explicit operator const std::string&() const;

    friend std::ostream&  operator <<(std::ostream&, const String&);
    friend std::ofstream& operator <<(std::ofstream&, const String&);

    auto begin() -> iterator;
    auto begin() const -> const_iterator;
    auto cbegin() const -> const_iterator;
    auto end() -> iterator;
    auto end() const -> const_iterator;
    auto cend() const -> const_iterator;

    void reserve(size_type);
    void resize(size_type);
    void clear();

    auto length() const -> size_type;
    auto capacity() const -> size_type;

    auto match(const String&, size_type = 0U) const -> size_type;
    auto match_last(const String&, size_type = npos) const -> size_type;
    auto mismatch(const String&, size_type = 0U) const -> size_type;
    //auto match_pair(const String& lhs, const String& rhs, size_t offset = 0U) const;

    bool empty() const;
    bool compare(const String&) const;
    bool starts_with(const String&) const;

    template<class... Others>
    bool starts_with_any(Others&&...) const;

    bool ends_with(const String&) const;

    template<class... Others>
    bool ends_with_any(Others&&...) const;

    bool contains(const String&) const;

    template<class... Others>
    bool contains_any(Others&&...) const;

    template<class... Others>
    bool contains_all(Others&&...) const;

    auto substr(size_type, size_type = npos) const -> String;
    void push_back(char);
    void pop_back();
    /*
    String& insert(const String& other, size_t pos = npos);
    String& erase(const String& other);
    */
    auto append(const String&) -> String&;
    /*
    auto replace(const String&, const String&);
    auto trim_front(const String& = "");
    auto trim_back();
    auto trim();
    auto reverse();
    auto delimit();
    auto split(const String& delim) const;
    */
};

template<class... Args>
String to_string(Args&&... args) {
    auto stream = std::stringstream{};
    (stream << ... << args);
    return String(stream.str());
}

inline bool operator ==(const String& lhs, const String& rhs) {
    return lhs.compare(rhs);
}

inline bool operator !=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

inline String& operator +=(String& lhs, const String& rhs) {
    return lhs.append(rhs);
}

inline String& operator +(const String& lhs, const String& rhs) {
    auto temp = lhs;
    return temp += rhs;
}

}

template<>
struct fmt::formatter<snc::String> : fmt::formatter<std::string> {
    template<class FormatContext>
    auto format(const snc::String& str, FormatContext& ctx) {
        return fmt::formatter<std::string>::format(static_cast<std::string>(str), ctx);
    }
};
