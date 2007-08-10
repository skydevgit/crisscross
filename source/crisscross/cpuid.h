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

#ifndef __included_cc_cpuid_h
#define __included_cc_cpuid_h

#ifndef __GNUC__
#include <crisscross/universal_include.h>
#endif

#ifdef ENABLE_CPUID

#   ifdef TARGET_OS_WINDOWS
#       include <windows.h>
#   endif

#   include "darray.h"
#   include "rbtree.h"

namespace CrissCross
{
	namespace System
	{

		class Feature
		{
		  public:
			bool Enabled;
			Feature ()
			{
				Enabled = 0;
			}

			~Feature ()
			{
			}
		};

		class Processor
		{
		  public:
			const char *Manufacturer;
			const char *ProcessorName;
			unsigned int LogicalPerPackage;
			unsigned int CoresPerPackage;
			char Family;
			char Model;
			char Stepping;
			char BrandID;
			char APICID;
			RedBlackTree<const char *, Feature *> features;
			DArray <char *> caches;
		  public:
			Processor ()
			{
			}

			~Processor ()
			{
			}
		};


		class CPUID
		{

		  protected:

		#ifdef TARGET_OS_WINDOWS

			struct GoThreadProc_Params
			{
				CPUID *cpuid_class;
				int processor;
			};

			static DWORD CALLBACK s_GoThreadProc ( LPVOID lpParameter )
			{
				return ( ( GoThreadProc_Params * ) lpParameter )->cpuid_class->
					GoThread ( ( LPVOID * ) &
							   ( ( GoThreadProc_Params * ) lpParameter )->processor );
			};
			DWORD WINAPI GoThread ( LPVOID * params );
		#else
			long int GoThread ( int processor );
		#endif

			void AddCacheDescription ( int processor, const char *description );
			void AddIntelCacheData ( int processor, int x );
			void DetectManufacturer ( int processor );
			void DetectProcessorName ( int processor );
			void DetectCacheInfo ( int processor );
			void DecodeAMDCacheIdentifiers ( int processor );
			void DetectFMS ( int processor );
			void DetectBrandID ( int processor );
			void DetectCount ( int processor );
			void DetectAPIC ( int processor );
			void DetectFeatures ( int processor );
			void DetectFeature ( const unsigned int *_register, long _flag, int _processor, const char *_name );

		  public:
			  CPUID ();
			 ~CPUID ();
			void Go ();

			/*!
				\return The number of hardware threads per physical package.
			 */
			int LogicalPerPackage ();

			/*!
				\return The number of physical cores per package.
			 */
			int CoresPerPackage ();

			/*!
				\return The number of virtual processors detected, including all cores and hardware threads.
			 */
			int VirtualCount ();

			Processor *proc[MAX_PROCESSORS];    // Support up to MAX_PROCESSORS

		};
	}
}

#endif

#endif
