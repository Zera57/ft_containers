#ifndef __xXx_VECTOR_HPP_xXx__
# define __xXx_VECTOR_HPP_xXx__

# include <iostream>
# include <iterator>
# include <memory>
# include <cstddef>
# include <stdexcept>
# include <typeinfo>
# include "IteratorTraits.hpp"
# include "Utils.hpp"
# include "compare_utils.hpp"

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
				return *(_it + index);
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

 template < typename T, typename Alloc = std::allocator<T> >
	class vector {

		public:
			typedef Alloc										allocator_type;
			typedef typename allocator_type::value_type			value_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef vectorIterator<pointer> 					iterator;
			typedef vectorIterator<const_pointer>				const_iterator;
			typedef reverseIterator<iterator>					reverse_iterator;
			typedef reverseIterator<const_iterator>				const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

		private:
			T*				_m_ptr;
			size_type		_capacity;
			size_type		_size;
			allocator_type	_allocator;
			
		public:
			explicit vector (const allocator_type& alloc = allocator_type()) :
				_m_ptr(NULL), _capacity(0), _size(0), _allocator(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(),
				 const allocator_type& alloc = allocator_type()) :
				 _m_ptr(NULL), _capacity(0), _size(0), _allocator(alloc)  {
					__hidden_constructor(n, val, true_type());
			}

			template <typename InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type()) :
					_m_ptr(NULL), _capacity(0), _size(0), _allocator(alloc) {
				typedef typename ft::is_integral<InputIterator>::type		itegral;

				__hidden_constructor(first, last, itegral());
			}

			vector (const vector& other) :
			 _m_ptr(NULL), _capacity(other.capacity()), _size(other.size()), _allocator(other.get_allocator()) {
				_m_ptr = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(&_m_ptr[i], other[i]);
			}

			~vector () {
				__destroy_vector();
			}

			vector&				operator= (const vector& other) {
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.destroy(&this->_m_ptr[i]);
				this->_size = 0;
				insert(this->begin(), other.begin(), other.end());
				return *this;
			 }

			iterator			begin() {
				return (iterator(_m_ptr));
			}
			
			const_iterator		begin() const {
				return (const_iterator(_m_ptr));
			}

			iterator			end() {
				return (iterator(_m_ptr + _size));
			}
			
			const_iterator		end() const {
				return (const_iterator(_m_ptr + _size));
			}

			reverse_iterator	rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(end()));
			}

			reverse_iterator	rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(begin()));
			}

			size_type			size(void) const {
				return (_size);
			}

			size_type			capacity(void) const {
				return (_capacity);
			}

			size_type			max_size() const {
				return (allocator_type().max_size());
			}

			bool				empty (void) const {
				return (_size == 0 ? true : false);
			}

			void resize (size_type n, value_type val = value_type()) {
				if (n < _size) {
					for (size_type i = n; i < _size; i++)
					{
						_allocator.destroy(&_m_ptr[i]);
					}
					_size = n;
				} else if (_size < n) {
					__smart_change_capacity(n);
					for (size_type i = _size; i < n; i++)
					{
						_allocator.construct(&_m_ptr[i], val);
					}
					_size = n;
				}
			}

			void reserve (size_type n) {
				if (_capacity < n) {
					__raw_change_capacity(n);
				}
			}

			reference operator[] (size_type n) {
				return (reference(_m_ptr[n]));
			}

			const_reference operator[] (size_type n) const {
				return (const_reference(_m_ptr[n]));
			}

			reference at (size_type n) {
				if (n >= _size)
					throw std::out_of_range("you go out of range");
				return (_m_ptr[n]);
			}

			const_reference at (size_type n) const {
				if (n >= _size)
					throw std::out_of_range("you go out of range");
				return (_m_ptr[n]);
			}

			reference front () {
				return (*begin());
			}

			const_reference front () const {
				return (*begin());
			}

			reference back () {
				return (*end());
			}

			const_reference back () const {
				return (*end());
			}

			template <class InputIterator>
				void assign (InputIterator first, InputIterator last) {
					typedef typename ft::is_integral<InputIterator>::type		itegral;

					__hidden_assign(first, last, itegral());
				}

			void assign (size_type n, const value_type& val) {
				__hidden_assign(n, val, true_type());
			}

			void push_back (const value_type& val) {
				difference_type size = _size + 1;
				if (size > static_cast<difference_type>(_capacity)) {
					__smart_change_capacity(size);
				}
				_size = size;
				_allocator.construct(&_m_ptr[_size - 1], val);
			}

			void pop_back () {
				_allocator.destroy(_m_ptr + _size - 1);
				--_size;
			}

			iterator insert (iterator position, const value_type& val) {
				difference_type	diff = std::distance(this->begin(), position);

				insert(position, 1, val);
				return this->begin() + diff;
			}

			void insert (iterator position, size_type n, const value_type& val) {
				__hidden_insert(position, n, val, true_type());
			}

			template< class InputIterator>
			void insert( iterator pos, InputIterator first, InputIterator last ) {
				typedef typename ft::is_integral<InputIterator>::type		itegral;

				__hidden_insert(pos, first, last, itegral());
			}

			iterator erase (iterator position) {
				return (erase(position, position + 1));
			}

			iterator erase (iterator first, iterator last) {
				size_type diff = std::distance(begin(), first);
				size_type n = std::distance(first, last);

				for (size_type i = diff; i < _size; i++)
				{
					_allocator.destroy(&_m_ptr[i]);
					_allocator.construct(&_m_ptr[i], _m_ptr[i + n]);
				}
				_size -= n;

				return (_m_ptr + diff);
			}

			void swap (vector& x) {
				vector<value_type, allocator_type>	buf = *this;
				*this = x;
				x = buf;
			}

			void clear() {
				if (_size > 0) {
						for (size_type i = 0; i < _size; i++) {
							_allocator.destroy(&_m_ptr[i]);
						}
						_size = 0;
				}
			}

			allocator_type get_allocator() const {
				return (_allocator);
			}

		private:

			void	__hidden_constructor (size_type n, const value_type& val, true_type) {
				_m_ptr = _allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(&_m_ptr[i], val);
				_capacity = n;
				_size = n;
			}

			template <typename InputIterator>
			void	__hidden_constructor (InputIterator first, InputIterator last, false_type) {
				size_type size = std::distance(first, last);
				_m_ptr = _allocator.allocate(size);
				size_type i = 0;
				while (first != last) {
					_allocator.construct(&_m_ptr[i++], *first);
					++first;
				}
				_size = size;
				_capacity = size;
			}

			void	__hidden_assign (size_type n, const value_type& val, true_type) {
				__destroy_vector();
				if (n > _capacity) {
					_m_ptr = _allocator.allocate(n);
					_capacity = n;
				} else {
					_m_ptr = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < n; i++) {
					_allocator.construct(&_m_ptr[i], val);
				}
				_size = n;
			}

			template <typename InputIterator>
			void	__hidden_assign (InputIterator first, InputIterator last, false_type) {
				__destroy_vector();
				size_type	new_capacity = std::distance(first, last);
				if (new_capacity > _capacity) {
					_m_ptr = _allocator.allocate(new_capacity);
					_capacity = new_capacity;
				} else {
					_m_ptr = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < new_capacity; i++) {
					_allocator.construct(&_m_ptr[i], *first);
					first++;
					if (first == last)
						break;
				}
				_size = new_capacity;
			}

			void	__reverse_insert(pointer dst, pointer begin, pointer end) {
				while (begin >= end) {
					this->_allocator.construct(dst, *begin);
					--begin;
					--dst;
				}
			}

			void	__hidden_insert(iterator position, size_type n, const value_type& val, true_type) {
				size_type diff = std::distance(begin(), position);

				__smart_change_capacity(n + _size);
				__reverse_insert(&_m_ptr[n + this->_size - 1], &_m_ptr[this->_size - 1], &_m_ptr[diff]);
				for (size_type i = diff; i < diff + n; i++) {
					this->_allocator.construct(&_m_ptr[i], val);
				}
				_size += n;
			}

			template <typename InputIterator>
			void	__hidden_insert( iterator position, InputIterator first, InputIterator last, false_type) {
				size_type diff = std::distance(begin(), position);
				size_type size = std::distance(first, last);

				__smart_change_capacity(size + _size);
				__reverse_insert(&_m_ptr[size + this->_size - 1], &_m_ptr[this->_size - 1], &_m_ptr[diff]);
				for (size_type i = diff; i < size + diff; i++) {
					this->_allocator.construct(&_m_ptr[i], *first++);
				}
				_size += size;
			}

			void __smart_change_capacity(size_type new_capacity) {
				if (new_capacity > 2 * _size) {
					__raw_change_capacity(new_capacity);
				} else {
					__raw_change_capacity(_size * 2);
				}
			}

			void __raw_change_capacity(size_type new_capacity) {
				if (new_capacity != _capacity) {
					value_type *new_vector = _allocator.allocate(new_capacity);
					size_type size = _size;
					for (size_type i = 0; i < _size; i++) {
						_allocator.construct(&new_vector[i], _m_ptr[i]);
					}
					__destroy_vector();

					_m_ptr = new_vector;
					_capacity = new_capacity;
					_size = size;
				}
			}

			void __destroy_vector() {
				if (_capacity > 0) {
					if (_size > 0) {
						for (size_type i = 0; i < _size; i++) {
							_allocator.destroy(&_m_ptr[i]);
						}
					}
					_allocator.deallocate(_m_ptr, _capacity);
				}
				_size = 0;
				_capacity = 0;
			}

			bool __check_Iterator(std::random_access_iterator_tag) {
				return true;
			}

			bool __check_Iterator() {
				return false;
			}
	};
}

	template <typename T>
	bool    operator == (const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T>
	bool    operator != (const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	bool    operator < (const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool    operator > (const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return rhs < lhs;
	}

	template <typename T>
	bool    operator <= (const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return !(lhs > rhs);
	}

	template <typename T>
	bool    operator >= (const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return !(lhs < rhs);
	}

#endif
