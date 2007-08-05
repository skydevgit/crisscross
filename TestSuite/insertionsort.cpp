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

#include "header.h"
#include "testutils.h"
#include "insertionsort.h"

#include <crisscross/universal_include.h>
#include <crisscross/darray.h>
#include <crisscross/insertionsort.h>

using namespace CrissCross::Data;

int TestInsertionSort_IntArray()
{
    int int_array[] = {0, 4, 3, 6, 2, 1, 5, 7, 9, 8 };
    InsertionSort<int> *is = new InsertionSort<int>();
    is->Sort ( int_array, 10 );
    for ( int i = 0; i < 10; i++ )
    {
        if ( int_array[i] != i )
            return i + 1;
    }
    delete is;
    return 0;
}

int TestInsertionSort_DArray()
{
    DArray<int> *darray = new DArray<int>();
    
    darray->insert ( 4 );
    darray->insert ( 2 );
    darray->insert ( 0 );
    darray->insert ( 3 );
    darray->insert ( 1 );
    
    InsertionSort<int> *is = new InsertionSort<int>();
    darray->sort ( is );
    delete is;
    
    for ( int i = 0; i < 5; i++ )
    {
        if ( darray->get(i) != i )
            return i + 1;
    }

    delete darray;    
    return 0;
}