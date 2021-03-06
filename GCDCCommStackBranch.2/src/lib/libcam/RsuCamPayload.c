/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Interoperability"
 * 	found in "interoperability.asn"
 * 	`asn1c -fnative-types -fcompound-names`
 */

#include <asn_internal.h>

#include "RsuCamPayload.h"

static int
memb_numOfItemsInTaggedList_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 32)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_TYPE_member_t asn_MBR_RsuCamPayload_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RsuCamPayload, nearestRsu),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_NearestRsu,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"nearestRsu"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RsuCamPayload, temperature),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_Temperature,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"temperature"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RsuCamPayload, visibilityRange),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_VisibilityRange,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"visibilityRange"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RsuCamPayload, weather),
		(ASN_TAG_CLASS_UNIVERSAL | (10 << 2)),
		0,
		&asn_DEF_Weather,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"weather"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RsuCamPayload, positionCovariance),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_PositionCovariance,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"positionCovariance"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RsuCamPayload, numOfItemsInTaggedList),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		memb_numOfItemsInTaggedList_constraint_1,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"numOfItemsInTaggedList"
		},
	{ ATF_POINTER, 1, offsetof(struct RsuCamPayload, taggedList),
		(ASN_TAG_CLASS_UNIVERSAL | (4 << 2)),
		0,
		&asn_DEF_CamTaggedList,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"taggedList"
		},
};
static ber_tlv_tag_t asn_DEF_RsuCamPayload_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RsuCamPayload_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, 0, 3 }, /* temperature at 44 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -1, 2 }, /* visibilityRange at 45 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 4, -2, 1 }, /* positionCovariance at 47 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 5, -3, 0 }, /* numOfItemsInTaggedList at 48 */
    { (ASN_TAG_CLASS_UNIVERSAL | (4 << 2)), 6, 0, 0 }, /* taggedList at 49 */
    { (ASN_TAG_CLASS_UNIVERSAL | (10 << 2)), 3, 0, 0 }, /* weather at 46 */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 0, 0, 0 } /* nearestRsu at 43 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RsuCamPayload_specs_1 = {
	sizeof(struct RsuCamPayload),
	offsetof(struct RsuCamPayload, _asn_ctx),
	asn_MAP_RsuCamPayload_tag2el_1,
	7,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RsuCamPayload = {
	"RsuCamPayload",
	"RsuCamPayload",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_RsuCamPayload_tags_1,
	sizeof(asn_DEF_RsuCamPayload_tags_1)
		/sizeof(asn_DEF_RsuCamPayload_tags_1[0]), /* 1 */
	asn_DEF_RsuCamPayload_tags_1,	/* Same as above */
	sizeof(asn_DEF_RsuCamPayload_tags_1)
		/sizeof(asn_DEF_RsuCamPayload_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RsuCamPayload_1,
	7,	/* Elements count */
	&asn_SPC_RsuCamPayload_specs_1	/* Additional specs */
};

