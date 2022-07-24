#ifndef __MAP_ITERATOR_HPP__
# define __MAP_ITERATOR_HPP__

namespace ft {

    template <typename T>
	class map_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	ft::iterator_traits<T>						iterator_traits;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::iterator_category	iterator_category;

			map_iterator() {}

			map_iterator(const T ptr)
				: m_ptr(ptr) {}

			template<typename Iter>
			map_iterator(const map_iterator<Iter> it) 
				: m_ptr(it.base()) {}

			map_iterator& operator++() {
				++m_ptr;
				return *this;
			}
            map_iterator& operator--() {
				--m_ptr;
				return *this;
			}

		private:
			pointer		m_ptr;
    };
}

#endif