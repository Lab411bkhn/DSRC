/*
 * $Id: ExtensibleInteger.c $
 *
 * This file is part of the CALM FAST Message Library.
 * 
 * Author: Andras Takacs <andras.takacs@ramsys.hu>
 *
 * Copyright 2006-2009 Ramsys Zrt
 *
 * CALM FAST Message Library is free software; you can redistribute
 * it and/or modify it under the terms of the GNU LEsser General Public
 * License as published by the Free Software Foundation; version 3 of
 * the License.
 *
 * CALM FAST Message Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CALM FAST Message Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

/*-
 * Copyright (c) 2004, 2005, 2006 Lev Walkin <vlm@lionet.info>.
 * All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * Read the NativeInteger.h for the explanation wrt. differences between
 * INTEGER and NativeInteger.
 * Basically, both are decoders and encoders of ASN.1 INTEGER type, but this
 * implementation deals with the standard (machine-specific) representation
 * of them instead of using the platform-independent buffer.
 */
#include <ctype.h>	/* endianness */

#include <asn_internal.h>
#include <ExtensibleInteger.h>

/*
 * NativeInteger basic type description.
 */
static ber_tlv_tag_t asn_DEF_ExtensibleInteger_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
asn_TYPE_descriptor_t asn_DEF_ExtensibleInteger = {
	"EXINTEGER",			/* The ASN.1 type is still INTEGER */
	"EXINTEGER",
	__LIBFAST__ExtensibleInteger_free,
	__LIBFAST__ExtensibleInteger_print,
	__LIBFAST__asn_generic_no_constraint,
	__LIBFAST__ExtensibleInteger_decode_ber,
	__LIBFAST__ExtensibleInteger_encode_der,
	__LIBFAST__ExtensibleInteger_decode_xer,
	__LIBFAST__ExtensibleInteger_encode_xer,
    __LIBFAST__ExtensibleInteger_decode_uper, 
    __LIBFAST__ExtensibleInteger_encode_uper,
	0, /* Use generic outmost tag fetcher */
	asn_DEF_ExtensibleInteger_tags,
	sizeof(asn_DEF_ExtensibleInteger_tags) / sizeof(asn_DEF_ExtensibleInteger_tags[0]),
	asn_DEF_ExtensibleInteger_tags,	/* Same as above */
	sizeof(asn_DEF_ExtensibleInteger_tags) / sizeof(asn_DEF_ExtensibleInteger_tags[0]),
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	0	/* No specifics */
};

/*
 * Decode INTEGER type.
 */
asn_dec_rval_t
__LIBFAST__ExtensibleInteger_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **nint_ptr, const void *buf_ptr, size_t size, int tag_mode) {
	long *native = (long *)*nint_ptr;
	asn_dec_rval_t rval;
	ber_tlv_len_t length;

	/*
	 * If the structure is not there, allocate it.
	 */
	if(native == NULL) {
		native = (long *)(*nint_ptr = CALLOC(1, sizeof(*native)));
		if(native == NULL) {
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
		}
	}

	__LIBFAST__ASN_DEBUG("Decoding %s as EXTINTEGER (tm=%d)",
		td->name, tag_mode);

	/*
	 * Check tags.
	 */
	rval = __LIBFAST__ber_check_tags(opt_codec_ctx, td, 0, buf_ptr, size,
			tag_mode, 0, &length, 0);
	if(rval.code != RC_OK)
		return rval;

	__LIBFAST__ASN_DEBUG("%s length is %d bytes", td->name, (int)length);

	/*
	 * Make sure we have this length.
	 */
	buf_ptr = ((const char *)buf_ptr) + rval.consumed;
	size -= rval.consumed;
	if(length > (ber_tlv_len_t)size) {
		rval.code = RC_WMORE;
		rval.consumed = 0;
		return rval;
	}

	/*
	 * ASN.1 encoded INTEGER: buf_ptr, length
	 * Fill the native, at the same time checking for overflow.
	 * If overflow occured, return with RC_FAIL.
	 */
	{
		INTEGER_t tmp;
		union {
			const void *constbuf;
			void *nonconstbuf;
		} unconst_buf;
		long l;

		unconst_buf.constbuf = buf_ptr;
		tmp.buf = (uint8_t *)unconst_buf.nonconstbuf;
		tmp.size = length;

		if(__LIBFAST__asn_INTEGER2long(&tmp, &l)) {
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
		}

        uint8_t * ei = (uint8_t *)&l;
#if __BYTE_ORDER == __BIG_ENDIAN
        *native = ei[3];                                    
        *native += 128 * ei[2];
        *native += 16384 * ei[1];
        *native += 2097152 * ei[0];
#else
#  if __BYTE_ORDER == __LITTLE_ENDIAN
        *native = ei[0];                                    
        *native += 128 * ei[1];
        *native += 16384 * ei[2];
        *native += 2097152 * ei[3];
#  else
#    error endianness not defined
#  endif
#endif
	}

	rval.code = RC_OK;
	rval.consumed += length;

	__LIBFAST__ASN_DEBUG("Took %ld/%ld bytes to encode %s (%ld)",
		(long)rval.consumed, (long)length, td->name, (long)*native);

	return rval;
}

/*
 * Encode the NativeInteger using the standard INTEGER type DER encoder.
 */
asn_enc_rval_t
__LIBFAST__ExtensibleInteger_encode_der(asn_TYPE_descriptor_t *sd, void *ptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	unsigned long native = *(unsigned long *)ptr;	/* Disable sign ext. */
    size_t ns = sizeof(native);
    uint8_t ei[sizeof(native)];
	asn_enc_rval_t erval;
	INTEGER_t tmp;

#ifdef	WORDS_BIGENDIAN		/* Opportunistic optimization */

    ei[0] = native & 0x7F;
    if (ns > 1) {
	    ei[1] = (native >> 7) & 0x7F;
        if (ns > 2) {
        	ei[2] = (native >> 14) & 0x7F;
            if (ns > 3)
            	ei[3] = (native >> 21) & 0x7F;
        }
    }
	tmp.buf = ei;
	tmp.size = sizeof(native);

#else	/* Works even if WORDS_BIGENDIAN is not set where should've been */
       
    ei[0] = (ns > 3) ? ((native >> 21) & 0x7F) : ((ns > 2) ? ((native >> 14) & 0x7F) : ((ns > 1) ? ((native >> 7) & 0x7F) : (native & 0x7F)));
    if (ns > 1) {
	    ei[1] = (ns > 2) ? ((native >> 14) & 0x7F) : ((ns > 1) ? ((native >> 7) & 0x7F) : (native & 0x7F));
        if (ns > 2) {
        	ei[2] = (ns > 1) ? ((native >> 7) & 0x7F) : (native & 0x7F);
            if (ns > 3)
            	ei[3] = native & 0x7F;
        }
    }

	tmp.buf = ei;
	tmp.size = sizeof(native);
#endif	/* WORDS_BIGENDIAN */
	
	/* Encode fake INTEGER */
	erval = __LIBFAST__INTEGER_encode_der(sd, &tmp, tag_mode, tag, cb, app_key);
	if(erval.encoded == -1) {
		assert(erval.structure_ptr == &tmp);
		erval.structure_ptr = ptr;
	}
	return erval;
}

/*
 * Decode the chunk of XML text encoding INTEGER.
 */
asn_dec_rval_t
__LIBFAST__ExtensibleInteger_decode_xer(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td, void **sptr, const char *opt_mname,
		const void *buf_ptr, size_t size) {
	asn_dec_rval_t rval;
	INTEGER_t st;
	void *st_ptr = (void *)&st;
	long *native = (long *)*sptr;

	if(!native) {
		native = (long *)(*sptr = CALLOC(1, sizeof(*native)));
		if(!native) _ASN_DECODE_FAILED;
	}

	memset(&st, 0, sizeof(st));
	rval = __LIBFAST__INTEGER_decode_xer(opt_codec_ctx, td, &st_ptr, 
		opt_mname, buf_ptr, size);
	if(rval.code == RC_OK) {
		long l;
		if(__LIBFAST__asn_INTEGER2long(&st, &l)) {
			rval.code = RC_FAIL;
			rval.consumed = 0;
		} else {
			*native = l;
		}
	} else {
		/*
		 * Cannot restart from the middle;
		 * there is no place to save state in the native type.
		 * Request a continuation from the very beginning.
		 */
		rval.consumed = 0;
	}
	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_INTEGER, &st);
	return rval;
}


asn_enc_rval_t
__LIBFAST__ExtensibleInteger_encode_xer(asn_TYPE_descriptor_t *td, void *sptr,
	int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	char scratch[32];	/* Enough for 64-bit int */
	asn_enc_rval_t er;
	const long *native = (const long *)sptr;

	(void)ilevel;
	(void)flags;

	if(!native) _ASN_ENCODE_FAILED;

	er.encoded = snprintf(scratch, sizeof(scratch), "%ld", *native);
	if(er.encoded <= 0 || (size_t)er.encoded >= sizeof(scratch)
		|| cb(scratch, er.encoded, app_key) < 0)
		_ASN_ENCODE_FAILED;

	_ASN_ENCODED_OK(er);
}

asn_dec_rval_t
__LIBFAST__ExtensibleInteger_decode_uper(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd) {

	asn_dec_rval_t rval;
	long *native = (long *)*sptr;
	INTEGER_t tmpint;
	void *tmpintptr = &tmpint;
    long l;

	(void)opt_codec_ctx;
	__LIBFAST__ASN_DEBUG("Decoding NativeInteger %s (UPER)", td->name);

	if(!native) {
		native = (long *)(*sptr = CALLOC(1, sizeof(*native)));
		if(!native) _ASN_DECODE_FAILED;
	}

	memset(&tmpint, 0, sizeof tmpint);
	rval = __LIBFAST__INTEGER_decode_uper(opt_codec_ctx, td, constraints,
				   &tmpintptr, pd);
	if(rval.code == RC_OK) {
		if(__LIBFAST__asn_INTEGER2long(&tmpint, &l))
			rval.code = RC_FAIL;
        else {
            uint8_t * ei = (uint8_t *)&l;
#if __BYTE_ORDER == __BIG_ENDIAN
            *native = ei[3];                                    
            *native += 128 * ei[2];
            *native += 16384 * ei[1];
            *native += 2097152 * ei[0];
#else
#  if __BYTE_ORDER == __LITTLE_ENDIAN
            *native = ei[0];                                    
            *native += 128 * ei[1];
            *native += 16384 * ei[2];
            *native += 2097152 * ei[3];
#  else
#    error endianness not defined
#  endif
#endif

			__LIBFAST__ASN_DEBUG("ExtensibleInteger %s got value %ld",
				td->name, *native);
        }
	}
	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_INTEGER, &tmpint);

	return rval;
}

asn_enc_rval_t
__LIBFAST__ExtensibleInteger_encode_uper(asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void *sptr, asn_per_outp_t *po) {
	asn_enc_rval_t er;
	unsigned long native = *(unsigned long *)sptr;
    size_t ns = sizeof(native);
    uint8_t ei[sizeof(native)];
	INTEGER_t tmp;

	if(!sptr) _ASN_ENCODE_FAILED;

    #ifdef	WORDS_BIGENDIAN		/* Opportunistic optimization */

    ei[0] = native & 0x7F;
    if (ns > 1) {
	    ei[1] = (native >> 7) & 0x7F;
        if (ns > 2) {
        	ei[2] = (native >> 14) & 0x7F;
            if (ns > 3)
            	ei[3] = (native >> 21) & 0x7F;
        }
    }
	tmp.buf = ei;
	tmp.size = sizeof(native);

    #else	/* Works even if WORDS_BIGENDIAN is not set where should've been */
       
    ei[0] = (ns > 3) ? ((native >> 21) & 0x7F) : ((ns > 2) ? ((native >> 14) & 0x7F) : ((ns > 1) ? ((native >> 7) & 0x7F) : (native & 0x7F)));
    if (ns > 1) {
	    ei[1] = (ns > 2) ? ((native >> 14) & 0x7F) : ((ns > 1) ? ((native >> 7) & 0x7F) : (native & 0x7F));
        if (ns > 2) {
        	ei[2] = (ns > 1) ? ((native >> 7) & 0x7F) : (native & 0x7F);
            if (ns > 3)
            	ei[3] = native & 0x7F;
        }
    }

	tmp.buf = ei;
	tmp.size = sizeof(native);
    
    #endif	/* WORDS_BIGENDIAN */

	__LIBFAST__ASN_DEBUG("Encoding ExtensibleInteger %s %ld (UPER)", td->name, native);

	er = __LIBFAST__INTEGER_encode_uper(td, constraints, &tmp, po);
	return er;
}

/*
 * INTEGER specific human-readable output.
 */
int
__LIBFAST__ExtensibleInteger_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	const long *native = (const long *)sptr;
	char scratch[32];	/* Enough for 64-bit int */
	int ret;

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(native) {
		ret = snprintf(scratch, sizeof(scratch), "%ld", *native);
		assert(ret > 0 && (size_t)ret < sizeof(scratch));
		return (cb(scratch, ret, app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}

void
__LIBFAST__ExtensibleInteger_free(asn_TYPE_descriptor_t *td, void *ptr, int contents_only) {

	if(!td || !ptr)
		return;

	__LIBFAST__ASN_DEBUG("Freeing %s as EXTINTEGER (%d, %p, Native)",
		td->name, contents_only, ptr);

	if(!contents_only) {
		FREEMEM(ptr);
	}
}

