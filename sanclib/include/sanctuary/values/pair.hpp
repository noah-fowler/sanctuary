#pragma once


namespace snc {

/**
 * Pair<T1, T2>
 *
 * A class that stores two elements
 */
template<class T1, class T2>
struct Pair {
    T1 first;  //!< First element
    T2 second; //!< Second element
};

}
