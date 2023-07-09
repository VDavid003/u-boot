// SPDX-License-Identifier: GPL-2.0+
/*
 * Samsung JACKPOTLTE board based on Exynos 7885 SoC
 */

#include <common.h>

int exynos_init(void)
{
	// This makes S-Boot's framebuffer continue on working.
	*((int*)0x14860070) = 0x1281;

	// S-Boot checks this register and powers off if this isn't set correctly when resetting.
	*((int*)0x11c80808) = 0x12345678;
	return 0;
}
