/*
 This file is provided under a dual BSD/GPLv2 license.  When using or
 redistributing this file, you may do so under either license.

 GPL LICENSE SUMMARY

 Copyright(c) 2016 - 2017 Intel Corporation.

 This program is free software; you can redistribute it and/or modify
 it under the terms of version 2 of the GNU General Public License as
 published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 Contact Information:
  Intel Corporation
  2200 Mission College Blvd.
  Santa Clara, CA  97052

 BSD LICENSE

 Copyright(c) 2016 - 2017 Intel Corporation.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
  * Neither the name of Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


#ifndef _ETHSW_INIT_H_
#define _ETHSW_INIT_H_

#define GSW_API_MODULE_NAME "F2X SWITCH API"
#define SWAPI_DRV_VERSION "1.0.5"
/* Switch Features  */
#define CONFIG_LTQ_STP		1
#define CONFIG_LTQ_8021X	1
#define CONFIG_LTQ_MULTICAST 1
#define CONFIG_LTQ_QOS		1
#define CONFIG_LTQ_VLAN		1
#define CONFIG_LTQ_WOL		1

/* User configuration options */
#define KERNEL_MODE 1
#define WIN_PC_MODE 0
#define UART_INTERFACE 0
#define SMDIO_INTERFACE 1
#define GSW_IOCTL_SUPPORT 1

#define VLAN_MAP_TBL_SIZE 4096
#define EG_VLAN_TBL_SIZE 16
#define SVLAN_PCP_TBL_SIZE 16

/*Depends on the Kernel/OS, user can add include files*/
#if defined(KERNEL_MODE) && KERNEL_MODE
	#include <linux/init.h>
	#include <linux/module.h>
	#include <linux/kernel.h>
	#include <linux/fs.h>
	#include <linux/version.h>
	#include <linux/string.h>
	#include <linux/types.h>
	#include <linux/delay.h>
	#include <linux/slab.h>
	#include <linux/moduleparam.h>
	#include <linux/platform_device.h>
	#include <linux/of_address.h>
	#include <linux/of_platform.h>
	#include <linux/clk.h>
	#include <linux/uaccess.h>
	#include <linux/err.h>
	#include <linux/interrupt.h>
	#include <linux/switch.h>
#else
	#include <stdio.h>
	#include <stdlib.h>
	#include <memory.h>
	#include <string.h>
	#include <malloc.h>
	#include <conio.h>
	#include <signal.h>
	#include <tchar.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
	#include <ctype.h>
/*
	#include <sys/ioctl.h>
*/
#endif /* KERNEL_MODE */

#if defined(KERNEL_MODE) && KERNEL_MODE
	#define GSW_PRINT	pr_err
#else
	#define GSW_PRINT	printf
#endif

#define	PCE_ASSERT(t)	if ((t)) { \
	GSW_PRINT("%s:%s:%d (" # t ")\n", __FILE__, __func__, __LINE__); \
	return GSW_statusValueRange; }

// do nothing here
#define	SWAPI_ASSERT(t)	if ((t)) { \
	GSW_PRINT("%s:%s:%d (" # t ")\n", __FILE__, __func__, __LINE__); \
	return GSW_statusMemErr; }
/* IOCTL handling incase the OS is not supporetd */
#if defined(WIN_PC_MODE) && WIN_PC_MODE
	#define NRBITS	8
	#define TYPEBITS	8
	#define SIZEBITS	13
	#define DIRBITS	3
	#define NRMASK	((1 << NRBITS)-1)
	#define TYPEMASK	((1 << TYPEBITS)-1)
	#define SIZEMASK	((1 << SIZEBITS)-1)
	#define XSIZEMASK	((1 << (SIZEBITS+1))-1)
	#define DIRMASK	((1 << DIRBITS)-1)
	#define NRSHIFT     0
	#define TYPESHIFT	(NRSHIFT + NRBITS)
	#define SIZESHIFT	(TYPESHIFT + TYPEBITS)
	#define DIRSHIFT	(SIZESHIFT + SIZEBITS)
	#define NN	1U
	#define RD	2U
	#define WR	4U
	#define IOC(dir, type, nr, size) \
		(((dir)  << DIRSHIFT) | \
		((type) << TYPESHIFT) | \
		((nr)   << NRSHIFT) | \
		((size) << SIZESHIFT))
	#define IO(type, nr)	IOC(NN, (type), (nr), 0)
	#define IOR(type, nr, size)	IOC(RD, (type), (nr), sizeof(size))
	#define IOW(type, nr, size)	IOC(WR, (type), (nr), sizeof(size))
	#define IOWR(type, nr, size)	IOC(RD | WR, (type), (nr), sizeof(size))
	#define IO_TYPE(nr)	(((nr) >> TYPESHIFT) & TYPEMASK)
	#define NR(nr)	(((nr) >> NRSHIFT) & NRMASK)
	#define SIZE(nr)   \
		((((((nr) >> DIRSHIFT) & DIRMASK) & (WR|RD)) == 0) ? \
		0 : (((nr) >> SIZESHIFT) & XSIZEMASK))
	#define GSW_IO	IO
	#define GSW_IOW IOW
	#define GSW_IOR IOR
	#define GSW_IOWR IOWR
	#define GSW_IOC_TYPE IO_TYPE
	#define GSW_IOC_NR NR
	#define GSW_IOC_SIZE	SIZE
	/* GSW Specific Include files */
	#include "../include/f2x_swapi_kapi.h"
#else
	#define GSW_IO	_IO
	#define GSW_IOW	_IOW
	#define GSW_IOR	_IOR
	#define GSW_IOWR	_IOWR
	#define GSW_IOC_TYPE	_IOC_TYPE
	#define GSW_IOC_NR	_IOC_NR
	#define GSW_IOC_SIZE	_IOC_SIZE
	/* GSW Specific Include files */
	#include "../include/f2x_swapi_kapi.h"
#endif /* WIN_PC_MODE */

enum {
	GROUND_MODE = 0,
	POWER_MODE
};

typedef enum {
	GSW_DEV_0 = 0,
	GSW_DEV_1,
	GSW_DEV_MAX
} gsw_devtype_t;

typedef struct {
	gsw_devtype_t sdev;
	/*mdio address*/
	u8 smdio_addr;
	/* device base address*/
	u32 dev_baddr;
	/* device memory map end address*/
	u32 dev_eaddr;
	/* platform */
	u8 devid;
} ethsw_core_init_t;

int ethsw_swapi_register(void);
int ethsw_swapi_unregister(void);

#include "gsw_io_wrap.h"
#include "gsw_core.h"
#include "gsw_api_func.h"
#include "gsw_swreg.h"
#include "gsw708x_reg.h"

extern GSW_return_t gsw_reg_rd(void *pdev, u16 Offset, u16 Shift, u16 Size, ur *value);
extern GSW_return_t gsw_reg_wr(void *pdev, u16 Offset, u16 Shift, u16 Size, u32 value);
extern GSW_return_t GSW_MDIO_DataRead(void *pdev, GSW_MDIO_data_t *parm);
extern GSW_return_t GSW_MDIO_DataWrite(void *pdev, GSW_MDIO_data_t *parm);

extern int sf_intel7084_qos_register(void);
extern int sf_intel7084_qos_unregister(void);

extern struct sf_eswitch_api_t intel7084_api;

void ethsw_init_pedev0(void);
int intel7084_phy_rd(GSW_MDIO_data_t *parm);
int intel7084_phy_wr(GSW_MDIO_data_t *parm);

int intel7084_mdio_rd(u16 Offset, u16 Shift, u16 Size, ur *value);
int intel7084_mdio_wr(u16 Offset, u16 Shift, u16 Size, u32 value);

int intel7084_mmd_rd(GSW_MMD_data_t *parm);
int intel7084_mmd_wr(GSW_MMD_data_t *parm);

int intel7084_count_rd(GSW_RMON_Port_cnt_t *parm);
int intel7084_count_clear(GSW_RMON_clear_t *parm);

int intel7084_mc_ioctl (unsigned int type, unsigned long arg);
int intel7084_multicast_entry_set(u32 port, u8 type,u32 mc_ip);
int intel7084_multicast_set(void);
int intel7084_multicast_entry_get(void);

int intel7084_bridge_redirect_ip(const char *name);
int intel7084_bridge_redirect_disable(void);

#endif    /* _ETHSW_INIT_H_ */
