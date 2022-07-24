#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "reverse_iterator.hpp"

namespace ft {
	template <
			typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator<T>
			>
    class map {
        public:
            typedef	Key													key_type;
			typedef	T													mapped_type;
			typedef	std::pair<const Key, T>								value_type;
			typedef	std::size_t											size_type;
			typedef	std::ptrdiff_t										difference_type;
			typedef	Compare												key_compare;
			typedef	Alloc												allocator_type;
			typedef	value_type&											reference;
			typedef	const value_type&									const_reference;
			typedef Alloc::pointer										pointer;
			typedef Alloc::const_pointer                                const_pointer;
			
			typedef ft::map_iterator<pointer>							iterator;
			typedef ft::map_iterator<const_pointer>	                   	const_iterator;
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

        public:
            map() {}

            explicit map( const Compare& comp,
                        const Allocator& alloc = Allocator() ) {}

            template< class InputIt >
            map( InputIt first, InputIt last,
                const Compare& comp = Compare(),
                const Allocator& alloc = Allocator() ) {}

            map( const map& other ) {}

            std::pair<iterator, bool> insert( const value_type& value );

            template< class InputIt >
            void insert( InputIt first, InputIt last );
    };
}


#endif