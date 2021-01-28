#pragma once


namespace snc {

template<unsigned N>
struct StaticString  {
    char buf[N + 1]{};

    constexpr StaticString(char const* str) {
        for (unsigned i = 0; i != N; ++i)
            buf[i] = str[i];
    }

    constexpr operator char const*() const {
        return buf;
    }
};

template<unsigned N> StaticString(char const (&)[N]) -> StaticString<N - 1>;

}
