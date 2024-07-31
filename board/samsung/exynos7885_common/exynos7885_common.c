// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024, Dávid Virág.
 */

#include <init.h>

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

int board_init(void)
{
#if IS_ENABLED(CONFIG_TARGET_JACKPOTLTE)
	*((uint32_t*)(0x14860070)) = 0x1281;
#endif
	return 0;
}
