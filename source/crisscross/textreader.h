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
    
#ifndef __included_textreader_h
#define __included_textreader_h

#include "core_error.h"
   
namespace CrissCross
{
    namespace IO
    {

        //! The text file input class.
        /*!
            Inherits CoreIO, so functions like CoreIO::Read and CoreIO::ReadLine are accessible to the programmer.
        */ 
        class TextReader : public CoreIO 
        {

        protected:
            //! The path to the file being read.
            const char *m_filePath;

        public:
            //! The constructor.
            TextReader ();

            //! The destructor
            /*!
                Closes the file and deallocates memory used by TextReader.
             */ 
            ~TextReader ();

            //! Opens the provided file for read access.
            /*!
				\param _file The path of the file to be read.
				\return Standard CrissCross::Errors values.
             */ 
			CrissCross::Errors Open ( const char *_file );

            //! Closes the file.
            /*!
                Closes the file and deallocates memory used by TextReader.
				\return Standard CrissCross::Errors values.
             */ 
			CrissCross::Errors Close ();

        private:
			// TextReader shouldn't make any write calls whatsoever.
            CrissCross::Errors Write ( const char *_format, ... )
                { return CC_ERR_INVALID_CALL; };
            CrissCross::Errors WriteLine ()
                { return CC_ERR_INVALID_CALL; };
            CrissCross::Errors WriteLine ( const char *_format, ... )
                { return CC_ERR_INVALID_CALL; };

        };
    }
}

#endif