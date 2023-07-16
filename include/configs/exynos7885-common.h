/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Configuration settings for the EXYNOS 7885 based boards.
 *
 * Copyright (c) 2023 Dávid Virág (virag.david003@gmail.com)
 * based on include/exynos78x0-common.h
 * Copyright (c) 2020 Dzmitry Sankouski (dsankouski@gmail.com)
 * based on include/exynos7420-common.h
 * Copyright (C) 2016 Samsung Electronics
 * Thomas Abraham <thomas.ab@samsung.com>
 *
 * TODO check stuff out more, memory is definitely weird now
 */

#ifndef __CONFIG_EXYNOS7885_COMMON_H
#define __CONFIG_EXYNOS7885_COMMON_H

#include <asm/arch/cpu.h>		/* get chip and board defs */
#include <linux/sizes.h>

/* Miscellaneous configurable options */

#define CPU_RELEASE_ADDR		secondary_boot_addr

#define CFG_SYS_BAUDRATE_TABLE \
	{9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600}

#define CFG_SYS_SDRAM_BASE		0x80000000
/* DRAM Memory Banks */
#define SDRAM_BANK_SIZE		(256UL << 20UL)	/* 256 MB */
#define PHYS_SDRAM_1		CFG_SYS_SDRAM_BASE
#define PHYS_SDRAM_1_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_2		(CFG_SYS_SDRAM_BASE + SDRAM_BANK_SIZE)
#define PHYS_SDRAM_2_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_3		(CFG_SYS_SDRAM_BASE + (2 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_3_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_4		(CFG_SYS_SDRAM_BASE + (3 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_4_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_5		(CFG_SYS_SDRAM_BASE + (4 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_5_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_6		(CFG_SYS_SDRAM_BASE + (5 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_6_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_7		(CFG_SYS_SDRAM_BASE + (6 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_7_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_8		(CFG_SYS_SDRAM_BASE + (7 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_8_SIZE	SDRAM_BANK_SIZE
//TODO 0x880000000 region?

#ifndef MEM_LAYOUT_ENV_SETTINGS
#define MEM_LAYOUT_ENV_SETTINGS \
	"bootm_size=0x10000000\0" \
	"bootm_low=0x80000000\0"
#endif

#ifndef EXYNOS_DEVICE_SETTINGS
#define EXYNOS_DEVICE_SETTINGS \
	"stdin=serial,button-kbd\0" \
	"stdout=serial,vidconsole\0" \
	"stderr=serial,vidconsole\0"
#endif

#ifndef EXYNOS_FDTFILE_SETTING
#define EXYNOS_FDTFILE_SETTING
#endif

#define CFG_EXTRA_ENV_SETTINGS \
	EXYNOS_DEVICE_SETTINGS \
	EXYNOS_FDTFILE_SETTING \
	MEM_LAYOUT_ENV_SETTINGS

#endif	/* __CONFIG_EXYNOS7885_COMMON_H */
