/*
 * gic.h - tegra 2 specific "legacy" interrupt controller
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT.
 */

struct IC {
    uint32_t PRI_ICTLR_VIRQ_CPU_0;
    uint32_t PRI_ICTLR_VIRQ_COP_0;
    uint32_t PRI_ICTLR_VFIQ_CPU_0;
    uint32_t PRI_ICTLR_VFIQ_COP_0;
    uint32_t PRI_ICTLR_ISR_0;
    uint32_t PRI_ICTLR_FIR_0;
    uint32_t PRI_ICTLR_FIR_SET_0;
    uint32_t PRI_ICTLR_FIR_CLR_0;
    uint32_t PRI_ICTLR_CPU_IER_0;
    uint32_t PRI_ICTLR_CPU_IER_SET_0;
    uint32_t PRI_ICTLR_CPU_IER_CLR_0;
    uint32_t PRI_ICTLR_CPU_IEP_CLASS_0;
    uint32_t PRI_ICTLR_COP_IER_0;
    uint32_t PRI_ICTLR_COP_IER_SET_0;
    uint32_t PRI_ICTLR_COP_IER_CLR_0;
    uint32_t PRI_ICTLR_COP_IEP_CLASS_0;
    uint32_t PRI_ICTLR_ARBGNT_CPU_STATUS_0;
    uint32_t PRI_ICTLR_ARBGNT_CPU_ENABLE_0;
    uint32_t PRI_ICTLR_ARBGNT_COP_STATUS_0;
    uint32_t PRI_ICTLR_ARBGNT_COP_ENABLE_0;
    uint32_t SEC_ICTLR_VIRQ_CPU_0;
    uint32_t SEC_ICTLR_VIRQ_COP_0;
    uint32_t SEC_ICTLR_VFIQ_CPU_0;
    uint32_t SEC_ICTLR_VFIQ_COP_0;
    uint32_t SEC_ICTLR_ISR_0;
    uint32_t SEC_ICTLR_FIR_0;
    uint32_t SEC_ICTLR_FIR_SET_0;
    uint32_t SEC_ICTLR_FIR_CLR_0;
    uint32_t SEC_ICTLR_CPU_IER_0;
    uint32_t SEC_ICTLR_CPU_IER_SET_0;
    uint32_t SEC_ICTLR_CPU_IER_CLR_0;
    uint32_t SEC_ICTLR_CPU_IEP_CLASS_0;
    uint32_t SEC_ICTLR_COP_IER_0;
    uint32_t SEC_ICTLR_COP_IER_SET_0;
    uint32_t SEC_ICTLR_COP_IER_CLR_0;
    uint32_t SEC_ICTLR_COP_IEP_CLASS_0;
    uint32_t SEC_ICTLR_DRQ_TX_STATUS_0;
    uint32_t SEC_ICTLR_DRQ_TX_ENABLE_0;
    uint32_t SEC_ICTLR_DRQ_RX_STATUS_0;
}