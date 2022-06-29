#ifndef MAP_HPP
# define MAP_HPP

# include "./rb_tree.hpp"
# include "map_iterator.hpp"

namespace ft {
    template < class K,
        class V,
        class Compare = std::less< K >,
        class Alloc = std::allocator <ft::pair<const K, V> >
        >
    class map {
        public:
        typedef K                                                						key_type;
		typedef V                                               						mapped_type;
		typedef ft::pair< const K, V >                          						value_type;
		typedef Compare                                         						key_compare;
		typedef Alloc                                           						allocator_type;
		typedef typename allocator_type::size_type										size_type;
		typedef typename allocator_type::reference              						reference;
		typedef typename allocator_type::const_reference        						const_reference;
		typedef typename allocator_type::pointer                						pointer;
		typedef typename allocator_type::const_pointer          						const_pointer;
		typedef typename allocator_type::difference_type								difference_type;
		typedef typename ft::MapIterator< map<K, V, Compare, Alloc>, false  >			iterator;
		typedef typename ft::MapIterator< const map<K, V, Compare, Alloc>, true >		const_iterator;
		typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef typename ft::RedBlackTree<K, V, key_compare>::alloc						BST_allocator_type;
		typedef typename ft::RedBlackTree<K, V, key_compare>::node_pointer				BST_pointer;
		typedef typename std::allocator< RedBlackTree< K, V, key_compare > >			Tree_Alloc;
		typedef typename Tree_Alloc::pointer											Tree_pointer;

        private:
		class value_compare
		{
			friend class ft::map<K, V, key_compare, allocator_type>;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
			public:	
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};

		key_compare							_compare;
		allocator_type						_alloc;
		size_type							_size;
		Tree_pointer						_bst;
		Tree_Alloc							_tree;
		BST_allocator_type					_bst_alloc;
		BST_pointer							_dummy_end;

    public:

		void	init_dummy( void )
		{
			_dummy_end = _bst_alloc.allocate(1);
		}

		void	destroy_dummy( void )
		{
			_bst_alloc.deallocate(_dummy_end, 1);
		}

		~map() {
			destroy_dummy();
			_tree.destroy(_bst);
			_tree.deallocate(_bst, 1);
		}

		void	printTree(){if (_bst) { _bst->printTree();}}
        ft::pair<iterator,bool> insert (const value_type& val){
			ft::pair<BST_pointer, bool>	ret;
			ft::pair<iterator, bool> 			convert;

            if (!_bst)
			{
				_bst = _tree.allocate(1);
				_tree.construct(_bst);
			}
				
			ret = _bst->insert(val);

            if (ret.second)	
			{
				convert.second = true;
				convert.first = iterator(ret.first, _dummy_end, 0, _bst->getTnull());
				_size++;
			}
			else
			{
				convert.second = false;
				convert.first = iterator(ret.first, _dummy_end, 0, _bst->getTnull());
			}
			return (convert);
        }
		
		iterator insert (iterator position, const value_type& val)
		{
			static_cast<void> (position);
			ft::pair<iterator, bool> ret = insert(val);
			return (ret.first);
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last){
			for (; first != last; first++)
				insert(*first);
		}
		
		explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _compare(comp), _alloc(alloc), _size(0), _bst(NULL), _dummy_end(NULL) { init_dummy(); }
		
		map (const map& x) : _compare(x._compare), _alloc(x._alloc), _size(x._size), _bst(NULL), _dummy_end(NULL) {
			init_dummy();
			if (x._bst)
				_bst = x._bst->copy_this();
		 }

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :  _compare(comp), _alloc(alloc), _size(0), _bst(NULL), _dummy_end(NULL) { 
			init_dummy();
			insert(first, last);
		}

		map&	operator=(const map& x) {
			if (this != &x)
			{
				_compare = x._compare;
				clear();
				if (x._bst)
					_bst = x._bst->copy_this();
				_size = x._size;
				_bst_alloc = x._bst_alloc;
			}
			return (*this);
		}
		void erase(iterator position)
		{
			if (!_bst)
				return ;
			else {
				if (_bst->erase(position.base()) != 0)
					_size--;
				
			}
		}

		void		erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		size_type	erase(const key_type & k)
		{
			if (!_bst)
				return (0);
			else
			{
				if (_bst->erase(_bst->fbk(k)) == 1)
				{
					_size--;
					return (1);
				}
				return (0);
			}
		}

		bool empty() {
			return (_size == 0);
		}

		void clear( void ) {
			if (_bst)
			{
				_tree.destroy(_bst);
				_tree.deallocate(_bst, 1);
				_bst = NULL;
				_size = 0;
			}
		};

		//ITERATORS//
	public:
		iterator begin( void ) {
			if (_bst)
				return (iterator(_bst->find_start(), _dummy_end, 0, _bst->getTnull()));
			else
				return (iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		const_iterator begin() const {
			if (_bst)
				return (const_iterator(_bst->find_start(), _dummy_end, 0, _bst->getTnull()));
			else
				return (const_iterator(_dummy_end, _dummy_end, 1, nullptr));
		};


		iterator end( void ){
			if (_bst)
				return (iterator(_bst->find_end(), _dummy_end, 1, _bst->getTnull()));
			else
				return (iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		const_iterator end( void ) const {
			if (_bst)
				return (const_iterator(_bst->find_end(), _dummy_end, 1, _bst->getTnull()));
			else
				return (const_iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		iterator find (const key_type& k){
			if (_bst)
			{
				BST_pointer tmp = _bst->fbk(k);
				if (tmp)
					return (iterator(tmp, _dummy_end, 0, _bst->getTnull()));
				else
					return (end());
			}
			else
				return (iterator(_dummy_end, _dummy_end, 1, nullptr));	
		}

		const_iterator find (const key_type& k) const{
			if (_bst)
			{
				BST_pointer tmp = _bst->fbk(k);
				if (tmp)
					return (const_iterator(tmp, _dummy_end, 0, _bst->getTnull()));
				else
					return (end());
			}
			else
				return (const_iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		size_type	count( const key_type& k) const{
			if (_bst)
			{
				BST_pointer tmp = _bst->fbk(k);
				if (tmp)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}

		iterator lower_bound (const key_type& k)
		{
			if (_bst)
			{
				iterator it = begin();
				iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
						break;
				}
				return (it);
			}
			else
				return (iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		const_iterator lower_bound (const key_type& k) const
		{
			if (_bst)
			{
				const_iterator it = begin();
				const_iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
						break;
				}
				return (it);
			}
			else
				return (const_iterator(_dummy_end, _dummy_end, 1, nullptr));
		}
	
		iterator upper_bound (const key_type& k){
			if (_bst)
			{
				iterator it = begin();
				iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
					{
						if (it->first == k)
							it++;
						break;
					}
				}
				return (it);
			}
			else
				return (iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		const_iterator upper_bound (const key_type& k) const{
			if (_bst)
			{
				const_iterator it = begin();
				const_iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
					{
						if (it->first == k)
							it++;
						break;
					}
				}
				return (it);
			}
			else
				return (const_iterator(_dummy_end, _dummy_end, 1, nullptr));
		}

		ft::pair<iterator,iterator>             equal_range (const key_type& k){
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		reverse_iterator rbegin( void ) {
			return reverse_iterator(end()); 
		};
		reverse_iterator rend( void ) {
			return reverse_iterator(begin()); 
		};
		
		const_reverse_iterator rbegin( void ) const { 
			return const_reverse_iterator(end()); 
		};
		const_reverse_iterator rend( void ) const { 
			return const_reverse_iterator(begin()); 
		};

		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

	public:
		size_type		size( void ) const { return _size; }
		size_type		max_size() const { return _bst_alloc.max_size(); }
		allocator_type	get_allocator( void ) const { return _alloc; }
		key_compare		key_comp() const { return _compare; }
		void			swap (map& x) { 
			size_type 		tmp_size = _size;
			Tree_pointer 	tmp_bst = _bst;
			BST_pointer		tmp_dummy = _dummy_end;

			_size = x._size;
			_bst = x._bst;
			_dummy_end = x._dummy_end;

			x._size = tmp_size;
			x._bst = tmp_bst;
			x._dummy_end = tmp_dummy;
		};
		value_compare 	value_comp() const { return value_compare(_compare); };
    };
    template <class Key, class T, class Compare, class Alloc>
bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
	if (lhs.size() == rhs.size())
	{
		typename map<Key,T,Compare,Alloc>::const_iterator it1 = lhs.begin();
		typename map<Key,T,Compare,Alloc>::const_iterator it2 = rhs.begin();

		for (; it1 != lhs.end(); it1++)
		{
			if (*it1 != *it2)
				return false;
			it2++;
		}
		return true;
	}
	else
		return false;
}

template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
	x.swap(y);
}

template <class Key, class T, class Compare, class Alloc>
bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
	return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
	return (!(rhs < lhs));
}
	
template <class Key, class T, class Compare, class Alloc>
bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
	return (!(lhs < rhs));
}
}
#endif