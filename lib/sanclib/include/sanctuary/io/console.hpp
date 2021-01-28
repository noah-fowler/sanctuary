#pragma once
#include <sanctuary/utility/string.hpp>

#include <fmt/format.h>
#include <fmt/ostream.h>


namespace snc {

template<class... Args>
void print(const String& str, Args&&... args) {
    fmt::print(static_cast<std::string>(str), std::forward<Args>(args)...);
}

template<class... Args>
void println(const String& str, Args&&... args) {
    fmt::print(static_cast<std::string>(str) + '\n', std::forward<Args>(args)...);
}

}
