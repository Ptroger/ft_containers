#ifndef RB_TREE_HPP
# define RB_TREE_HPP
# include "include.hpp"
# include "utils.hpp"
# define RED 1
# define BLACK 0

namespace ft{
    template <class pair_type>
    struct Node {
        pair_type       data;
        Node            *left;
        Node            *right;
        Node            *parent;
        int             color;
        Node(pair_type pair) : data(pair){}
        Node() {
            data.second = -1;
            color = BLACK;
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        
    };

    template <class K, class V, class Compare, typename A = std::allocator< Node< ft::pair< const K, V> > > >
    class RedBlackTree {

        public:
            typedef  A                                                          alloc;
            typedef  Compare                                                    key_compare;
		    typedef  ft::pair< const K, V >                          			pair_type;
            typedef  typename ft::pair_traits<pair_type>::value_type            value_type;
            typedef  typename ft::pair_traits<pair_type>::key_type              key_type;
            typedef  typename alloc::pointer                                    node_pointer;
            typedef  typename std::allocator< RedBlackTree< K, V, key_compare > >	allocator_type;
	        typedef  typename allocator_type::pointer							pointer;
	        typedef  typename allocator_type::const_pointer						const_pointer;
	        typedef  typename allocator_type::reference							reference;
	        typedef  typename allocator_type::const_reference					const_reference;
	        typedef  typename allocator_type::difference_type					difference_type;


        private:
            key_compare                 _compare;
            node_pointer                _root;
            node_pointer                _TNULL;
            alloc                       _alloc;
            allocator_type              _tree;

        public:

            node_pointer    fs(node_pointer node) const
            {
                if (node->left && node->left != _TNULL)
                    return (fs(node->left));
                return(node);
            }

            node_pointer    fe(node_pointer node) const
            {
                if (node->right && node->right != _TNULL)
                    return (fs(node->right));
                return(node);
            }
            node_pointer	find_start( void ) const
	        {
                return (fs(_root));
	        }

            node_pointer    find_end(void) const
            {
                return (fe(_root));
            }

            node_pointer    find_by_key(K key, node_pointer node) const
            {
                if (_compare(key, node->data.first))
		        {
		        	if (node->left && node->left != _TNULL)
		        		return (find_by_key(key, node->left));
		        	else
		        		return NULL;
		        }
		        else
		        {
		        	if (key == node->data.first)
		        		return node;
		        	else if (node->right && node->right != _TNULL)
		        		return (find_by_key(key, node->right));
		        	else
		        		return NULL;
		        }
            }
            node_pointer    fbk(K key) const
            {
                return (find_by_key(key, _root));
            }

            size_t    erase(node_pointer node)
            {
                if (node && node != _TNULL)
                    return (deleteNode(node->data.first));
                return (0);
            }
            node_pointer    minimum(node_pointer node) {
                while (node->left != _TNULL)
                    node = node->left;
                return (node);
            }

            node_pointer    maximum(node_pointer node) {
                while (node->right != _TNULL)
                    node = node->right;
                return (node);
            }

            pointer	copy_this( void ) const
	        {
	        	pointer tmp;
	        	tmp = _tree.allocate(1);
	        	_tree.construct(tmp, *this);
	        	return tmp;
	        }

            void    initializeNULLNode(node_pointer nodd, node_pointer parent)
            {
                Node< ft::pair< const K, V> > Node;
                _alloc.construct(nodd, Node);
            };

            // PREORDER
            void    preOrderHelper(node_pointer node) {
                if (node != _TNULL) {
                    std::cout << node->data << " ";
                    preOrderHelper(node->left);
                    preOrderHelper(node->right);
                }
            }

            //INORDER
            void    inOrderHelper(node_pointer node) {
                if (node != _TNULL) {
                    inOrderHelper(node->left);
                    std::cout << node->data << " ";
                    inOrderHelper(node->right);
                }
            }

            //POSTORDER
            void    postOrderHelper(node_pointer node) {
                if (node != _TNULL) {
                     if (node != _TNULL) {
                         postOrderHelper(node->left);
                         postOrderHelper(node->right);
                         std::cout << node->data << " ";
                     }
                }
            }

            node_pointer    searchTreeHelper(node_pointer node, int key)
            {
                if (node == _TNULL || key == node->data) {
                    return (node);
                }
                if (_compare(key, node->data)) {
                    return (searchTreeHelper(node->left, key));
                }
                return (searchTreeHelper(node->right, key));
            }

            void rightRotate(node_pointer x) {
                node_pointer y = x->left;
                x->left = y->right;
                if (y->right != _TNULL) {
                  y->right->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == NULL) {
                  this->_root = y;
                } else if (x == x->parent->right) {
                  x->parent->right = y;
                } else {
                  x->parent->left = y;
                }
                y->right = x;
                x->parent = y;
            }

            void leftRotate(node_pointer x) {
                node_pointer y = x->right;
                x->right = y->left;
                if (y->left != _TNULL) {
                  y->left->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == NULL) {
                  this->_root = y;
                } else if (x == x->parent->left) {
                  x->parent->left = y;
                } else {
                  x->parent->right = y;
                }
                y->left = x;
                x->parent = y;
            }

            void    insertFix(node_pointer node)
            {
                node_pointer    uncle;
                while (node->parent->color == RED) {
                    if (node->parent == node->parent->parent->right) {
                        uncle = node->parent->parent->left;
                        if (uncle->color == RED) {
                            uncle->color = BLACK;
                            node->parent->color = BLACK;
                            node->parent->parent->color = RED;
                            node = node->parent->parent;
                        }
                        else {
                            if (node == node->parent->left) {
                                node = node->parent;
                                rightRotate(node);
                            }
                            node->parent->color = BLACK;
                            node->parent->parent->color = RED;
                            leftRotate(node->parent->parent);
                        }
                    }
                    else {
                        uncle = node->parent->parent->right;

                        if (uncle->color == RED) {
                            uncle->color = BLACK;
                            node->parent->color = BLACK;
                            node->parent->parent->color = RED;
                            node = node->parent->parent;
                        }
                        else {
                            if (node == node->parent->right) {
                                node = node->parent;
                                leftRotate(node);
                            }
                            node->parent->color = BLACK;
                            node->parent->parent->color = RED;
                            rightRotate(node->parent->parent);
                        }
                    }
                    if (node == _root)
                        break ;
                }
                _root->color = BLACK;
            }

            ft::pair<node_pointer, bool>    insert(pair_type elem) {

                ft::pair<node_pointer, bool> ret;
                node_pointer    newNode;
                node_pointer    x;
                node_pointer    y;

                y = NULL;
                x = this->_root;

                newNode = _alloc.allocate(1);
                _alloc.construct(newNode, Node<pair_type>(elem));
                newNode->right = _TNULL;
                newNode->left = _TNULL;
                newNode->color = RED;

                while (x != _TNULL) {
                    y = x;
                    if (_compare(newNode->data.first, x->data.first)) {
                        x = x->left;
                    }
                    else if (newNode->data.first == x->data.first) {
                        ret.second = false;
                        ret.first = x;
                        return (ret);
                    }
                    else {
                       x = x->right;
                    }
                }

                ret.first = newNode;
                ret.second = true;
                newNode->parent = y;
                if (y == NULL) {
                    _root = newNode;
                }
                else if (_compare(newNode->data.first, y->data.first))
                    y->left = newNode;
                else
                    y->right = newNode;
                if (newNode->parent == NULL) {
                    newNode->color = BLACK;
                    return (ret);
                }
                if (newNode->parent->parent == NULL)
                    return (ret);
                insertFix(newNode);
                return (ret);
            }

            void rbTransplant(node_pointer u, node_pointer v) {
                if (u->parent == NULL)
                    _root = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;
                v->parent = u->parent;
            }

            void deleteFix(node_pointer x) {
                node_pointer s;
                while (x != _root && x->color == BLACK) {
                    if (x == x->parent->left) {
                        s = x->parent->right;
                        if (s->color == RED) {
                            s->color = BLACK;
                            x->parent->color = RED;
                            leftRotate(x->parent);
                            s = x->parent->right;
                        }

                        if (s->left->color == BLACK && s->right->color == BLACK) {
                            s->color = RED;
                            x = x->parent;
                        } else {
                            if (s->right->color == BLACK) {
                                s->left->color = BLACK;
                                s->color = RED;
                                rightRotate(s);
                                s = x->parent->right;
                            }

                            s->color = x->parent->color;
                            x->parent->color = BLACK;
                            s->right->color = BLACK;
                            leftRotate(x->parent);
                            x = _root;
                        }
                    } else {
                        s = x->parent->left;
                        if (s->color == RED) {
                            s->color = BLACK;
                            x->parent->color = RED;
                            rightRotate(x->parent);
                            s = x->parent->left;
                        }
                        if (s->right->color == BLACK && s->right->color == BLACK) {
                            s->color = RED;
                            x = x->parent;
                        } else {
                            if (s->left->color == BLACK) {
                              s->right->color = BLACK;
                              s->color = RED;
                              leftRotate(s);
                              s = x->parent->left;
                            }
                            s->color = x->parent->color;
                            x->parent->color = BLACK;
                            s->left->color = BLACK;
                            rightRotate(x->parent);
                            x = _root;
                        }
                    }
                }
                x->color = BLACK;
            }

            size_t deleteNode(K key)
            {
                node_pointer    z = _TNULL;
                node_pointer    i = _root;
                node_pointer    x, y;
                while (i != _TNULL) {
                    if (i->data.first == key)
                        z = i;
                    if (_compare(i->data.first, key))
                        i = i->right;
                    else
                        i = i->left;
                }
                if (z == _TNULL)
                    return (0);

                y = z;
                int y_oc = y->color;
                if (z->left == _TNULL) {
                    x = z->right;
                    rbTransplant(z, z->right);
                } else if (z->right == _TNULL) {
                    x = z->left;
                    rbTransplant(z, z->left);
                } else {
                    y = minimum(z->right);
                    y_oc = y->color;
                    x = y->right;
                    if (y->parent == z) {
                            x->parent = y;
                    } else {
                        rbTransplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }

                    rbTransplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }
                _alloc.destroy(z);
                _alloc.deallocate(z, 1);
                return (1);
            }        

            void printHelper(node_pointer root, std::string indent, bool last) {
                if (root != _TNULL) {
                    std::cout << indent;
                    if (last) {
                        std::cout << "R----";
                        indent += "   ";
                    }
                    else {
                        std::cout << "L----";
                        indent += "|  ";
                    }
                }
                std::string sColor = root->color ? "RED" : "BLACK";
                std::cout << root->data.first << " --- " << root->data.second << "(" << sColor << ")" << std::endl;
                if (root->left && root->left != _TNULL)
                    printHelper(root->left, indent, false);
                if (root->right && root->right != _TNULL)
                    printHelper(root->right, indent, true);
            }

            void printTree() {
                if (_root) {
                    printHelper(this->_root, "", true);
                }
            }

            node_pointer    getTnull() const 
            {
                return (_TNULL);
            }

            void    swap(RedBlackTree& x) {
                node_pointer    tmp;
                node_pointer    tnull;

                tmp = _root;
                tnull = _TNULL;

                _root = x._root;
                _TNULL = x._TNULL;

                x._root = tmp;
                x._TNULL = tnull;
            }

            void    dest(node_pointer node) {
                if (node->left && node->left != _TNULL)
                    dest(node->left);
                if (node->right && node->right != _TNULL)
                    dest(node->right);
                _alloc.destroy(node);
                _alloc.deallocate(node, 1);
            }

            void    destroy() {
                if (_root != _TNULL) {
                    dest(_root);
                    _root = _TNULL;
                    }
            }

        public:
            const RedBlackTree&	operator=(const RedBlackTree& x) const{
                return (x);
            }

            explicit RedBlackTree() : _alloc(alloc()) {
                _TNULL = _alloc.allocate(1);
                initializeNULLNode(_TNULL, NULL);
                _root = _TNULL;
            };

            RedBlackTree( RedBlackTree<K, V, Compare> const &src) : _root(src._root), _TNULL(src._TNULL), _alloc(src._alloc) {};
            ~RedBlackTree() {
                destroy();
                _alloc.destroy(_TNULL);
                _alloc.deallocate(_TNULL, 1);
            };
    };
}

#endif