/*
 * hwtimer_cpu.h - tegra2 specific definitions
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT
 */

#ifndef HWTIMER_CPU_H_
#define HWTIMER_CPU_H_

#define ARCH_MAXTIMERS 4
#define HWTIMER_SPEED 1000000
#define HWTIMER_MAXTICKS (0xFFFFFFFF)

#define HWTIMER_MSEC  (HWTIMER_SPEED/1000)
#define HWTIMER_SEC   (HWTIMER_SPEED)

#endif /* HWTIMER_CPU_H_ */
