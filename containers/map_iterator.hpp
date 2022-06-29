#ifndef __MAP_ITERATOR_HPP__
# define __MAP_ITERATOR_HPP__

# include "iterator.hpp"

namespace ft{

template < class map, bool isConst = false >
class MapIterator
{
	public :
		typedef typename map::key_type				key_type;
		typedef typename map::mapped_type			mapped_type;
		typedef typename map::value_type			value_type;
		typedef typename map::key_compare			key_compare;
		typedef typename map::allocator_type		allocator_type;
		typedef typename map::size_type				size_type;
		typedef typename map::difference_type		difference_type;
		typedef typename map::BST_allocator_type	BST_allocator_type;
		typedef typename map::BST_pointer			BST_pointer;
		typedef typename ft::conditional< isConst, typename map::const_reference, typename map::reference >::type	reference;
		typedef typename ft::conditional< isConst, typename map::const_pointer, typename map::pointer >::type		pointer;

	public:
		MapIterator( void ) : _it(NULL), _dummy_end(NULL), _out(false), _offset(0) {

		};
		MapIterator( BST_pointer TNULL ) : _it(NULL), _dummy_end(NULL), _out(false), _offset(0), _TNULL(TNULL){

		};
		MapIterator( BST_pointer root, BST_pointer end, int flag, BST_pointer TNULL) : _it(root), _dummy_end(end), _out(flag), _offset(flag), _TNULL(TNULL) { 
			if (flag)
			{
				BST_pointer tmp = _it;

				_it = _dummy_end;
				_dummy_end = tmp;
			}
		};
		virtual ~MapIterator( void ) {};
		MapIterator( MapIterator const & src) : _it(NULL), _dummy_end(NULL), _out(false), _offset(0), _TNULL(src._TNULL) {*this = src;};
		MapIterator & operator=( MapIterator const & src ) {
			if (this != &src)
			{
				_it = src._it;
				_dummy_end = src._dummy_end;
				_out = src._out;
				_offset = src._offset;
				_TNULL = src._TNULL;
			}
			return *this;
		};

		operator MapIterator< const map, true>() const {
			if (_offset)
				return MapIterator< const map, true>(_dummy_end, _it, _offset, _TNULL);
			else
				return MapIterator< const map, true>(_it, _dummy_end, _offset, _TNULL);
		};
	
		friend bool	operator==(MapIterator const & lhs, MapIterator const & rhs){
			return (lhs.base() == rhs.base() ? true : false);
		}

		friend bool	operator!=(MapIterator const & lhs, MapIterator const & rhs){
			return (!(lhs == rhs));
		}
		reference 		operator*( void ) { return (this->_it->data); };
		reference 		operator*( void ) const { return (this->_it->data); };
		pointer			operator->( void ) { return (&(this->_it->data)); };
		pointer			operator->( void ) const { return (&(this->_it->data)); };
		MapIterator& 	operator++( void ) {
			if (_out)
			{
				if (this->_offset == -1)
				{
					BST_pointer tmp = _it;	
					_it = _dummy_end;
					_dummy_end = tmp;

					this->_out = false;
					this->_offset = 0;
				}
			}
			else
			{
				BST_pointer tmp_it = this->_it;
				
				if (this->_it->right && this->_it->right != _TNULL)
				{
					tmp_it = tmp_it->right;
					while (tmp_it->left != _TNULL)
					{
						tmp_it = tmp_it->left;
					}
					_it = tmp_it;
				}
				else
				{
					tmp_it = tmp_it->parent;
					while (tmp_it)
					{
						if (!comp(tmp_it->data.first, _it->data.first))
							break;
						tmp_it = tmp_it->parent;
					}
					if (tmp_it)
						this->_it = tmp_it;
					else
					{
						BST_pointer tmp = _it;
						_it = _dummy_end;
						_dummy_end = tmp;

						this->_offset = 1;
						this->_out = true;
					}
				}
			}
			return (*this); 
		};
		MapIterator		operator++( int ) { 
			MapIterator tmp(_it, _dummy_end, _offset, _TNULL); operator++(); return tmp; 
		};
		MapIterator&	operator--( void ) { 
			if (_out)
			{
				if (this->_offset == 1)
				{
					BST_pointer tmp = _it;
					_it = _dummy_end;
					_dummy_end = tmp;

					this->_out = false;
					this->_offset = 0;
				}
			}
			else
			{
				BST_pointer tmp_it = this->_it;

				if (this->_it->left && this->_it->left != _TNULL)
				{
					tmp_it = tmp_it->left;
					while (tmp_it->right && tmp_it->right != _TNULL)
					{
						tmp_it = tmp_it->right;
					}
					_it = tmp_it;
				}
				else
				{
					tmp_it = tmp_it->parent;
					while (tmp_it && tmp_it != _TNULL)
					{
						if (comp(tmp_it->data.first, _it->data.first))
							break;
						tmp_it = tmp_it->parent;
					}
					if (tmp_it)
						this->_it = tmp_it;
					else
					{
						BST_pointer tmp = _it;
						_it = _dummy_end;
						_dummy_end = tmp;

						this->_out = true;
						this->_offset = -1;
					}
				}
			}
			return (*this);
		};

		MapIterator		operator--( int ) { 
			MapIterator tmp(_it, _dummy_end, _offset, _TNULL); operator--(); return tmp;
		};

	private:
		BST_pointer _it;
		BST_pointer	_dummy_end;
		BST_pointer _TNULL;
		key_compare comp;
		bool		_out;
		int			_offset;

	public:
		void		setOut( bool bl) { _out = bl; };
		void		setOffset( int nb) { _offset = nb; };
		BST_pointer	base( void ) const { return _it; };

};

}

#endif