/*
 * $Id: asn_codecs_prim.c $
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
 * Copyright (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.h>
#include <asn_codecs_prim.h>
#include <errno.h>

/*
 * Decode an always-primitive type.
 */
asn_dec_rval_t
__LIBFAST__ber_decode_primitive(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **sptr, const void *buf_ptr, size_t size, int tag_mode) {
	ASN__PRIMITIVE_TYPE_t *st = (ASN__PRIMITIVE_TYPE_t *)*sptr;
	asn_dec_rval_t rval;
	ber_tlv_len_t length;

	/*
	 * If the structure is not there, allocate it.
	 */
	if(st == NULL) {
		st = (ASN__PRIMITIVE_TYPE_t *)CALLOC(1, sizeof(*st));
		if(st == NULL) _ASN_DECODE_FAILED;
		*sptr = (void *)st;
	}

	__LIBFAST__ASN_DEBUG("Decoding %s as plain primitive (tm=%d)",
		td->name, tag_mode);

	/*
	 * Check tags and extract value length.
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

	st->size = (int)length;
	/* The following better be optimized away. */
	if(sizeof(st->size) != sizeof(length)
			&& (ber_tlv_len_t)st->size != length) {
		st->size = 0;
		_ASN_DECODE_FAILED;
	}

	st->buf = (uint8_t *)MALLOC(length + 1);
	if(!st->buf) {
		st->size = 0;
		_ASN_DECODE_FAILED;
	}

	memcpy(st->buf, buf_ptr, length);
	st->buf[length] = '\0';		/* Just in case */

	rval.code = RC_OK;
	rval.consumed += length;

	__LIBFAST__ASN_DEBUG("Took %ld/%ld bytes to encode %s",
		(long)rval.consumed,
		(long)length, td->name);

	return rval;
}

/*
 * Encode an always-primitive type using DER.
 */
asn_enc_rval_t
__LIBFAST__der_encode_primitive(asn_TYPE_descriptor_t *td, void *sptr,
	int tag_mode, ber_tlv_tag_t tag,
	asn_app_consume_bytes_f *cb, void *app_key) {
	asn_enc_rval_t erval;
	ASN__PRIMITIVE_TYPE_t *st = (ASN__PRIMITIVE_TYPE_t *)sptr;

	__LIBFAST__ASN_DEBUG("%s %s as a primitive type (tm=%d)",
		cb?"Encoding":"Estimating", td->name, tag_mode);

	erval.encoded = __LIBFAST__der_write_tags(td, st->size, tag_mode, 0, tag,
		cb, app_key);
	__LIBFAST__ASN_DEBUG("%s wrote tags %d", td->name, (int)erval.encoded);
	if(erval.encoded == -1) {
		erval.failed_type = td;
		erval.structure_ptr = sptr;
		return erval;
	}

	if(cb && st->buf) {
		if(cb(st->buf, st->size, app_key) < 0) {
			erval.encoded = -1;
			erval.failed_type = td;
			erval.structure_ptr = sptr;
			return erval;
		}
	} else {
		assert(st->buf || st->size == 0);
	}

	erval.encoded += st->size;
	_ASN_ENCODED_OK(erval);
}

void
__LIBFAST__ASN__PRIMITIVE_TYPE_free(asn_TYPE_descriptor_t *td, void *sptr,
		int contents_only) {
	ASN__PRIMITIVE_TYPE_t *st = (ASN__PRIMITIVE_TYPE_t *)sptr;

	if(!td || !sptr)
		return;

	__LIBFAST__ASN_DEBUG("Freeing %s as a primitive type", td->name);

	if(st->buf)
		FREEMEM(st->buf);

	if(!contents_only)
		FREEMEM(st);
}


/*
 * Local internal type passed around as an argument.
 */
struct xdp_arg_s {
	asn_TYPE_descriptor_t *type_descriptor;
	void *struct_key;
	xer_primitive_body_decoder_f *prim_body_decoder;
	int decoded_something;
	int want_more;
};


static int
__LIBFAST__xer_decode__unexpected_tag(void *key, const void *chunk_buf, size_t chunk_size) {
	struct xdp_arg_s *arg = (struct xdp_arg_s *)key;
	enum xer_pbd_rval bret;

	if(arg->decoded_something) {
		if(__LIBFAST__xer_is_whitespace(chunk_buf, chunk_size))
			return 0;	/* Skip it. */
		/*
		 * Decoding was done once already. Prohibit doing it again.
		 */
		return -1;
	}

	bret = arg->prim_body_decoder(arg->type_descriptor,
		arg->struct_key, chunk_buf, chunk_size);
	switch(bret) {
	case XPBD_SYSTEM_FAILURE:
	case XPBD_DECODER_LIMIT:
	case XPBD_BROKEN_ENCODING:
		break;
	case XPBD_BODY_CONSUMED:
		/* Tag decoded successfully */
		arg->decoded_something = 1;
		/* Fall through */
	case XPBD_NOT_BODY_IGNORE:	/* Safe to proceed further */
		return 0;
	}

	return -1;
}

static ssize_t
__LIBFAST__xer_decode__body(void *key, const void *chunk_buf, size_t chunk_size, int have_more) {
	struct xdp_arg_s *arg = (struct xdp_arg_s *)key;
	enum xer_pbd_rval bret;

	if(arg->decoded_something) {
		if(__LIBFAST__xer_is_whitespace(chunk_buf, chunk_size))
			return chunk_size;
		/*
		 * Decoding was done once already. Prohibit doing it again.
		 */
		return -1;
	}

	if(!have_more) {
		/*
		 * If we've received something like "1", we can't really
		 * tell whether it is really `1` or `123`, until we know
		 * that there is no more data coming.
		 * The have_more argument will be set to 1 once something
		 * like this is available to the caller of this callback:
		 * "1<tag_start..."
		 */
		arg->want_more = 1;
		return -1;
	}

	bret = arg->prim_body_decoder(arg->type_descriptor,
		arg->struct_key, chunk_buf, chunk_size);
	switch(bret) {
	case XPBD_SYSTEM_FAILURE:
	case XPBD_DECODER_LIMIT:
	case XPBD_BROKEN_ENCODING:
		break;
	case XPBD_BODY_CONSUMED:
		/* Tag decoded successfully */
		arg->decoded_something = 1;
		/* Fall through */
	case XPBD_NOT_BODY_IGNORE:	/* Safe to proceed further */
		return chunk_size;
	}

	return -1;
}


asn_dec_rval_t
__LIBFAST__xer_decode_primitive(asn_codec_ctx_t *opt_codec_ctx,
	asn_TYPE_descriptor_t *td,
	void **sptr,
	size_t struct_size,
	const char *opt_mname,
	const void *buf_ptr, size_t size,
	xer_primitive_body_decoder_f *prim_body_decoder
) {
	const char *xml_tag = opt_mname ? opt_mname : td->xml_tag;
	asn_struct_ctx_t s_ctx;
	struct xdp_arg_s s_arg;
	asn_dec_rval_t rc;

	/*
	 * Create the structure if does not exist.
	 */
	if(!*sptr) {
		*sptr = CALLOC(1, struct_size);
		if(!*sptr) _ASN_DECODE_FAILED;
	}

	memset(&s_ctx, 0, sizeof(s_ctx));
	s_arg.type_descriptor = td;
	s_arg.struct_key = *sptr;
	s_arg.prim_body_decoder = prim_body_decoder;
	s_arg.decoded_something = 0;
	s_arg.want_more = 0;

	rc = __LIBFAST__xer_decode_general(opt_codec_ctx, &s_ctx, &s_arg,
		xml_tag, buf_ptr, size,
		__LIBFAST__xer_decode__unexpected_tag, __LIBFAST__xer_decode__body);
	switch(rc.code) {
	case RC_OK:
		if(!s_arg.decoded_something) {
			char ch;
			__LIBFAST__ASN_DEBUG("Primitive body is not recognized, "
				"supplying empty one");
			/*
			 * Decoding opportunity has come and gone.
			 * Where's the result?
			 * Try to feed with empty body, see if it eats it.
			 */
			if(prim_body_decoder(s_arg.type_descriptor,
				s_arg.struct_key, &ch, 0)
					!= XPBD_BODY_CONSUMED) {
				/*
				 * This decoder does not like empty stuff.
				 */
				_ASN_DECODE_FAILED;
			}
		}
		break;
	case RC_WMORE:
		/*
		 * Redo the whole thing later.
		 * We don't have a context to save intermediate parsing state.
		 */
		rc.consumed = 0;
		break;
	case RC_FAIL:
		rc.consumed = 0;
		if(s_arg.want_more)
			rc.code = RC_WMORE;
		else
			_ASN_DECODE_FAILED;
		break;
	}
	return rc;
}

