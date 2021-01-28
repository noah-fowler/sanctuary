#pragma once
#include <tuple>
#include <utility>
#include <functional>


namespace snc {

template<class... Args>
struct Pack {
    template<template<class...> class List>
    using apply = List<Args...>;
};


template<class... Ts>
struct TypeList {
    using type = TypeList;
    static constexpr size_t size = sizeof...(Ts);

private:
    template<class List>
    struct Front;

    template<class List>
    struct Back;

    template<class List>
    struct PopFront;

    template<class List, class Element>
    struct PushFront;

    template<class Head, class... Tail>
    struct Front<TypeList<Head, Tail...>> {
        using type = Head;
    };

    template<class Head, class... Tail>
    struct PopFront<TypeList<Head, Tail...>> {
        using type = TypeList<Tail...>;
    };

    template<class... Elements, class Element>
    struct PushFront<TypeList<Elements...>, Element> {
        using type = TypeList<Element, Elements...>;
    };

    template<class... Elements>
    struct Prepend {
        using type = TypeList<Elements..., Ts...>;
    };

    template<class... Elements>
    struct Append {
        using type = TypeList<Ts..., Elements...>;
    };

    template<class List, unsigned Index>
    struct Element {
        using type = typename Element<typename PopFront<List>::type, Index - 1>::type;
    };

    template<class List>
    struct Element<List, 0> {
        using type = typename Front<List>::type;
    };

    template<class... Elements>
    struct Back<TypeList<Elements...>> {
        using type = typename Element<TypeList<Elements...>, sizeof...(Elements) - 1>::type;
    };

    template<size_t... Is>
    static constexpr auto first_n(std::index_sequence<Is...>) {
        constexpr auto tup = std::tuple<Ts...>{};
        return TypeList<std::decay_t<decltype(std::get<Is>(tup))>...>{};
    }

public:
    using tuple = std::tuple<Ts...>;
    using front = Front<TypeList>::type;
    using back  = Back<TypeList>::type;
    using pop_front = PopFront<TypeList>::type;

    template<size_t N>
    using slice = decltype(TypeList::first_n(std::make_index_sequence<N>{}));

    template<class T>
    using push_front = PushFront<TypeList, T>::type;

    template<unsigned Index>
    using at = Element<TypeList, Index>::type;

    template<unsigned Index>
    using get = at<Index>;

    template<class... Elements>
    using prepend = Prepend<Elements...>::type;

    template<class... Elements>
    using append = Append<Elements...>::type;
};

}
