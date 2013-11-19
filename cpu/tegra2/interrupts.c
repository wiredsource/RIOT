/*
 * interrupts.c - tegra 2 specific isr
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT.
 */


// #define MAX_IRQ_INDEX 10
// #define MAX_IRQ_NUM 11
// 
// static void (*isr_funcs[MAX_IRQ_NUM])(void) = {
//     tmr1,
//     tmr2,
//     rtc,
//     i2s2,
//     
// };
// 
// void register_isr(uint8_t interrupt, void (*isr)(void)) {
//     if (interrupt <= MAX_IRQ_INDEX) {
//         isr_funcs[interrupt] = isr;
//     }
// }
// 
void isr(void)
{
//     /* set irq_num to an invalid value */
//     uint8_t irq_num = MAX_IRQ_NUM;
// 
//     /* pending interrupt? */
//     while (ITC->NIPEND) {
//         /* get interrupt source, range 0-10 */
//         irq_num = ITC->NIVECTOR;
//         /* call corresponding ISR */
//         if (isr_funcs[irq_num] != 0) {
//             (isr_funcs[irq_num])();
//         }
//     }
}
