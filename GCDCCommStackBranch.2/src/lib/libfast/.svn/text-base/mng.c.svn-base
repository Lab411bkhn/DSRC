/*
 * $Id: mng.c $
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

#include <sys/types.h>

#include <linux/unistd.h>
#include <linux/sysctl.h>
#include <sys/sysctl.h>

#include "mng.h"

/**
 * Get inter CCK device
 *
 * @dev Device name buffer
 * @devlen Length of device buffer
 *
 * @return error code
 */
int fast_get_icck_dev(char * dev, size_t * devlen)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_ICCKD };

    return sysctl(name, 3, dev, devlen, NULL, 0);
}

/**
 * Set inter CCK device
 *
 * @dev Device name buffer
 * @devlen Length of device buffer
 *
 * @return error code
 */
int fast_set_icck_dev(char * dev, size_t devlen)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_ICCKD };

    return sysctl(name, 3, NULL, NULL, dev, devlen);
}

/**
 * Get timeout of FFWT's remote entries.
 *
 * @return timeout or -1
 */
int fast_get_ffwt_rem_to()
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_FFWT_TO_REM };
    int to = 0;
    size_t tolen = sizeof(to);
    int ret;

    ret = sysctl(name, 3, &to, &tolen, NULL, 0);

    if (ret)
        return -1;

    return to;
}

/**
 * Set timeout of FFWT's remote entries.
 *
 * @to Timeout
 *
 * @return error code
 */
int fast_set_ffwt_rem_to(uint32_t to)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_FFWT_TO_REM };
    int toint = (int)to;

    return sysctl(name, 3, NULL, NULL, &toint, sizeof(toint));
}

/**
 * Get default timeout of FFWT's native entries.
 *
 * @return timeout or -1
 */
int fast_get_ffwt_default_to()
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_FFWT_TO_DEF };
    int to = 0;
    size_t tolen = sizeof(to);
    int ret;

    ret = sysctl(name, 3, &to, &tolen, NULL, 0);

    if (ret)
        return -1;

    return to;
}

/**
 * Set default timeout of FFWT's native entries.
 *
 * @to Timeout
 *
 * @return error code
 */
int fast_set_ffwt_default_to(uint32_t to)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_FFWT_TO_DEF };
    int toint = (int)to;

    return sysctl(name, 3, NULL, NULL, &toint, sizeof(toint));
}

/**
 * Get cleanup interval of FFWT entries.
 *
 * @return timeout or -1
 */
int fast_get_ffwt_cleanup_tv()
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_FFWT_TV_CLEAN };
    int to = 0;
    size_t tolen = sizeof(to);
    int ret;

    ret = sysctl(name, 3, &to, &tolen, NULL, 0);

    if (ret)
        return -1;

    return to;
}

/**
 * Set cleanup interval of FFWT entries.
 *
 * @tv Timeout
 *
 * @return error code
 */
int fast_set_ffwt_cleanup_tv(uint32_t tv)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_FFWT_TV_CLEAN };
    int tvint = (int)tv;

    return sysctl(name, 3, NULL, NULL, &tvint, sizeof(tvint));
}

/**
 * Get router behaviour.
 *
 * @return 1 if router, 0 if not, or -1
 */
int fast_get_router()
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_IS_ROUTER };
    int is_router = 0;
    size_t len = sizeof(is_router);
    int ret;

    ret = sysctl(name, 3, &is_router, &len, NULL, 0);

    if (ret)
        return -1;

    return is_router;
}

/**
 * Set router behaviour.
 *
 * @is_router 1 if rourer, 0 if not
 *
 * @return error code
 */
int fast_set_router(int is_router)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_IS_ROUTER };

    return sysctl(name, 3, NULL, NULL, &is_router, sizeof(is_router));
}

/**
 * Get groupcast broadcast forwarding.
 *
 * @return 1 if enabled, 0 if not, or -1
 */
int fast_get_gmbcfw()
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_GM_BC_FW };
    int enabled = 0;
    size_t len = sizeof(enabled);
    int ret;

    ret = sysctl(name, 3, &enabled, &len, NULL, 0);

    if (ret)
        return -1;

    return enabled;
}

/**
 * Set groupcaset broadcast forwarding.
 *
 * @enabled 1 if yes, 0 if not
 *
 * @return error code
 */
int fast_set_gmbcfw(int enabled)
{
    int name[] =  {CTL_NET, NET_CALM, NET_CALM_GM_BC_FW };

    return sysctl(name, 3, NULL, NULL, &enabled, sizeof(enabled));
}
