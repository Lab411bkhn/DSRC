/*
 * $Id: xer_support.h $
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
 * Copyright (c) 2003, 2004 X/IO Labs, xiolabs.com.
 * Copyright (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_XER_SUPPORT_H_
#define	_XER_SUPPORT_H_

#include <asn_system.h>		/* Platform-specific types */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Types of data transferred to the application.
 */
typedef enum {
	PXML_TEXT,	/* Plain text between XML tags. */
	PXML_TAG,	/* A tag, starting with '<'. */
	PXML_COMMENT,	/* An XML comment, including "<!--" and "-->". */
	/* 
	 * The following chunk types are reported if the chunk
	 * terminates the specified XML element.
	 */
	PXML_TAG_END,		/* Tag ended */
	PXML_COMMENT_END	/* Comment ended */
} pxml_chunk_type_e;

/*
 * Callback function that is called by the parser when parsed data is
 * available. The _opaque is the pointer to a field containing opaque user 
 * data specified in pxml_create() call. The chunk type is _type and the text 
 * data is the piece of buffer identified by _bufid (as supplied to
 * pxml_feed() call) starting at offset _offset and of _size bytes size. 
 * The chunk is NOT '\0'-terminated.
 */
typedef int (pxml_callback_f)(pxml_chunk_type_e _type,
	const void *_chunk_data, size_t _chunk_size, void *_key);

/*
 * Parse the given buffer as it were a chunk of XML data.
 * Invoke the specified callback each time the meaninful data is found.
 * This function returns number of bytes consumed from the bufer.
 * It will always be lesser than or equal to the specified _size.
 * The next invocation of this function must account the difference.
 */
ssize_t __LIBFAST__pxml_parse(int *_stateContext, const void *_buf, size_t _size,
	pxml_callback_f *cb, void *_key);

#ifdef __cplusplus
}
#endif

#endif	/* _XER_SUPPORT_H_ */
