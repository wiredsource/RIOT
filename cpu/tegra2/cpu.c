/*
 * cpu.c - tegra2 architecture common support functions
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT.
 *
 */

#include "tegra2.h"
#include "cpu.h"
#include "lpm.h"
#include "armv7_cpu.h"

__attribute__((naked,noreturn)) void arm_reset(void)
{
    dINT();
    // TODO: implement SW reset
    while(1);
}

enum lpm_mode lpm_set(enum lpm_mode target) {
    (void) target;
    return LPM_ON;
}