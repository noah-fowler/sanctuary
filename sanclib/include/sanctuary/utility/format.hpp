#pragma once
#include <sanctuary/utility/string.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/chrono.h>


namespace snc {

template<class... Args>
String format(const String& str, Args&&... args) {
    return String(fmt::format(static_cast<std::string>(str), std::forward<Args>(args)...));
}

}
