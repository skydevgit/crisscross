/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_rbtree_cpp
#define __included_rbtree_cpp

#include <stdlib.h>

#include <crisscross/core_debug.h>
#include <crisscross/rbtree.h>

using namespace CrissCross::Data;

template <class Key, class Data>
    RedBlackTree<Key,Data>::RedBlackTree ()
{
    NULL_NODE = new BinaryNode<Key,Data> ();
    NULL_NODE->color = BLACK;
    rootNode = NULL_NODE;
}

template <class Key, class Data>
    RedBlackTree<Key,Data>::~RedBlackTree ()
{
    killAll ();
    delete NULL_NODE;
}

template <class Key, class Data>
    void RedBlackTree<Key,Data>::rotateLeft ( BinaryNode<Key,Data> * x )
{
    BinaryNode<Key,Data> *y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if ( y->left != NULL_NODE )
        y->left->parent = x;

    /* establish y->parent link */
    if ( y != NULL_NODE )
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
    if ( x != NULL_NODE )
        x->parent = y;
}

template <class Key, class Data>
void RedBlackTree<Key,Data>::rotateRight ( BinaryNode<Key,Data> * x )
{
    BinaryNode<Key,Data> *y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if ( y->right != NULL_NODE )
        y->right->parent = x;

    /* establish y->parent link */
    if ( y != NULL_NODE )
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
    if ( x != NULL_NODE )
        x->parent = y;
}

template <class Key, class Data>
void RedBlackTree<Key,Data>::insertFixup ( BinaryNode<Key,Data> * x )
{
    /* check Red-Black properties */
    while ( x != rootNode && x->parent->color == RED )
    {
        /* we have a violation */
        if ( x->parent == x->parent->parent->left )
        {
            BinaryNode<Key,Data> *y = x->parent->parent->right;

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
            BinaryNode<Key,Data> *y = x->parent->parent->left;

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
    statusEnum RedBlackTree<Key,Data>::insert ( const Key &key, const Data & rec )
{
    BinaryNode<Key,Data> *current = NULL_NODE, *parent = NULL, *x = NULL_NODE;

    /* find future parent */
    current = rootNode;
    while ( current != NULL_NODE )
    {
        parent = current;
        current = ( key <= current->id ) ?
            current->left : current->right;
    }

    /* setup new node */
    if ( (x = new BinaryNode<Key,Data>()) == 0 )
        return STATUS_MEM_EXHAUSTED;

    x->parent = parent;
    x->left = NULL_NODE;
    x->right = NULL_NODE;
    x->color = RED;
    x->id = key;
    x->data = rec;
    x->beenThere = NODE_ITSELF_VISITED;

    /* insert node in tree */
    if ( parent != NULL )
    {
        if ( key <= parent->id )
            parent->left = x;
        else
            parent->right = x;
    }
    else
    {
        rootNode = x;
    }

    insertFixup ( x );

    return STATUS_OK;
}

template <class Key, class Data>
void RedBlackTree<Key,Data>::deleteFixup ( BinaryNode<Key,Data> * x )
{
    while ( x != rootNode && x->color == BLACK )
    {
        if ( x == x->parent->left )
        {
            BinaryNode<Key,Data> *w = x->parent->right;

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
            BinaryNode<Key,Data> *w = x->parent->left;

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
    statusEnum RedBlackTree<Key,Data>::erase ( const Key &key )
{
    BinaryNode<Key,Data> *z, *parent;

    //  delete node z from tree

    /* find node in tree */
    z = rootNode;
    parent = 0;

    while ( z != NULL_NODE )
    {
        if ( key == z->id )
            break;
        else
        {
            parent = z;
            z = ( key <= z->id ) ? z->left : z->right;
        }
    }

    if ( z == NULL_NODE )
        return STATUS_NOT_FOUND;

    return killNode ( z );
}

template <class Key, class Data>
    statusEnum RedBlackTree<Key,Data>::killNode ( BinaryNode<Key,Data> * z )
{
    BinaryNode<Key,Data> *x, *y;

    if ( z->left == NULL_NODE || z->right == NULL_NODE )
    {
        /* y has a NULL_NODE node as a child */
        y = z;
    }
    else
    {
        /* find tree successor with a NULL_NODE node as a child */
        y = z->right;

        while ( y->left != NULL_NODE )
            y = y->left;
    }

    /* x is y's only child */
    if ( y->left != NULL_NODE )
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
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
        z->id = y->id;
        z->data = y->data;
    }

    if ( y->color == BLACK )
        deleteFixup ( x );

    delete y;

    return STATUS_OK;
}


/* --------------------------------------------------------------------------------
    getNext:
        Get next node in tree after the one specified.
    
    TAKES:
        current        -    The node whose successor we are to get, or NULL_NODE to
                        get the first node.
    
    GIVES:
        current        -    The node following the one specified on input, or
                        NULL_NODE if there are no more nodes.
    
    NOTE:        Iterating a tree this way is kinda hairy. For this reason we keep
                some data in each node that tells us whether we already visited
                this node. There are three states: NODE_ITSELF_VISITED means we
                are returning this node right now, and this is set whenever a node
                is returned.
                LEFT_CHILD_VISITED means this node has been visited and it has two
                children of which we are now returning the left one.
                ALL_CHILDS_VISITED means this node has been visited and it has one
                unvisited child which we are now returning.
            
                If a node with ALL_CHILDS_VISITED is passed in, this means we are
                completely done with this node. So we loop uptree again (using the
                "parent" field) until we encounter a node that is
                LEFT_CHILD_VISITED (it can't be NODE_ITSELF_VISITED since it's our
                parent and we do a left-first search) or until we are at the root
                and the root also has ALL_CHILDS_VISITED set, in which case we
                return NULL.
        
    WARNING:    If you call getNext() in a loop, be sure to check the node pointer
                you pass in against the NULL node (NULL_NODE) and exit if that's the
                case, or you could enter an endless loop. Also verify that the new
                pointer for 'current' points to a valid node (ValidNode() does this
                trick).

   ----------------------------------------------------------------------------- */

template <class Key, class Data>
    void RedBlackTree<Key,Data>::getNext ( BinaryNode<Key,Data> ** current )
{
    if ( ( *current ) == NULL_NODE )
    {
        ( *current ) = rootNode;
        if ( ( **current ).left == NULL_NODE )
        {
            if ( ( **current ).right == NULL_NODE )
                ( **current ).beenThere = ALL_CHILDS_VISITED;
            else
                ( **current ).beenThere = LEFT_CHILD_VISITED;
        }
        else
            ( **current ).beenThere = NODE_ITSELF_VISITED;
        return;
    }

    switch ( ( **current ).beenThere )
    {
    case NODE_ITSELF_VISITED:
        // Go to our left child:
        if ( ( **current ).right != NULL_NODE )    // Have a right child that also needs to be walked?
            ( **current ).beenThere = LEFT_CHILD_VISITED;
        else                    // This is the only child?
            ( **current ).beenThere = ALL_CHILDS_VISITED;    // We're done.
        if ( ( **current ).left != NULL_NODE )
        {
            ( *current ) = ( **current ).left;
            // Clear left child's flag:
            ( **current ).beenThere = NODE_ITSELF_VISITED;
            break;
        }
        // Else drop through!!!

    case LEFT_CHILD_VISITED:
        // Go to our right child:
        ( **current ).beenThere = ALL_CHILDS_VISITED;
        if ( ( **current ).right != NULL_NODE )
        {
            ( *current ) = ( **current ).right;
            // Clear right child's flag:
            ( **current ).beenThere = NODE_ITSELF_VISITED;
            break;
        }
        // Else drop through!

    case ALL_CHILDS_VISITED:
        // Go to our boss:
        // Note that for some strange reason this NULL_NODE nonsense isn't used for parents.
        while ( ( *current ) != NULL_NODE
                && ( **current ).beenThere == ALL_CHILDS_VISITED )
            if ( ( **current ).parent != NULL )
                ( *current ) = ( **current ).parent;
            else
            {
                ( *current ) = NULL;
                return;
            }

        if ( ( *current ) != NULL_NODE )    // We're about to return a node:
        {
            if ( ( **current ).beenThere == NODE_ITSELF_VISITED )
            {
                if ( ( **current ).right == NULL_NODE )
                    ( **current ).beenThere = ALL_CHILDS_VISITED;
                else
                    ( **current ).beenThere = LEFT_CHILD_VISITED;

                ( *current ) = ( **current ).left;
                ( **current ).beenThere = NODE_ITSELF_VISITED;
            }
            else if ( ( **current ).beenThere == LEFT_CHILD_VISITED )
            {
                ( **current ).beenThere = ALL_CHILDS_VISITED;

                ( *current ) = ( **current ).right;
                ( **current ).beenThere = NODE_ITSELF_VISITED;
            }
        }
        break;
    }
}

template <class Key, class Data>
    Data RedBlackTree<Key,Data>::find ( const Key &key ) const
{
    BinaryNode<Key,Data> *current = rootNode;

    while ( current != NULL_NODE )
    {
        if ( key == current->id )
        {
            return current->data;
        }
        else
        {
            current = ( key <= current->id ) ?
                current->left : current->right;
        }
    }

    return (Data)0;
}

template <class Key, class Data>
    BinaryNode<Key,Data> * RedBlackTree<Key,Data>::findNode ( const Key &key ) const
{
    BinaryNode<Key,Data> * current = rootNode;
    while ( current != NULL_NODE )
    {
        if ( key == current->id )
        {
            return current;
        }
        else
        {
            current = ( key <= current->id ) ? current->left : current->right;
        }
    }

    return NULL;
}

template <class Key, class Data>
    void RedBlackTree<Key,Data>::killAll ( BinaryNode<Key,Data> *rec )
{
    if ( rec == NULL_NODE )
        return;

    // First kill our subnodes:
    if ( rec->left != NULL_NODE )
        killAll ( rec->left );

    if ( rec->right != NULL_NODE )
        killAll ( rec->right );

    if ( rec->parent != NULL )    // We're not root.
    {
        if ( rec->parent->left == rec )
            rec->parent->left = NULL_NODE;
        else
            rec->parent->right = NULL_NODE;
    }

    delete rec;
}

template <class Key, class Data>
    void RedBlackTree<Key,Data>::killAll ()
{
    killAll ( rootNode );
}

template <class Key, class Data>
    int RedBlackTree<Key,Data>::size ()
{
    BinaryNode<Key,Data> *vNode = NULL_NODE;
    int vCount = 0;

    getNext ( &vNode );
    while ( valid ( vNode ) )
    {
        vCount++;
        getNext ( &vNode );
    }

    return vCount;
}

template <class Key, class Data>
    bool RedBlackTree<Key,Data>::valid ( const BinaryNode<Key,Data> * node ) const
{
    if ( node != NULL && node != NULL_NODE )
        return true;
    else
        return false;
}

template <class Key, class Data>
    DArray<Data> *RedBlackTree<Key,Data>::ConvertToDArray ()
{
    DArray<Data> *darray = new DArray<Data> ( (int)size() );
    RecursiveConvertToDArray ( darray, rootNode );
    return darray;
}

template <class Key, class Data>
    DArray<char *> *RedBlackTree<Key,Data>::ConvertIndexToDArray ()
{
    DArray<char *> *darray = new DArray<char *> ( (int)size () );
    RecursiveConvertIndexToDArray ( darray, rootNode );
    return darray;
}

template <class Key, class Data>
    void RedBlackTree<Key,Data>::RecursiveConvertToDArray ( DArray<Data> *darray, BinaryNode<Key,Data> *btree )
{
    // note that the btree parameter is ignored

    BinaryNode<Key,Data> *current = NULL_NODE;

    CoreAssert ( darray != NULL );

    getNext ( &current );
    while ( valid ( current ) )
    {
        if ( current->data )
            darray->insert ( current->data );
        getNext ( &current );
    }
}

template <class Key, class Data>
    void RedBlackTree<Key,Data>::RecursiveConvertIndexToDArray ( DArray<char *> *darray, BinaryNode<Key,Data> *btree )
{
    // note that the btree parameter is ignored

    BinaryNode<Key,Data> *current = NULL_NODE;

    CoreAssert ( darray != NULL );

    getNext ( &current );
    while ( valid ( current ) )
    {
        if ( current->id )
            darray->insert ( current->id );
        getNext ( &current );
    }
}

#endif
