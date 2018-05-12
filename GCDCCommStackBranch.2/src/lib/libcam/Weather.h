/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Interoperability"
 * 	found in "interoperability.asn"
 * 	`asn1c -fnative-types -fcompound-names`
 */

#ifndef	_Weather_H_
#define	_Weather_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Weather {
	Weather_other	= 1,
	Weather_unknown	= 2,
	Weather_noPrecipitation	= 3,
	Weather_unidentifiedSlight	= 4,
	Weather_unidentifiedModerate	= 5,
	Weather_unidentifiedHeavy	= 6,
	Weather_snowSlight	= 7,
	Weather_snowModerate	= 8,
	Weather_snowHeavy	= 9,
	Weather_rainSlight	= 10,
	Weather_rainModerate	= 11,
	Weather_rainHeavy	= 12,
	Weather_frozenPrecipitationSlight	= 13,
	Weather_frozenPrecipitationModerate	= 14,
	Weather_frozenPrecipitationHeavy	= 15
} e_Weather;

/* Weather */
typedef long	 Weather_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Weather;
asn_struct_free_f Weather_free;
asn_struct_print_f Weather_print;
asn_constr_check_f Weather_constraint;
ber_type_decoder_f Weather_decode_ber;
der_type_encoder_f Weather_encode_der;
xer_type_decoder_f Weather_decode_xer;
xer_type_encoder_f Weather_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _Weather_H_ */