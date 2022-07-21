#ifndef __REVERSE_ITERATOR_HPP__
# define __REVERSE_ITERATOR_HPP__

# include "iterator_traits.hpp"

namespace ft {

	template<typename Iter>
	class reverseIterator {
		public:
			typedef	Iter										iterator_type;
			typedef	ft::iterator_traits<iterator_type>			iterator_traits;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::iterator_category	iterator_category;

			reverseIterator() {}

			reverseIterator(const iterator_type ptr)
				: _it(ptr) {}

			template<typename RIter>
			reverseIterator(const reverseIterator<RIter> it) 
				: _it(it.base()) {}
			
			template<typename RIter>
			reverseIterator& operator=(const reverseIterator<RIter> &it) {
				_it = it.base();
				return *this;
			}

			reverseIterator& operator++() {
				--_it;
				return *this;
			}
			reverseIterator operator++(int) {
				reverseIterator temp = *this;
				--_it;
				return temp;
			}
			reverseIterator& operator--() {
				++_it;
				return *this;
			}
			reverseIterator operator--(int) {
				reverseIterator temp = *this;
				++_it;
				return temp;
			}
			reference	operator[](int index) {
				return *(*this + index);
			}
			pointer		operator->() {
				iterator_type temp = _it;
				--temp;
				return temp.operator->();
			}
			reference	operator*() {
				iterator_type temp = _it;
				--temp;
				return *temp;
			}
			bool operator == (const reverseIterator& o) const {
				return _it == o._it;
			}
			bool operator != (const reverseIterator& o) const {
				return !(_it == o._it);
			}
			iterator_type		base() const {
				return _it;
			}

			reverseIterator	operator + (difference_type n) const {
				reverseIterator	dst = *this;
				dst._it -= n;
				return dst;
			}

			reverseIterator	&operator += (difference_type n) {
				this->_it -= n;
				return *this;
			}

			reverseIterator	operator - (difference_type n) const {
				reverseIterator	dst = *this;
				dst._it += n;
				return dst;
			}

			reverseIterator	&operator -= (difference_type n) {
				this->_it += n;
				return *this;
			}

		private:
			iterator_type	_it;
	};

	template <typename T_L, typename T_R>
	bool    operator == (const ft::reverseIterator<T_L> &lhs, const ft::reverseIterator<T_R> &rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator != (const ft::reverseIterator<T_L> &lhs, const ft::reverseIterator<T_R> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T_L, typename T_R>
	bool    operator < (const ft::reverseIterator<T_L> &lhs, const ft::reverseIterator<T_R> &rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator > (const ft::reverseIterator<T_L> &lhs, const ft::reverseIterator<T_R> &rhs) {
		return rhs < lhs;
	}

	template <typename T_L, typename T_R>
	bool    operator <= (const ft::reverseIterator<T_L> &lhs, const ft::reverseIterator<T_R> &rhs) {
		return !(lhs > rhs);
	}

	template <typename T_L, typename T_R>
	bool    operator >= (const ft::reverseIterator<T_L> &lhs, const ft::reverseIterator<T_R> &rhs) {
		return !(lhs < rhs);
	}

	template <typename Iter>
	reverseIterator<Iter>
	operator + (typename ft::reverseIterator<Iter>::difference_type n,
				const ft::reverseIterator<Iter> &it) {
		return it + n;
	}

	template <typename Iter>
	typename ft::reverseIterator<Iter>::difference_type
	operator - (const ft::reverseIterator<Iter> &lhs,
				const ft::reverseIterator<Iter> &rhs) {
		return rhs.base() - lhs.base();
	}

	template <typename T_L, typename T_R>
	typename ft::iterator_traits<T_L>::difference_type
	operator - (ft::reverseIterator<T_L> lhs,
				ft::reverseIterator<T_R> rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif