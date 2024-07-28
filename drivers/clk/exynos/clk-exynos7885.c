// SPDX-License-Identifier: GPL-2.0+
/*
 * Samsung Exynos7885 clock driver.
 * Copyright (c) 2024 Dávid Virág
 */

#include <dm.h>
#include <asm/io.h>
#include <dt-bindings/clock/exynos7885.h>
#include "clk.h"

enum exynos7885_cmu_id {
	CMU_TOP,
	CMU_CORE,
	CMU_PERI,
	CMU_FSYS,
};

/* ---- CMU_TOP ------------------------------------------------------------- */

/* Register Offset definitions for CMU_TOP (0x12060000) */
#define PLL_CON0_PLL_SHARED0			0x0100
#define PLL_CON0_PLL_SHARED1			0x0120
#define CLK_CON_MUX_MUX_CLKCMU_PERI_BUS		0x1058
#define CLK_CON_MUX_MUX_CLKCMU_PERI_UART0	0x1064
#define CLK_CON_MUX_MUX_CLKCMU_PERI_UART1	0x1068
#define CLK_CON_MUX_MUX_CLKCMU_PERI_UART2	0x106c
#define CLK_CON_DIV_CLKCMU_PERI_BUS		0x1874
#define CLK_CON_DIV_CLKCMU_PERI_UART0		0x1880
#define CLK_CON_DIV_CLKCMU_PERI_UART1		0x1884
#define CLK_CON_DIV_CLKCMU_PERI_UART2		0x1888
#define CLK_CON_DIV_PLL_SHARED0_DIV2		0x189c
#define CLK_CON_DIV_PLL_SHARED0_DIV3		0x18a0
#define CLK_CON_DIV_PLL_SHARED0_DIV4		0x18a4
#define CLK_CON_DIV_PLL_SHARED0_DIV5		0x18a8
#define CLK_CON_DIV_PLL_SHARED1_DIV2		0x18ac
#define CLK_CON_DIV_PLL_SHARED1_DIV3		0x18b0
#define CLK_CON_DIV_PLL_SHARED1_DIV4		0x18b4
#define CLK_CON_GAT_GATE_CLKCMUC_PERI_UART1	0x2004
#define CLK_CON_GAT_GATE_CLKCMU_PERI_BUS	0x207c
#define CLK_CON_GAT_GATE_CLKCMU_PERI_UART0	0x2088
#define CLK_CON_GAT_GATE_CLKCMU_PERI_UART2	0x208c

/* List of parent clocks for Muxes in CMU_TOP: for PURECLKCOMP */
//PNAME(mout_shared0_pll_p)	= { "clock-oscclk", "fout_shared0_pll" };
//PNAME(mout_shared1_pll_p)	= { "clock-oscclk", "fout_shared1_pll" };
/* List of parent clocks for Muxes in CMU_TOP: for CMU_PERI */
PNAME(mout_peri_bus_p)		= { "dout_shared0_div4", "dout_shared1_div4" };
PNAME(mout_peri_uart0_p)	= { "osc-clock", "dout_shared0_div4" };
PNAME(mout_peri_uart1_p)	= { "osc-clock", "dout_shared0_div4" };
PNAME(mout_peri_uart2_p)	= { "osc-clock", "dout_shared0_div4" };

/* PURECLKCOMP */

static const struct samsung_pll_clock top_pure_pll_clks[] = {
	PLL(pll_1417x, CLK_FOUT_SHARED0_PLL, "fout_shared0_pll", "osc-clock",
	    PLL_CON0_PLL_SHARED0),
	PLL(pll_1417x, CLK_FOUT_SHARED1_PLL, "fout_shared1_pll", "osc-clock",
	    PLL_CON0_PLL_SHARED1),
};

//TODO enable this after fix in mainline
static const struct samsung_mux_clock top_pure_mux_clks[] = {
//	MUX(CLK_MOUT_SHARED0_PLL, "mout_shared0_pll", mout_shared0_pll_p,
//	    PLL_CON0_PLL_SHARED0, 4, 1),
//	MUX(CLK_MOUT_SHARED1_PLL, "mout_shared1_pll", mout_shared1_pll_p,
//	    PLL_CON0_PLL_SHARED1, 4, 1),
};

static const struct samsung_div_clock top_pure_div_clks[] = {
	DIV(CLK_DOUT_SHARED0_DIV2, "dout_shared0_div2", "fout_shared0_pll",
	    CLK_CON_DIV_PLL_SHARED0_DIV2, 0, 1),
	DIV(CLK_DOUT_SHARED0_DIV3, "dout_shared0_div3", "fout_shared0_pll",
	    CLK_CON_DIV_PLL_SHARED0_DIV3, 0, 2),
	DIV(CLK_DOUT_SHARED0_DIV4, "dout_shared0_div4", "dout_shared0_div2",
	    CLK_CON_DIV_PLL_SHARED0_DIV4, 0, 1),
	DIV(CLK_DOUT_SHARED0_DIV5, "dout_shared0_div5", "fout_shared0_pll",
	    CLK_CON_DIV_PLL_SHARED0_DIV5, 0, 3),
	DIV(CLK_DOUT_SHARED1_DIV2, "dout_shared1_div2", "fout_shared1_pll",
	    CLK_CON_DIV_PLL_SHARED1_DIV2, 0, 1),
	DIV(CLK_DOUT_SHARED1_DIV3, "dout_shared1_div3", "fout_shared1_pll",
	    CLK_CON_DIV_PLL_SHARED1_DIV3, 0, 2),
	DIV(CLK_DOUT_SHARED1_DIV4, "dout_shared1_div4", "dout_shared1_div2",
	    CLK_CON_DIV_PLL_SHARED1_DIV4, 0, 1),
};

/* PERI */

static const struct samsung_mux_clock top_peri_mux_clks[] = {
	MUX(CLK_MOUT_PERI_BUS, "mout_peri_bus", mout_peri_bus_p,
	    CLK_CON_MUX_MUX_CLKCMU_PERI_BUS, 0, 1),
	MUX(CLK_MOUT_PERI_UART0, "mout_peri_uart0", mout_peri_uart0_p,
	    CLK_CON_MUX_MUX_CLKCMU_PERI_UART0, 0, 1),
	MUX(CLK_MOUT_PERI_UART1, "mout_peri_uart1", mout_peri_uart1_p,
	    CLK_CON_MUX_MUX_CLKCMU_PERI_UART1, 0, 1),
	MUX(CLK_MOUT_PERI_UART2, "mout_peri_uart2", mout_peri_uart2_p,
	    CLK_CON_MUX_MUX_CLKCMU_PERI_UART2, 0, 1),
};

static const struct samsung_gate_clock top_peri_gate_clks[] = {
	GATE(CLK_GOUT_PERI_BUS, "gout_peri_bus", "mout_peri_bus",
	     CLK_CON_GAT_GATE_CLKCMU_PERI_BUS, 21, 0, 0),
	GATE(CLK_GOUT_PERI_UART0, "gout_peri_uart0", "mout_peri_uart0",
	     CLK_CON_GAT_GATE_CLKCMU_PERI_UART0, 21, 0, 0),
	GATE(CLK_GOUT_PERI_UART1, "gout_peri_uart1", "mout_peri_uart1",
	     CLK_CON_GAT_GATE_CLKCMUC_PERI_UART1, 21, 0, 0),
	GATE(CLK_GOUT_PERI_UART2, "gout_peri_uart2", "mout_peri_uart2",
	     CLK_CON_GAT_GATE_CLKCMU_PERI_UART2, 21, 0, 0),
};

static const struct samsung_div_clock top_peri_div_clks[] = {
	DIV(CLK_DOUT_PERI_BUS, "dout_peri_bus", "gout_peri_bus",
	    CLK_CON_DIV_CLKCMU_PERI_BUS, 0, 4),
	DIV(CLK_DOUT_PERI_UART0, "dout_peri_uart0", "gout_peri_uart0",
	    CLK_CON_DIV_CLKCMU_PERI_UART0, 0, 4),
	DIV(CLK_DOUT_PERI_UART1, "dout_peri_uart1", "gout_peri_uart1",
	    CLK_CON_DIV_CLKCMU_PERI_UART1, 0, 4),
	DIV(CLK_DOUT_PERI_UART2, "dout_peri_uart2", "gout_peri_uart2",
	    CLK_CON_DIV_CLKCMU_PERI_UART2, 0, 4),
};

static const struct samsung_clk_group top_cmu_clks[] = {
	/* CMU_TOP_PURECLKCOMP */
	{ S_CLK_PLL, top_pure_pll_clks, ARRAY_SIZE(top_pure_pll_clks) },
	{ S_CLK_MUX, top_pure_mux_clks, ARRAY_SIZE(top_pure_mux_clks) },
	{ S_CLK_DIV, top_pure_div_clks, ARRAY_SIZE(top_pure_div_clks) },

	/* CMU_TOP clocks for CMU_PERI */
	{ S_CLK_MUX, top_peri_mux_clks, ARRAY_SIZE(top_peri_mux_clks) },
	{ S_CLK_GATE, top_peri_gate_clks, ARRAY_SIZE(top_peri_gate_clks) },
	{ S_CLK_DIV, top_peri_div_clks, ARRAY_SIZE(top_peri_div_clks) },
};

static int exynos7885_cmu_top_probe(struct udevice *dev)
{
	return samsung_cmu_register_one(dev, CMU_TOP, top_cmu_clks,
					ARRAY_SIZE(top_cmu_clks));
}

static const struct udevice_id exynos7885_cmu_top_ids[] = {
	{ .compatible = "samsung,exynos7885-cmu-top" },
	{ }
};

SAMSUNG_CLK_OPS(exynos7885_cmu_top, CMU_TOP);

U_BOOT_DRIVER(exynos7885_cmu_top) = {
	.name		= "exynos7885-cmu-top",
	.id		= UCLASS_CLK,
	.of_match	= exynos7885_cmu_top_ids,
	.ops		= &exynos7885_cmu_top_clk_ops,
	.probe		= exynos7885_cmu_top_probe,
	.flags		= DM_FLAG_PRE_RELOC,
};

/* ---- CMU_PERI ------------------------------------------------------------ */

/* Register Offset definitions for CMU_PERI (0x10010000) */
#define PLL_CON0_MUX_CLKCMU_PERI_BUS_USER	0x0100
#define PLL_CON0_MUX_CLKCMU_PERI_UART0_USER	0x0160
#define PLL_CON0_MUX_CLKCMU_PERI_UART1_USER	0x0180
#define PLL_CON0_MUX_CLKCMU_PERI_UART2_USER	0x01a0
#define CLK_CON_GAT_GOUT_PERI_I2C_0_PCLK	0x2038
#define CLK_CON_GAT_GOUT_PERI_I2C_1_PCLK	0x203c
#define CLK_CON_GAT_GOUT_PERI_I2C_2_PCLK	0x2040
#define CLK_CON_GAT_GOUT_PERI_I2C_3_PCLK	0x2044
#define CLK_CON_GAT_GOUT_PERI_I2C_4_PCLK	0x2048
#define CLK_CON_GAT_GOUT_PERI_I2C_5_PCLK	0x204c
#define CLK_CON_GAT_GOUT_PERI_I2C_6_PCLK	0x2050
#define CLK_CON_GAT_GOUT_PERI_I2C_7_PCLK	0x2054
#define CLK_CON_GAT_GOUT_PERI_UART_0_EXT_UCLK	0x206c
#define CLK_CON_GAT_GOUT_PERI_UART_0_PCLK	0x2070
#define CLK_CON_GAT_GOUT_PERI_UART_1_EXT_UCLK	0x2074
#define CLK_CON_GAT_GOUT_PERI_UART_1_PCLK	0x2078
#define CLK_CON_GAT_GOUT_PERI_UART_2_EXT_UCLK	0x207c
#define CLK_CON_GAT_GOUT_PERI_UART_2_PCLK	0x2080

/* List of parent clocks for Muxes in CMU_PERI */
PNAME(mout_peri_bus_user_p)	= { "osc-clock", "dout_peri_bus" };
PNAME(mout_peri_uart0_user_p)	= { "osc-clock", "dout_peri_uart0" };
PNAME(mout_peri_uart1_user_p)	= { "osc-clock", "dout_peri_uart1" };
PNAME(mout_peri_uart2_user_p)	= { "osc-clock", "dout_peri_uart2" };

static const struct samsung_mux_clock peri_mux_clks[] = {
	MUX(CLK_MOUT_PERI_BUS_USER, "mout_peri_bus_user", mout_peri_bus_user_p,
	    PLL_CON0_MUX_CLKCMU_PERI_BUS_USER, 4, 1),
	MUX(CLK_MOUT_PERI_UART0_USER, "mout_peri_uart0_user",
	    mout_peri_uart0_user_p, PLL_CON0_MUX_CLKCMU_PERI_UART0_USER, 4, 1),
	MUX(CLK_MOUT_PERI_UART1_USER, "mout_peri_uart1_user",
	    mout_peri_uart1_user_p, PLL_CON0_MUX_CLKCMU_PERI_UART1_USER, 4, 1),
	MUX(CLK_MOUT_PERI_UART2_USER, "mout_peri_uart2_user",
	    mout_peri_uart2_user_p, PLL_CON0_MUX_CLKCMU_PERI_UART2_USER, 4, 1),
};

static const struct samsung_gate_clock peri_gate_clks[] = {
	GATE(CLK_GOUT_I2C0_PCLK, "gout_i2c0_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_0_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C1_PCLK, "gout_i2c1_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_1_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C2_PCLK, "gout_i2c2_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_2_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C3_PCLK, "gout_i2c3_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_3_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C4_PCLK, "gout_i2c4_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_4_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C5_PCLK, "gout_i2c5_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_5_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C6_PCLK, "gout_i2c6_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_6_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_I2C7_PCLK, "gout_i2c7_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_I2C_7_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_UART0_EXT_UCLK, "gout_uart0_ext_uclk", "mout_peri_uart0_user",
	     CLK_CON_GAT_GOUT_PERI_UART_0_EXT_UCLK, 21, 0, 0),
	GATE(CLK_GOUT_UART0_PCLK, "gout_uart0_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_UART_0_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_UART1_EXT_UCLK, "gout_uart1_ext_uclk", "mout_peri_uart1_user",
	     CLK_CON_GAT_GOUT_PERI_UART_1_EXT_UCLK, 21, 0, 0),
	GATE(CLK_GOUT_UART1_PCLK, "gout_uart1_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_UART_1_PCLK, 21, 0, 0),
	GATE(CLK_GOUT_UART2_EXT_UCLK, "gout_uart2_ext_uclk", "mout_peri_uart2_user",
	     CLK_CON_GAT_GOUT_PERI_UART_2_EXT_UCLK, 21, 0, 0),
	GATE(CLK_GOUT_UART2_PCLK, "gout_uart2_pclk", "mout_peri_bus_user",
	     CLK_CON_GAT_GOUT_PERI_UART_2_PCLK, 21, 0, 0),
};

static const struct samsung_clk_group peri_cmu_clks[] = {
	{ S_CLK_MUX, peri_mux_clks, ARRAY_SIZE(peri_mux_clks) },
	{ S_CLK_GATE, peri_gate_clks, ARRAY_SIZE(peri_gate_clks) },
};

static int exynos7885_cmu_peri_probe(struct udevice *dev)
{
	return samsung_register_cmu(dev, CMU_PERI, peri_cmu_clks,
				    exynos7885_cmu_top);
}

static const struct udevice_id exynos7885_cmu_peri_ids[] = {
	{ .compatible = "samsung,exynos7885-cmu-peri" },
	{ }
};

SAMSUNG_CLK_OPS(exynos7885_cmu_peri, CMU_PERI);

U_BOOT_DRIVER(exynos7885_cmu_peri) = {
	.name		= "exynos7885-cmu-peri",
	.id		= UCLASS_CLK,
	.of_match	= exynos7885_cmu_peri_ids,
	.ops		= &exynos7885_cmu_peri_clk_ops,
	.probe		= exynos7885_cmu_peri_probe,
	.flags		= DM_FLAG_PRE_RELOC,
};
