/*
 * $Id: asn_SEQUENCE_OF.c $
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
#include <asn_SEQUENCE_OF.h>

typedef A_SEQUENCE_OF(void) asn_sequence;

void
__LIBFAST__asn_sequence_del(void *asn_sequence_of_x, int number, int _do_free) {
	asn_sequence *as = (asn_sequence *)asn_sequence_of_x;

	if(as) {
		void *ptr;
		int n;

		if(number < 0 || number >= as->count)
			return;	/* Nothing to delete */

		if(_do_free && as->free) {
			ptr = as->array[number];
		} else {
			ptr = 0;
		}

		/*
		 * Shift all elements to the left to hide the gap.
		 */
		--as->count;
		for(n = number; n < as->count; n++)
			as->array[n] = as->array[n+1];

		/*
		 * Invoke the third-party function only when the state
		 * of the parent structure is consistent.
		 */
		if(ptr) as->free(ptr);
	}
}

