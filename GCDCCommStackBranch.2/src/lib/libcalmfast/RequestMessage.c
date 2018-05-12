/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "CalmFast"
 * 	found in "calmfast.asn1"
 * 	`asn1c -fnative-types -fcompound-names`
 */

#include <asn_internal.h>

#include "RequestMessage.h"

static int
memb_serial_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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

static asn_TYPE_member_t asn_MBR_payload_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.open),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OpenRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"open"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.close),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EmptyRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"close"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.send),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SendRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"send"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.publish),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PublishRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"publish"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.unpublish),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EmptyRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"unpublish"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.monitor),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EmptyRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"monitor"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage__payload, choice.unmonitor),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EmptyRequest,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"unmonitor"
		},
};
static asn_TYPE_tag2member_t asn_MAP_payload_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* open at 12 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* close at 13 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* send at 14 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* publish at 15 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* unpublish at 16 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* monitor at 17 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* unmonitor at 19 */
};
static asn_CHOICE_specifics_t asn_SPC_payload_specs_3 = {
	sizeof(struct RequestMessage__payload),
	offsetof(struct RequestMessage__payload, _asn_ctx),
	offsetof(struct RequestMessage__payload, present),
	sizeof(((struct RequestMessage__payload *)0)->present),
	asn_MAP_payload_tag2el_3,
	7,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_payload_3 = {
	"payload",
	"payload",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_payload_3,
	7,	/* Elements count */
	&asn_SPC_payload_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_RequestMessage_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage, serial),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		memb_serial_constraint_1,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"serial"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RequestMessage, payload),
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_payload_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"payload"
		},
};
static ber_tlv_tag_t asn_DEF_RequestMessage_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RequestMessage_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 0 }, /* serial at 10 */
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 1, 0, 0 }, /* open at 12 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* close at 13 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 1, 0, 0 }, /* send at 14 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 1, 0, 0 }, /* publish at 15 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 1, 0, 0 }, /* unpublish at 16 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 1, 0, 0 }, /* monitor at 17 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 1, 0, 0 } /* unmonitor at 19 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RequestMessage_specs_1 = {
	sizeof(struct RequestMessage),
	offsetof(struct RequestMessage, _asn_ctx),
	asn_MAP_RequestMessage_tag2el_1,
	8,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RequestMessage = {
	"RequestMessage",
	"RequestMessage",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_RequestMessage_tags_1,
	sizeof(asn_DEF_RequestMessage_tags_1)
		/sizeof(asn_DEF_RequestMessage_tags_1[0]), /* 1 */
	asn_DEF_RequestMessage_tags_1,	/* Same as above */
	sizeof(asn_DEF_RequestMessage_tags_1)
		/sizeof(asn_DEF_RequestMessage_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RequestMessage_1,
	2,	/* Elements count */
	&asn_SPC_RequestMessage_specs_1	/* Additional specs */
};

