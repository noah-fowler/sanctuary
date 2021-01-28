#pragma once
#include <variant>


namespace snc {

template<class... Ts>
using Variant = std::variant<Ts...>;

template<class... Ts>
struct Overload { using Ts::operator()...; };

template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;

template<class Variant, class... Matches>
auto match(Variant&& variant, Matches&&... matches) {
    return std::visit(
        Overload{ std::forward<Matches>(matches)... },
        std::forward<Variant>(variant)
    );
}

}
