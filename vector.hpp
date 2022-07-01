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

			vectorIterator(value_type* ptr)
				: m_ptr(ptr) {}
			
			vectorIterator& operator++() {
				++m_ptr;
				return *this;
			}
			vectorIterator& operator++(int) {
				vectorIterator* temp = this;
				++(*this);
				return *temp;
			}
			vectorIterator& operator--() {
				--m_ptr;
				return *this;
			}
			vectorIterator& operator--(int) {
				vectorIterator* temp = *this;
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
			pointer		base() {
				return m_ptr;
			}

			vectorIterator	operator + (difference_type n) {
				vectorIterator	dst = *this;
				dst.m_ptr += n;
				return dst;
			}

			vectorIterator	&operator += (difference_type n) {
				this->m_ptr += n;
				return *this;
			}

			vectorIterator	operator - (difference_type n) {
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

class ReversevectorIterator {

};

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
			typedef ReversevectorIterator				reverse_iterator;
			typedef ReversevectorIterator		const_reverse_iterator;
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

			vector&				operator= (const vector& x) {
				_m_ptr = x._m_ptr;
				_capacity = x._capacity;
				_size = x._size;
				_allocator = x._allocator;
				return (*this);
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

			reverse_iterator	rend() {
				return (reverse_iterator(begin()));
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
					for (size_t i = n; i < _size; i++)
					{
						_allocator.destroy(&_m_ptr[i]);
					}
					_size = n;
				} else if (_size < n) {
					__smart_change_capacity(n);
					for (size_t i = _size; i < n; i++)
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
				return (_m_ptr[n]);
			}

			const_reference at (size_type n) const {
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
				void assign (InputIterator first, InputIterator last,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
					__destroy_vector();
					size_type	new_capacity = std::distance(first, last);
					if (new_capacity > _capacity) {
						_m_ptr = _allocator.allocate(new_capacity);
						_capacity = new_capacity;
					} else {
						_m_ptr = _allocator.allocate(_capacity);
					}
					for (size_t i = 0; i < new_capacity; i++) {
						_allocator.construct(&_m_ptr[i], *first);
						first++;
						if (first == last)
							break;
					}
					_size = new_capacity;
				}

			void assign (size_type n, const value_type& val) {
				__destroy_vector();
				if (n > _capacity) {
					_m_ptr = _allocator.allocate(n);
					_capacity = n;
				} else {
					_m_ptr = _allocator.allocate(_capacity);
				}
				for (size_t i = 0; i < n; i++) {
					_allocator.construct(&_m_ptr[i], val);
				}
				_size = n;
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
				size_type size = _size + n;
				size_type diff = std::distance(begin(), position);
				if (size > _capacity) {
					__smart_change_capacity(size);
				}
				value_type *dst = _m_ptr + size - 1;
				value_type *begin = _m_ptr + _size - 1;
				value_type *end = _m_ptr + diff;
				while (begin >= end) {
					_allocator.construct(dst, *begin);
					--dst;
					--begin;
				}
				for (size_type i = diff; i < diff + n; i++) {
					_allocator.destroy(&_m_ptr[i]);
					_allocator.construct(&_m_ptr[i], val);
				}
				_size = size;
			}

			template< class InputIterator,
					  typename std::enable_if<!is_integral<InputIterator>::value, InputIterator>::type*
			>
			void insert( iterator pos, InputIterator first, InputIterator last ) {
				pos;
				first;
				last;
			}

			iterator erase (iterator position) {
				return (erase(position, position + 1));
			}

			iterator erase (iterator first, iterator last) {
				difference_type diff = std::distance(begin(), first);
				difference_type n = std::distance(first, last);

				for (difference_type i = diff; i < _size; i++)
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
						for (size_t i = 0; i < _size; i++) {
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
				for (size_t i = 0; i < n; i++)
					_allocator.construct(&_m_ptr[i], val);
				_capacity = n;
				_size = n;
			}

			template <typename InputIterator>
			void	__hidden_constructor (InputIterator first, InputIterator last, false_type) {
				_m_ptr = _allocator.allocate(std::distance(first, last));
				size_t i = 0;
				while (first != last) {
					_allocator.construct(&_m_ptr[i++], *first);
					++first;
				}
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
					value_type *temp = _allocator.allocate(new_capacity);

					for (size_t i = 0; i < _size; i++) {
						_allocator.construct(&temp[i], _m_ptr[i]);
					}
					__destroy_vector();

					_m_ptr = temp;
					_capacity = new_capacity;
				}
			}

			void __destroy_vector() {
				if (_capacity > 0) {
					if (_size > 0) {
						for (size_t i = 0; i < _size; i++) {
							_allocator.destroy(&_m_ptr[i]);
						}
					}
					_allocator.deallocate(_m_ptr, _capacity);
				}
			}

			bool __check_Iterator(std::random_access_iterator_tag) {
				return true;
			}

			bool __check_Iterator() {
				return false;
			}
	};
}


#endif
