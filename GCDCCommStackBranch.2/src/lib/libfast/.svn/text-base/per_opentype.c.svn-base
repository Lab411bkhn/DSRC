/*
 * $Id: per_opentype.c $
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

/*
 * Copyright (c) 2007 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.h>
#include <per_support.h>
#include <constr_TYPE.h>
#include <per_opentype.h>

typedef struct uper_ugot_key {
	asn_per_data_t oldpd;	/* Old per data source */
	size_t unclaimed;
	size_t ot_moved;	/* Number of bits moved by OT processing */
	int repeat;
} uper_ugot_key;

static int __LIBFAST__uper_ugot_refill(asn_per_data_t *pd);
static int __LIBFAST__per_skip_bits(asn_per_data_t *pd, int skip_nbits);
static asn_dec_rval_t __LIBFAST__uper_sot_suck(asn_codec_ctx_t *, asn_TYPE_descriptor_t *td, asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd);

int asn_debug_indent;

/*
 * Encode an "open type field".
 * #10.1, #10.2
 */
int
__LIBFAST__uper_open_type_put(asn_TYPE_descriptor_t *td, asn_per_constraints_t *constraints, void *sptr, asn_per_outp_t *po) {
	void *buf;
	void *bptr;
	ssize_t size;
	size_t toGo;

	__LIBFAST__ASN_DEBUG("Open type put %s ...", td->name);

	size = __LIBFAST__uper_encode_to_new_buffer(td, constraints, sptr, &buf);
	if(size <= 0) return -1;

	for(bptr = buf, toGo = size; toGo;) {
		ssize_t maySave = __LIBFAST__uper_put_length(po, toGo);
		if(maySave < 0) break;
		if(__LIBFAST__per_put_many_bits(po, bptr, maySave * 8)) break;
		bptr = (char *)bptr + maySave;
		toGo -= maySave;
	}

	FREEMEM(buf);
	if(toGo) return -1;

	__LIBFAST__ASN_DEBUG("Open type put %s of length %d + overhead (1byte?)",
		td->name, size);

	return 0;
}

static asn_dec_rval_t
__LIBFAST__uper_open_type_get_simple(asn_codec_ctx_t *ctx, asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd) {
	asn_dec_rval_t rv;
	ssize_t chunk_bytes;
	int repeat;
	uint8_t *buf = 0;
	size_t bufLen = 0;
	size_t bufSize = 0;
	asn_per_data_t spd;
	size_t padding;

	__LIBFAST___ASN_STACK_OVERFLOW_CHECK(ctx);

	__LIBFAST__ASN_DEBUG("Getting open type %s...", td->name);

	do {
		chunk_bytes = __LIBFAST__uper_get_length(pd, -1, &repeat);
		if(chunk_bytes < 0) {
			FREEMEM(buf);
			_ASN_DECODE_STARVED;
		}
		if(bufLen + chunk_bytes > bufSize) {
			void *ptr;
			bufSize = chunk_bytes + (bufSize << 2);
			ptr = REALLOC(buf, bufSize);
			if(!ptr) {
				FREEMEM(buf);
				_ASN_DECODE_FAILED;
			}
			buf = ptr;
		}
		if(__LIBFAST__per_get_many_bits(pd, buf + bufLen, 0, chunk_bytes << 3)) {
			FREEMEM(buf);
			_ASN_DECODE_STARVED;
		}
		bufLen += chunk_bytes;
	} while(repeat);

	__LIBFAST__ASN_DEBUG("Getting open type %s encoded in %d bytes", td->name,
		bufLen);

	memset(&spd, 0, sizeof(spd));
	spd.buffer = buf;
	spd.nbits = bufLen << 3;

	asn_debug_indent += 4;
	rv = td->uper_decoder(ctx, td, constraints, sptr, &spd);
	asn_debug_indent -= 4;

	if(rv.code == RC_OK) {
		/* Check padding validity */
		padding = spd.nbits - spd.nboff;
		if(padding < 8 && __LIBFAST__per_get_few_bits(&spd, padding) == 0) {
			/* Everything is cool */
			FREEMEM(buf);
			return rv;
		}
		FREEMEM(buf);
		if(padding >= 8) {
			__LIBFAST__ASN_DEBUG("Too large padding %d in open type", padding);
			_ASN_DECODE_FAILED;
		} else {
			__LIBFAST__ASN_DEBUG("Non-zero padding");
			_ASN_DECODE_FAILED;
		}
	} else {
		FREEMEM(buf);
		/* rv.code could be RC_WMORE, nonsense in this context */
		rv.code = RC_FAIL; /* Noone would give us more */
	}

	return rv;
}

static asn_dec_rval_t GCC_NOTUSED
__LIBFAST__uper_open_type_get_complex(asn_codec_ctx_t *ctx, asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd) {
	uper_ugot_key arg;
	asn_dec_rval_t rv;
	ssize_t padding;

	__LIBFAST___ASN_STACK_OVERFLOW_CHECK(ctx);

	__LIBFAST__ASN_DEBUG("Getting open type %s from %s", td->name,
		__LIBFAST__per_data_string(pd));
	arg.oldpd = *pd;
	arg.unclaimed = 0;
	arg.ot_moved = 0;
	arg.repeat = 1;
	pd->refill = __LIBFAST__uper_ugot_refill;
	pd->refill_key = &arg;
	pd->nbits = pd->nboff;	/* 0 good bits at this point, will refill */
	pd->moved = 0;	/* This now counts the open type size in bits */

	asn_debug_indent += 4;
	rv = td->uper_decoder(ctx, td, constraints, sptr, pd);
	asn_debug_indent -= 4;

#define	UPDRESTOREPD	do {						\
	/* buffer and nboff are valid, preserve them. */		\
	pd->nbits = arg.oldpd.nbits - (pd->moved - arg.ot_moved);	\
	pd->moved = arg.oldpd.moved + (pd->moved - arg.ot_moved);	\
	pd->refill = arg.oldpd.refill;					\
	pd->refill_key = arg.oldpd.refill_key;				\
  } while(0)

	if(rv.code != RC_OK) {
		UPDRESTOREPD;
		return rv;
	}

	__LIBFAST__ASN_DEBUG("OpenType %s pd%s old%s unclaimed=%d, repeat=%d"
		, td->name,
		__LIBFAST__per_data_string(pd),
		__LIBFAST__per_data_string(&arg.oldpd),
		arg.unclaimed, arg.repeat);

	padding = pd->moved % 8;
	if(padding) {
		int32_t pvalue;
		if(padding > 7) {
			__LIBFAST__ASN_DEBUG("Too large padding %d in open type",
				padding);
			rv.code = RC_FAIL;
			UPDRESTOREPD;
			return rv;
		}
		padding = 8 - padding;
		__LIBFAST__ASN_DEBUG("Getting padding of %d bits", padding);
		pvalue = __LIBFAST__per_get_few_bits(pd, padding);
		switch(pvalue) {
		case -1:
			__LIBFAST__ASN_DEBUG("Padding skip failed");
			UPDRESTOREPD;
			_ASN_DECODE_STARVED;
		case 0: break;
		default:
			__LIBFAST__ASN_DEBUG("Non-blank padding (%d bits 0x%02x)",
				padding, (int)pvalue);
			UPDRESTOREPD;
			_ASN_DECODE_FAILED;
		}
	}
	if(pd->nboff != pd->nbits) {
		__LIBFAST__ASN_DEBUG("Open type %s overhead pd%s old%s", td->name,
			__LIBFAST__per_data_string(pd), __LIBFAST__per_data_string(&arg.oldpd));
		if(1) {
			UPDRESTOREPD;
			_ASN_DECODE_FAILED;
		} else {
			arg.unclaimed += pd->nbits - pd->nboff;
		}
	}

	/* Adjust pd back so it points to original data */
	UPDRESTOREPD;

	/* Skip data not consumed by the decoder */
	if(arg.unclaimed) __LIBFAST__ASN_DEBUG("Getting unclaimed %d", arg.unclaimed);
	if(arg.unclaimed) {
		switch(__LIBFAST__per_skip_bits(pd, arg.unclaimed)) {
		case -1:
			__LIBFAST__ASN_DEBUG("Claim of %d failed", arg.unclaimed);
			_ASN_DECODE_STARVED;
		case 0:
			__LIBFAST__ASN_DEBUG("Got claim of %d", arg.unclaimed);
			break;
		default:
			/* Padding must be blank */
			__LIBFAST__ASN_DEBUG("Non-blank unconsumed padding");
			_ASN_DECODE_FAILED;
		}
		arg.unclaimed = 0;
	}

	if(arg.repeat) {
		__LIBFAST__ASN_DEBUG("Not consumed the whole thing");
		rv.code = RC_FAIL;
		return rv;
	}

	return rv;
}


asn_dec_rval_t
__LIBFAST__uper_open_type_get(asn_codec_ctx_t *ctx, asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd) {

	return __LIBFAST__uper_open_type_get_simple(ctx, td, constraints,
		sptr, pd);

}

int
__LIBFAST__uper_open_type_skip(asn_codec_ctx_t *ctx, asn_per_data_t *pd) {
	asn_TYPE_descriptor_t s_td;
	asn_dec_rval_t rv;

	s_td.name = "<unknown extension>";
	s_td.uper_decoder = __LIBFAST__uper_sot_suck;

	rv = __LIBFAST__uper_open_type_get(ctx, &s_td, 0, 0, pd);
	if(rv.code != RC_OK)
		return -1;
	else
		return 0;
}

/*
 * Internal functions.
 */

static asn_dec_rval_t
__LIBFAST__uper_sot_suck(asn_codec_ctx_t *ctx, asn_TYPE_descriptor_t *td,
	asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd) {
	asn_dec_rval_t rv;

	(void)ctx;
	(void)td;
	(void)constraints;
	(void)sptr;

	while(__LIBFAST__per_get_few_bits(pd, 24) >= 0);

	rv.code = RC_OK;
	rv.consumed = pd->moved;

	return rv;
}

static int
__LIBFAST__uper_ugot_refill(asn_per_data_t *pd) {
	uper_ugot_key *arg = pd->refill_key;
	ssize_t next_chunk_bytes, next_chunk_bits;
	ssize_t avail;

	asn_per_data_t *oldpd = &arg->oldpd;

	__LIBFAST__ASN_DEBUG("REFILLING pd->moved=%d, oldpd->moved=%d",
		pd->moved, oldpd->moved);

	/* Advance our position to where pd is */
	oldpd->buffer = pd->buffer;
	oldpd->nboff  = pd->nboff;
	oldpd->nbits -= pd->moved - arg->ot_moved;
	oldpd->moved += pd->moved - arg->ot_moved;
	arg->ot_moved = pd->moved;

	if(arg->unclaimed) {
		/* Refill the container */
		if(__LIBFAST__per_get_few_bits(oldpd, 1))
			return -1;
		if(oldpd->nboff == 0) {
			assert(0);
			return -1;
		}
		pd->buffer = oldpd->buffer;
		pd->nboff = oldpd->nboff - 1;
		pd->nbits = oldpd->nbits;
		__LIBFAST__ASN_DEBUG("UNCLAIMED <- return from (pd->moved=%d)", pd->moved);
		return 0;
	}

	if(!arg->repeat) {
		__LIBFAST__ASN_DEBUG("Want more but refill doesn't have it");
		return -1;
	}

	next_chunk_bytes = __LIBFAST__uper_get_length(oldpd, -1, &arg->repeat);
	__LIBFAST__ASN_DEBUG("Open type LENGTH %d bytes at off %d, repeat %d",
		next_chunk_bytes, oldpd->moved, arg->repeat);
	if(next_chunk_bytes < 0) return -1;
	if(next_chunk_bytes == 0) {
		pd->refill = 0;	/* No more refills, naturally */
		assert(!arg->repeat);	/* Implementation guarantee */
	}
	next_chunk_bits = next_chunk_bytes << 3;
	avail = oldpd->nbits - oldpd->nboff;
	if(avail >= next_chunk_bits) {
		pd->nbits = oldpd->nboff + next_chunk_bits;
		arg->unclaimed = 0;
		__LIBFAST__ASN_DEBUG("!+Parent frame %d bits, alloting %d [%d..%d] (%d)",
			next_chunk_bits, oldpd->moved,
			oldpd->nboff, oldpd->nbits,
			oldpd->nbits - oldpd->nboff);
	} else {
		pd->nbits = oldpd->nbits;
		arg->unclaimed = next_chunk_bits - avail;
		__LIBFAST__ASN_DEBUG("!-Parent frame %d, require %d, will claim %d", avail, next_chunk_bits, arg->unclaimed);
	}
	pd->buffer = oldpd->buffer;
	pd->nboff = oldpd->nboff;
	__LIBFAST__ASN_DEBUG("Refilled pd%s old%s",
		__LIBFAST__per_data_string(pd), __LIBFAST__per_data_string(oldpd));
	return 0;
}

static int
__LIBFAST__per_skip_bits(asn_per_data_t *pd, int skip_nbits) {
	int hasNonZeroBits = 0;
	while(skip_nbits > 0) {
		int skip;
		if(skip_nbits < skip)
			skip = skip_nbits;
		else
			skip = 24;
		skip_nbits -= skip;

		switch(__LIBFAST__per_get_few_bits(pd, skip)) {
		case -1: return -1;	/* Starving */
		case 0: continue;	/* Skipped empty space */
		default: hasNonZeroBits = 1; continue;
		}
	}
	return hasNonZeroBits;
}
