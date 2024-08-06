/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024, Dávid Virág
 *
 * Configuration for XCOVER4S board.
 */

#ifndef __XCOVER4S_H
#define __XCOVER4S_H

#include <configs/exynos7885-common.h>

#undef EXYNOS_DEVICE_SETTINGS
#define EXYNOS_DEVICE_SETTINGS \
	"bootmenu_0=Boot Arch Linux=setenv bootargs console=ttyGS0;bootm 0x89000000\0" \
	"bootmenu_1=Connect USB to USB=i2c dev 1; i2c mw 0x3E 0x70 0x24 1; i2c mw 0x3E 0x6D 0x12 1;bootmenu\0" \
	"bootmenu_2=!!!DANGER!!! Connect UART to USB=i2c dev 1; i2c mw 0x3E 0x70 0x48 1; i2c mw 0x3E 0x6D 0x12 1;bootmenu\0" \
	"bootmenu_3=Disconnect UART from USB=i2c dev 1; i2c mw 0x3E 0x70 0x00 1; i2c mw 0x3E 0x6D 0x13 1;bootmenu\0" \

#endif /* __XCOVER4S_H */
