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

#ifndef __included_cc_avltree_h
#define __included_cc_avltree_h

#include <crisscross/deprecate.h>
#include <crisscross/node.h>
#include <crisscross/internal_mem.h>

namespace CrissCross
{
	namespace Data
	{

		//! The current balance status of a node
		typedef enum AVLBalance
		{
			//! The left side of the tree is heaviest.
			LEFTHEAVY,

			//! The tree is well balanced.
			BALANCED,

			//! The right side of the tree is heaviest.
			RIGHTHEAVY
		};

		template <class Key, class Data>
		class AVLNode : public BinaryNode<Key,Data>
		{
		public:
			AVLNode();

			//! The state of this part of the tree's balance.
			/*!
				\sa AVLBalance
			 */
			AVLBalance m_balance;

            //! The left branch of the tree from this node.
			AVLNode *left;

            //! The right branch of the tree from this node.
			AVLNode *right;

            //! The parent node.
			AVLNode *parent;

		};

		template <class Key, class Data>
		class AVLTree
		{
		protected:
			//! The root node.
			AVLNode<Key,Data> *m_root;

			//! The current tree size.
			size_t m_size;

			//! Result of tree operation
			typedef enum Result
			{
				//! None of the subtrees has grown in height, entire tree is still balanced
				OK,

				//! One of the branches has grown/shrunk in height, tree might need rebalancing
				BALANCE,

				//! Error
				INVALID
			};

			//! Rotate tree left
			/*!
				Rotate tree left around the given node
				\param _node                                        Pointer to current node pointer to rotate
			*/
			inline void                                             rotateLeft ( AVLNode<Key,Data> **_node );

			//! Rotate tree right
			/*!
				Rotate tree right around the given node
				\param _node                                        Pointer to current node pointer to rotate
			*/
			inline void                                             rotateRight ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after left side has grown
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has grown in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceLeftGrown ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after right side has grown
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has grown in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceRightGrown ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after left side has shrunk
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has shrunk in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceLeftShrunk ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after right side has shrunk
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has shrunk in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceRightShrunk ( AVLNode<Key,Data> **_node );

			//! Replace node
			/*!
				Replace a node with the highest-ranking item in subtree
				\param _target                                      Pointer to node to be replaced
				\param _subtree                                     Pointer to subtree pointer to search
				\param _result                                      Pointer to result variable to tell caller if further checks are needed
				\return                                             true if node found, false if not
			*/
			inline bool                                             replaceWithHighest ( AVLNode<Key,Data> *_target, AVLNode<Key,Data> **_subtree, Result *_result );

			//! Replace node
			/*!
				Replace a node with the lowest-ranking item in subtree
				\param _target                                      Pointer to node to be replaced
				\param _subtree                                     Pointer to subtree pointer to search
				\param _result                                      Pointer to result variable to tell caller if further checks are needed
				\return                                             true if node found, false if not
			*/
			inline bool                                             replaceWithLowest ( AVLNode<Key,Data> *_target, AVLNode<Key,Data> **_subtree, Result *_result );

			//! Add object
			/*!
				Insert object in tree and rebalance
				\param _parent                                      Pointer to parent node pointer
				\param _node                                        Pointer to current node pointer
				\param _key                                         Key to insert
				\param _data                                        Data to insert
				\return                                             Result of addition (OK if subtree is balanced, BALANCE if tree is heavy on either side)
			*/
			Result                                                  insert ( AVLNode<Key,Data> **_parent, AVLNode<Key,Data> **_node, Key const &_key, Data const &_data );

			//! Remove object
			/*!
				Remove object from tree and rebalance
				\param _node                                        Pointer to current node pointer
				\param _key                                         Identifier of node to remove
				\return                                             Result of removal (OK if subtree is balanced, BALANCE if tree is heavy on either side)
			*/
			Result                                                  erase ( AVLNode<Key,Data> **_node, Key const &_key );

			//! Remove object
			/*!
				Remove object from tree and rebalance, taking the key and data into account
				\param _node                                        Pointer to current node pointer
				\param _key                                         Identifier of node to remove
				\param _data                                         Data identifier of node to remove
				\return                                             Result of removal (OK if subtree is balanced, BALANCE if tree is heavy on either side)
			*/
			Result                                                  erase ( AVLNode<Key,Data> **_node, Key const &_key, Data const &_data );

			//! Find a node in the tree
			/*!
				Get a pointer to a node with the specified key value
				\param _key                                         Identifier of node to remove
				\return                                             Address of the node. If not found, returns NULL.
			*/
			AVLNode<Key,Data>                                      *findNode ( Key const &_key ) const;

			//! Recursively convert the tree's keys into a DArray
			/*!
				\param _darray										Array to insert keys into
				\param _btree										The node being traversed
			*/
            void													RecursiveConvertIndexToDArray ( DArray <Key> *_darray, AVLNode<Key,Data> *_btree ) const;

			//! Recursively convert the tree's data into a DArray
			/*!
				\param _darray										Array to insert data into
				\param _btree										The node being traversed
			*/
            void													RecursiveConvertToDArray ( DArray <Data> *_darray, AVLNode<Key,Data> *_btree ) const;

			//! Recursively find all nodes with the specified key
			/*!
				\param _darray										Array to insert data into
				\param _key											Identifier of nodes to find
				\param _node										The node being traversed
			*/
			void													findRecursive ( DArray<Data> *_array, Key const &_key, AVLNode<Key,Data> *_node ) const;

		public:

			//! The default constructor.
			AVLTree();

			//! The destructor.
			virtual ~AVLTree();

            //! Inserts data into the tree.
            /*!
                \param _key The key of the data.
                \param _data The data to insert.
                \return True on success, false on failure.
             */
			void insert ( Key const &_key, Data const &_data );

			//! Deletes a node from the tree, specified by the node's key.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \return True on success, false on failure
             */
			bool erase ( Key const &_key );

            //! Deletes a node from the tree, specified by the node's key and data.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \param _data The data of the node to delete.
                \return True on success, false on failure.
             */
			bool erase ( Key const &_key, Data const &_data );
			
            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \param _data On return, will contain the data at the node. If not found, _data does not change.
				\return True on success, false on failure.
             */
			bool find ( Key const &_key, Data &_data ) const;

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The data at the node. NULL if not found.
             */
			_CC_DEPRECATE_FUNCTION_N Data find ( Key const &_key ) const;

            //! Finds all instances of the specified key in the tree.
            /*!
                \param _key The key of the node to find.
                \return A DArray containing the data with key _key. MUST be deleted when done!
             */
			DArray<Data> *findAll ( Key const &_key ) const;

            //! Tests whether a key is in the tree or not.
            /*!
                \param _key The key of the node to find.
                \return True if the key is in the tree, false if not.
             */
			bool exists ( Key const &_key ) const;

            //! Empties the tree of all nodes.
            /*!
				Deletes all nodes, but does not free data stored in the nodes.
             */
			inline void empty () { delete m_root; m_root = NULL; };

            //! Indicates the size of the tree.
            /*!
                \return Size of the tree.
             */
			inline size_t size () const { return m_size; };

            //! Change the data at the given node.
            /*!
                \param _key The key of the node to be modified.
                \param _data The data to insert.
                \return True on success, false on failure.
             */
            bool replace ( Key const &_key, Data const &_data );
			
            //! Converts the tree data into a linearized DArray.
            /*!
                \return A DArray containing the data of the tree.
             */
            DArray <Data> *ConvertToDArray () const;

            //! Converts the tree keys into a linearized DArray.
            /*!
                \return A DArray containing the keys in the tree.
             */
            DArray <Key>  *ConvertIndexToDArray () const;

            //! Verifies that a node is valid.
            /*!
                \param _node A node pointer.
                \return True if the node is a valid node, false otherwise.
             */
            inline bool valid ( const AVLNode<Key,Data> *_node ) const
			{ return ( _node != NULL ); };
		};
	}
}

#include <crisscross/avltree.cpp>

#endif
