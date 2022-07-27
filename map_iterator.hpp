#ifndef __MAP_ITERATOR_HPP__
# define __MAP_ITERATOR_HPP__

# include "iterator_traits.hpp"

namespace ft {

	template <typename T, typename N>
	class map_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	ft::iterator_traits<T>						iterator_traits;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;
			typedef typename iterator_traits::iterator_category	iterator_category;


		private:
			typedef N<T>										node_type;
			typedef *node										node_pointer;
			typedef &node										node_reference;

		public:
			map_iterator() {}

			map_iterator(const node_type node)
				: m_node(node) {}

			template<typename Iter>
			map_iterator(const map_iterator<Iter> it) 
				: m_node(*m_node) {}

			map_iterator& operator++() {
				node_pointer result;

				// TODO: продумать логику end
				if (check_nill_node(result->parent)/* && result->right == previous*/) {
					
				}
				// спускаемся по мапе
				else if (!check_nill_node(m_node->right)) {
					result = iterate_down_left();
				}
				// поднимаемся по мапе
				else if (!check_nill_node(m_node->parent)) {
					result = iterate_up_left();
				}
				m_node = result;
				return *this;
			}
			
			map_iterator& operator--() {
				node_pointer result;

				// TODO: продумать логику end
				if (check_nill_node(result->parent)/* && result->right == previous*/) {
					
				}
				// спускаемся по мапе
				else if (!check_nill_node(m_node->left)) {
					result = iterate_down_right();
				}
				// поднимаемся по мапе
				else if (!check_nill_node(m_node->parent)) {
					result = iterate_up_right();
				}
				m_node = result;
				return *this;
			}

		private:
			node_pointer		 m_node;

			node_pointer			iterate_down_left() {
				node_pointer result = m_node->right;
				while (!check_nill_node(result->left)) {
					result = result->left;
				}
				return result;
			}

			node_pointer			iterate_up_left() {
				node_pointer result = m_node->parent;
				node_pointer previous = m_node;

				while (!check_nill_node(result) || result->right == previous) {
					previous = result;
					result = result->parent;
				}
				return result;
			}

			node_pointer			iterate_down_right() {
				node_pointer result = m_node->left;
				while (!check_nill_node(result->right)) {
					result = result->right;
				}
				return result;
			}

			node_pointer			iterate_up_right() {
				node_pointer result = m_node->parent;
				node_pointer previous = m_node;

				while (!check_nill_node(result) || result->left == previous) {
					previous = result;
					result = result->parent;
				}
				return result;
			}

			bool			check_nill_node(node_pointer node) {
				if (node->value != NULL) {
					return false;
				}
				return true;
			}
	};
}

#endif