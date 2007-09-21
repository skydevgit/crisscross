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

#ifndef __included_cc_dstack_h
#   error "This file shouldn't be compiled directly."
#endif

#include <crisscross/dstack.h>

namespace CrissCross
{
	namespace Data
	{
		template < class dataType >
		DStack<dataType>::DStack ( size_t N )
		{
			if ( N < 1 )
				m_stepSize = -1;
			else
				m_stepSize = N;
			m_top = m_bottom = NULL;
			m_size = m_origSize = 0;
		}

		template < class dataType >
		DStack<dataType>::~DStack ()
		{
			delete [] m_bottom;
			m_top = m_bottom = NULL;
		}

		template < class dataType >
		void DStack<dataType>::setSize ( size_t _size )
		{
			m_lock.Lock();

			// This function is ONLY stable for increases in size, not decreases.
			dataType *newstack_ = NULL;
			newstack_ = new dataType[_size];
			if ( m_bottom )
			{
				memcpy ( newstack_, m_bottom, sizeof ( dataType ) * m_size );
				delete [] m_bottom;
			}
			m_bottom = newstack_;
			m_top = m_bottom + m_size;
			m_size = _size;

			m_lock.Unlock();
		}

		template < class dataType >
		void DStack<dataType>::grow ()
		{
			if ( m_stepSize == (size_t)-1 )
			{
				if ( m_size == 0 )
				{
					setSize ( 64 );
				} else {
					setSize ( m_size * 2 );
				}
			} else {
				setSize ( m_size + m_stepSize );
			}
		}

		template < class dataType >
		void DStack<dataType>::push ( dataType val )
		{
			m_lock.Lock();
			if ( count() == m_size )    // the stack is full. need more space!
			{
				grow();
			}
			*m_top = val;
			m_top++;
			m_lock.Unlock();
		}

		template < class dataType >
		size_t DStack<dataType>::count () const
		{
			return (m_top - m_bottom);
		}

		template < class dataType >
		dataType DStack<dataType>::pop ()
		{
			m_lock.Lock();
			if ( !m_top ) return (dataType)0;
			m_top--;
			dataType ret = *m_top;
			m_lock.Unlock();
			return ret;
		}

		template < class dataType >
		const dataType &DStack<dataType>::peek ()
		{
			m_lock.Lock();
			static dataType nullItem(0);
			if ( !m_top ) return nullItem;
			const dataType &ret = *(m_top - 1);
			m_lock.Unlock();
			return ret;
		}

		template < class dataType >
		void DStack<dataType>::empty ()
		{
			m_lock.Lock();
			delete [] m_bottom;
			m_top = m_bottom = NULL;
			m_size = m_origSize = 0;
			m_lock.Unlock();
		}
	}
}
