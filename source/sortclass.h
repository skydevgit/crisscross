/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006 IO.IN Research
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of the I.O. Independent Network nor the names of its contributors
 *       may be used to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */  
    
#ifndef __included_sortclass_h
#define __included_sortclass_h

#include "compare.h"

namespace CrissCross
{
    namespace Data
    {
        //! Sorting abstract class.
        template <class T>
        class SortClass
        {
        public:
            //! The constructor.
            SortClass();

            //! The destructor.
            virtual ~SortClass();

            //! The abstract sort function.
            /*!
                Does nothing except return 0.
                \param _array The array to sort.
                \param _size The size of the array to sort.
                \return Always 0. Abstract class.
             */
            virtual int Sort ( T *_array, int _size ) { return 0; };

            //! The swap function.
            /*!
                Will swap two items in an array.
                \param _array The array to swap items in.
                \param _first The first item to swap.
                \param _second The second item to swap.
             */
            virtual void Swap ( T *_array, int _first, int _second );
        };

        //! A HeapSort implementation for sorting arrays.
        template <class T>
        class HeapSort : public SortClass<T>
        {
        public:
            //! The constructor.
            HeapSort();

            //! Sorts the array using the HeapSort method.
            /*!
                \param _array The array to sort.
                \param _size The size of the array to sort.
                \return Always 0, for the time being.
             */
            int Sort ( T *_array, int _size );
        };
    }
}

#include "sortclass.cpp"

#endif