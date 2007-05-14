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

#include "compare.h"
#include "datatypes.h"
#include "darray.h"
#include "dstack.h"
#include "llist.h"
#include "rbtree.h"
#include "sort.h"
#include "stopwatch.h"

using namespace CrissCross;

CrissCross::IO::Console *g_console;

int RunApplication (int argc, char **argv) {
	
	g_console = new IO::Console();
	g_console->WriteLine ( "CrissCross Test Suite v" CC_LIB_VERSION );
	g_console->WriteLine ();
    
	int retval = 0;

	WritePrefix ( "Size of Uint8" ); retval |= WriteResult ( TestDatatypes_Uint8() );
	WritePrefix ( "Size of Uint16" ); retval |= WriteResult ( TestDatatypes_Uint16() );
	WritePrefix ( "Size of Uint32" ); retval |= WriteResult ( TestDatatypes_Uint32() );
	WritePrefix ( "Size of Uint64" ); retval |= WriteResult ( TestDatatypes_Uint64() );
	WritePrefix ( "Size of Bool" ); retval |= WriteResult ( TestDatatypes_Bool() );
	WritePrefix ( "Size of Float" ); retval |= WriteResult ( TestDatatypes_Float() );
	WritePrefix ( "Size of Double" ); retval |= WriteResult ( TestDatatypes_Double() );
	WritePrefix ( "Size of void *" ); retval |= WriteResult ( TestDatatypes_Pointer() );

	WritePrefix ( "DataBuffer Compare" ); retval |= WriteResult ( TestComparison_DataBuffer() );
	WritePrefix ( "Integer Compare" ); retval |= WriteResult ( TestComparison_Integer() );
	WritePrefix ( "Unsigned Integer Compare" ); retval |= WriteResult ( TestComparison_UnsignedInteger() );
	WritePrefix ( "LList" ); retval |= WriteResult ( TestLList() );
	WritePrefix ( "DArray" ); retval |= WriteResult ( TestDArray() );
	WritePrefix ( "DStack" ); retval |= WriteResult ( TestDStack() );

	WritePrefix ( "RedBlackTree<DataBuffer, DataBuffer *>" ); retval |= WriteResult ( TestRedBlackTree_DataBuffer() );
	WritePrefix ( "RedBlackTree<std::string, std::string>" ); retval |= WriteResult ( TestRedBlackTree_stdstring() );
	WritePrefix ( "RedBlackTree<int, int>" ); retval |= WriteResult ( TestRedBlackTree_Int() );

	WritePrefix ( "HeapSort (integer array)" ); retval |= WriteResult ( TestHeapSort_IntArray() );
	WritePrefix ( "HeapSort (integer DArray)" ); retval |= WriteResult ( TestHeapSort_DArray() );

	WritePrefix ( "Stopwatch" ); retval |= WriteResult ( TestStopwatch() );
	g_console->Flush();

#ifdef TARGET_OS_WINDOWS
	system ( "pause" );
#endif

	delete g_console;

    CoreAssert ( retval == 0 );

	return 0;
}
