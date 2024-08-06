/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024, Dávid Virág
 *
 * Configuration for the Samsung Exynos7885 SoC.
 */

#ifndef __EXYNOS7885_H
#define __EXYNOS7885_H

#ifndef EXYNOS_DEVICE_SETTINGS
#define EXYNOS_DEVICE_SETTINGS
#endif

#define CFG_EXTRA_ENV_SETTINGS \
	"stdin=serial,button-kbd\0" \
	"stdout=serial,vidconsole\0" \
	"stderr=serial,vidconsole\0" \
	EXYNOS_DEVICE_SETTINGS

#endif /* __EXYNOS7885_H */
