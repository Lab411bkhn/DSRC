/*
 * $Id: ServiceID.h $
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

#ifndef	_ServiceID_H_
#define	_ServiceID_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ExtensibleInteger.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ServiceID */
typedef long	 ServiceID_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ServiceID;
asn_struct_free_f __LIBFAST__ServiceID_free;
asn_struct_print_f __LIBFAST__ServiceID_print;
asn_constr_check_f __LIBFAST__ServiceID_constraint;
ber_type_decoder_f __LIBFAST__ServiceID_decode_ber;
der_type_encoder_f __LIBFAST__ServiceID_encode_der;
xer_type_decoder_f __LIBFAST__ServiceID_decode_xer;
xer_type_encoder_f __LIBFAST__ServiceID_encode_xer;
per_type_decoder_f __LIBFAST__ServiceID_decode_uper;
per_type_encoder_f __LIBFAST__ServiceID_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ServiceID_H_ */
