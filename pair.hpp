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
			pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

			pair	&operator = (const pair& other) {
				this->first = other.first;
				this->second = other.second;
				return *this;
			}
	};

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u ) {
		return pair<T1, T2>(t, u);
	}

	template<typename T1, typename T2>
	bool	operator == (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
		return (lhs.first == rhs.first) && (lhs.second == rhs.second);
	}

	template<typename T1, typename T2>
	bool	operator != (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T1, typename T2>
	bool	operator < (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || ((lhs.first == rhs.first) && lhs.second < rhs.second);
	}

	template<typename T1, typename T2>
	bool	operator > (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
		return rhs < lhs;
	}

	template<typename T1, typename T2>
	bool	operator <= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
		return !(lhs > rhs);
	}

	template<typename T1, typename T2>
	bool	operator >= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}

}

#endif