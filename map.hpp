#ifndef __MAP_HPP__
#define __MAP_HPP__

# include "reverse_iterator.hpp"

namespace ft {
    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T> >
    >
    class map {

    };
}


#endif