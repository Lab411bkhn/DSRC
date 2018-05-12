/*
 * $Id: Stc.h $
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

#ifndef	_Stc_H_
#define	_Stc_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>
#include "MessageType.h"
#include "StationID.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ServContextList;
struct IpContextList;
struct IpPrefixList;

/* Stc */
typedef struct Stc {
	BIT_STRING_t	 fill;
	MessageType_t	 messageType;
	StationID_t	 clientID;
	struct ServContextList	*servContextList	/* OPTIONAL */;
	struct IpContextList	*ipContextList	/* OPTIONAL */;
	struct IpPrefixList	*ipPrefixList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Stc_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Stc;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ServContextList.h"
#include "IpContextList.h"
#include "IpPrefixList.h"

#endif	/* _Stc_H_ */