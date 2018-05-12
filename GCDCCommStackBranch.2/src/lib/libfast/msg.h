/*
 * $Id: msg.h $
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

#ifndef __FAST_MSG_H__
#define __FAST_MSG_H__ 1

#include <inttypes.h>

#define AT_unknown		0 //TransportAddressType_unknown
#define AT_udpIpv4		1 //TransportAddressType_udpIpv4
#define AT_udpIpv6		2 //TransportAddressType_udpIpv6
#define AT_tcpIpv4		5 //TransportAddressType_tcpIpv4
#define AT_tcpIpv6		6 //TransportAddressType_tcpIpv6

struct fs {
    uint32_t            fs_sid;
    unsigned char *     fs_data;            //OPTIONAL, NULL to skip
    uint32_t            fs_dlen;            //   - " -
    uint8_t             fs_nwref;           //OPTIONAL, 255 to skip
    uint8_t             fs_chid;            //OPTIONALL, 0 to skip
};

extern inline void fs_p_free(struct fs *);
extern inline void fs_free(struct fs *);

struct fipa {
    unsigned char *     fipa_addr;
    uint8_t             fipa_alen;
    uint8_t             fipa_type;
};

extern inline void fipa_p_free(struct fipa *);
extern inline void fipa_free(struct fipa *);

struct fis {
    uint32_t            fis_sid;
    unsigned char *     fis_data;           //OPTIONAL, NULL to skip
    uint32_t            fis_dlen;           //   - " -
    struct fipa         fis_ipa;
    uint8_t             fis_chid;           //OPTIONALL, 0 to skip
};

extern inline void fis_p_free(struct fis *);
extern inline void fis_free(struct fis *);

struct fch {
    uint8_t             fch_id;
    uint32_t            fch_medtype;
    unsigned char *     fch_params;
    uint32_t            fch_plen;
};

extern inline void fch_p_free(struct fch *);
extern inline void fch_free(struct fch *);

struct fipp {
    unsigned char *     fipp_addr;
    uint8_t             fipp_alen;
    uint8_t             fipp_len;
};

extern inline void fipp_p_free(struct fipp *);
extern inline void fipp_free(struct fipp *);

struct fsta {
    unsigned char       fsta_sid[4];
    struct fipp *       fsta_ipp;           //OPTIONAL, 0 to skip
    uint32_t            fsta_ippnum;        //   - " -
    struct fs *         fsta_fs;            //OPTIONAl, 0 to skip
    uint32_t            fsta_fsnum;         //   - " -
    struct fis *        fsta_is;            //OPTIONAL, 0 to skip
    uint32_t            fsta_isnum;         //   - " -
    struct fch *        fsta_ch;            //OPTIONAL, 0 to skip
    uint32_t            fsta_chnum;         //   - " -
};

extern inline void fsta_p_free(struct fsta *);
extern inline void fsta_free(struct fsta *);

struct fc {
    uint32_t            fc_sid;
    unsigned char *     fc_data;
    uint32_t            fc_dlen;
    uint8_t             fc_nwref;
};

extern inline void fc_p_free(struct fc *);
extern inline void fc_free(struct fc *);

struct fic {
    uint32_t            fic_sid;
    unsigned char *     fic_data;
    uint32_t            fic_dlen;
    struct fipa         fic_ipa;
};

extern inline void fic_p_free(struct fic *);
extern inline void fic_free(struct fic *);

struct fstc {
    unsigned char       fstc_sid[4];
    struct fipp *       fstc_ipp;           //OPTIONAL, 0 to skip
    uint32_t            fstc_ippnum;        //   - " -
    struct fc *         fstc_fc;            //OPTIONAL, 0 to skip
    uint32_t            fstc_fcnum;         //   - " -
    struct fic *        fstc_ic;            //OPTIONAL, 0 to skip
    uint32_t            fstc_icnum;         //   - " -
};

extern inline void fstc_p_free(struct fstc *);
extern inline void fstc_free(struct fstc *);

#define FAST_ERR_STA_BUF            1
#define FAST_ERR_STA_NOMEM          2
#define FAST_ERR_STA_EMPTY          3
#define FAST_ERR_STA_SERVERID       4
#define FAST_ERR_STA_PREFIX         5
#define FAST_ERR_STA_SID            6
#define FAST_ERR_STA_NWREF          7
#define FAST_ERR_STA_IPADDR         8
#define FAST_ERR_STA_IPTYPE         9
#define FAST_ERR_STA_DATA           10
#define FAST_ERR_STA_CHID           11
#define FAST_ERR_STA_MEDTYPE        12
#define FAST_ERR_STA_CHPARAMS       13
#define FAST_ERR_STA_CHUNUSED       14
#define FAST_ERR_STA_CONSTRAINTS    15
#define FAST_ERR_STA_BLEN           16
#define FAST_ERR_STA_ENCODE         17
#define FAST_ERR_STA_DECODE         18
#define FAST_ERR_STA_MSGTYPE        19

int fast_create_sta(struct fsta *, unsigned char[], size_t);
int fast_get_sta(struct fsta *, unsigned char[], size_t);

#define FAST_ERR_STC_BUF            101
#define FAST_ERR_STC_NOMEM          102
#define FAST_ERR_STC_EMPTY          103
#define FAST_ERR_STC_CLIENTID       104
#define FAST_ERR_STC_PREFIX         105
#define FAST_ERR_STC_SID            106
#define FAST_ERR_STC_NWREF          107
#define FAST_ERR_STC_IPADDR         108
#define FAST_ERR_STC_IPTYPE         109
#define FAST_ERR_STC_DATA           110
#define FAST_ERR_STC_CONSTRAINTS    111
#define FAST_ERR_STC_BLEN           112
#define FAST_ERR_STC_ENCODE         113
#define FAST_ERR_STC_DECODE         114
#define FAST_ERR_STC_MSGTYPE        115

int fast_create_stc(struct fstc *, unsigned char[], size_t);
int fast_get_stc(struct fstc *, unsigned char[], size_t);

#define FAST_ERR_RX_BUF             201
#define FAST_ERR_RX_NOMEM           202
#define FAST_ERR_RX_EMPTY           203
#define FAST_ERR_RX_DATA            204
#define FAST_ERR_RX_CONSTRAINTS     205
#define FAST_ERR_RX_BLEN            206
#define FAST_ERR_RX_ENCODE          207
#define FAST_ERR_RX_DECODE          208
#define FAST_ERR_RX_MSGTYPE         209
#define FAST_ERR_RX_MSGCNT          210

int fast_create_req(unsigned char *, size_t, uint8_t, uint8_t, unsigned char[], size_t);
int fast_get_req(unsigned char *, size_t, uint8_t *, uint8_t *, unsigned char[], size_t);

int fast_create_resp(unsigned char *, size_t, uint8_t, unsigned char[], size_t);
int fast_get_resp(unsigned char *, size_t, uint8_t *, unsigned char[], size_t);

#endif

