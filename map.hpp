#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "pair.hpp"
# include "map_iterator.hpp"
# include "map_node.hpp"
# include "reverse_iterator.hpp"
# include <iostream>
# include <limits>

namespace ft {
	template <
			typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator< ft::pair<const Key,T> >
			>
	class map {
		public:
			typedef	Key													key_type;
			typedef	T													mapped_type;
			typedef	ft::pair<const Key, T>								value_type;
			typedef	std::size_t											size_type;
			typedef	std::ptrdiff_t										difference_type;
			typedef	Compare												key_compare;
			typedef	Alloc												alloc_type;
			typedef	typename alloc_type::reference						reference;
			typedef	typename alloc_type::const_reference				const_reference;
			typedef typename alloc_type::pointer						pointer;
			typedef typename alloc_type::const_pointer                  const_pointer;

		private:
			typedef map_node<value_type>    node_type;
			typedef node_type*              node_pointer;
			typedef node_type&              node_reference;
			typedef typename alloc_type::template rebind<node_type>::other alloc_node;

		public:
			typedef ft::map_iterator<node_type>							iterator;
			typedef ft::map_iterator<node_type>	        				const_iterator;
			typedef std::reverse_iterator<iterator>						reverse_iterator;
			typedef std::reverse_iterator<const_iterator>				const_reverse_iterator;

		private:
			class value_compare {
					
					public :

						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

					protected :

						Compare				_comp;

					public :

						value_compare(Compare comp) :
							_comp(comp) { }

						~value_compare() { }

						result_type		operator () (const first_argument_type &lhs, const second_argument_type &rhs) const { return _comp(lhs.first, rhs.first); }

			} ;



			// variables
			size_t          _size;
			alloc_type      _allocator;
			alloc_node      _node_allocator;
			key_compare     _key_compare;
			value_compare   _value_compare;
			node_pointer    _nill;
			node_pointer    _root;
			node_pointer    _begin;
			node_pointer    _end;

		public:
			map() :
				_size(0),
				_allocator(),
				_node_allocator(),
				_key_compare(),
				_value_compare(_key_compare),
				_nill(_node_allocator.allocate(1)),
				_root(_nill),
				_begin(_nill),
				_end(_nill) {
					_init_nill();
				}

			explicit map( const Compare& comp,
						const alloc_type& alloc = alloc_type() ) :
				_size(0),
				_allocator(alloc),
				_node_allocator(alloc),
				_key_compare(comp),
				_value_compare(comp),
				_nill(_node_allocator.allocate(1)),
				_root(_nill),
				_begin(_nill),
				_end(_nill) {
					_init_nill();
				}

			template< class InputIt >
			map( InputIt first, InputIt last,
				const Compare& comp = Compare(),
				const alloc_type& alloc = alloc_type() ) :
				_size(0),
				_allocator(alloc),
				_node_allocator(alloc),
				_key_compare(comp),
				_value_compare(comp),
				_nill(_node_allocator.allocate(1)),
				_root(_nill),
				_begin(_nill),
				_end(_nill) {
					_init_nill();
					insert(first, last);
				}

			map( const map& other ) :
				_size(other._size),
				_allocator(other._allocator),
				_node_allocator(other._node_allocator),
				_key_compare(other._key_compare),
				_value_compare(other._value_compare),
				_nill(_node_allocator.allocate(1)),
				_root(_nill),
				_begin(_nill),
				_end(_nill) {
					_init_nill();
					insert(other.begin(), other.end());
				}

			iterator			begin() {
				return (iterator(_begin));
			}
			
			const_iterator		begin() const {
				return (const_iterator(_begin));
			}

			iterator			end() {
				return (iterator(_nill));
			}
			
			const_iterator		end() const {
				return (const_iterator(_nill));
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

				
			size_t			size() const {
				return _size;
			}
			
			size_type	max_size() const {
				return std::min((size_type) std::numeric_limits<difference_type>::max(),
						std::numeric_limits<size_type>::max() / (sizeof(node_type) + sizeof(value_type)));
			}

			ft::pair<iterator, bool> insert( const value_type& value ) {
				if ( _size == 0 ) {
					_root = _init_node(_root, value, _nill->parent);
					_begin = _root;
					_end = _root;
					return ft::make_pair(iterator(_root), true);
				}
				node_pointer leaf = _find_leaf(value);
				node_pointer new_node = leaf;

				if (leaf->left == _nill && _key_compare(value.first, leaf->value->first)) {
					new_node = _init_node(leaf, value, leaf->left);
				} else if (leaf->right == _nill && _key_compare(leaf->value->first, value.first)) {
					new_node = _init_node(leaf, value, leaf->right);
				}
				return ft::make_pair(iterator(new_node), new_node != leaf);
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last ) {
				while (first != last) {
					insert(*first++);
				}
			}

			iterator insert (iterator position, const value_type& value) {
				(void)position;
				return insert( value ).first;
			}

			void erase( iterator pos ) {
				if (*pos == _root) {

				} else if (pos->value->left != _nill && pos->value->right != _nill) {
					
				}
			}

			void erase( iterator first, iterator last );

			size_type erase( const Key& key );

			void print() {
				print_node(_root);
			}

		private:

			void print_node(node_pointer node) {
				if (node != _nill) {
					std::cout << node->value->first << " | " << node->value->second << std::endl;
					print_node(node->left);
					print_node(node->right);
				}
			}

			node_pointer        _find_leaf( const value_type& value ) {
				node_pointer it = _root;

				while (it->value != NULL) {
					if (it->left != _nill && _key_compare(value.first, it->value->first)) {
						it = it->left;
					} else if (it->right != _nill && _key_compare(it->value->first, value.first)) {
						it = it->right;
					} else {
						return it;
					}
				}
				return _nill;
			}

			void    _init_nill() {
				_nill->parent = _nill;
				_nill->left = _nill;
				_nill->right = _nill;
				_nill->value = NULL;
			}

			node_pointer    _init_node( node_pointer parent, const value_type& value, node_pointer &parent_side ) {
				node_pointer new_node = _node_allocator.allocate(1);
				_node_allocator.construct(new_node, node_type());
				new_node->value = _allocator.allocate(1);
				_allocator.construct(new_node->value, value);
				new_node->left = _nill;
				new_node->right = _nill;
				new_node->parent = parent;

				parent_side = new_node;
				++_size;
				if (parent == _begin && parent_side == parent->left) {
					_begin = new_node;
				} else if (parent == _end && parent_side == parent->right) {
					_end = new_node;
				}
				return new_node;
			}
	};
}


#endif