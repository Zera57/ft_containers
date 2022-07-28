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
			typedef N												node_type;
			typedef node_type*										node_pointer;
			typedef node_type&										node_reference;

		public:
			map_iterator() {}

			map_iterator(const node_type node)
				: m_node(node) {}

			template<typename Iter>
			map_iterator(const map_iterator<Iter> it) 
				: m_node(*m_node) {}

			map_iterator& operator++() {
				m_node = iterator_increment(m_node);
				return *this;
			}
			
			map_iterator& operator++(int) {
				vector_iterator temp = *this;
				m_node = iterator_increment(m_node);
				return temp;
			}
			
			map_iterator& operator--() {
				m_node = iterator_decrement(m_node);
				return *this;
			}
			
			map_iterator& operator--(int) {
				vector_iterator temp = *this;
				m_node = iterator_derement(m_node);
				return temp;
			}

		private:
			node_pointer		 m_node;

			node_pointer			iterator_increment(node_pointer node) {
				// TODO: продумать логику end
				if (check_nill_node(node->parent)/* && node->right == previous*/) {
					
				}
				// спускаемся по мапе
				else if (!check_nill_node(node->right)) {
					node = iterate_down_left(node->right);
				}
				// поднимаемся по мапе
				else if (!check_nill_node(node->parent)) {
					node = iterate_up_left(node->parent, node);
				}
				return node;
			}

		
			node_pointer			iterator_decrement(node_pointer node) {
				// TODO: продумать логику end
				if (check_nill_node(node)/* && node->right == previous*/) {
					
				}
				// спускаемся по мапе
				else if (!check_nill_node(m_node->left)) {
					node = iterate_down_right(m_node->left);
				}
				// поднимаемся по мапе
				else if (!check_nill_node(m_node->parent)) {
					node = iterate_up_right(m_node->parent, node);
				}
				return node;
			}

			node_pointer			iterate_down_left(node_pointer node) {
				while (!check_nill_node(node->left)) {
					node = node->left;
				}
				return node;
			}

			node_pointer			iterate_up_left(node_pointer node, node_pointer previous) {
				while (!check_nill_node(node) || node->right == previous) {
					previous = node;
					node = node->parent;
				}
				return node;
			}

			node_pointer			iterate_down_right(node_pointer node) {
				while (!check_nill_node(node->right)) {
					node = node->right;
				}
				return node;
			}

			node_pointer			iterate_up_right(node_pointer node, node_pointer previous) {
				while (!check_nill_node(node) || node->left == previous) {
					previous = node;
					node = node->parent;
				}
				return node;
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