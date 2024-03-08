#pragma once

#include <cassert>

namespace detail {
    // Implementation for natural 0's and 1's in a collection
    template<class Iter>
    int glzp_impl(Iter b, Iter e) noexcept requires std::is_same_v<std::decay_t<decltype(*std::declval<Iter>())>, int> {
        auto const dist = std::distance(b, e);
        assert(dist);                                                   // always at least 1-sized length
        if (!*b and !*(e-1))                                            // inside 0 or 0,0 or 0...0 range
            return dist;                                                // count zeros in this full range
        if (*b) {                                                       // inside 1...1 range!
            assert(*(e-1));                                             // task conditions violation!
            return 0;                                                   // don't count anything and no more recurse
        }
        assert(dist > 1);                                               // always more than 1-sized length
        return glzp_impl(b, b + dist / 2) + glzp_impl(b + dist / 2, e); // inside 0...1 range
    }

    // Implementation for std::string version where 0 - '0' char , 1 - '1' char
    template<class Iter, char zero='0'>
    int glzp_impl(Iter b, Iter e) noexcept requires std::is_same_v<std::decay_t<decltype(*std::declval<Iter>())>, char> {
        auto const dist = std::distance(b, e);
        if (*b == zero and *(e-1) == zero)
            return dist;
        if (*b != zero)
            return 0;
        return glzp_impl(b, b + dist / 2) + glzp_impl(b + dist / 2, e);
    }
}

namespace {
    // Concept for collections with random-access-iterators (arrays, vectors, string)
    template <class Coll>
    concept Randomly_iterable_collection = std::is_same_v<typename std::iterator_traits<decltype(std::declval<Coll&>().cbegin())>::iterator_category, std::random_access_iterator_tag>;
    // Generic function
    template <Randomly_iterable_collection coll>
    int getLastZeroPos(coll const & cont) noexcept {
        assert(cont.size());
        return detail::glzp_impl(cont.cbegin(), cont.cend());
    }

    // Function specific for builtin arrays
    template<typename T, std::size_t S>
    int getLastZeroPos(T const (& arr)[S]) noexcept {
        assert(S);
        return detail::glzp_impl(std::cbegin(arr), std::cend(arr));
    }
}
