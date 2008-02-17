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

#ifndef __included_cc_md4_h
#define __included_cc_md4_h

#include <crisscross/deprecate.h>
#include <crisscross/hash.h>

#define MD4_DIGEST_LENGTH       16

/* MD4 context. */
//@cond
typedef struct  {
    cc_uint32_t state[4];                                 /* state (ABCD) */
    cc_uint32_t count[2];      /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];                       /* input buffer */
} cc_md4_ctx;
//@endcond

namespace CrissCross
{
    namespace Crypto
    {
		//! An MD4 hash generator.
		/*!
			MD4 hashes are rarely used anymore due to the advent of MD5. MD5 was
			created because several speculated that MD4 was vulnerable to collisions
			(that is, two different sets of initialization vectors could result in
			the same hash). However, MD5 has proven no more secure than MD4 in the
			long run, and an MD4 hash is generally faster to generate than an MD5
			hash.
			\warning Because of popular belief that MD4 is less secure than MD5,
				use at your own risk!
			\sa Hash MD2Hash MD5Hash
		 */
        class MD4Hash : public Hash
        {
private:
            unsigned char *m_hash;
            cc_md4_ctx m_state;

public:
			//! The default constructor.
            MD4Hash ();
			
			//! The default destructor.
            virtual ~MD4Hash ();

			//! Runs an MD4 hash on the data provided.
			/*!
				\param _data The data to hash. The buffer does not need to be null
					terminated.
				\param _length The data length in bytes.
				\return Zero on success, nonzero on failure.
			 */
			int Process ( const void *_data, size_t _length );
			
			//! Resets the internal MD4 context and hash buffer.
            void Reset ();

			//! Converts the internal hash data into an hex string, a human readable format.
			/*!
				The memory location returned by this function is freed when the class
				is destructed.
			 */
            virtual const char *ToString () const;

        };
    }
}

#endif
