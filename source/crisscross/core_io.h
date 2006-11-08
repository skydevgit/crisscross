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

#ifndef __included_core_io_h
#define __included_core_io_h

#include "core_error.h"
#include "core_mutex.h"

namespace CrissCross
{
    namespace IO
    {

		//! File write modes.
		/*!
		   Provides the choice of creating a file when opening it or appending to it.
	     */
        enum FileWriteMode
        {
			CC_FILE_CREATE,                     /*!< Default. Will create a new file if the one opened does not exist. */
            CC_FILE_APPEND                      /*!< Write operations will append data to the end of the file. */
        };

        //! The core input/output class.
        /*!
            An abstract class inherited by most I/O classes, including CoreConsole, TextReader
            and TextWriter. Programmers can write their own I/O classes which inherit CoreIO.
        */
        class CoreIO
        {
          public:
            //! Line ending conventions.
            /*!
               An enumeration of different ending types.
             */
            enum LineEndingType
            {
				CC_LN_NATIVE,                     /*!< Automatically selects the appropriate line ending for the running platform. */
                CC_LN_CR,                         /*!< Carriage return only. (default for Commodore machines, Apple II family and Mac OS through version 9) */
                CC_LN_LF,                         /*!< Line feed only. (default for UNIX and UNIX-like systems, Linux, AIX, Xenix, Mac OS X, BeOS, Amiga, RISC OS and others) */
                CC_LN_CRLF                        /*!< Carriage return and line feed. (default for CP/M, MP/M, DOS, OS/2, Microsoft Windows) */
            };

          protected:

            //! Line ending buffer.
            /*!
               Stores the line ending selected by CoreIO::SetLineEndings.
             */
            CHAR *m_lineEnding;

            //! Input/output buffer.
            FILE *m_fileBuffer;

            //! Indicates whether the buffer is to be written in unicode or not.
            bool m_unicode;

        #ifndef TARGET_COMPILER_GCC
            //! Thread-safe mutex.
            /*!
               Prevents more than one read or write from occurring simultaneously.
             */
            CrissCross::System::CoreMutex *m_ioMutex;
        #endif

          public:
            //! The constructor.
            /*!
               Creates a new CoreIO instance. Will initialize line endings to the platform's
               default, also initializes CoreIO::m_ioMutex.
               \param _fileBuffer The buffer to be used for I/O operations.
               \param _isUnicode The buffer is going to be a Unicode I/O buffer.
               \param _lnEnding The line ending to use.
             */
            CoreIO ( FILE * _fileBuffer, bool _isUnicode, LineEndingType _lnEnding = CC_LN_NATIVE );

            //! The destructor.
            virtual ~CoreIO ();

            //! Determines whether the end of the file has been reached.
            /*!
               \return Boolean indicating whether the end of the file has been reached.
             */
            virtual bool EndOfFile ();

            //! Determines the length of the file buffer.
            /*!
               \return Indicates the length of the buffer in bytes.
             */
            virtual size_t Length ();

            //! Validates that the file buffer isn't NULL.
            /*!
               \return Boolean indicating whether the file is safe to write to.
             */
            virtual bool IsOpen ();

            //! Reads one character from the file buffer.
            /*!
               \param _destination A pointer to where the character can be stored.
               \return Number of bytes read (size of the character type).
             */
            virtual size_t Read ( CHAR *_destination );

            //! Reads one unicode character from the file buffer.
            /*!
               \param _destination A pointer to where the character can be stored.
               \return Number of bytes read (size of the character type).
             */
            virtual size_t Read ( WCHAR *_destination );

            //! Reads a block of data from the file buffer.
            /*!
               \param _buffer The output buffer to read to.
               \param _bufferLength The size of _buffer (in bytes).
               \param _bufferIndex The position in _buffer to begin writing.
               \param _count The number of bytes to read.
               \return The actual number of bytes read.
             */
            virtual size_t Read ( CHAR *_buffer, int _bufferLength, int _bufferIndex, int _count );

            //! Reads a block of unicode data from the file buffer.
            /*!
               \param _buffer The output buffer to read to.
               \param _bufferLength The size of _buffer (in bytes).
               \param _bufferIndex The position in _buffer to begin writing.
               \param _count The number of bytes to read.
               \return The actual number of bytes read.
             */
            virtual size_t Read ( WCHAR *_buffer, int _bufferLength, int _bufferIndex, int _count );

            //! Reads a line of data.
            /*!
               Data returned by this function should be copied to another location before being parsed.
               \param _string A reference of an std::string where the data will be stored.
               \return The number of bytes read.
             */
            virtual size_t ReadLine ( std::string &_string );

            //! Reads a line of unicode data.
            /*!
               Data returned by this function should be copied to another location before being parsed.
               \param _string A reference of an std::wstring where the unicode data will be stored.
               \return The number of bytes read.
             */
            virtual size_t ReadLine ( std::wstring &_string );

            //! Sets the line ending convention used by this CoreIO instance.
            /*!
               \param _ending Any of the CoreIO::LineEndingType values.
             */
            virtual CrissCross::Errors SetLineEndings ( LineEndingType _ending );

            //! Writes a string to the buffer.
            /*!
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors Write ( CONST CHAR *_format, ... );

            //! Writes a unicode string to the buffer.
            /*!
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors Write ( CONST WCHAR *_format, ... );

            //! Writes a string to the buffer.
            /*!
               \param _string The string to be written.
             */
            virtual CrissCross::Errors Write ( std::string _string );

            //! Writes a unicode string to the buffer.
            /*!
               \param _string The unicode string to be written.
             */
            virtual CrissCross::Errors Write ( std::wstring _string );

            //! Writes an empty line to the buffer.
            /*!
               Writes CoreIO::m_lineEnding to the buffer.
             */
            virtual CrissCross::Errors WriteLine ();

            //! Writes a string to the buffer with a newline appended.
            /*
               Prints the string to the buffer, and then prints the line terminator in the
               format specified by CoreIO::m_lineEnding.
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors WriteLine ( CONST CHAR *_format, ... );

            //! Writes a unicode string to the buffer with a newline appended.
            /*
               Prints the unicode string to the buffer, and then prints the line terminator in
               the format specified by CoreIO::m_lineEnding.
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors WriteLine ( CONST WCHAR *_format, ... );

            //! Writes a string to the buffer with a newline appended.
            /*
               Prints the string to the buffer, and then prints the line terminator in the
               format specified by CoreIO::m_lineEnding.
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors WriteLine ( std::string _string );

            //! Writes a unicode string to the buffer with a newline appended.
            /*
               Prints the unicode string to the buffer, and then prints the line terminator in the
               format specified by CoreIO::m_lineEnding.
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors WriteLine ( std::wstring _string );

            //! Seeks to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to the first byte of the buffer.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            virtual int Seek ( int _position );

            //! Moves forward to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to the current position in the buffer.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            virtual int Forward ( int _position );

            //! Flushes the output buffer.
            void Flush ();

          protected:
            //! Seeks to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to _origin.
               \param _origin Can be one of SEEK_SET, SEEK_CUR, or SEEK_END.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            int Seek ( int _position, int _origin );

        };
    }
}
#endif
