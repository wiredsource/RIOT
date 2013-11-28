/*
 * tegra2.h - tegra2 specific definitions
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT
 */

#ifndef TEGRA2_H_
#define TEGRA2_H_

#define F_CPU   (24000000)				///< CPU target speed in Hz

#define NV_PA_ARM_PERIPHBASE	0x50040000
#define NV_PA_PG_UP_BASE	0x60000000
#define NV_PA_TMRUS_BASE	0x60005010
#define NV_PA_CLK_RST_BASE	0x60006000
#define NV_PA_FLOW_BASE		0x60007000
#define NV_PA_GPIO_BASE		0x6000D000
#define NV_PA_EVP_BASE		0x6000F000
#define NV_PA_APB_MISC_BASE	0x70000000
#define NV_PA_APB_MISC_GP_BASE	(NV_PA_APB_MISC_BASE + 0x0800)
#define NV_PA_APB_UARTA_BASE	(NV_PA_APB_MISC_BASE + 0x6000)
#define NV_PA_APB_UARTB_BASE	(NV_PA_APB_MISC_BASE + 0x6040)
#define NV_PA_APB_UARTC_BASE	(NV_PA_APB_MISC_BASE + 0x6200)
#define NV_PA_APB_UARTD_BASE	(NV_PA_APB_MISC_BASE + 0x6300)
#define NV_PA_APB_UARTE_BASE	(NV_PA_APB_MISC_BASE + 0x6400)
#define NV_PA_NAND_BASE		(NV_PA_APB_MISC_BASE + 0x8000)
#define NV_PA_SPI_BASE		(NV_PA_APB_MISC_BASE + 0xC380)
#define NV_PA_SLINK1_BASE	(NV_PA_APB_MISC_BASE + 0xD400)
#define NV_PA_SLINK2_BASE	(NV_PA_APB_MISC_BASE + 0xD600)
#define NV_PA_SLINK3_BASE	(NV_PA_APB_MISC_BASE + 0xD800)
#define NV_PA_SLINK4_BASE	(NV_PA_APB_MISC_BASE + 0xDA00)
#define NV_PA_SLINK5_BASE	(NV_PA_APB_MISC_BASE + 0xDC00)
#define NV_PA_SLINK6_BASE	(NV_PA_APB_MISC_BASE + 0xDE00)
#define TEGRA_DVC_BASE		(NV_PA_APB_MISC_BASE + 0xD000)
#define NV_PA_PMC_BASE		(NV_PA_APB_MISC_BASE + 0xE400)
#define NV_PA_EMC_BASE		(NV_PA_APB_MISC_BASE + 0xF400)
#define NV_PA_FUSE_BASE		(NV_PA_APB_MISC_BASE + 0xF800)
#define NV_PA_CSITE_BASE	0x70040000
#define TEGRA_USB_ADDR_MASK	0xFFFFC000

#define NV_PA_SDRC_CS0		NV_PA_SDRAM_BASE
#define LOW_LEVEL_SRAM_STACK	0x4000FFFC
#define EARLY_AVP_STACK		(NV_PA_SDRAM_BASE + 0x20000)
#define EARLY_CPU_STACK		(EARLY_AVP_STACK - 4096)
#define PG_UP_TAG_AVP		0xAAAAAAAA

#ifndef __ASSEMBLY__
struct timerus {
	unsigned int cntr_1us;
};

/* Address at which WB code runs, it must not overlap Bootrom's IRAM usage */
#define NV_WB_RUN_ADDRESS	0x40020000

#define NVBOOTINFOTABLE_BCTSIZE	0x38	/* BCT size in BIT in IRAM */
#define NVBOOTINFOTABLE_BCTPTR	0x3C	/* BCT pointer in BIT in IRAM */

/* These are the available SKUs (product types) for Tegra */
enum {
	SKU_ID_T20_7		= 0x7,
	SKU_ID_T20		= 0x8,
	SKU_ID_T25SE		= 0x14,
	SKU_ID_AP25		= 0x17,
	SKU_ID_T25		= 0x18,
	SKU_ID_AP25E		= 0x1b,
	SKU_ID_T25E		= 0x1c,
	SKU_ID_T33		= 0x80,
	SKU_ID_T30		= 0x81, /* Cardhu value */
	SKU_ID_T114_ENG		= 0x00, /* Dalmore value, unfused */
	SKU_ID_T114_1		= 0x01,
};

/*
 * These are used to distinguish SOC types for setting up clocks. Mostly
 * we can tell the clocking required by looking at the SOC sku_id, but
 * for T30 it is a user option as to whether to run PLLP in fast or slow
 * mode, so we have two options there.
 */
enum {
	TEGRA_SOC_T20,
	TEGRA_SOC_T25,
	TEGRA_SOC_T30,
	TEGRA_SOC_T114,

	TEGRA_SOC_CNT,
	TEGRA_SOC_UNKNOWN	= -1,
};

#else  /* __ASSEMBLY__ */
#define PRM_RSTCTRL		NV_PA_PMC_BASE
#endif

#define __arch_getb(a)			(*(volatile unsigned char *)(a))
#define __arch_getw(a)			(*(volatile unsigned short *)(a))
#define __arch_getl(a)			(*(volatile unsigned int *)(a))

#define __arch_putb(v,a)		(*(volatile unsigned char *)(a) = (v))
#define __arch_putw(v,a)		(*(volatile unsigned short *)(a) = (v))
#define __arch_putl(v,a)		(*(volatile unsigned int *)(a) = (v))

#define dmb()		__asm__ __volatile__ ("" : : : "memory")
#define __iormb()	dmb()
#define __iowmb()	dmb()


#define writeb(v,c)	({ uint8_t  __v = v; __iowmb(); __arch_putb(__v,c); __v; })
#define writew(v,c)	({ uint16_t __v = v; __iowmb(); __arch_putw(__v,c); __v; })
#define writel(v,c)	({ uint32_t __v = v; __iowmb(); __arch_putl(__v,c); __v; })

#define readb(c)	({ uint8_t  __v = __arch_getb(c); __iormb(); __v; })
#define readw(c)	({ uint16_t __v = __arch_getw(c); __iormb(); __v; })
#define readl(c)	({ uint32_t __v = __arch_getl(c); __iormb(); __v; })

#endif /* TEGRA2_H_ */