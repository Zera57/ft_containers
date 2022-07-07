#ifndef __PAIR_HPP__
#define __PAIR_HPP__

namespace ft {

    template<
        class T1,
        class T2
    > struct pair {
        public:
            typedef T1  first_type;
            typedef T2  second_type;

            first_type  first;
            second_type second;

            pair() : first(), second() {}

            pair( const first_type& x, const second_type& y ) : first(x), second(y) {}

            pair( const pair& p ) : first(p.first), second(p.second) {}

            template< class U1, class U2 >
            pair( const pair<U1, U2>& p ) : first(p.second), second(p.first) {}
    };

    template< class T1, class T2 >
    std::pair<T1,T2> make_pair( T1 t, T2 u ) {
        return pair(t, u);
    }

}

#endif