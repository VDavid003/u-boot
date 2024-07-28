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
	return 0;
}
