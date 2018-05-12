/*
 * $Id: mng.h $
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

#ifndef __LIBFAST_MNG_H
#define __LIBFAST_MNG_H 1

#include <inttypes.h>

/**
 * Get inter CCK device
 *
 * @dev Device name buffer
 * @devlen Length of device buffer
 *
 * @return error code
 */
int fast_get_icck_dev(char * dev, size_t * devlen);

/**
 * Set inter CCK device
 *
 * @dev Device name buffer
 * @devlen Length of device buffer
 *
 * @return error code
 */
int fast_set_icck_dev(char * dev, size_t devlen);

/**
 * Get timeout of FFWT's remote entries.
 *
 * @return timeout or -1
 */
int fast_get_ffwt_rem_to();

/**
 * Set timeout of FFWT's remote entries.
 *
 * @to Timeout
 *
 * @return error code
 */
int fast_set_ffwt_rem_to(uint32_t to);

/**
 * Get default timeout of FFWT's native entries.
 *
 * @return timeout or -1
 */
int fast_get_ffwt_default_to();

/**
 * Set default timeout of FFWT's native entries.
 *
 * @to Timeout
 *
 * @return error code
 */
int fast_set_ffwt_default_to(uint32_t to);

/**
 * Get cleanup interval of FFWT entries.
 *
 * @return timeout or -1
 */
int fast_get_ffwt_cleanup_tv();

/**
 * Set cleanup interval of FFWT entries.
 *
 * @tv Timeout
 *
 * @return error code
 */
int fast_set_ffwt_cleanup_tv(uint32_t tv);

/**
 * Get router behaviour.
 *
 * @return 1 if router, 0 if not, or -1
 */
int fast_get_router();

/**
 * Set router behaviour.
 *
 * @is_router 1 if rourer, 0 if not
 *
 * @return error code
 */
int fast_set_router(int is_router);

/**
 * Get groupcast broadcast forwarding.
 *
 * @return 1 if enabled, 0 if not, or -1
 */
int fast_get_gmbcfw();

/**
 * Set groupcaset broadcast forwarding.
 *
 * @enabled 1 if yes, 0 if not
 *
 * @return error code
 */
int fast_set_gmbcfw(int enabled);

#endif

