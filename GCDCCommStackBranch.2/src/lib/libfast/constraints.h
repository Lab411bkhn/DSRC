/*
 * $Id: constraints.h $
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
 * Copyright (c) 2004, 2006 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_ASN1_CONSTRAINTS_VALIDATOR_H_
#define	_ASN1_CONSTRAINTS_VALIDATOR_H_

#include <asn_system.h>		/* Platform-dependent types */

#ifdef __cplusplus
extern "C" {
#endif

struct asn_TYPE_descriptor_s;		/* Forward declaration */

/*
 * Validate the structure according to the ASN.1 constraints.
 * If errbuf and errlen are given, they shall be pointing to the appropriate
 * buffer space and its length before calling this function. Alternatively,
 * they could be passed as NULL's. If constraints validation fails,
 * errlen will contain the actual number of bytes taken from the errbuf
 * to encode an error message (properly 0-terminated).
 * 
 * RETURN VALUES:
 * This function returns 0 in case all ASN.1 constraints are met
 * and -1 if one or more constraints were failed.
 */
int
__LIBFAST__asn_check_constraints(struct asn_TYPE_descriptor_s *type_descriptor,
	const void *struct_ptr,	/* Target language's structure */
	char *errbuf,		/* Returned error description */
	size_t *errlen		/* Length of the error description */
	);


/*
 * Generic type for constraint checking callback,
 * associated with every type descriptor.
 */
typedef int (asn_constr_check_f)(
	struct asn_TYPE_descriptor_s *type_descriptor,
	const void *struct_ptr,
	asn_app_constraint_failed_f *optional_callback,	/* Log the error */
	void *optional_app_key		/* Opaque key passed to a callback */
	);

/*******************************
 * INTERNALLY USEFUL FUNCTIONS *
 *******************************/

asn_constr_check_f __LIBFAST__asn_generic_no_constraint;	/* No constraint whatsoever */
asn_constr_check_f __LIBFAST__asn_generic_unknown_constraint; /* Not fully supported */

/*
 * Invoke the callback with a complete error message.
 */
#define	_ASN_CTFAIL	if(ctfailcb) ctfailcb

#ifdef __cplusplus
}
#endif

#endif	/* _ASN1_CONSTRAINTS_VALIDATOR_H_ */
