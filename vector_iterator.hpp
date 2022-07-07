#ifndef __VECTOR_ITERATOR_HPP__
#define __VECTOR_ITERATOR_HPP__

# include "iterator_traits.hpp"


namespace ft {

 template <typename T>
	class vectorIterator : public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef	ft::iterator_traits<T>						iterator_traits;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::iterator_category	iterator_category;

			vectorIterator() {}

			vectorIterator(const T ptr)
				: m_ptr(ptr) {}

			template<typename Iter>
			vectorIterator(const vectorIterator<Iter> it) 
				: m_ptr(it.base()) {}
			
			vectorIterator& operator++() {
				++m_ptr;
				return *this;
			}
			vectorIterator operator++(int) {
				vectorIterator temp = *this;
				++(*this);
				return temp;
			}
			vectorIterator& operator--() {
				--m_ptr;
				return *this;
			}
			vectorIterator operator--(int) {
				vectorIterator temp = *this;
				--(*this);
				return temp;
			}
			reference	operator[](int index) {
				return *(m_ptr + index);
			}
			pointer		operator->() {
				return m_ptr;
			}
			reference	operator*() {
				return *m_ptr;
			}
			bool operator == (const vectorIterator& o) const {
				return m_ptr == o.m_ptr;
			}
			bool operator != (const vectorIterator& o) const {
				return !(m_ptr == o.m_ptr);
			}
			pointer const		base() const {
				return m_ptr;
			}

			vectorIterator	operator + (difference_type n) const {
				vectorIterator	dst = *this;
				dst.m_ptr += n;
				return dst;
			}

			vectorIterator	&operator += (difference_type n) {
				this->m_ptr += n;
				return *this;
			}

			vectorIterator	operator - (difference_type n) const {
				vectorIterator	dst = *this;
				dst.m_ptr -= n;
				return dst;
			}

			vectorIterator	&operator -= (difference_type n) {
				this->m_ptr -= n;
				return *this;
			}

			difference_type	operator + (const vectorIterator &other) {
				return this->m_ptr + other.m_ptr;
			}

			difference_type	operator - (const vectorIterator &other) {
				return this->m_ptr - other.m_ptr;
			}

			// typename vectorIterator<T>::difference_type
			// operator-(vectorIterator<T> temp1, vectorIterator<T> temp2) {
			// 	return (temp1.base() - temp2.base());
			// }

		private:
			pointer		m_ptr;
	};

	template <typename Iter>
	typename ft::vectorIterator<Iter>
	operator + (typename ft::vectorIterator<Iter>::difference_type lhs,
				ft::vectorIterator<Iter> rhs) {
		return rhs + lhs;
	}

	template <typename Iter>
	typename ft::iterator_traits<Iter>::difference_type
	operator - (ft::vectorIterator<Iter> lhs,
				ft::vectorIterator<Iter> rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename T_L, typename T_R>
	typename ft::iterator_traits<T_L>::difference_type
	operator - (ft::vectorIterator<T_L> lhs,
				ft::vectorIterator<T_R> rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator == (const ft::vectorIterator<T_L> lhs, ft::vectorIterator<T_R> rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator != (const ft::vectorIterator<T_L> lhs, ft::vectorIterator<T_R> rhs) {
		return !(lhs == rhs);
	}

	template <typename T_L, typename T_R>
	bool    operator < (const ft::vectorIterator<T_L> lhs, ft::vectorIterator<T_R> rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator > (const ft::vectorIterator<T_L> lhs, ft::vectorIterator<T_R> rhs) {
		return rhs < lhs;
	}

	template <typename T_L, typename T_R>
	bool    operator <= (const ft::vectorIterator<T_L> lhs, ft::vectorIterator<T_R> rhs) {
		return !(lhs > rhs);
	}

	template <typename T_L, typename T_R>
	bool    operator >= (const ft::vectorIterator<T_L> lhs, ft::vectorIterator<T_R> rhs) {
		return !(lhs < rhs);
	}
}

#endif