#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "pair.hpp"
# include "map_iterator.hpp"
# include "map_node.hpp"
# include "reverse_iterator.hpp"
# include "compare_utils.hpp"
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
			typedef map_node<value_type>    		node_type;
			typedef map_node<const value_type>   	node_const_type;
			typedef node_type*              		node_pointer;
			typedef node_type&              		node_reference;
			typedef typename alloc_type::template rebind<node_type>::other alloc_node;

		public:
			typedef ft::map_iterator<value_type>							iterator;
			typedef ft::map_iterator_const<value_type>	        	const_iterator;
			typedef ft::reverseIterator<iterator>						reverse_iterator;
			typedef ft::reverseIterator<const_iterator>					const_reverse_iterator;

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
				_size(0),
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

			~map() {
				clear();
				_allocator.deallocate(_nill->value, 1);
				_node_allocator.deallocate(_nill, 1);
			}

			mapped_type		&operator [] (const key_type &key) {
				return insert(ft::make_pair(key, mapped_type())).first->second;
			}

			map		&operator = (const map &other) {
				if (this == &other)
					return *this;
				clear();
				insert(other.begin(), other.end());
				return *this;
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
			
			ft::pair<iterator,iterator> equal_range( const Key& key ) {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound( const Key& key ) {
				node_pointer	node = _find_leaf(key);
				node_pointer	result;

				if (node != _nill && node->value->first >= key) {
					result = node;
				} else if (node != _nill && node->right != _nill) {
					result = node->right;
				} else {
					return end();
				}
				return iterator(result);
			}
			
			const_iterator lower_bound( const Key& key ) const {
				node_pointer	node = _find_leaf(key);
				node_pointer	result;

				if (node != _nill && node->value->first >= key) {
					result = node;
				} else if (node != _nill && node->right != _nill) {
					result = node->right;
				} else {
					return end();
				}
				return const_iterator(result);
			}
			
			iterator upper_bound( const Key& key ) {
				node_pointer	node = _find_leaf(key);
				node_pointer	result;

				if (node != _nill && node->value->first > key) {
					result = node;
				} else if (node != _nill && node->right != _nill) {
					result = node->right;
				} else {
					return end();
				}
				return iterator(result);
			}
			
			const_iterator upper_bound( const Key& key ) const {
				node_pointer	node = _find_leaf(key);
				node_pointer	result;

				if (node != _nill && node->value->first > key) {
					result = node;
				} else if (node != _nill && node->right != _nill) {
					result = node->right;
				} else {
					return end();
				}
				return const_iterator(result);
			}

			size_t			size() const {
				return _size;
			}
			
			size_type	max_size() const {
				return std::min((size_type) std::numeric_limits<difference_type>::max(),
						std::numeric_limits<size_type>::max() / (sizeof(node_type) + sizeof(value_type)));
			}

			bool			empty() const {
				return _size == 0;
			}

			key_compare 	key_comp() const {
				return _key_compare;
			}

			value_compare 	value_comp() const {
				return _value_compare;
			}

			void clear() {
				erase(begin(), end());
			}

			void swap( map& other ) {
				std::swap(_size, other._size);
				std::swap(_allocator, other._allocator);
				std::swap(_node_allocator, other._node_allocator);
				std::swap(_key_compare, other._key_compare);
				std::swap(_value_compare, other._value_compare);
				std::swap(_nill, other._nill);
				std::swap(_root, other._root);
				std::swap(_begin, other._begin);
				std::swap(_end, other._end);
			}

			size_type count( const Key& key ) const {
				node_pointer	node = _find_leaf(key);

				if (node != _nill && node->value->first == key) {
					return 1;
				} else {
					return 0;
				}
			}

			iterator find( const Key& key ) {
				node_pointer	node = _find_leaf(key);

				if (node != _nill && node->value->first == key) {
					return iterator(node);
				} else {
					return end();
				}
			}

			const_iterator find( const Key& key ) const {
				node_pointer	node = _find_leaf(key);

				if (node != _nill && node->value->first == key) {
					return const_iterator(node);
				} else {
					return end();
				}
			}

			ft::pair<iterator, bool> insert( const value_type& value ) {
				if ( _size == 0 ) {
					_root = _init_node(_root, value, _nill->parent);
					_begin = _root;
					_end = _root;
					return ft::make_pair(iterator(_root), true);
				}
				node_pointer leaf = _find_leaf(value.first);
				node_pointer new_node = leaf;

				if (leaf->left == _nill && _key_compare(value.first, leaf->value->first)) {
					new_node = _init_node(leaf, value, leaf->left);
				} else if (leaf->right == _nill && _key_compare(leaf->value->first, value.first)) {
					new_node = _init_node(leaf, value, leaf->right);
				}
				_recalculate_rben();
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
				if (empty()) {
					return;
				}

				node_pointer	node_to_delete = pos.base();

				 if (node_to_delete->left != _nill && node_to_delete->right == _nill) {
					change_node_parent(node_to_delete, node_to_delete->left);
				} else {
					change_node_parent(node_to_delete, node_to_delete->right);
					node_pointer right_branch_left_leaf = node_to_delete->right;
					while (right_branch_left_leaf->left != _nill) {
						right_branch_left_leaf = right_branch_left_leaf->left;
					}
					right_branch_left_leaf->left = node_to_delete->left;
					node_to_delete->left->parent = right_branch_left_leaf;
				}

				_destroy_node(node_to_delete);
				
				_recalculate_rben();
			}

			void erase( iterator first, iterator last ) {
				while (first != last) {
					erase(first++);
				}
			}

			size_type erase( const Key& key ) {
				node_pointer node_to_delete = _find_leaf(key);

				if (node_to_delete != _nill && node_to_delete->value->first == key) {
					erase(iterator(node_to_delete));
					return 1;
				}
				return 0;
			}

		private:

			void			change_node_parent(node_pointer node_to_delete, node_pointer node_change) {
				node_pointer node_parent = node_to_delete->parent;

				if (node_to_delete == _root) {
					_root = node_change;
					node_change->parent = _nill;
				}
				if (node_parent == _nill) {
					return ;
				}
				if (node_parent->left == node_to_delete) {
					node_parent->left = node_change;
				} else if (node_parent->right == node_to_delete) {
					node_parent->right = node_change;
				}
				node_change->parent = node_parent;

			}

			node_pointer        _find_leaf( const key_type& key ) const {
				node_pointer it = _root;

				while (it->value != NULL) {
					if (it->left != _nill && _key_compare(key, it->value->first)) {
						it = it->left;
					} else if (it->right != _nill && _key_compare(it->value->first, key)) {
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

			void		_destroy_node(node_pointer node_to_delete) {
				--_size;
				_allocator.destroy(node_to_delete->value);
				_node_allocator.destroy(node_to_delete);
				_allocator.deallocate(node_to_delete->value, 1);
				_node_allocator.deallocate(node_to_delete, 1);
			}

			void		_recalculate_rben() {
				_begin = _root;
				while (_root != _nill && _begin->left != _nill) {
					_begin = _begin->left;
				}
				_end = _root;
				while (_root != _nill && _end->right != _nill) {
					_end = _end->right;
				}
				_nill->parent = _root;
				_nill->left = _begin;
				_nill->right = _end;
			}
	};
}


	template <typename K, typename T>
	bool    operator == (const ft::map<K,T> &lhs, const ft::map<K,T> &rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename K, typename T>
	bool    operator != (const ft::map<K,T> &lhs, const ft::map<K,T> &rhs) {
		return !(lhs == rhs);
	}

	template <typename K, typename T>
	bool    operator < (const ft::map<K,T> &lhs, const ft::map<K,T> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename K, typename T>
	bool    operator > (const ft::map<K,T> &lhs, const ft::map<K,T> &rhs) {
		return rhs < lhs;
	}

	template <typename K, typename T>
	bool    operator <= (const ft::map<K,T> &lhs, const ft::map<K,T> &rhs) {
		return !(lhs > rhs);
	}

	template <typename K, typename T>
	bool    operator >= (const ft::map<K,T> &lhs, const ft::map<K,T> &rhs) {
		return !(lhs < rhs);
	}

	template <typename K, typename T, typename Comp, typename Alloc>
	void	swap( ft::map<K,T,Comp,Alloc>& lhs, ft::map<K,T,Comp,Alloc>& rhs) {
		ft::map<K,T,Comp,Alloc>	buf = lhs;
		lhs = rhs;
		rhs = buf;
	}


#endif