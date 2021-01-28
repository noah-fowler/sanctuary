#pragma once
#include <type_traits>


namespace snc {

template<class T>
using print_t = T::failed_assert;

template<class T, class U>
using is_same_t = std::is_same<T, U>::type;

template<class T>
using is_void_t = std::is_void<T>::type;

template<class T>
using is_nullptr_t = std::is_null_pointer<T>::type;

template<class T>
using is_integral_t = std::is_integral<T>::type;

template<class T>
using is_real_t = std::is_floating_point<T>::type;

}
