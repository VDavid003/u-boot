// SPDX-License-Identifier: GPL-2.0+
/*
 * Exynos7885 pinctrl driver.
 *
 * Copyright (c) 2023 Dávid Virág (virag.david003@gmail.com)
 *
 * based on drivers/pinctrl/exynos/pinctrl-exynos7420.c :
 * Copyright (C) 2016 Samsung Electronics
 * Thomas Abraham <thomas.ab@samsung.com>
 *
 * and on drivers/pinctrl/exynos/pinctrl-exynos78x0.c :
 * Copyright (c) 2020 Dzmitry Sankouski (dsankouski@gmail.com)
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <asm/io.h>
#include <dm/pinctrl.h>
#include <dm/root.h>
#include <fdtdec.h>
#include <asm/arch/pinmux.h>
#include "pinctrl-exynos.h"

static const struct pinctrl_ops exynos7885_pinctrl_ops = {
	.set_state	= exynos_pinctrl_set_state
};

/* pin banks of exynos7885 pin-controller 0 (ALIVE) */
static const struct samsung_pin_bank_data exynos7885_pin_banks0[] = {
	EXYNOS_PIN_BANK(3, 0x000, "etc0"),
	EXYNOS_PIN_BANK(3, 0x020, "etc1"),
	EXYNOS_PIN_BANK(8, 0x040, "gpa0"),
	EXYNOS_PIN_BANK(8, 0x060, "gpa1"),
	EXYNOS_PIN_BANK(8, 0x080, "gpa2"),
	EXYNOS_PIN_BANK(5, 0x0a0, "gpq0"),
};

/* pin banks of exynos7885 pin-controller 1 (DISPAUD) */
static const struct samsung_pin_bank_data exynos7885_pin_banks1[] = {
	EXYNOS_PIN_BANK(5, 0x000, "gpb0"),
	EXYNOS_PIN_BANK(4, 0x020, "gpb1"),
	EXYNOS_PIN_BANK(5, 0x040, "gpb2"),
};

/* pin banks of exynos7885 pin-controller 2 (FSYS) */
static const struct samsung_pin_bank_data exynos7885_pin_banks2[] = {
	EXYNOS_PIN_BANK(4, 0x000, "gpf0"),
	EXYNOS_PIN_BANK(8, 0x020, "gpf2"),
	EXYNOS_PIN_BANK(6, 0x040, "gpf3"),
	EXYNOS_PIN_BANK(6, 0x060, "gpf4"),
};

/* pin banks of exynos7885 pin-controller 3 (TOP) */
static const struct samsung_pin_bank_data exynos7885_pin_banks3[] = {
	EXYNOS_PIN_BANK(4, 0x000, "gpp0"),
	EXYNOS_PIN_BANK(3, 0x020, "gpg0"),
	EXYNOS_PIN_BANK(4, 0x040, "gpp1"),
	EXYNOS_PIN_BANK(4, 0x060, "gpp2"),
	EXYNOS_PIN_BANK(3, 0x080, "gpp3"),
	EXYNOS_PIN_BANK(6, 0x0a0, "gpp4"),
	EXYNOS_PIN_BANK(4, 0x0c0, "gpp5"),
	EXYNOS_PIN_BANK(5, 0x0e0, "gpp6"),
	EXYNOS_PIN_BANK(2, 0x100, "gpp7"),
	EXYNOS_PIN_BANK(2, 0x120, "gpp8"),
	EXYNOS_PIN_BANK(8, 0x140, "gpg1"),
	EXYNOS_PIN_BANK(8, 0x160, "gpg2"),
	EXYNOS_PIN_BANK(8, 0x180, "gpg3"),
	EXYNOS_PIN_BANK(2, 0x1a0, "gpg4"),
	EXYNOS_PIN_BANK(4, 0x1c0, "gpc0"),
	EXYNOS_PIN_BANK(8, 0x1e0, "gpc1"),
	EXYNOS_PIN_BANK(8, 0x200, "gpc2"),
};

const struct samsung_pin_ctrl exynos7885_pin_ctrl[] = {
	{
		/* pin-controller instance 0 ALIVE data */
		.pin_banks	= exynos7885_pin_banks0,
		.nr_banks	= ARRAY_SIZE(exynos7885_pin_banks0),
	}, {
		/* pin-controller instance 1 DISPAUD data */
		.pin_banks	= exynos7885_pin_banks1,
		.nr_banks	= ARRAY_SIZE(exynos7885_pin_banks1),
	}, {
		/* pin-controller instance 2 FSYS data */
		.pin_banks	= exynos7885_pin_banks2,
		.nr_banks	= ARRAY_SIZE(exynos7885_pin_banks2),
	}, {
		/* pin-controller instance 4 TOP data */
		.pin_banks	= exynos7885_pin_banks3,
		.nr_banks	= ARRAY_SIZE(exynos7885_pin_banks3),
	},
	{/* list terminator */}
};

static const struct udevice_id exynos7885_pinctrl_ids[] = {
	{ .compatible = "samsung,exynos7885-pinctrl",
		.data = (ulong)exynos7885_pin_ctrl },
	{ }
};

U_BOOT_DRIVER(pinctrl_exynos7885) = {
	.name		= "pinctrl_exynos7885",
	.id		= UCLASS_PINCTRL,
	.of_match	= exynos7885_pinctrl_ids,
	.priv_auto = sizeof(struct exynos_pinctrl_priv),
	.ops		= &exynos7885_pinctrl_ops,
	.probe		= exynos_pinctrl_probe,
};
