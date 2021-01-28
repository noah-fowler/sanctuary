#pragma once
#include <sanctuary/meta/traits.hpp>


namespace snc {

template<class T>
concept IntegralType = requires {
    { std::is_integral<T>::value };
};

template<class T>
concept RealType = requires {
    { std::is_floating_point<T>::value };
};

template<class T>
concept ScalarType = requires {
    { std::is_scalar<T>::value };
};

template<class T>
concept NullptrType = requires {
    { std::is_null_pointer<T>::value };
};

template<class T, class U>
concept SameType = requires {
    { std::is_same<T, U>::value };
};

template<class... Ts>
concept VariadicType = requires {
    { sizeof...(Ts) > 0 };
};

}
