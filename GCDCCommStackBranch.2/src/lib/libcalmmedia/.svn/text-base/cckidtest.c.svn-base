/*
 * $Id: cckidtest.c $
 *
 * This file is part of the Low-layer CALM Management (CDDF) Library.
 * 
 * Author: Andras Takacs <andras.takacs@ramsys.hu>
 * Author: Laszlo Virag <laszlo.virag@ramsys.hu>
 *
 * Copyright 2006-2009 Ramsys Zrt
 *
 * Low-layer CALM Management (CDDF) Library is free software; you can redistribute
 * it and/or modify it under the terms of the GNU LEsser General Public
 * License as published by the Free Software Foundation; version 3 of
 * the License.
 *
 * Low-layer CALM Management (CDDF) Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Low-layer CALM Management (CDDF) Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

#include <stdio.h>
#include <netinet/ip6.h>
#include <inttypes.h>
#include <calm/calmmedia/calm.h>

int main()
{
	int ret;
    uint8_t cckid;

	ret = calm_get_cckid();
	printf("CCKID is %u (ret: %d)\n", (uint8_t)ret, ret);

    cckid = (ret + 1) % 256;

	ret = calm_set_cckid((uint8_t)cckid);
	printf("CCKID set to %u (ret: %d)\n", cckid, ret);

	ret = calm_get_cckid();
	printf("CCKID is %u (ret: %d)\n", (uint8_t)ret, ret);

	return 0;
}

