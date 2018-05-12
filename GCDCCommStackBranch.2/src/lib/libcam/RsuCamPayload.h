/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Interoperability"
 * 	found in "interoperability.asn"
 * 	`asn1c -fnative-types -fcompound-names`
 */

#ifndef	_RsuCamPayload_H_
#define	_RsuCamPayload_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NearestRsu.h"
#include "Temperature.h"
#include "VisibilityRange.h"
#include "Weather.h"
#include "PositionCovariance.h"
#include <NativeInteger.h>
#include "CamTaggedList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RsuCamPayload */
typedef struct RsuCamPayload {
	NearestRsu_t	 nearestRsu;
	Temperature_t	 temperature;
	VisibilityRange_t	 visibilityRange;
	Weather_t	 weather;
	PositionCovariance_t	 positionCovariance;
	long	 numOfItemsInTaggedList;
	CamTaggedList_t	*taggedList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RsuCamPayload_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RsuCamPayload;

#ifdef __cplusplus
}
#endif

#endif	/* _RsuCamPayload_H_ */