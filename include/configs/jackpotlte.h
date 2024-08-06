/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024, Dávid Virág
 *
 * Configuration for JACKPOTLTE board.
 */

#ifndef __JACKPOTLTE_H
#define __JACKPOTLTE_H

#include <configs/exynos7885-common.h>

#undef EXYNOS_DEVICE_SETTINGS
#define EXYNOS_DEVICE_SETTINGS \
	"bootmenu_0=Boot Arch Linux=setenv bootargs root=/dev/mmcblk0p19;bootm 0x89000000\0"	\
	"bootmenu_1=!!!DANGER!!! Connect UART to USB=i2c dev 1; i2c mw 0x3D 0xCA 0x48 1; i2c mw 0x3D 0xC7 0x12 1;bootmenu\0" \
	"bootmenu_2=Disconnect UART from USB=i2c dev 1; i2c mw 0x3D 0xCA 0x00 1; i2c mw 0x3D 0xC7 0x17 1;bootmenu\0" \

#endif /* __JACKPOTLTE_H */
