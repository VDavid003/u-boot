/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024, Dávid Virág
 *
 * Configuration for JACKPOTLTE board.
 */

#ifndef __JACKPOTLTE_H
#define __JACKPOTLTE_H

#define CFG_EXTRA_ENV_SETTINGS \
	"stdin=serial\0" \
	"stdout=serial,vidconsole\0" \
	"stderr=serial,vidconsole\0"

#endif /* __JACKPOTLTE_H */
