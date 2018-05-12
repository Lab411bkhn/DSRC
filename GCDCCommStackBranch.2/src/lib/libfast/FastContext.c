/*
 * $Id: FastContext.c $
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
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "CALMime"
 * 	found in "29281.asn"
 * 	`asn1c -fnative-types -fcompound-names -fskeletons-copy`
 */

#include <asn_internal.h>

#include "FastContext.h"

static asn_TYPE_member_t asn_MBR_FastContext_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct FastContext, serviceID),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_ServiceID,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"serviceID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FastContext, contextData),
		(ASN_TAG_CLASS_UNIVERSAL | (4 << 2)),
		0,
		&asn_DEF_ContextData,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"contextData"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FastContext, userNWref),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NWref,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"userNWref"
		},
};
static ber_tlv_tag_t asn_DEF_FastContext_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_FastContext_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 1 }, /* serviceID at 103 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -1, 0 }, /* userNWref at 106 */
    { (ASN_TAG_CLASS_UNIVERSAL | (4 << 2)), 1, 0, 0 } /* contextData at 104 */
};
static asn_SEQUENCE_specifics_t asn_SPC_FastContext_specs_1 = {
	sizeof(struct FastContext),
	offsetof(struct FastContext, _asn_ctx),
	asn_MAP_FastContext_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_FastContext = {
	"FastContext",
	"FastContext",
	__LIBFAST__SEQUENCE_free,
	__LIBFAST__SEQUENCE_print,
	__LIBFAST__SEQUENCE_constraint,
	__LIBFAST__SEQUENCE_decode_ber,
	__LIBFAST__SEQUENCE_encode_der,
	__LIBFAST__SEQUENCE_decode_xer,
	__LIBFAST__SEQUENCE_encode_xer,
	__LIBFAST__SEQUENCE_decode_uper,
	__LIBFAST__SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_FastContext_tags_1,
	sizeof(asn_DEF_FastContext_tags_1)
		/sizeof(asn_DEF_FastContext_tags_1[0]), /* 1 */
	asn_DEF_FastContext_tags_1,	/* Same as above */
	sizeof(asn_DEF_FastContext_tags_1)
		/sizeof(asn_DEF_FastContext_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_FastContext_1,
	3,	/* Elements count */
	&asn_SPC_FastContext_specs_1	/* Additional specs */
};
