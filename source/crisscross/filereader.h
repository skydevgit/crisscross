/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_filereader_h
#define __included_cc_filereader_h

#include <crisscross/error.h>

namespace CrissCross
{
	namespace IO
	{
		/*! The file input class. */
		/*!
		 *  Inherits CoreIO, so functions like CoreIO::Read and CoreIO::ReadLine are accessible to the programmer.
		 */
		class FileReader : public CoreIOReader
		{
			protected:
				/*! The path to the file being read. */
				const char *m_filePath;

			public:
				/*! The constructor. */
				FileReader();

				/*! The destructor */
				/*!
				 *  Closes the file and deallocates memory used by FileReader.
				 */
				~FileReader();

				/*! Opens the provided file for read access. */
				/*!
				 * \param _file The path of the file to be read.
				 * \return Standard CrissCross::Errors values.
				 */
				CrissCross::Errors Open(const char *_file);

				/*! Closes the file. */
				/*!
				 *  Closes the file and deallocates memory used by FileReader.
				 * \return Standard CrissCross::Errors values.
				 */
				CrissCross::Errors Close();
		};
	}
}

#endif
