/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Interoperability"
 * 	found in "interoperability.asn"
 * 	`asn1c -fnative-types -fcompound-names`
 */

#ifndef	_VehicleCamPayload_H_
#define	_VehicleCamPayload_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Elevation.h"
#include "VehicleType.h"
#include "VehicleSize.h"
#include "LongitudinalAcceleration.h"
#include "YawRate.h"
#include "ExteriorLights.h"
#include "AccelerationControl.h"
#include "IncompleteCovarianceMatrix.h"
#include <NativeInteger.h>
#include "CamTaggedList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VehicleCamPayload */
typedef struct VehicleCamPayload {
	Elevation_t	 vehicleElevation;
	VehicleType_t	 vehicleType;
	VehicleSize_t	 vehicleSize;
	LongitudinalAcceleration_t	 longitudinalAcceleration;
	YawRate_t	 yawRate;
	ExteriorLights_t	 exteriorLights;
	AccelerationControl_t	 accelerationControl;
	IncompleteCovarianceMatrix_t	 covarianceMatrix;
	long	 numOfItemsInTaggedList;
	CamTaggedList_t	*taggedList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehicleCamPayload_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleCamPayload;

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleCamPayload_H_ */
