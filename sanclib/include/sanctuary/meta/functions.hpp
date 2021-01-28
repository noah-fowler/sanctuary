#pragma once


namespace snc {

constexpr bool is_constexpr() {
    return __builtin_is_constant_expression();
}

}
