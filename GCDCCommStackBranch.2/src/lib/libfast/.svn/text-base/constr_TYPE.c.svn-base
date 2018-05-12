/*
 * $Id: constr_TYPE.c $
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
 * Copyright (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.h>
#include <constr_TYPE.h>
#include <errno.h>

/*
 * Version of the ASN.1 infrastructure shipped with compiler.
 */
int __LIBFAST__get_asn1c_environment_version() { return ASN1C_ENVIRONMENT_VERSION; }

static asn_app_consume_bytes_f __LIBFAST___print2fp;

/*
 * Return the outmost tag of the type.
 */
ber_tlv_tag_t
__LIBFAST__asn_TYPE_outmost_tag(asn_TYPE_descriptor_t *type_descriptor,
		const void *struct_ptr, int tag_mode, ber_tlv_tag_t tag) {

	if(tag_mode)
		return tag;

	if(type_descriptor->tags_count)
		return type_descriptor->tags[0];

	return type_descriptor->outmost_tag(type_descriptor, struct_ptr, 0, 0);
}

/*
 * Print the target language's structure in human readable form.
 */
int
__LIBFAST__asn_fprint(FILE *stream, asn_TYPE_descriptor_t *td, const void *struct_ptr) {
	if(!stream) stream = stdout;
	if(!td || !struct_ptr) {
		errno = EINVAL;
		return -1;
	}

	/* Invoke type-specific printer */
	if(td->print_struct(td, struct_ptr, 1, __LIBFAST___print2fp, stream))
		return -1;

	/* Terminate the output */
	if(__LIBFAST___print2fp("\n", 1, stream))
		return -1;

	return fflush(stream);
}

/* Dump the data into the specified stdio stream */
static int
__LIBFAST___print2fp(const void *buffer, size_t size, void *app_key) {
	FILE *stream = (FILE *)app_key;

	if(fwrite(buffer, 1, size, stream) != size)
		return -1;

	return 0;
}


/*
 * Some compilers do not support variable args macros.
 * This function is a replacement of __LIBFAST__ASN_DEBUG() macro.
 */
void __LIBFAST__ASN_DEBUG_f(const char *fmt, ...);
void __LIBFAST__ASN_DEBUG_f(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}
