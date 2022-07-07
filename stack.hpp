#ifndef __STACK_HPP__
#define __STACK_HPP__

# include "vector.hpp"

namespace ft {
    
    template< typename T, typename Container >
    class stack;

    template< class T, class Container >
    bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
    template< class T, class Container >
    bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
    template< class T, class Container >
    bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
    template< class T, class Container >
    bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
    template< class T, class Container >
    bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
    template< class T, class Container >
    bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

    template< typename T, typename Container = vector<T> >
    class stack {
    public:
        typedef Container                               container_type;
        typedef typename Container::value_type          value_type;
        typedef typename Container::size_type           size_type;
        typedef typename Container::reference           reference;
        typedef typename Container::const_reference     const_reference;

    private:

        container_type container;

    public:
        explicit stack( const Container& cont = Container() ) :
            container(cont) {}

        stack( const stack& other ) :
            container(other.container) {}

        reference top() {
            return container.back();
        }

        const_reference top() const {
            return container.back();
        }

        bool empty() const {
            return container.empty();
        }

        size_type size() const {
            return container.size();
        }

        void push( const value_type& value ) {
            container.insert(container.end(), value);
        }

        void pop() {
            container.pop_back();
        }


        friend bool operator== < T, Container >( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

        friend bool operator!= < T, Container >( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

        friend bool operator< < T, Container >( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

        friend bool operator<= < T, Container >( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

        friend bool operator> < T, Container >( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

        friend bool operator>= < T, Container >( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
        
    };

    template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return lhs.container == rhs.container;
    } 
    template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return lhs.container != rhs.container;
    } 
    template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return lhs.container < rhs.container;
    } 
    template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return lhs.container <= rhs.container;
    } 
    template< class T, class Container >
    bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return lhs.container > rhs.container;
    } 
    template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return lhs.container >= rhs.container;
    }
}

#endif