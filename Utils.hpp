#ifndef UTILS_HPP
# define UTILS_HPP


namespace ft {
	// static class nullptr_t
	// {
	// 	public:
	// 		template<class T>
	// 		operator T*() const { return (0); }

	// 		template<class C, class T>
	// 		operator T C::*() const { return (0); }

	// 	private:
			
	// 		void operator&() const;

	// } u_nullptr = {};

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	struct true_type { } ;
	struct false_type { } ;

template <typename T>
	struct is_integral_res;

template <>
	struct is_integral_res <true_type> {
		static const bool value =	1;
		typedef true_type			type;
} ;

template <>
	struct is_integral_res <false_type> {
		static const bool value =	0;
		typedef false_type			type;
} ;


template <typename T>
	struct is_integral_type : public is_integral_res<false_type> { };

 
template <>
	struct is_integral_type<bool> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<char> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<signed char> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<short int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<long int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<long long int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<unsigned char> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<unsigned short int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<unsigned int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<unsigned long int> : public is_integral_res<true_type> { };

template <>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true_type> { };



template <typename T>
	struct is_integral : public is_integral_type<T> { };


}


#endif
