#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "include.hpp"

namespace   ft{

	template<bool B, typename first, typename second>
	struct conditional
	{
		typedef second type;
	};

	template < typename first, typename second >
	struct conditional<true, first, second>
	{
		typedef first	type;
	};

    template < typename container, bool isConst = false >
    class bidir_iterator
    {
        public:
		typedef	typename container::value_type			value_type;
		typedef typename container::difference_type		difference_type;
		typedef std::bidirectional_iterator_tag			iterator_category;
        typedef typename ft::conditional< isConst, typename container::const_reference, typename container::reference >::type	reference;
		typedef typename ft::conditional< isConst, typename container::const_pointer, typename container::pointer >::type		pointer;
        // CONSTRUCTORS -------------------------------------------------------------------------//
        //---------------------------------------------------------------------------------------//
        bidir_iterator( void ) : _it(NULL) {};
		bidir_iterator( pointer vct ) : _it(vct) {};
		virtual ~bidir_iterator( void ) {};
		bidir_iterator ( bidir_iterator const & src) : _it(NULL){
				*this = src;
		};
        //---------------------------------------------------------------------------------------//
        bidir_iterator & operator=(bidir_iterator const & src){
			if (*this == src)
			    return *this;
            _it = src._it;
		};
        pointer			base( void ) const { return _it;};
		friend bool		operator==(bidir_iterator const & lhs, bidir_iterator const & rhs){ return (lhs.base() == rhs.base() ? true : false); }
		friend bool		operator!=(bidir_iterator const & lhs, bidir_iterator const & rhs){ return (!(lhs == rhs)); }
		reference 		operator*( void ) { return (*_it); };
		pointer			operator->( void ) { return (_it); };
		bidir_iterator& operator++( void ) { _it++; return (*this); };
		bidir_iterator	operator++( int ) { bidir_iterator tmp(_it); _it++; return tmp; };
		bidir_iterator&	operator--( void ) { _it--; return (*this); };
		bidir_iterator	operator--( int ) { bidir_iterator tmp(_it); _it--; return tmp; };

        protected:
		pointer _it;
    };
    template < typename container, bool isConst = false >
    class RandomAccessIterator : public bidir_iterator< container, isConst >
    {
    	public:
    		typedef bidir_iterator< container, isConst >			_bidir_iterator;

    		using typename _bidir_iterator::value_type;
    		using typename _bidir_iterator::pointer;
    		using typename _bidir_iterator::reference;
    		using typename _bidir_iterator::difference_type;
    		typedef std::random_access_iterator_tag		iterator_category;

    		RandomAccessIterator( void ) : _bidir_iterator() {};
    		RandomAccessIterator( pointer vct ) : _bidir_iterator(vct) {};
    		virtual ~RandomAccessIterator( void ) {};

    		RandomAccessIterator ( RandomAccessIterator const & src) : _bidir_iterator(){
    				*this = src;
    		};

    		RandomAccessIterator & operator=(RandomAccessIterator const & src){
    			if (*this != src)
    				_bidir_iterator::_it = src._it;
    			return *this;
    		};

    		operator RandomAccessIterator< const container, true>() const { return RandomAccessIterator< const container, true>(this->_it); };

    		//BIDIR OVERLOADS
    		RandomAccessIterator& 	operator++( void ) { _bidir_iterator::_it++; return (*this); };
    		RandomAccessIterator	operator++( int ) { RandomAccessIterator tmp(_bidir_iterator::_it); _bidir_iterator::_it++; return tmp; };
    		RandomAccessIterator&	operator--( void ) { _bidir_iterator::_it--; return (*this); };
    		RandomAccessIterator	operator--( int ) { RandomAccessIterator tmp(_bidir_iterator::_it); _bidir_iterator::_it--; return tmp; };

    		//OPERATOR OVERLOAD
    		RandomAccessIterator 		operator+(difference_type n) const { return RandomAccessIterator((_bidir_iterator::_it) + n); };
    		RandomAccessIterator		operator-(difference_type n) const { return RandomAccessIterator((_bidir_iterator::_it) - n); };
    		friend RandomAccessIterator	operator+(difference_type n, RandomAccessIterator it) { return RandomAccessIterator(n + (it._it)); };
    		difference_type				operator-(RandomAccessIterator const & it) const { return ((_bidir_iterator::_it - it._it)); };
    		friend bool 				operator<(RandomAccessIterator const & lhs, RandomAccessIterator const & rhs) { return (lhs._it < rhs._it); };
    		friend bool 				operator>(RandomAccessIterator const & lhs, RandomAccessIterator const & rhs) { return (lhs._it > rhs._it); };
    		friend bool 				operator<=(RandomAccessIterator const & lhs, RandomAccessIterator const & rhs) { return (lhs._it <= rhs._it); };
    		friend bool 				operator>=(RandomAccessIterator const & lhs, RandomAccessIterator const & rhs) { return (lhs._it >= rhs._it); };
    		RandomAccessIterator&		operator+=(difference_type n) { _bidir_iterator::_it = _bidir_iterator::_it + n; return (*this); };
    		RandomAccessIterator&		operator-=(difference_type n) { _bidir_iterator::_it = _bidir_iterator::_it - n; return (*this); };
    		reference					operator[](difference_type n) { return (*(_bidir_iterator::_it + n)); }
    		reference					operator[](difference_type n) const { return (*(_bidir_iterator::_it + n)); }
    };

    template < class Iterator >
    class reverse_iterator{	
    
    	public:
    		typedef typename Iterator::value_type		value_type;
    		typedef typename Iterator::pointer			pointer;
    		typedef typename Iterator::reference		reference;
    		typedef typename Iterator::difference_type	difference_type;


    	private:
    		Iterator _it;
    
    	public:
    		reverse_iterator( void ) {};
    		virtual ~reverse_iterator( void ) {};
    		explicit reverse_iterator(Iterator it) : _it(it) {};
    
    		template <typename Snd_Ite>
    		reverse_iterator( reverse_iterator<Snd_Ite> const & cpy){
    			*this = cpy;
    		}

    		template <typename Snd_Ite>
    		reverse_iterator & operator=( reverse_iterator<Snd_Ite> const & cpy)
    		{
    			if (*this != cpy)
    				_it = cpy.base();
    			return *this;
    		}
    		reference			operator*( void ) const { 
    			Iterator tmp = _it;
    			return (*(--tmp));
    		};
    		reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_it - n); };
    		reverse_iterator &	operator++( void ) { _it--; return (*this); };
    		reverse_iterator	operator++( int ) { reverse_iterator tmp(*this); _it--; return tmp; };
    		reverse_iterator & 	operator+= (difference_type n) { _it -= n ; return (*this);};
    		reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_it + n); };
    		reverse_iterator &	operator--( void ) { _it++; return (*this); };
    		reverse_iterator	operator--( int ) { reverse_iterator tmp(*this); _it++; return tmp; };
    		reverse_iterator & 	operator-= (difference_type n) { _it += n ; return (*this);};
    		pointer				operator->( void ) { return (&(operator*())); };
    		pointer				operator->( void ) const { return (&(operator*())); };
    		reference 			operator[] (difference_type n) const {return (_it[-n - 1]); };

    	public:
    		Iterator base( void ) const {return _it;}

        };
    template <class Ite1, class Ite2>
    bool	operator==(reverse_iterator<Ite1> const & lhs, reverse_iterator<Ite2> const & rhs) { return (lhs.base() == rhs.base() ? true : false); }

    template <class Ite1, class Ite2>
    bool	operator!=(reverse_iterator<Ite1> const & lhs, reverse_iterator<Ite2> const & rhs) { return (!(lhs == rhs)); }

    //START
    template <class Ite1, class Ite2>
    bool	operator<(reverse_iterator<Ite1> const & lhs, reverse_iterator<Ite2> const & rhs) { return (lhs.base() > rhs.base()); }

    template <class Ite1, class Ite2>
    bool	operator<=(reverse_iterator<Ite1> const & lhs, reverse_iterator<Ite2> const & rhs) { return (lhs.base() >= rhs.base()); }

    template <class Ite1, class Ite2>
    bool	operator>(reverse_iterator<Ite1> const & lhs, reverse_iterator<Ite2> const & rhs) { return (lhs.base() < rhs.base()); }

    template <class Ite1, class Ite2>
    bool	operator>=(reverse_iterator<Ite1> const & lhs, reverse_iterator<Ite2> const & rhs) { return (lhs.base() <= rhs.base()); }


    template < class Iterator >
    reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rhs ) { return reverse_iterator<Iterator>(rhs + n); }

    template < class Iterator >
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (rhs.base() - lhs.base()); }

    template < class Ite1, class Ite2 >
    typename reverse_iterator<Ite1>::difference_type operator-(const reverse_iterator<Ite1>& lhs, const reverse_iterator<Ite2>& rhs) { return ((lhs.base() - rhs.base()) * - 1) ; }

    
}
#endif