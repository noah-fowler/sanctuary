#pragma once
#include <tuple>


namespace snc {

template<class... Ts>
using Tuple = std::tuple<Ts...>;

}
