/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_rbtree_h
#   error "This file shouldn't be compiled directly."
#endif

#include <stdlib.h>

#include <crisscross/compare.h>
#include <crisscross/debug.h>
#include <crisscross/rbtree.h>

namespace CrissCross
{
	namespace Data
	{
		template <class Key, class Data>
			RedBlackTree<Key,Data>::RedBlackTree ()
		{
			rootNode = NULL;
			m_cachedSize = 0;
		}

		template <class Key, class Data>
			RedBlackTree<Key,Data>::~RedBlackTree ()
		{
			killAll ();
		}

		template <class Key, class Data>
			void RedBlackTree<Key,Data>::rotateLeft ( RedBlackNode<Key,Data> * x )
		{
			RedBlackNode<Key,Data> *y = x->right;

			/* establish x->right link */
			x->right = y->left;
			if ( y->left != NULL )
				y->left->parent = x;

			/* establish y->parent link */
			if ( y != NULL )
				y->parent = x->parent;
			if ( x->parent )
			{
				if ( x == x->parent->left )
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			else
			{
				rootNode = y;
			}

			/* link x and y */
			y->left = x;
			if ( x != NULL )
				x->parent = y;
		}

		template <class Key, class Data>
		void RedBlackTree<Key,Data>::rotateRight ( RedBlackNode<Key,Data> * x )
		{
			RedBlackNode<Key,Data> *y = x->left;

			/* establish x->left link */
			x->left = y->right;
			if ( y->right != NULL )
				y->right->parent = x;

			/* establish y->parent link */
			if ( y != NULL )
				y->parent = x->parent;
			if ( x->parent )
			{
				if ( x == x->parent->right )
					x->parent->right = y;
				else
					x->parent->left = y;
			}
			else
			{
				rootNode = y;
			}

			/* link x and y */
			y->right = x;
			if ( x != NULL )
				x->parent = y;
		}

		template <class Key, class Data>
		void RedBlackTree<Key,Data>::insertFixup ( RedBlackNode<Key,Data> * x )
		{
			/* check Red-Black properties */
			while ( x != rootNode && x->parent->color == RED )
			{
				/* we have a violation */
				if ( x->parent == x->parent->parent->left )
				{
					RedBlackNode<Key,Data> *y = x->parent->parent->right;

					if ( y->color == RED )
					{

						/* uncle is RED */
						x->parent->color = BLACK;
						y->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					}
					else
					{

						/* uncle is BLACK */
						if ( x == x->parent->right )
						{
							/* make x a left child */
							x = x->parent;
							rotateLeft ( x );
						}

						/* recolor and rotate */
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						rotateRight ( x->parent->parent );
					}
				}
				else
				{

					/* mirror image of above code */
					RedBlackNode<Key,Data> *y = x->parent->parent->left;

					if ( y && y->color == RED )
					{

						/* uncle is RED */
						x->parent->color = BLACK;
						y->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					}
					else
					{

						/* uncle is BLACK */
						if ( x == x->parent->left )
						{
							x = x->parent;
							rotateRight ( x );
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						rotateLeft ( x->parent->parent );
					}
				}
			}
			rootNode->color = BLACK;
		}

		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::replace ( Key const &key, Data const & rec )
		{
			RedBlackNode<Key,Data> *current;
			current = findNode ( key );
			if ( !valid ( current ) ) return false;
			current->data = rec;
			return true;
		}

		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::insert ( Key const &key, Data const & rec )
		{
			RedBlackNode<Key,Data> *current = NULL, *parent = NULL, *x = NULL;

			/* find future parent */
			current = rootNode;
			while ( current != NULL )
			{
				parent = current;
				current = ( Compare ( key, current->id ) <= 0 ) ?
					current->left : current->right;
			}

			/* setup new node */
			if ( (x = new RedBlackNode<Key,Data>()) == 0 )
			{
				return false;
			}

			x->parent = parent;
			x->left = NULL;
			x->right = NULL;
			x->color = RED;
			x->id = Duplicate ( key );
			x->data = rec;

			/* insert node in tree */
			if ( parent != NULL )
			{
				if ( Compare ( key, parent->id ) <= 0 )
					parent->left = x;
				else
					parent->right = x;
			}
			else
			{
				rootNode = x;
			}

			m_cachedSize++;

			insertFixup ( x );

			return true;
		}

		template <class Key, class Data>
		void RedBlackTree<Key,Data>::deleteFixup ( RedBlackNode<Key,Data> * x )
		{
			if ( !x ) return;
			while ( x != rootNode && x->color == BLACK )
			{
				if ( x == x->parent->left )
				{
					RedBlackNode<Key,Data> *w = x->parent->right;

					if ( w->color == RED )
					{
						w->color = BLACK;
						x->parent->color = RED;
						rotateLeft ( x->parent );
						w = x->parent->right;
					}
					if ( w->left->color == BLACK && w->right->color == BLACK )
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if ( w->right->color == BLACK )
						{
							w->left->color = BLACK;
							w->color = RED;
							rotateRight ( w );
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						rotateLeft ( x->parent );
						x = rootNode;
					}
				}
				else
				{
					RedBlackNode<Key,Data> *w = x->parent->left;

					if ( w->color == RED )
					{
						w->color = BLACK;
						x->parent->color = RED;
						rotateRight ( x->parent );
						w = x->parent->left;
					}
					if ( w->right->color == BLACK && w->left->color == BLACK )
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if ( w->left->color == BLACK )
						{
							w->right->color = BLACK;
							w->color = RED;
							rotateLeft ( w );
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rotateRight ( x->parent );
						x = rootNode;
					}
				}
			}
			x->color = BLACK;
		}

		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::erase ( Key const &key )
		{
			RedBlackNode<Key,Data> *z, *parent;

			//  delete node z from tree

			/* find node in tree */
			z = rootNode;
			parent = 0;

			while ( z != NULL )
			{
				if ( Compare ( key, z->id ) == 0 )
					break;
				else
				{
					parent = z;
					z = ( Compare ( key, z->id ) <= 0 ) ? z->left : z->right;
				}
			}

			if ( z == NULL ) {
				return false;
			}

			return killNode ( z );
		}

		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::erase ( Key const &key, Data const &rec)
		{
			RedBlackNode<Key,Data>        *node = findNode(key);
			return erase ( key, rec, node );
		}
		
		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::erase ( Key const &key, Data const &rec, RedBlackNode<Key,Data> *curnode )
		{
			if ( !valid ( curnode ) ) return false;
			
			bool killed = false;
			
			if ( Compare(curnode->key, key) == 0 && Compare(curnode->data, rec) == 0 )
			{
				killNode ( curnode );
				killed = true;
			}
			
			if ( !killed )
				killed = erase ( key, rec, curnode->left );
				
			if ( !killed )
				killed = erase ( key, rec, curnode->right );
			
			return killed;
		}

		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::killNode ( RedBlackNode<Key,Data> * z )
		{
			RedBlackNode<Key,Data> *x, *y;

			if ( z->left == NULL || z->right == NULL )
			{
				/* y has a NULL node as a child */
				y = z;
			}
			else
			{
				/* find tree successor with a NULL node as a child */
				y = z->right;

				while ( y->left != NULL )
					y = y->left;
			}

			/* x is y's only child */
			if ( y->left != NULL )
				x = y->left;
			else
				x = y->right;

			/* remove y from the parent chain */
			if ( x ) x->parent = y->parent;

			if ( y->parent )
			{
				if ( y == y->parent->left )
					y->parent->left = x;
				else
					y->parent->right = x;
			}
			else
				rootNode = x;

			if ( y != z )
			{
				Dealloc ( z->id );
				z->id = Duplicate ( y->id );
				z->data = y->data;
			} else {
				Dealloc ( y->id );
			}

			if ( y->color == BLACK )
				deleteFixup ( x );

			m_cachedSize--;

			y->left = NULL;
			y->right = NULL;
			delete y;

			return true;
		}

		template <class Key, class Data>
			Data RedBlackTree<Key,Data>::find ( Key const &key ) const
		{
			RedBlackNode<Key,Data> *current = rootNode;

			while ( current != NULL )
			{
				if ( Compare ( key, current->id ) == 0 )
				{
					return current->data;
				}
				else
				{
					current = ( Compare ( key, current->id ) <= 0 ) ?
						current->left : current->right;
				}
			}

			return (Data)0;
		}

		template <class Key, class Data>
			bool RedBlackTree<Key,Data>::find ( Key const &key, Data &_data ) const
		{
			RedBlackNode<Key,Data> *current = rootNode;

			while ( current != NULL )
			{
				if ( Compare ( key, current->id ) == 0 )
				{
					_data = current->data;
					return true;
				}
				else
				{
					current = ( Compare ( key, current->id ) <= 0 ) ?
						current->left : current->right;
				}
			}

			return false;
		}

		template <class Key, class Data>
			RedBlackNode<Key,Data> * RedBlackTree<Key,Data>::findNode ( Key const &key ) const
		{
			RedBlackNode<Key,Data> * current = rootNode;

			while ( current != NULL )
			{
				if ( Compare ( key, current->id ) == 0 )
				{
					return current;
				}
				else
				{
					current = ( Compare ( key, current->id ) <= 0 ) ? current->left : current->right;
				}
			}

			return NULL;
		}

		template <class Key, class Data>
		bool RedBlackTree<Key,Data>::exists ( Key const &_key ) const
		{
			RedBlackNode<Key,Data> *p_current = findNode ( _key );
			if ( !p_current ) return false;
			else              return true;
		}

		template <class Key, class Data>
			void RedBlackTree<Key,Data>::killAll ( RedBlackNode<Key,Data> *rec )
		{
			
			if ( rec == NULL )
			{
				return;
			}

			// First kill our subnodes:
			if ( rec->left != NULL )
				killAll ( rec->left );

			if ( rec->right != NULL )
				killAll ( rec->right );

			if ( rec->parent != NULL )    // We're not root.
			{
				if ( rec->parent->left == rec )
					rec->parent->left = NULL;
				else
					rec->parent->right = NULL;
			}

			Dealloc ( rec->id );
			rec->left = NULL;
			rec->right = NULL;
			delete rec;
		}

		template <class Key, class Data>
			void RedBlackTree<Key,Data>::killAll ()
		{
			killAll ( rootNode );
			rootNode = NULL;
			m_cachedSize = 0;
		}

		template <class Key, class Data>
		DArray<Data> *RedBlackTree<Key,Data>::findAll ( Key const &_key ) const
		{
			RedBlackNode<Key,Data> *p_current = findNode ( _key );
			DArray<Data> *data = new DArray<Data>();
			findRecursive ( data, _key, p_current );
			return data;
		}

		template<class Key, class Data>
		void RedBlackTree<Key,Data>::findRecursive ( DArray<Data> *_array, Key const &_key, RedBlackNode<Key,Data> *_node ) const
		{
			CoreAssert ( _array );
			if ( !_node ) return;
			findRecursive ( _array, _key, _node->left );
			if ( Compare(_node->id, _key) == 0 ) _array->insert ( _node->data );
			findRecursive ( _array, _key, _node->right );
		}

		template <class Key, class Data>
			DArray<Data> *RedBlackTree<Key,Data>::ConvertToDArray () const
		{
			DArray<Data> *darray = new DArray<Data> ( (int)size() );
			RecursiveConvertToDArray ( darray, rootNode );
			return darray;
		}

		template <class Key, class Data>
			DArray<Key> *RedBlackTree<Key,Data>::ConvertIndexToDArray () const
		{
			DArray<Key> *darray = new DArray<Key> ( (int)size () );
			RecursiveConvertIndexToDArray ( darray, rootNode );
			return darray;
		}

		template <class Key, class Data>
			void RedBlackTree<Key,Data>::RecursiveConvertToDArray ( DArray<Data> *darray, RedBlackNode<Key,Data> *btree ) const
		{
			if ( !btree || btree == NULL ) return;
			RecursiveConvertToDArray ( darray, btree->left );
			darray->insert ( btree->data );
			RecursiveConvertToDArray ( darray, btree->right );
		}

		template <class Key, class Data>
			void RedBlackTree<Key,Data>::RecursiveConvertIndexToDArray ( DArray<Key> *darray, RedBlackNode<Key,Data> *btree ) const
		{
			if ( !btree || btree == NULL ) return;
			RecursiveConvertIndexToDArray ( darray, btree->left );
			darray->insert ( btree->id );
			RecursiveConvertIndexToDArray ( darray, btree->right );
		}
	}
}
