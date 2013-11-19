/*
 * cpu.h - tegra2 specific definitions
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT
 */

#ifndef CPU_H
#define CPU_H 

/**
 * @defgroup	tegra2		Nvidia Tegra2
 * @ingroup		cpu
 * @{
 */

#include <stdbool.h>
#include "armv7_cpu.h"
#include "tegra2.h"

extern uintptr_t __stack_start;		///< end of user stack memory space
//bool install_irq(int int_number, void *handler_addr, int priority);

/** @} */
#endif /* CPU_H */
