/*
 * $Id: per_opentype.h $
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
 * Copyright (c) 2007 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_PER_OPENTYPE_H_
#define	_PER_OPENTYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

asn_dec_rval_t __LIBFAST__uper_open_type_get(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td, asn_per_constraints_t *constraints, void **sptr, asn_per_data_t *pd);

int __LIBFAST__uper_open_type_skip(asn_codec_ctx_t *opt_codec_ctx, asn_per_data_t *pd);

int __LIBFAST__uper_open_type_put(asn_TYPE_descriptor_t *td, asn_per_constraints_t *constraints, void *sptr, asn_per_outp_t *po);

#ifdef __cplusplus
}
#endif

#endif	/* _PER_OPENTYPE_H_ */
