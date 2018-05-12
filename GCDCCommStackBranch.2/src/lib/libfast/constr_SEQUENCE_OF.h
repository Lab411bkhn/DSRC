/*
 * $Id: constr_SEQUENCE_OF.h $
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

/*-
 * Copyright (c) 2003, 2005 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SEQUENCE_OF_H_
#define	_CONSTR_SEQUENCE_OF_H_

#include <asn_application.h>
#include <constr_SET_OF.h>		/* Implemented using SET OF */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * A set specialized functions dealing with the SEQUENCE OF type.
 * Generally implemented using SET OF.
 */
#define	SEQUENCE_OF_free	__LIBFAST__SET_OF_free
#define	SEQUENCE_OF_print	__LIBFAST__SET_OF_print
#define	SEQUENCE_OF_constraint	__LIBFAST__SET_OF_constraint
#define	SEQUENCE_OF_decode_ber	__LIBFAST__SET_OF_decode_ber
#define	SEQUENCE_OF_decode_xer	__LIBFAST__SET_OF_decode_xer
#define	SEQUENCE_OF_decode_uper	__LIBFAST__SET_OF_decode_uper
der_type_encoder_f __LIBFAST__SEQUENCE_OF_encode_der;
xer_type_encoder_f __LIBFAST__SEQUENCE_OF_encode_xer;
per_type_encoder_f __LIBFAST__SEQUENCE_OF_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CONSTR_SET_OF_H_ */
