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

#include <crisscross/universal_include.h>
#include <crisscross/core_debug.h>
#include <crisscross/textreader.h>

using namespace CrissCross::IO;

TextReader::TextReader ():
CoreIOReader ( NULL, false ), m_filePath ( NULL )
{
}

TextReader::~TextReader ()
{
    Close ();
}

CrissCross::Errors TextReader::Open ( const char *_file )
{

	Close ();

    int _filePathLength = 0;

	if ( _file == NULL )
		return CC_ERR_BADPARAMETER;

	if ( ( _filePathLength = (int)strlen ( _file ) ) < 1 )
		return CC_ERR_BADPARAMETER;

    delete [] (char *) m_filePath;
    m_filePath = new char[_filePathLength + 1];
    strcpy ( (char *) m_filePath, _file );

    m_fileInputPointer = fopen ( m_filePath, "rt" );

    if ( m_fileInputPointer == NULL )
    {
        m_fileInputBuffer = new std::ifstream ( m_fileInputPointer );
		return CC_ERR_FILE_OPEN;
    }
	else
    {
		return CC_ERR_NONE;
    }
}

CrissCross::Errors TextReader::Close ()
{
	if ( m_fileInputPointer )
		fclose ( m_fileInputPointer );
	m_fileInputPointer = NULL;

    delete m_fileInputBuffer;
    m_fileInputBuffer = NULL;

	delete [] (char *)m_filePath;
	m_filePath = NULL;
	
	return CC_ERR_NONE;
}
