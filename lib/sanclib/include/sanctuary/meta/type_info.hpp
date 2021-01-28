#pragma once
#include <typeindex>
#include <cxxabi.h>

#include <sanctuary/utility/string.hpp>


namespace snc {

template<class T>
String type_name() {
    int status;
    char* res = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
    String name = { res };
    free(res);
    return name;
}

template<class T>
struct TypeInfo {
    using type = T;

    static std::type_index index() {
        return std::type_index(typeid(T));
    };

    static String name() {
        return type_name<T>();
    };
};

}
