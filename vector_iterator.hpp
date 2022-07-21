#ifndef __VECTOR_ITERATOR_HPP__
# define __VECTOR_ITERATOR_HPP__

# include "iterator_traits.hpp"


namespace ft {

 template <typename T>
	class vector_iterator : public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef	ft::iterator_traits<T>						iterator_traits;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::iterator_category	iterator_category;

			vector_iterator() {}

			vector_iterator(const T ptr)
				: m_ptr(ptr) {}

			template<typename Iter>
			vector_iterator(const vector_iterator<Iter> it) 
				: m_ptr(it.base()) {}
			
			vector_iterator& operator++() {
				++m_ptr;
				return *this;
			}
			vector_iterator operator++(int) {
				vector_iterator temp = *this;
				++(*this);
				return temp;
			}
			vector_iterator& operator--() {
				--m_ptr;
				return *this;
			}
			vector_iterator operator--(int) {
				vector_iterator temp = *this;
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
			bool operator == (const vector_iterator& o) const {
				return m_ptr == o.m_ptr;
			}
			bool operator != (const vector_iterator& o) const {
				return !(m_ptr == o.m_ptr);
			}
			pointer const		base() const {
				return m_ptr;
			}

			vector_iterator	operator + (difference_type n) const {
				vector_iterator	dst = *this;
				dst.m_ptr += n;
				return dst;
			}

			vector_iterator	&operator += (difference_type n) {
				this->m_ptr += n;
				return *this;
			}

			vector_iterator	operator - (difference_type n) const {
				vector_iterator	dst = *this;
				dst.m_ptr -= n;
				return dst;
			}

			vector_iterator	&operator -= (difference_type n) {
				this->m_ptr -= n;
				return *this;
			}

			difference_type	operator + (const vector_iterator &other) {
				return this->m_ptr + other.m_ptr;
			}

			difference_type	operator - (const vector_iterator &other) {
				return this->m_ptr - other.m_ptr;
			}

			// typename vector_iterator<T>::difference_type
			// operator-(vector_iterator<T> temp1, vector_iterator<T> temp2) {
			// 	return (temp1.base() - temp2.base());
			// }

		private:
			pointer		m_ptr;
	};

	template <typename Iter>
	typename ft::vector_iterator<Iter>
	operator + (typename ft::vector_iterator<Iter>::difference_type lhs,
				ft::vector_iterator<Iter> rhs) {
		return rhs + lhs;
	}

	template <typename Iter>
	typename ft::iterator_traits<Iter>::difference_type
	operator - (ft::vector_iterator<Iter> lhs,
				ft::vector_iterator<Iter> rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename T_L, typename T_R>
	typename ft::iterator_traits<T_L>::difference_type
	operator - (ft::vector_iterator<T_L> lhs,
				ft::vector_iterator<T_R> rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator == (const ft::vector_iterator<T_L> lhs, ft::vector_iterator<T_R> rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator != (const ft::vector_iterator<T_L> lhs, ft::vector_iterator<T_R> rhs) {
		return !(lhs == rhs);
	}

	template <typename T_L, typename T_R>
	bool    operator < (const ft::vector_iterator<T_L> lhs, ft::vector_iterator<T_R> rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename T_L, typename T_R>
	bool    operator > (const ft::vector_iterator<T_L> lhs, ft::vector_iterator<T_R> rhs) {
		return rhs < lhs;
	}

	template <typename T_L, typename T_R>
	bool    operator <= (const ft::vector_iterator<T_L> lhs, ft::vector_iterator<T_R> rhs) {
		return !(lhs > rhs);
	}

	template <typename T_L, typename T_R>
	bool    operator >= (const ft::vector_iterator<T_L> lhs, ft::vector_iterator<T_R> rhs) {
		return !(lhs < rhs);
	}
}

#endif