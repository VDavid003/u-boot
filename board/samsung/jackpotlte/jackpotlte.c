// SPDX-License-Identifier: GPL-2.0+
/*
 * Samsung JACKPOTLTE board based on Exynos 7885 SoC
 */

#include <common.h>

int exynos_init(void)
{
	// This makes S-Boot's framebuffer continue on working.
	*((int*)0x14860070) = 0x1281;
	return 0;
}
