#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator>
# include <memory>
# include <cstddef>
# include <stdexcept>
# include <typeinfo>
# include "Utils.hpp"

 template <typename T>
	class vectorIterator : public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;

			vectorIterator() {}

			vectorIterator(value_type* ptr)
				: m_ptr(ptr) {}
			
			vectorIterator& operator++() {
				m_ptr++;
				return *this;
			}
			vectorIterator& operator++(int) {
				vectorIterator* temp = this;
				++(*this);
				return *temp;
			}
			vectorIterator& operator--() {
				m_ptr--;
				return *this;
			}
			vectorIterator& operator--(int) {
				vectorIterator* temp = *this;
				--(*this);
				return temp;
			}
			value_type& operator[](int index) {
				return *(m_ptr + index);
			}
			value_type* operator->() {
				return m_ptr;
			}
			value_type& operator*() {
				return *m_ptr;
			}
			void operator*=(value_type a) {
				*m_ptr = a;
			}
			bool operator == (const vectorIterator& o) const {
				return m_ptr == o.m_ptr;
			}
			bool operator != (const vectorIterator& o) const {
				return !(m_ptr == o.m_ptr);
			}
			value_type* base() {
				return m_ptr;
			}

			vectorIterator	operator + (difference_type n) {
				vectorIterator	dst = *this;
				dst.m_ptr += n;
				return dst;
			}

			vectorIterator	operator - (difference_type n) {
				vectorIterator	dst = *this;
				dst -= n;
				return dst;
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
			value_type* m_ptr;
	};

class ReversevectorIterator {

};

 template < typename T, typename Alloc = std::allocator<T> >
	class vector {

		public:
			typedef T								value_type;
			typedef Alloc							allocator_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef vectorIterator<T> 				iterator;
			typedef const vectorIterator<vector>	const_iterator;
			typedef ReversevectorIterator			reverse_iterator;
			typedef const ReversevectorIterator		const_reverse_iterator;
			typedef ptrdiff_t						difference_type;
			typedef size_t							size_type;

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
				_m_ptr = _allocator.allocate(n);
				for (size_t i = 0; i < n; i++)
					_allocator.construct(&_m_ptr[i], val);
				_capacity = n;
				_size = n;
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) :
					_m_ptr(NULL), _capacity(0), _size(0), _allocator(alloc) {
				_m_ptr = _allocator.allocate(std::distance(first, last));
				size_t i = 0;
				while (first != last) {
					_allocator.construct(&_m_ptr[i++], *first);
					++first;
				}
			}

			vector (const vector& x) :
			 _m_ptr(NULL), _capacity(x._capacity), _size(x.size), _allocator(x._allocator) {
				_m_ptr = _allocator.allocate(x._capacity);
				size_t i = 0;
				for (iterator elem = x.begin(); elem != x.end(); elem++) {
					_allocator.construct(_m_ptr[i], *elem);
					++i;
				}
			}

			~vector () {
				_destroy_vector();
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

			iterator			end() {
				return (iterator(_m_ptr + _size));
			}

			reverse_iterator	rbegin() {
				return (reverse_iterator(_m_ptr + _size - 1));
			}

			reverse_iterator	rend() {
				return (reverse_iterator(_m_ptr - 1));
			}

			size_type			size(void) const {
				return (_size);
			}

			size_type			capacity(void) const {
				return (_capacity);
			}

			size_type			max_size() {
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
					_smart_change_capacity(n);
					for (size_t i = _size; i < n; i++)
					{
						_allocator.construct(&_m_ptr[i], val);
					}
					_size = n;
				}
			}

			void reserve (size_type n) {
				if (_capacity < n) {
					_raw_change_capacity(n);
				}
			}

			reference operator[] (size_type n) {
				return (reference(_m_ptr[n]));
			}

			const_reference operator[] (size_type n) const {
				return (const_reference(_m_ptr[n]));
			}

			reference at (size_type n) {
				return (reference(_m_ptr[n]));
			}

			const_reference at (size_type n) const {
				return (const_reference(_m_ptr[n]));
			}

			reference front (size_type n) {
				return (reference(*_m_ptr));
			}

			const_reference front (size_type n) const {
				return (const_reference(*_m_ptr));
			}

			reference back (size_type n) {
				return (reference(*(_m_ptr + _size)));
			}

			const_reference back (size_type n) const {
				return (const_reference(*(_m_ptr + _size)));
			}

			template <class InputIterator>
				void assign (InputIterator first, InputIterator last,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) {
					_destroy_vector();
					size_type	new_capacity = std::distance(first, last);
					if (new_capacity > _capacity) {
						_m_ptr = _allocator.allocate(new_capacity);
						_capacity = new_capacity;
					} else {
						_m_ptr = _allocator.allocate(_capacity);
					}
					for (size_t i = 0; i < new_capacity; i++) {
						_allocator.construct(&_m_ptr[i], &(*first));
						first++;
						if (first == last)
							break;
					}
					_size = new_capacity;
				}

			void assign (size_type n, const value_type& val) {
				_destroy_vector();
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
				if (size > _capacity) {
					_smart_change_capacity(size);
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
				difference_type diff = std::distance(begin(), position);
				if (size > _capacity) {
					_smart_change_capacity(size);
				}
				value_type *dst = _m_ptr + size - 1;
				value_type *begin = _m_ptr + _size - 1;
				value_type *end = _m_ptr + diff;
				while (begin >= end) {
					_allocator.construct(dst, *begin);
					--dst;
					--begin;
				}
				for (value_type i = diff; i < diff + n; i++) {
					_allocator.destroy(&_m_ptr[i]);
					_allocator.construct(&_m_ptr[i], val);
				}
				_size = size;
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
				size_type size = x._size;
				size_type capacity = x._capacity;
				value_type *m_ptr = x._m_ptr;
				allocator_type allocator = x._allocator;
				x._size = this->_size;
				x._capacity = this->_capacity;
				x._m_ptr = this->_m_ptr;
				x._allocator = this->_allocator;
				this->_size = size;
				this->_capacity = capacity;
				this->_m_ptr = m_ptr;
				this->_allocator = allocator;
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
			void _smart_change_capacity(size_type new_capacity) {
				if (new_capacity > 2 * _size) {
					_raw_change_capacity(new_capacity);
				} else {
					_raw_change_capacity(_size * 2);
				}
			}

			void _raw_change_capacity(size_type new_capacity) {
				if (new_capacity != _capacity) {
					value_type *temp = _allocator.allocate(new_capacity);

					for (size_t i = 0; i < _size; i++) {
						_allocator.construct(&temp[i], _m_ptr[i]);
					}
					_destroy_vector();

					_m_ptr = temp;
					_capacity = new_capacity;
				}
			}

			void _destroy_vector() {
				if (_capacity > 0) {
					if (_size > 0) {
						for (size_t i = 0; i < _size; i++) {
							_allocator.destroy(&_m_ptr[i]);
						}
					}
					_allocator.deallocate(_m_ptr, _capacity);
				}
			}

			bool _check_Iterator(std::random_access_iterator_tag) {
				return true;
			}

			bool _check_Iterator() {
				return false;
			}
	};


#endif
