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

#ifndef __included_stopwatch_h
#define __included_stopwatch_h

#if defined ( TARGET_OS_MACOSX )
#   include <CoreServices/CoreServices.h>
#   include <mach/mach.h>
#   include <mach/mach_time.h>
#elif defined ( TARGET_OS_LINUX )
#   include <sys/time.h>
#   include <time.h>
#endif

namespace CrissCross
{
    namespace System
    {
        //! A timer class designed for code profiling.
        class Stopwatch
        {
        private:
#if defined ( TARGET_OS_WINDOWS )
            LARGE_INTEGER               m_start, m_finish;
            double                      m_tickInterval;
#elif defined ( TARGET_OS_MACOSX )
            uint64_t					m_start;
            uint64_t					m_finish;
            mach_timebase_info_data_t 	m_timebase;
#elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
            timeval                     m_start;
            timeval                     m_finish;
#endif
        public:
            //! The constructor.
            Stopwatch();

            //! The destructor.
            ~Stopwatch();

            //! Starts the timer counter.
            void Start();

            //! Stops the timer counter.
            void Stop();

            //! Indicates the number of seconds elapsed.
            /*!
                \return Number of seconds elapsed between the Start() and Stop() calls.
             */
            double Elapsed();
        };
    }
}

#endif
