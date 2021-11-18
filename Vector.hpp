#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator>
# include <memory>
# include <cstddef>
# include <stdexcept>
# include <typeinfo>

template<bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if <true, T> { typedef T type; };

 template <typename T>
	class vectorIterator : public std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef T								value_type;


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
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		private:
			T*				_m_ptr;
			size_type		_capacity;
			size_type		size;
			allocator_type	_allocator;
			
		public:
			explicit vector (const allocator_type& alloc = allocator_type()) :
				_m_ptr(NULL), _capacity(0), size(0), _allocator(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(),
				 const allocator_type& alloc = allocator_type()) :
				 _m_ptr(NULL), _capacity(0), size(0), _allocator(alloc)  {
				_m_ptr = _allocator.allocate(n);
				for (size_t i = 0; i < n; i++)
					_allocator.construct(&_m_ptr[i], val);
				_capacity = n;
				size = n;
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) :
					_m_ptr(NULL), _capacity(0), size(0), _allocator(alloc) {
				if (typeid(std::iterator_traits<InputIterator>::iterator_category()) != typeid(std::random_access_iterator_tag))
					throw;
				_m_ptr = _allocator.allocate(5);
				size_t i = 0;
				while (first != last) {
					_allocator.construct(&_m_ptr[i++], *first);
					++first;
				}
			}

			vector (const vector& x) :
			 _m_ptr(NULL), _capacity(x._capacity), size(x.size), _allocator(x._allocator) {
				_m_ptr = _allocator.allocate(x._capacity);
				size_t i = 0;
				for (iterator elem = x.begin(); elem != x.end(); elem++) {
					_allocator.construct(_m_ptr[i], *elem);
					++i;
				}
			}

			~vector () {
				for (size_t i = 0; i < size; i++) {
					_allocator.destroy(&_m_ptr[i]);
				}
				_allocator.deallocate(_m_ptr, _capacity);
			}

			iterator begin() {
				return (iterator(_m_ptr));
			}

			iterator end() {
				return (iterator(_m_ptr + size));
			}
		private:
			bool _check_Iterator(std::random_access_iterator_tag) {
				return true;
			}

			bool _check_Iterator() {
				return false;
			}
	};


#endif