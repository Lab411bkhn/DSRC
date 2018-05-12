/*
 * $Id: NativeInteger.c $
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
#include <asn_internal.h>
#include <NativeInteger.h>

/*
 * NativeInteger basic type description.
 */
static ber_tlv_tag_t asn_DEF_NativeInteger_tags[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (2 << 2))
};
asn_TYPE_descriptor_t asn_DEF_NativeInteger = {
	"INTEGER",			/* The ASN.1 type is still INTEGER */
	"INTEGER",
	__LIBFAST__NativeInteger_free,
	__LIBFAST__NativeInteger_print,
	__LIBFAST__asn_generic_no_constraint,
	__LIBFAST__NativeInteger_decode_ber,
	__LIBFAST__NativeInteger_encode_der,
	__LIBFAST__NativeInteger_decode_xer,
	__LIBFAST__NativeInteger_encode_xer,
	__LIBFAST__NativeInteger_decode_uper,	/* Unaligned PER decoder */
	__LIBFAST__NativeInteger_encode_uper,	/* Unaligned PER encoder */
	0, /* Use generic outmost tag fetcher */
	asn_DEF_NativeInteger_tags,
	sizeof(asn_DEF_NativeInteger_tags) / sizeof(asn_DEF_NativeInteger_tags[0]),
	asn_DEF_NativeInteger_tags,	/* Same as above */
	sizeof(asn_DEF_NativeInteger_tags) / sizeof(asn_DEF_NativeInteger_tags[0]),
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	0	/* No specifics */
};

/*
 * Decode INTEGER type.
 */
asn_dec_rval_t
__LIBFAST__NativeInteger_decode_ber(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **nint_ptr, const void *buf_ptr, size_t size, int tag_mode) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
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

	__LIBFAST__ASN_DEBUG("Decoding %s as INTEGER (tm=%d)",
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

		if((specs&&specs->field_unsigned)
			? __LIBFAST__asn_INTEGER2ulong(&tmp, (unsigned long *)&l)
			: __LIBFAST__asn_INTEGER2long(&tmp, &l)) {
			rval.code = RC_FAIL;
			rval.consumed = 0;
			return rval;
		}

		*native = l;
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
__LIBFAST__NativeInteger_encode_der(asn_TYPE_descriptor_t *sd, void *ptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	unsigned long native = *(unsigned long *)ptr;	/* Disable sign ext. */
	asn_enc_rval_t erval;
	INTEGER_t tmp;

#ifdef	WORDS_BIGENDIAN		/* Opportunistic optimization */

	tmp.buf = (uint8_t *)&native;
	tmp.size = sizeof(native);

#else	/* Works even if WORDS_BIGENDIAN is not set where should've been */
	uint8_t buf[sizeof(native)];
	uint8_t *p;

	/* Prepare a fake INTEGER */
	for(p = buf + sizeof(buf) - 1; p >= buf; p--, native >>= 8)
		*p = (uint8_t)native;

	tmp.buf = buf;
	tmp.size = sizeof(buf);
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
__LIBFAST__NativeInteger_decode_xer(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td, void **sptr, const char *opt_mname,
		const void *buf_ptr, size_t size) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
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
		if((specs&&specs->field_unsigned)
			? __LIBFAST__asn_INTEGER2ulong(&st, (unsigned long *)&l)
			: __LIBFAST__asn_INTEGER2long(&st, &l)) {
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
__LIBFAST__NativeInteger_encode_xer(asn_TYPE_descriptor_t *td, void *sptr,
	int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	char scratch[32];	/* Enough for 64-bit int */
	asn_enc_rval_t er;
	const long *native = (const long *)sptr;

	(void)ilevel;
	(void)flags;

	if(!native) _ASN_ENCODE_FAILED;

	er.encoded = snprintf(scratch, sizeof(scratch),
			(specs && specs->field_unsigned)
			? "%lu" : "%ld", *native);
	if(er.encoded <= 0 || (size_t)er.encoded >= sizeof(scratch)
		|| cb(scratch, er.encoded, app_key) < 0)
		_ASN_ENCODE_FAILED;

	_ASN_ENCODED_OK(er);
}

asn_dec_rval_t
__LIBFAST__NativeInteger_decode_uper(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd) {

	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	asn_dec_rval_t rval;
	long *native = (long *)*sptr;
	INTEGER_t tmpint;
	void *tmpintptr = &tmpint;

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
		if((specs&&specs->field_unsigned)
			? __LIBFAST__asn_INTEGER2ulong(&tmpint, (unsigned long *)native)
			: __LIBFAST__asn_INTEGER2long(&tmpint, native))
			rval.code = RC_FAIL;
		else
			__LIBFAST__ASN_DEBUG("NativeInteger %s got value %ld",
				td->name, *native);
	}
	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_INTEGER, &tmpint);

	return rval;
}

asn_enc_rval_t
__LIBFAST__NativeInteger_encode_uper(asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void *sptr, asn_per_outp_t *po) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	asn_enc_rval_t er;
	long native;
	INTEGER_t tmpint;

	if(!sptr) _ASN_ENCODE_FAILED;

	native = *(long *)sptr;

	__LIBFAST__ASN_DEBUG("Encoding NativeInteger %s %ld (UPER)", td->name, native);

	memset(&tmpint, 0, sizeof(tmpint));
	if((specs&&specs->field_unsigned)
		? __LIBFAST__asn_ulong2INTEGER(&tmpint, native)
		: __LIBFAST__asn_long2INTEGER(&tmpint, native))
		_ASN_ENCODE_FAILED;
	er = __LIBFAST__INTEGER_encode_uper(td, constraints, &tmpint, po);
	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_INTEGER, &tmpint);
	return er;
}

/*
 * INTEGER specific human-readable output.
 */
int
__LIBFAST__NativeInteger_print(asn_TYPE_descriptor_t *td, const void *sptr, int ilevel,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_INTEGER_specifics_t *specs=(asn_INTEGER_specifics_t *)td->specifics;
	const long *native = (const long *)sptr;
	char scratch[32];	/* Enough for 64-bit int */
	int ret;

	(void)td;	/* Unused argument */
	(void)ilevel;	/* Unused argument */

	if(native) {
		ret = snprintf(scratch, sizeof(scratch),
			(specs && specs->field_unsigned)
			? "%lu" : "%ld", *native);
		assert(ret > 0 && (size_t)ret < sizeof(scratch));
		return (cb(scratch, ret, app_key) < 0) ? -1 : 0;
	} else {
		return (cb("<absent>", 8, app_key) < 0) ? -1 : 0;
	}
}

void
__LIBFAST__NativeInteger_free(asn_TYPE_descriptor_t *td, void *ptr, int contents_only) {

	if(!td || !ptr)
		return;

	__LIBFAST__ASN_DEBUG("Freeing %s as INTEGER (%d, %p, Native)",
		td->name, contents_only, ptr);

	if(!contents_only) {
		FREEMEM(ptr);
	}
}

