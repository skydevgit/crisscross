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

#ifndef __included_cc_darray_h
#   error "This file shouldn't be compiled directly."
#endif

#include <crisscross/debug.h>

#include <crisscross/darray.h>
#include <crisscross/dstack.h>

using namespace CrissCross::Data;

template < class T >
DArray < T >::DArray ()
{
    m_stepSize = -1;
    m_numUsed = m_arraySize = 0;
    m_shadow = NULL;
    m_array = NULL;
    m_emptyNodes = new DStack<size_t>;
    m_emptyNodes->push ( (size_t)-1 );
}

template < class T >
DArray < T >::DArray ( int _newStepSize )
{
    m_stepSize = _newStepSize;
    m_numUsed = m_arraySize = 0;
    m_shadow = NULL;
    m_array = NULL;
    m_emptyNodes = new DStack<size_t> ( _newStepSize + 1 );
    m_emptyNodes->push ( (size_t)-1 );
}

template < class T >
DArray < T >::~DArray ()
{
    empty ();
    delete m_emptyNodes;
}

template < class T >
void DArray < T >::rebuildStack ()
{
    //  Reset free list

    m_emptyNodes->empty();
    m_emptyNodes->push ( (size_t)-1 );

    // Step through, rebuilding

    for ( size_t i = m_arraySize - 1; (int)i >= 0; i-- )
        if ( m_shadow[i] == 0 )
            m_emptyNodes->push ( i );

}

template < class T >
void DArray < T >::recount()
{
    m_numUsed = 0;
    for ( size_t i = 0; i < m_arraySize; i++ )
        if ( m_shadow[i] == 1 )
            m_numUsed++;
}

template < class T >
void DArray < T >::setSize ( size_t newsize )
{
    if ( newsize > m_arraySize )
    {
        size_t oldarraysize = m_arraySize;

        m_arraySize = newsize;
        T *temparray = new T[m_arraySize];
        char *tempshadow = new char[m_arraySize];

        if ( m_array && m_shadow )
        {
            memcpy ( &temparray[0], &m_array[0], sizeof ( temparray[0] ) * oldarraysize );
            memcpy ( &tempshadow[0], &m_shadow[0], sizeof ( tempshadow[0] ) * oldarraysize );
        }

        memset ( &temparray[oldarraysize], 0, sizeof ( temparray[0] ) * ( m_arraySize - oldarraysize ) );
        memset ( &tempshadow[oldarraysize], 0, sizeof ( tempshadow[0] ) * ( m_arraySize - oldarraysize ) );

        for ( size_t a = m_arraySize - 1; (int)a >= (int)oldarraysize; a-- ) 
        {
            m_emptyNodes->push ( a );
        }

        delete [] m_array;
        delete [] m_shadow;

        m_array = temparray;
        m_shadow = tempshadow;

    }
    else if ( newsize < m_arraySize )
    {

        m_arraySize = newsize;
        T *temparray = new T[m_arraySize];
        char *tempshadow = new char[m_arraySize];

        if ( m_array && m_shadow )
        {
            memcpy ( &temparray[0], &m_array[0], sizeof ( temparray[0] ) * m_arraySize );
            memcpy ( &tempshadow[0], &m_shadow[0], sizeof ( tempshadow[0] ) * m_arraySize );
        }

        // We may have lost more than one node. It's worth rebuilding over.
        rebuildStack();
        recount();

        delete [] m_array;
        delete [] m_shadow;

        m_array = temparray;
        m_shadow = tempshadow;

    }
    else if ( newsize == m_arraySize )
    {
        // Do nothing
    }
}

template < class T >
void DArray < T >::grow ()
{
    if ( m_stepSize == -1 )
    {
        // Double array size
        if ( m_arraySize == 0 )
        {
            setSize ( 1 );
        }
        else
        {
            setSize ( m_arraySize * 2 );
        }
    }
    else
    {
        // Increase array size by fixed amount
        setSize ( m_arraySize + m_stepSize );
    }
}

template < class T >
void DArray < T >::setStepSize ( int _stepSize )
{
    m_stepSize = _stepSize;
}


template < class T >
void DArray < T >::setStepDouble ()
{
    m_stepSize = -1;
}

template < class T >
size_t DArray < T >::insert ( T const & newdata )
{
    size_t freeslot = getNextFree();

    m_array[freeslot] = newdata;
    if ( m_shadow[freeslot] == 0 ) m_numUsed++;
    m_shadow[freeslot] = 1;
    
    return freeslot;
}

template < class T >
void DArray < T >::insert ( T const & newdata, size_t index )
{
    CoreAssert ( index >= 0 );
    while ( index >= m_arraySize ) grow();

    m_array[index] = newdata;
    if ( m_shadow[index] == 0 ) m_numUsed++;
    m_shadow[index] = 1;
}

template < class T >
void DArray < T >::empty ()
{

    delete [] m_array;
    delete [] m_shadow;

    m_array = NULL;
    m_shadow = NULL;

    m_emptyNodes->empty ();
    m_emptyNodes->push ( (size_t)-1 );

    m_arraySize = 0;
    m_numUsed = 0;

}

template < class T >
size_t DArray < T >::getNextFree()
{
    // WARNING: This function assumes the node returned
    //          will be used by the calling function.

    if ( !m_shadow )
        grow();

    size_t freeslot = -2;

    while ( (freeslot = m_emptyNodes->pop() ) != (size_t)-1 )
    {
        if ( m_shadow[freeslot] == 0 )
            break;
    }

    if ( freeslot == (size_t)-1 )
    {
        m_emptyNodes->push ( (size_t)-1 );
        freeslot = m_arraySize;    
        grow();
    }
    
    if ( m_shadow[freeslot] == 0 )
        m_numUsed++;

    m_shadow[freeslot] = 1;

    return freeslot;
}

template < class T >
T DArray < T >::get ( size_t index ) const
{

    CoreAssert ( m_shadow[index] );
    CoreAssert ( index < m_arraySize );

    return m_array[index];

}

template < class T >
void DArray < T >::remove ( size_t index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize );

    m_emptyNodes->push ( index );

    if ( m_shadow[index] == 1 ) m_numUsed--;
    m_shadow[index] = 0;

}

template < class T >
size_t DArray < T >::used () const
{
    return m_numUsed;
}

template < class T >
size_t DArray < T >::size () const
{
    return m_arraySize;
}

template < class T >
bool DArray < T >::valid ( size_t index ) const
{

    if ( index >= m_arraySize || index < 0 )
        return false;

    if ( !m_shadow[index] )
        return false;

    return true;

}

template < class T >
size_t DArray < T >::findData ( T const & newdata )
{

    for ( size_t a = 0; a < m_arraySize; ++a )
        if ( m_shadow[a] )
            if ( m_array[a] == newdata )
                return a;

    return -1;

}

template < class T >
void DArray < T >::sort ( Sorter<T> *_sortMethod )
{
    T *temp_array = new T[m_numUsed];
    T *temp_ptr = temp_array;
    for ( size_t i = 0; i < m_arraySize; i++ )
    {
        if ( valid ( i ) )
        {
            *temp_ptr = m_array[i];
            temp_ptr++;
        }
    }
    
    _sortMethod->Sort ( temp_array, m_numUsed );
    
    delete [] m_shadow;
    m_shadow = new char[m_numUsed];
    memset ( m_shadow, 1, m_numUsed );
    
    delete [] m_array;
    m_array = temp_array;

    m_arraySize = m_numUsed;
    
    rebuildStack();
    recount();
}

template < class T >
void DArray < T >::sort ( Sorter<T> &_sortMethod )
{
    T *temp_array = new T[m_numUsed];
    T *temp_ptr = temp_array;
    for ( size_t i = 0; i < m_arraySize; i++ )
    {
        if ( valid ( i ) )
        {
            *temp_ptr = m_array[i];
            temp_ptr++;
        }
    }
    
    _sortMethod.Sort ( temp_array, m_numUsed );
    
    delete [] m_shadow;
    m_shadow = new char[m_numUsed];
    memset ( m_shadow, 1, m_numUsed );
    
    delete [] m_array;
    m_array = temp_array;

    m_arraySize = m_numUsed;
    
    rebuildStack();
    recount();
}

/* BELOW ARE DEPRECATED FUNCTIONS */

template <class T>
void DArray<T>::EmptyAndDelete()
{
    for (int i = 0; i < m_arraySize; ++i)
    {
        if (valid(i))
        {
            delete m_array[i];
        }
    }

    empty();
}

template <class T>
void DArray<T>::ChangeData ( T const & _rec, size_t index )
{
    CoreAssert ( m_shadow[index] == 1 );

    m_array[index] = _rec;
}
