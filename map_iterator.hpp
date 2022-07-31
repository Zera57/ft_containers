#ifndef __MAP_ITERATOR_HPP__
# define __MAP_ITERATOR_HPP__

# include "iterator_traits.hpp"
# include "map_node.hpp"
# include <iostream>

namespace ft {

	template <typename T>
	class map_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {

		private:
			typedef map_node<T>										node_type;
			typedef node_type*										node_pointer;
			typedef node_type&										node_reference;
		public:
			typedef T											value_type;
			typedef value_type*									pointer;
			typedef value_type&									reference;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t								difference_type;


		public:
			map_iterator() {}

			map_iterator(const node_pointer node)
				: m_node(node) {}

			map_iterator(const map_iterator &it) 
				: m_node(it.m_node) {}

			pointer		operator->() const {
				return m_node->value;
			}

			reference	operator*() const {
				return *m_node->value;
			}

			map_iterator& operator++() {
				m_node = iterator_increment(m_node);
				return *this;
			}
			
			map_iterator operator++(int) {
				map_iterator temp = *this;
				m_node = iterator_increment(m_node);
				return temp;
			}
			
			map_iterator& operator--() {
				m_node = iterator_decrement(m_node);
				return *this;
			}
			
			map_iterator operator--(int) {
				map_iterator temp = *this;
				m_node = iterator_decrement(m_node);
				return temp;
			}

			bool operator == (const map_iterator& o) const {
				return m_node == o.m_node;
			}

			bool operator != (const map_iterator& o) const {
				return !(m_node == o.m_node);
			}

			node_pointer		base() const {
				return m_node;
			}

		private:
			node_pointer		 m_node;

			node_pointer			iterator_increment(node_pointer node) {
				// TODO: продумать логику end
				if (check_nill_node(node)/* && node->right == previous*/) {
					// std::cout << "Конец" << std::endl;
					node = node->left;
				}
				// спускаемся по мапе
				else if (!check_nill_node(node->right)) {
					// std::cout << "Спускаемся" << std::endl;
					node = iterate_down_left(node->right);
				}
				// поднимаемся по мапе
				else {
					// std::cout << "Поднимаемся" << std::endl;
					node = iterate_up_left(node->parent, node);
				}
				return node;
			}

		
			node_pointer			iterator_decrement(node_pointer node) {
				// TODO: продумать логику end
				if (check_nill_node(node)/* && node->right == previous*/) {
					node = node->right;
				}
				// спускаемся по мапе
				else if (!check_nill_node(m_node->left)) {
					node = iterate_down_right(m_node->left);
				}
				// поднимаемся по мапе
				else {
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
				while (!check_nill_node(node) && node->right == previous) {
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
				while (!check_nill_node(node) && node->left == previous) {
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

	template <typename T>
	class map_iterator_const : public std::iterator<std::bidirectional_iterator_tag, T> {

		private:
			typedef map_node<T>										node_type;
			typedef node_type*										node_pointer;
			typedef node_type&										node_reference;
		public:
			typedef const T											value_type;
			typedef value_type*									pointer;
			typedef value_type&									reference;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t								difference_type;


		public:
			map_iterator_const() {}

			map_iterator_const(const node_pointer node)
				: m_node(node) {}

			map_iterator_const(const map_iterator<T> &it) 
				: m_node(it.base()) {}

			map_iterator_const(const map_iterator_const &it) 
				: m_node(it.m_node) {}

			pointer		operator->() const {
				return m_node->value;
			}

			reference	operator*() const {
				return *m_node->value;
			}

			map_iterator_const& operator++() {
				m_node = iterator_increment(m_node);
				return *this;
			}
			
			map_iterator_const operator++(int) {
				map_iterator_const temp = *this;
				m_node = iterator_increment(m_node);
				return temp;
			}
			
			map_iterator_const& operator--() {
				m_node = iterator_decrement(m_node);
				return *this;
			}
			
			map_iterator_const operator--(int) {
				map_iterator_const temp = *this;
				m_node = iterator_decrement(m_node);
				return temp;
			}

			bool operator == (const map_iterator_const& o) const {
				return m_node == o.m_node;
			}

			bool operator != (const map_iterator_const& o) const {
				return !(m_node == o.m_node);
			}

			node_pointer		base() const {
				return m_node;
			}

		private:
			node_pointer		 m_node;

			node_pointer			iterator_increment(node_pointer node) {
				// TODO: продумать логику end
				if (check_nill_node(node)/* && node->right == previous*/) {
					// std::cout << "Конец" << std::endl;
					node = node->left;
				}
				// спускаемся по мапе
				else if (!check_nill_node(node->right)) {
					// std::cout << "Спускаемся" << std::endl;
					node = iterate_down_left(node->right);
				}
				// поднимаемся по мапе
				else {
					// std::cout << "Поднимаемся" << std::endl;
					node = iterate_up_left(node->parent, node);
				}
				return node;
			}

		
			node_pointer			iterator_decrement(node_pointer node) {
				// TODO: продумать логику end
				if (check_nill_node(node)/* && node->right == previous*/) {
					node = node->right;
				}
				// спускаемся по мапе
				else if (!check_nill_node(m_node->left)) {
					node = iterate_down_right(m_node->left);
				}
				// поднимаемся по мапе
				else {
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
				while (!check_nill_node(node) && node->right == previous) {
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
				while (!check_nill_node(node) && node->left == previous) {
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