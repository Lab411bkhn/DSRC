/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Interoperability"
 * 	found in "interoperability.asn"
 * 	`asn1c -fnative-types -fcompound-names`
 */

#include <asn_internal.h>

#include "CamHeader.h"

static int
memb_sequenceNumber_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 65535)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_TYPE_member_t asn_MBR_CamHeader_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, sequenceNumber),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		memb_sequenceNumber_constraint_1,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"sequenceNumber"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, nodeID),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NodeID,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"nodeID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, nodeType),
		(ASN_TAG_CLASS_UNIVERSAL | (10 << 2)),
		0,
		&asn_DEF_NodeType,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"nodeType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, timestamp),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_Timestamp,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"timestamp"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, position),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_Position2D,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"position"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, positionVariance),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_PositionVariance,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"positionVariance"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, nodeSpeed),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_SpeedModule,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"nodeSpeed"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, nodeHeading),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_Heading,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"nodeHeading"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CamHeader, priority),
		(ASN_TAG_CLASS_UNIVERSAL | (10 << 2)),
		0,
		&asn_DEF_Priority,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"priority"
		},
};
static ber_tlv_tag_t asn_DEF_CamHeader_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_CamHeader_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 3 }, /* sequenceNumber at 12 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, -1, 2 }, /* nodeID at 13 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 6, -2, 1 }, /* nodeSpeed at 18 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 7, -3, 0 }, /* nodeHeading at 19 */
    { (ASN_TAG_CLASS_UNIVERSAL | (10 << 2)), 2, 0, 1 }, /* nodeType at 14 */
    { (ASN_TAG_CLASS_UNIVERSAL | (10 << 2)), 8, -1, 0 }, /* priority at 21 */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 3, 0, 2 }, /* timestamp at 15 */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 4, -1, 1 }, /* position at 16 */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 5, -2, 0 } /* positionVariance at 17 */
};
static asn_SEQUENCE_specifics_t asn_SPC_CamHeader_specs_1 = {
	sizeof(struct CamHeader),
	offsetof(struct CamHeader, _asn_ctx),
	asn_MAP_CamHeader_tag2el_1,
	9,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CamHeader = {
	"CamHeader",
	"CamHeader",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_CamHeader_tags_1,
	sizeof(asn_DEF_CamHeader_tags_1)
		/sizeof(asn_DEF_CamHeader_tags_1[0]), /* 1 */
	asn_DEF_CamHeader_tags_1,	/* Same as above */
	sizeof(asn_DEF_CamHeader_tags_1)
		/sizeof(asn_DEF_CamHeader_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CamHeader_1,
	9,	/* Elements count */
	&asn_SPC_CamHeader_specs_1	/* Additional specs */
};
