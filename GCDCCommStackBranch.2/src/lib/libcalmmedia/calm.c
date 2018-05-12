/*
 * $Id: calm.c $
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

/**
 * @file calm.c
 * @brief CALM netlink interface for CALM management daemon
 */
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <net/if.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "calm.h"
#include "mininl.h"
#include <linux/calm.h>

//#define _LIBCALMMEDIA_DEBUG

#ifdef _LIBCALMMEDIA_DEBUG 
    #define debugging(...) \
        printf(__VA_ARGS__) 
#else 
    #define debugging(...)  
#endif

/*
 * Send a CALM mesage and wit / check the response
 *
 * @nl NL handle
 * @ci_id CI-ID
 * @msg CALM message to send
 * @mlen Messge len
 * @buff Pointer for the reply buffer
 * @blen Ponter for the buffer's length
 *
 * @return error code
 */
int calm_sndrcv(struct nl_handle * nl, uint32_t ci_id, unsigned char * msg, int mlen, unsigned char ** buf, int * blen)
{
	int ret = CALM_ERR_OTHER;
	struct ucred * creds = NULL;
	int counter = CALM_BADSEQ_MAX;

//	debugging("send msg.\n");
	if ( mnl_sendto(nl, msg, mlen) < 0) {
		debugging("unable to send message to the kernel.\n");
        ret = CALM_ERR_COMM;
		goto srerr;
	}

	do
	{
retry: 
//		debugging("waiting for the answer.\n");
		if ((*blen = mnl_recv(nl, NULL, buf, &creds)) < 0) {
			debugging("error in message receiving.\n");
			ret = CALM_ERR_COMM;
			goto srerr;
		}

//		debugging("check answer.\n");
		ret = mnl_checkmsg(*buf, ci_id);
		if (ret < 0) {
			if (ret == CALM_ERR_FAMILY)
				goto retry;
			else {
				debugging("error in message checking: %d\n", ret);
				goto srerr;
			}
		}

		counter--;

	} while ( (mnl_checkseq(nl, *buf)) && (counter > 0) );

	if (counter <= 0) {
		debugging("Too much message with bad sequence\n");
		ret = CALM_ERR_SEQ;
		goto srerr;
	}

	ret = 0;

srerr:
	return ret;
}

/**
 * Get parameter from a CALM device.
 *
 * @param nl netlink handle for the communication
 * @param attr CALM attribute
 * @param ci_id requested CI's id
 * @param buf communication buffer
 * @param len size of the buffer
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_get(struct nl_handle *nl, int attr, uint32_t ci_id, unsigned char **buf, int * len)
{
	unsigned char *msg = NULL;
	int msg_len = 0;
	int ret = CALM_ERR_OTHER;
	uint32_t val = 0;

//	debugging("create msg (cmd: %d, attr: %d, ci_id: 0x%x).\n", CALM_C_GET, attr, ci_id);
	if ((msg = mnl_generatemsg(CALM_C_GET, attr, &val, ci_id, &msg_len)) == NULL) {
		debugging("failed to create message.\n");
		ret = CALM_ERR_CREATE;
		goto err;
	}

	ret = calm_sndrcv(nl, ci_id, msg, msg_len, buf, len);

err:
	if (msg)
		free(msg);
	return ret;
}

/**
 * Set parameter in a CALM device.
 *
 * @param nl netlink handle for the communication
 * @param attr CALM attribute
 * @param val attribute value
 * @param ci_id requested CI's id
 * @param buf communication buffer
 * @param len size of the buffer
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_set(struct nl_handle *nl, int attr, void *val, uint32_t ci_id, unsigned char **buf, int * len)
{
	unsigned char *msg = NULL;
	int msg_len = 0;
	int ret = CALM_ERR_OTHER;

//	debugging("create msg (cmd: %d, attr: %d, ci_id: 0x%x).\n", CALM_C_SET, attr, ci_id);
	if ((msg = mnl_generatemsg(CALM_C_SET, attr, val, ci_id, &msg_len)) == NULL) {
		debugging("failed to create message.\n");
		ret = CALM_ERR_CREATE;
		goto err;
	}

	ret = calm_sndrcv(nl, ci_id, msg, msg_len, buf, len);

err:
	if (msg)
		free(msg);
	return ret;
}

/**
 * Send command to a CALM device.
 *
 * @param nl netlink handle for the communication
 * @param attr CALM attribute
 * @param val command attr value
 * @param ci_id requested CI's id
 * @param buf communication buffer
 * @param len size of the buffer
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_cmd(struct nl_handle *nl, int attr, void *val, uint32_t ci_id, unsigned char **buf, int * len)
{
	unsigned char *msg = NULL;
	int msg_len = 0;
	int ret = CALM_ERR_OTHER;

//	debugging("create msg (cmd: %d, attr: %d, ci_id: 0x%x).\n", CALM_C_CMD, attr, ci_id);
	if ((msg = mnl_generatemsg(CALM_C_CMD, attr, val, ci_id, &msg_len)) == NULL) {
		debugging("failed to create message.\n");
		ret = CALM_ERR_CREATE;
		goto err;
	}

	ret = calm_sndrcv(nl, ci_id, msg, msg_len, buf, len);

err:
	if (msg)
		free(msg);
	return ret;
}

/**
 * Free the list.
 *
 * @param list CI's list
 * @param nr number of CI
 *
 * @return Connection state (0: ok, -1: error)
 */
int calm_free(calm_ci_t **list, int nr)
{
	int i;
	calm_ci_t *ci_list = *list;

	if ((list == NULL)||(*list == NULL)||(nr <= 0)) {
		return CALM_ERR_OTHER;
	}

	for (i = 0;i < nr;i++) {
		if (ci_list[i].nr_vci) {
			free(ci_list[i].vci_list);
		}
	}
	free(*list);
	*list = NULL;
	return 0;
}

#if defined(__CALM__TEST__)
void show_ci(calm_ci_t *ci_list, int nr)
{
	int i, j, k;
	char ip[INET6_ADDRSTRLEN];

	/**
	 * show all CI
	 */
	printf(" - number of CI: %d\n", nr);
	if (nr) {
		for (i = 0;i < nr;i++) {
			printf("  - %d: 0x%08x\n", i, ci_list[i].ci_id);

			/**
			 * show list of VCIs from the current CI
			 */
			printf("    - number of VCIs: %d\n", ci_list[i].nr_vci);
			if (ci_list[i].nr_vci) {
				for (j = 0;j < ci_list[i].nr_vci;j++) {
					printf("      - VCI ID: 0x%08x\n", ci_list[i].vci_list[j].ci_id);
					printf("        - if index: %d, name: %s\n", ci_list[i].vci_list[j].if_index, ci_list[i].vci_list[j].if_name);
					printf("        - number of IPv6 address: %d\n", ci_list[i].vci_list[j].nr_ipv6addr);
					for (k = 0;k < ci_list[i].vci_list[j].nr_ipv6addr;k++)
					printf("          - %s\n",inet_ntop(AF_INET6, &ci_list[i].vci_list[j].ipv6addr[k], ip, sizeof(ip)));
				}
			}
		}
	} else {
		printf(" ! CI not found.\n");
	}
}

int main(int argc, char **argv)
{
	int groups = 0;
	int i;

	struct nl_handle *nl = mnl_handle_alloc();

	calm_ci_t *ci_list;
	int nr;

	if (argc > 1) {
		//if (strcmp(argv[1], "sdr") == 0) {
			if (mnl_connect(nl, groups) != 0)
				goto main_uc;

			uint8_t val8;
			uint32_t ci_id = atoi(argv[1]);

			if (calm_get_AUXCH(nl, ci_id, &val8))
				return 1;
			printf(" ! auxch: %u\n", val8);
			if (calm_set_AUXCH(nl, ci_id, &val8))
				return 1;
			if (calm_get_TXPWR(nl, ci_id, &val8))
				return 1;
			printf(" ! txpwr: %u\n", val8);
			if (calm_get_TXPWR(nl, ci_id, &val8))
				return 1;
			printf(" ! txpwr: %u\n", val8);

			uint32_t sec, usec;
			if (calm_get_LASTRX(nl, ci_id, &sec, &usec))
				return 1;
			printf(" ! lastrx: %lu.%lu\n", sec, usec);

			unsigned char *mac;
			int mac_len;
			if (calm_get_PEERMAC(nl, ci_id, &mac, &mac_len))
				return 1;
			printf(" ! mac_len: %d; mac_addr: ", mac_len);
			for (i = 0; i < mac_len; i++)
				printf("%02x", mac[i]);
			printf("\n");

			if (calm_get_CTRLCH(nl, ci_id, &val8))
				return 1;
			printf(" ! ctrlch: %u\n", val8);

			for (i = 0; i < 9; i++) {
				val8 = 1;
				if (calm_cmd_VCI(nl, CALM_GET_MEDID(ci_id), &val8))
					return 1;
			}
			if (calm_cmd_MONITOR(nl, ci_id, CALM_A_AUXCH, 1))
				return 1;

			mnl_close(nl);
			return 0;
		//}

main_uc:
		printf(" ! unable to connect to CALM link.\n");
		return 1;

	}

	/**
	 * Get all datas from CIs
	 */
	for (i = 1;i <= 100;i++) {
		printf("\ntry: %d\n", i);
		if (mnl_connect(nl, groups) == 0) {
			calm_get_cis(nl, &ci_list, &nr);
			show_ci(ci_list, nr);
			calm_free(&ci_list, nr);
			mnl_close(nl);
		}
		sleep(1);
	}

	mnl_handle_destroy(nl);
	return 0;
}
#endif
