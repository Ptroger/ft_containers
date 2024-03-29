namespace ft{
    template < class Iterator >
    struct iterator_traits{
	    typedef	typename Iterator::value_type			value_type;
	    typedef typename Iterator::pointer           	pointer;
        typedef typename Iterator::const_pointer     	const_pointer;
        typedef typename Iterator::reference         	reference;
        typedef typename Iterator::const_reference   	const_reference;
	    typedef typename Iterator::difference_type		difference_type;
	    typedef typename Iterator::iterator_category	iterator_category;
    };
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2)
    {
    	while (first1!=last1)
    	{
    		if (first2==last2 || *first2 < *first1) 
    			return false;
    		else if (*first1 < *first2)
    			return true;
    		++first1; 
    		++first2;
    	}   
    	return (first2 != last2);
    }

    template <class T1, class T2>
    struct pair{
	    typedef T1 first_type;
	    typedef T2 second_type;

	    first_type  first;
	    second_type second;

	    pair( void ) : first(first_type()), second(second_type()){};
	    pair (const first_type& a, const second_type& b) : first(a), second(b) { };
	    ~pair( void ) { };

	    template<class K, class V> 
	    pair (const pair<K,V>& pr) : first(pr.first), second(pr.second) { };

	    pair & operator=( const pair & pr)
	    {
	    	if (this != &pr)
	    	{
	    		first = pr.first;
	    		second = pr.second;
	    	}
	    	return *this;
	    }
    };

    template < bool B, typename T = void >
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T> 
    { 
      typedef T type; 
    };

    template <class T, T v>
    struct integral_constant {
    	static const T value = v;
    	typedef T value_type;
    	typedef integral_constant<T,v> type;
    	operator T() { return v; }
    };
    typedef integral_constant<bool,false>	false_type;
    typedef integral_constant<bool,true>	true_type;

    template<typename T>
    struct is_integral : public false_type {};

    template<>
    struct is_integral<bool> : public true_type {};

    template<>
    struct is_integral<char> : public true_type {};

    template<>
    struct is_integral<wchar_t> : public true_type{};

    template<>
    struct is_integral<signed char> : public true_type{};

    template<>
    struct is_integral<short int> : public true_type{};

    template<>
    struct is_integral<int> : public true_type{};

    template<>
    struct is_integral<const int> : public true_type{};

    template<>
    struct is_integral<long int> : public true_type{};

    template<>
    struct is_integral<unsigned char> : public true_type{};

    template<>
    struct is_integral<unsigned short int> : public true_type{};

    template<>
    struct is_integral<unsigned int> : public true_type{};

    template<>
    struct is_integral<unsigned long int> : public true_type{};

    template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }
	
template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);  }

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

template <class Pair>
struct pair_traits{
	typedef typename Pair::first_type	key_type;
	typedef typename Pair::second_type	value_type;
};

template <class T1,class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( ft::pair<T1,T2>(x,y) );
}
};