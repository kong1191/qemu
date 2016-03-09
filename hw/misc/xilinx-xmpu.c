/*
 * QEMU model of the XMPU xmpu
 *
 * Copyright (c) 2014 Xilinx Inc.
 *
 * Partially autogenerated by xregqemu.py 2014-08-07.
 * Written by Edgar E. Iglesias <edgari@xilinx.com>
 *            Alistair Francis <alistai@xilinx.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "hw/sysbus.h"
#include "hw/register.h"
#include "qemu/bitops.h"
#include "qemu/log.h"

#include "sysemu/dma.h"
#include "exec/address-spaces.h"

#include "hw/fdt_generic_util.h"

#ifndef XILINX_XMPU_ERR_DEBUG
#define XILINX_XMPU_ERR_DEBUG 0
#endif

#define TYPE_XILINX_XMPU "xlnx.xmpu"

#define XILINX_XMPU(obj) \
     OBJECT_CHECK(XMPU, (obj), TYPE_XILINX_XMPU)

REG32(CTRL, 0x0)
    FIELD(CTRL, ALIGNCFG, 1, 3)
    FIELD(CTRL, POISONCFG, 1, 2)
    FIELD(CTRL, DEFWRALLOWED, 1, 1)
    FIELD(CTRL, DEFRDALLOWED, 1, 0)
REG32(ERR_STATUS1, 0x4)
    FIELD(ERR_STATUS1, AXI_ADDR, 20, 0)
REG32(ERR_STATUS2, 0x8)
    FIELD(ERR_STATUS2, AXI_ID, 10, 0)
REG32(POISON, 0xc)
    FIELD(POISON, ATTRIB, 1, 20)
    FIELD(POISON, BASE, 20, 0)
REG32(ISR, 0x10)
    FIELD(ISR, SECURITYVIO, 1, 3)
    FIELD(ISR, WRPERMVIO, 1, 2)
    FIELD(ISR, RDPERMVIO, 1, 1)
    FIELD(ISR, INV_APB, 1, 0)
REG32(IMR, 0x14)
    FIELD(IMR, SECURITYVIO, 1, 3)
    FIELD(IMR, WRPERMVIO, 1, 2)
    FIELD(IMR, RDPERMVIO, 1, 1)
    FIELD(IMR, INV_APB, 1, 0)
REG32(IEN, 0x18)
    FIELD(IEN, SECURITYVIO, 1, 3)
    FIELD(IEN, WRPERMVIO, 1, 2)
    FIELD(IEN, RDPERMVIO, 1, 1)
    FIELD(IEN, INV_APB, 1, 0)
REG32(IDS, 0x1c)
    FIELD(IDS, SECURITYVIO, 1, 3)
    FIELD(IDS, WRPERMVIO, 1, 2)
    FIELD(IDS, RDPERMVIO, 1, 1)
    FIELD(IDS, INV_APB, 1, 0)
REG32(LOCK, 0x20)
    FIELD(LOCK, REGWRDIS, 1, 0)
REG32(ECO, 0xfc)
REG32(R00_START, 0x100)
    FIELD(R00_START, ADDR, 20, 0)
REG32(R00_END, 0x104)
    FIELD(R00_END, ADDR, 20, 0)
REG32(R00_MASTER, 0x108)
    FIELD(R00_MASTER, MASK, 10, 16)
    FIELD(R00_MASTER, ID, 10, 0)
REG32(R00_CONFIG, 0x10c)
    FIELD(R00_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R00_CONFIG, REGIONNS, 1, 3)
    FIELD(R00_CONFIG, WRALLOWED, 1, 2)
    FIELD(R00_CONFIG, RDALLOWED, 1, 1)
    FIELD(R00_CONFIG, ENABLE, 1, 0)
REG32(R01_START, 0x110)
    FIELD(R01_START, ADDR, 20, 0)
REG32(R01_END, 0x114)
    FIELD(R01_END, ADDR, 20, 0)
REG32(R01_MASTER, 0x118)
    FIELD(R01_MASTER, MASK, 10, 16)
    FIELD(R01_MASTER, ID, 10, 0)
REG32(R01_CONFIG, 0x11c)
    FIELD(R01_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R01_CONFIG, REGIONNS, 1, 3)
    FIELD(R01_CONFIG, WRALLOWED, 1, 2)
    FIELD(R01_CONFIG, RDALLOWED, 1, 1)
    FIELD(R01_CONFIG, ENABLE, 1, 0)
REG32(R02_START, 0x120)
    FIELD(R02_START, ADDR, 20, 0)
REG32(R02_END, 0x124)
    FIELD(R02_END, ADDR, 20, 0)
REG32(R02_MASTER, 0x128)
    FIELD(R02_MASTER, MASK, 10, 16)
    FIELD(R02_MASTER, ID, 10, 0)
REG32(R02_CONFIG, 0x12c)
    FIELD(R02_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R02_CONFIG, REGIONNS, 1, 3)
    FIELD(R02_CONFIG, WRALLOWED, 1, 2)
    FIELD(R02_CONFIG, RDALLOWED, 1, 1)
    FIELD(R02_CONFIG, ENABLE, 1, 0)
REG32(R03_START, 0x130)
    FIELD(R03_START, ADDR, 20, 0)
REG32(R03_END, 0x134)
    FIELD(R03_END, ADDR, 20, 0)
REG32(R03_MASTER, 0x138)
    FIELD(R03_MASTER, MASK, 10, 16)
    FIELD(R03_MASTER, ID, 10, 0)
REG32(R03_CONFIG, 0x13c)
    FIELD(R03_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R03_CONFIG, REGIONNS, 1, 3)
    FIELD(R03_CONFIG, WRALLOWED, 1, 2)
    FIELD(R03_CONFIG, RDALLOWED, 1, 1)
    FIELD(R03_CONFIG, ENABLE, 1, 0)
REG32(R04_START, 0x140)
    FIELD(R04_START, ADDR, 20, 0)
REG32(R04_END, 0x144)
    FIELD(R04_END, ADDR, 20, 0)
REG32(R04_MASTER, 0x148)
    FIELD(R04_MASTER, MASK, 10, 16)
    FIELD(R04_MASTER, ID, 10, 0)
REG32(R04_CONFIG, 0x14c)
    FIELD(R04_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R04_CONFIG, REGIONNS, 1, 3)
    FIELD(R04_CONFIG, WRALLOWED, 1, 2)
    FIELD(R04_CONFIG, RDALLOWED, 1, 1)
    FIELD(R04_CONFIG, ENABLE, 1, 0)
REG32(R05_START, 0x150)
    FIELD(R05_START, ADDR, 20, 0)
REG32(R05_END, 0x154)
    FIELD(R05_END, ADDR, 20, 0)
REG32(R05_MASTER, 0x158)
    FIELD(R05_MASTER, MASK, 10, 16)
    FIELD(R05_MASTER, ID, 10, 0)
REG32(R05_CONFIG, 0x15c)
    FIELD(R05_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R05_CONFIG, REGIONNS, 1, 3)
    FIELD(R05_CONFIG, WRALLOWED, 1, 2)
    FIELD(R05_CONFIG, RDALLOWED, 1, 1)
    FIELD(R05_CONFIG, ENABLE, 1, 0)
REG32(R06_START, 0x160)
    FIELD(R06_START, ADDR, 20, 0)
REG32(R06_END, 0x164)
    FIELD(R06_END, ADDR, 20, 0)
REG32(R06_MASTER, 0x168)
    FIELD(R06_MASTER, MASK, 10, 16)
    FIELD(R06_MASTER, ID, 10, 0)
REG32(R06_CONFIG, 0x16c)
    FIELD(R06_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R06_CONFIG, REGIONNS, 1, 3)
    FIELD(R06_CONFIG, WRALLOWED, 1, 2)
    FIELD(R06_CONFIG, RDALLOWED, 1, 1)
    FIELD(R06_CONFIG, ENABLE, 1, 0)
REG32(R07_START, 0x170)
    FIELD(R07_START, ADDR, 20, 0)
REG32(R07_END, 0x174)
    FIELD(R07_END, ADDR, 20, 0)
REG32(R07_MASTER, 0x178)
    FIELD(R07_MASTER, MASK, 10, 16)
    FIELD(R07_MASTER, ID, 10, 0)
REG32(R07_CONFIG, 0x17c)
    FIELD(R07_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R07_CONFIG, REGIONNS, 1, 3)
    FIELD(R07_CONFIG, WRALLOWED, 1, 2)
    FIELD(R07_CONFIG, RDALLOWED, 1, 1)
    FIELD(R07_CONFIG, ENABLE, 1, 0)
REG32(R08_START, 0x180)
    FIELD(R08_START, ADDR, 20, 0)
REG32(R08_END, 0x184)
    FIELD(R08_END, ADDR, 20, 0)
REG32(R08_MASTER, 0x188)
    FIELD(R08_MASTER, MASK, 10, 16)
    FIELD(R08_MASTER, ID, 10, 0)
REG32(R08_CONFIG, 0x18c)
    FIELD(R08_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R08_CONFIG, REGIONNS, 1, 3)
    FIELD(R08_CONFIG, WRALLOWED, 1, 2)
    FIELD(R08_CONFIG, RDALLOWED, 1, 1)
    FIELD(R08_CONFIG, ENABLE, 1, 0)
REG32(R09_START, 0x190)
    FIELD(R09_START, ADDR, 20, 0)
REG32(R09_END, 0x194)
    FIELD(R09_END, ADDR, 20, 0)
REG32(R09_MASTER, 0x198)
    FIELD(R09_MASTER, MASK, 10, 16)
    FIELD(R09_MASTER, ID, 10, 0)
REG32(R09_CONFIG, 0x19c)
    FIELD(R09_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R09_CONFIG, REGIONNS, 1, 3)
    FIELD(R09_CONFIG, WRALLOWED, 1, 2)
    FIELD(R09_CONFIG, RDALLOWED, 1, 1)
    FIELD(R09_CONFIG, ENABLE, 1, 0)
REG32(R10_START, 0x1a0)
    FIELD(R10_START, ADDR, 20, 0)
REG32(R10_END, 0x1a4)
    FIELD(R10_END, ADDR, 20, 0)
REG32(R10_MASTER, 0x1a8)
    FIELD(R10_MASTER, MASK, 10, 16)
    FIELD(R10_MASTER, ID, 10, 0)
REG32(R10_CONFIG, 0x1ac)
    FIELD(R10_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R10_CONFIG, REGIONNS, 1, 3)
    FIELD(R10_CONFIG, WRALLOWED, 1, 2)
    FIELD(R10_CONFIG, RDALLOWED, 1, 1)
    FIELD(R10_CONFIG, ENABLE, 1, 0)
REG32(R11_START, 0x1b0)
    FIELD(R11_START, ADDR, 20, 0)
REG32(R11_END, 0x1b4)
    FIELD(R11_END, ADDR, 20, 0)
REG32(R11_MASTER, 0x1b8)
    FIELD(R11_MASTER, MASK, 10, 16)
    FIELD(R11_MASTER, ID, 10, 0)
REG32(R11_CONFIG, 0x1bc)
    FIELD(R11_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R11_CONFIG, REGIONNS, 1, 3)
    FIELD(R11_CONFIG, WRALLOWED, 1, 2)
    FIELD(R11_CONFIG, RDALLOWED, 1, 1)
    FIELD(R11_CONFIG, ENABLE, 1, 0)
REG32(R12_START, 0x1c0)
    FIELD(R12_START, ADDR, 20, 0)
REG32(R12_END, 0x1c4)
    FIELD(R12_END, ADDR, 20, 0)
REG32(R12_MASTER, 0x1c8)
    FIELD(R12_MASTER, MASK, 10, 16)
    FIELD(R12_MASTER, ID, 10, 0)
REG32(R12_CONFIG, 0x1cc)
    FIELD(R12_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R12_CONFIG, REGIONNS, 1, 3)
    FIELD(R12_CONFIG, WRALLOWED, 1, 2)
    FIELD(R12_CONFIG, RDALLOWED, 1, 1)
    FIELD(R12_CONFIG, ENABLE, 1, 0)
REG32(R13_START, 0x1d0)
    FIELD(R13_START, ADDR, 20, 0)
REG32(R13_END, 0x1d4)
    FIELD(R13_END, ADDR, 20, 0)
REG32(R13_MASTER, 0x1d8)
    FIELD(R13_MASTER, MASK, 10, 16)
    FIELD(R13_MASTER, ID, 10, 0)
REG32(R13_CONFIG, 0x1dc)
    FIELD(R13_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R13_CONFIG, REGIONNS, 1, 3)
    FIELD(R13_CONFIG, WRALLOWED, 1, 2)
    FIELD(R13_CONFIG, RDALLOWED, 1, 1)
    FIELD(R13_CONFIG, ENABLE, 1, 0)
REG32(R14_START, 0x1e0)
    FIELD(R14_START, ADDR, 20, 0)
REG32(R14_END, 0x1e4)
    FIELD(R14_END, ADDR, 20, 0)
REG32(R14_MASTER, 0x1e8)
    FIELD(R14_MASTER, MASK, 10, 16)
    FIELD(R14_MASTER, ID, 10, 0)
REG32(R14_CONFIG, 0x1ec)
    FIELD(R14_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R14_CONFIG, REGIONNS, 1, 3)
    FIELD(R14_CONFIG, WRALLOWED, 1, 2)
    FIELD(R14_CONFIG, RDALLOWED, 1, 1)
    FIELD(R14_CONFIG, ENABLE, 1, 0)
REG32(R15_START, 0x1f0)
    FIELD(R15_START, ADDR, 20, 0)
REG32(R15_END, 0x1f4)
    FIELD(R15_END, ADDR, 20, 0)
REG32(R15_MASTER, 0x1f8)
    FIELD(R15_MASTER, MASK, 10, 16)
    FIELD(R15_MASTER, ID, 10, 0)
REG32(R15_CONFIG, 0x1fc)
    FIELD(R15_CONFIG, NSCHECKTYPE, 1, 4)
    FIELD(R15_CONFIG, REGIONNS, 1, 3)
    FIELD(R15_CONFIG, WRALLOWED, 1, 2)
    FIELD(R15_CONFIG, RDALLOWED, 1, 1)
    FIELD(R15_CONFIG, ENABLE, 1, 0)

#define R_MAX (R_R15_CONFIG + 1)

#define NR_XMPU_REGIONS 16
#define MAX_NR_MASTERS  8

typedef struct XMPU XMPU;

typedef struct XMPUMaster {
    XMPU *parent;

    AddressSpace *parent_as;
    MemoryRegion *parent_mr;
    uint64_t size;

    MemoryRegion mr;
    MemoryRegion iommu;

    struct {
        struct {
            AddressSpace as;
            MemoryRegion mr;
        } rw, ro, none;
    } down;

    struct {
        MemoryRegion mr[NR_XMPU_REGIONS];
    } err;
} XMPUMaster;

struct XMPU {
    SysBusDevice parent_obj;
    MemoryRegion iomem;

    MemoryRegion *protected_mr;

    /* Dynamically size this one based on attached masters.  */
    XMPUMaster masters[MAX_NR_MASTERS];
    qemu_irq irq_isr;

    uint64_t addr_mask;
    uint32_t addr_shift;

    struct {
        uint32_t nr_masters;
        /* Will go away with proper MRs.  */
        uint64_t base;

        bool align;
        bool poison;
    } cfg;

    uint32_t regs[R_MAX];
    RegisterInfo regs_info[R_MAX];
    const char *prefix;
    bool enabled;
    qemu_irq enabled_signal;
};

typedef struct XMPURegion {
    uint64_t start;
    uint64_t end;
    uint64_t size;
    union {
        uint32_t u32;
        struct {
            uint16_t mask;
            uint16_t id;
        };
    } master;
    struct {
        bool nschecktype;
        bool regionns;
        bool wrallowed;
        bool rdallowed;
        bool enable;
    } config;
} XMPURegion;

static void xmpu_decode_region(XMPU *s, XMPURegion *xr, unsigned int region)
{
    assert(region < NR_XMPU_REGIONS);
    uint32_t config;
    unsigned int offset = region * (R_R01_START - R_R00_START);

    xr->start = s->regs[offset + R_R00_START];
    xr->end = s->regs[offset + R_R00_END];
    xr->start <<= 12;
    xr->end <<= 12;

    xr->size = xr->end - xr->start;
    xr->master.u32 = s->regs[offset + R_R00_MASTER];

    config = s->regs[offset + R_R00_CONFIG];
    xr->config.enable = F_EX32(config, R00_CONFIG, ENABLE);
    xr->config.rdallowed = F_EX32(config, R00_CONFIG, RDALLOWED);
    xr->config.wrallowed = F_EX32(config, R00_CONFIG, WRALLOWED);
    xr->config.regionns = F_EX32(config, R00_CONFIG, REGIONNS);
    xr->config.nschecktype = F_EX32(config, R00_CONFIG, NSCHECKTYPE);
}

static void isr_update_irq(XMPU *s)
{
    bool pending = s->regs[R_ISR] & ~s->regs[R_IMR];
    qemu_set_irq(s->irq_isr, pending);
}

static void isr_postw(RegisterInfo *reg, uint64_t val64)
{
    XMPU *s = XILINX_XMPU(reg->opaque);
    isr_update_irq(s);
}

static uint64_t ien_prew(RegisterInfo *reg, uint64_t val64)
{
    XMPU *s = XILINX_XMPU(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR] &= ~val;
    isr_update_irq(s);
    return 0;
}

static uint64_t ids_prew(RegisterInfo *reg, uint64_t val64)
{
    XMPU *s = XILINX_XMPU(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR] |= val;
    isr_update_irq(s);
    return 0;
}

static void xmpu_update_enabled(XMPU *s)
{
    bool regions_enabled = false;
    bool default_wr = AF_EX32(s->regs, CTRL, DEFWRALLOWED);
    bool default_rd = AF_EX32(s->regs, CTRL, DEFRDALLOWED);
    int i;

    /* Lookup if this address fits a region.  */
    for (i = NR_XMPU_REGIONS - 1; i >= 0; i--) {
        XMPURegion xr;
        xmpu_decode_region(s, &xr, i);
        if (!xr.config.enable) {
            continue;
        }
        qemu_log("regions_enabled\n");
        regions_enabled = true;
        break;
    }

    s->enabled = true;
    if (!regions_enabled && default_wr && default_rd) {
        s->enabled = false;
    }
}

static void xmpu_flush(XMPU *s)
{
    unsigned int i;

    xmpu_update_enabled(s);
    qemu_set_irq(s->enabled_signal, s->enabled);

    for (i = 0; i < s->cfg.nr_masters; i++) {
        IOMMUTLBEntry entry = {
            .target_as = s->masters[i].parent_as,
            .iova = 0,
            .translated_addr = 0,
            .addr_mask = ~0,
            .perm = IOMMU_NONE,
        };
        memory_region_notify_iommu(&s->masters[i].iommu, entry);
        /* Temporary hack.  */
        memory_region_transaction_begin();
        memory_region_set_readonly(&s->masters[i].iommu, false);
        memory_region_set_readonly(&s->masters[i].iommu, true);
        memory_region_set_enabled(&s->masters[i].iommu, s->enabled);
        memory_region_transaction_commit();
    }
}

static void xmpu_setup_postw(RegisterInfo *reg, uint64_t val64)
{
    XMPU *s = XILINX_XMPU(reg->opaque);
    xmpu_flush(s);
}

static RegisterAccessInfo xmpu_regs_info[] = {
    {   .name = "CTRL",  .decode.addr = A_CTRL,
        .reset = 0x3,
        .rsvd = 0xfffffff0,
        .ro = 0xfffffff8,
        .post_write = xmpu_setup_postw,
    },{ .name = "ERR_STATUS1",  .decode.addr = A_ERR_STATUS1,
        .rsvd = 0xfff00000,
        .ro = 0xffffffff,
    },{ .name = "ERR_STATUS2",  .decode.addr = A_ERR_STATUS2,
        .rsvd = 0xfffffc00,
        .ro = 0xffffffff,
    },{ .name = "POISON",  .decode.addr = A_POISON,
        .rsvd = 0xffe00000,
        .ro = 0xffefffff,
        .post_write = xmpu_setup_postw,
    },{ .name = "ISR",  .decode.addr = A_ISR,
        .rsvd = 0xfffffff0,
        .ro = 0xfffffff0,
        .w1c = 0xf,
        .post_write = isr_postw,
    },{ .name = "IMR",  .decode.addr = A_IMR,
        .reset = 0xf,
        .rsvd = 0xfffffff0,
        .ro = 0xffffffff,
    },{ .name = "IEN",  .decode.addr = A_IEN,
        .rsvd = 0xfffffff0,
        .ro = 0xfffffff0,
        .pre_write = ien_prew,
    },{ .name = "IDS",  .decode.addr = A_IDS,
        .rsvd = 0xfffffff0,
        .ro = 0xfffffff0,
        .pre_write = ids_prew,
    },{ .name = "LOCK",  .decode.addr = A_LOCK,
    },{ .name = "ECO",  .decode.addr = A_ECO,
    },{ .name = "R00_START",  .decode.addr = A_R00_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R00_END",  .decode.addr = A_R00_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R00_MASTER",  .decode.addr = A_R00_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R00_CONFIG",  .decode.addr = A_R00_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R01_START",  .decode.addr = A_R01_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R01_END",  .decode.addr = A_R01_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R01_MASTER",  .decode.addr = A_R01_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R01_CONFIG",  .decode.addr = A_R01_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R02_START",  .decode.addr = A_R02_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R02_END",  .decode.addr = A_R02_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R02_MASTER",  .decode.addr = A_R02_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R02_CONFIG",  .decode.addr = A_R02_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R03_START",  .decode.addr = A_R03_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R03_END",  .decode.addr = A_R03_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R03_MASTER",  .decode.addr = A_R03_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R03_CONFIG",  .decode.addr = A_R03_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R04_START",  .decode.addr = A_R04_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R04_END",  .decode.addr = A_R04_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R04_MASTER",  .decode.addr = A_R04_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R04_CONFIG",  .decode.addr = A_R04_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R05_START",  .decode.addr = A_R05_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R05_END",  .decode.addr = A_R05_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R05_MASTER",  .decode.addr = A_R05_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R05_CONFIG",  .decode.addr = A_R05_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R06_START",  .decode.addr = A_R06_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R06_END",  .decode.addr = A_R06_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R06_MASTER",  .decode.addr = A_R06_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R06_CONFIG",  .decode.addr = A_R06_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R07_START",  .decode.addr = A_R07_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R07_END",  .decode.addr = A_R07_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R07_MASTER",  .decode.addr = A_R07_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R07_CONFIG",  .decode.addr = A_R07_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R08_START",  .decode.addr = A_R08_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R08_END",  .decode.addr = A_R08_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R08_MASTER",  .decode.addr = A_R08_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R08_CONFIG",  .decode.addr = A_R08_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R09_START",  .decode.addr = A_R09_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R09_END",  .decode.addr = A_R09_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R09_MASTER",  .decode.addr = A_R09_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R09_CONFIG",  .decode.addr = A_R09_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R10_START",  .decode.addr = A_R10_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R10_END",  .decode.addr = A_R10_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R10_MASTER",  .decode.addr = A_R10_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R10_CONFIG",  .decode.addr = A_R10_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R11_START",  .decode.addr = A_R11_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R11_END",  .decode.addr = A_R11_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R11_MASTER",  .decode.addr = A_R11_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R11_CONFIG",  .decode.addr = A_R11_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R12_START",  .decode.addr = A_R12_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R12_END",  .decode.addr = A_R12_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R12_MASTER",  .decode.addr = A_R12_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R12_CONFIG",  .decode.addr = A_R12_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R13_START",  .decode.addr = A_R13_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R13_END",  .decode.addr = A_R13_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R13_MASTER",  .decode.addr = A_R13_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R13_CONFIG",  .decode.addr = A_R13_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R14_START",  .decode.addr = A_R14_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R14_END",  .decode.addr = A_R14_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R14_MASTER",  .decode.addr = A_R14_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R14_CONFIG",  .decode.addr = A_R14_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    },{ .name = "R15_START",  .decode.addr = A_R15_START,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R15_END",  .decode.addr = A_R15_END,
        .rsvd = 0xfff00000,
        .ro = 0xfff00000,
    },{ .name = "R15_MASTER",  .decode.addr = A_R15_MASTER,
        .rsvd = 0xfc00fc00,
        .ro = 0xfc00fc00,
    },{ .name = "R15_CONFIG",  .decode.addr = A_R15_CONFIG,
        .reset = 0x8,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffe0,
    }
};

static void xmpu_reset(DeviceState *dev)
{
    XMPU *s = XILINX_XMPU(dev);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }

    AF_DP32(s->regs, CTRL, ALIGNCFG, s->cfg.align);
    isr_update_irq(s);
    xmpu_flush(s);
}

static uint64_t xmpu_read(void *opaque, hwaddr addr, unsigned size,
                          MemTxAttrs attr)
{
    XMPU *s = XILINX_XMPU(opaque);
    RegisterInfo *r = &s->regs_info[addr / 4];

    if (!attr.secure) {
        /* Non secure, return zero */
        return 0;
    }

    if (!r->data) {
        qemu_log("%s: Decode error: read from %" HWADDR_PRIx "\n",
                 object_get_canonical_path(OBJECT(s)),
                 addr);
        AF_DP32(s->regs, ISR, INV_APB, true);
        return 0;
    }
    return register_read(r);
}

static void xmpu_write(void *opaque, hwaddr addr, uint64_t value,
                      unsigned size, MemTxAttrs attr)
{
    XMPU *s = XILINX_XMPU(opaque);
    RegisterInfo *r = &s->regs_info[addr / 4];

    if (!attr.secure) {
        return;
    }

    if (!r->data) {
        qemu_log("%s: Decode error: write to %" HWADDR_PRIx "=%" PRIx64 "\n",
                 object_get_canonical_path(OBJECT(s)),
                 addr, value);
        AF_DP32(s->regs, ISR, INV_APB, true);
        return;
    }
    register_write(r, value, ~0);

    if (addr > R_R00_MASTER) {
        xmpu_flush(s);
    }
}

static void xmpu_access(MemoryTransaction *tr)
{
    MemTxAttrs attr = tr->attr;
    void *opaque = tr->opaque;
    XMPU *s = XILINX_XMPU(opaque);
    hwaddr addr = tr->addr;
    unsigned size = tr->size;
    uint64_t value = tr->data.u64;;
    bool is_write = tr->rw;
    bool locked;

    locked = AF_EX32(s->regs, LOCK, REGWRDIS);
    if (locked && (addr < A_ISR || addr >= A_LOCK)) {
        /* Locked access.  */
        qemu_log_mask(LOG_GUEST_ERROR, "%s: accessing locked register %lx\n",
                      object_get_canonical_path(OBJECT(s)), addr);
        tr->data.u64 = 0;
        return;
    }

    if (is_write) {
        xmpu_write(opaque, addr, value, size, attr);
    } else {
        tr->data.u64 = xmpu_read(opaque, addr, size, attr);
    }
}

static const MemoryRegionOps xmpu_ops = {
    .access = xmpu_access,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 1,
        .max_access_size = 8,
    },
};

static IOMMUTLBEntry xmpu_master_translate(XMPUMaster *xm, hwaddr addr,
                                           MemTxAttrs attr,
                                           bool *sec_vio)
{
    XMPU *s = xm->parent;
    XMPURegion xr;
    IOMMUTLBEntry ret = {
        .iova = addr,
        .translated_addr = addr,
        .addr_mask = s->addr_mask,
        .perm = IOMMU_NONE,
    };
    AddressSpace *as_map[] = {
        [IOMMU_NONE] = &xm->down.none.as,
        [IOMMU_RO] = &xm->down.ro.as,
        [IOMMU_WO] = &xm->down.none.as,
        [IOMMU_RW] = &xm->down.rw.as,
    };
    bool default_wr = AF_EX32(s->regs, CTRL, DEFWRALLOWED);
    bool default_rd = AF_EX32(s->regs, CTRL, DEFRDALLOWED);
    bool sec = attr.secure;
    bool sec_access_check;
    unsigned int nr_matched = 0;
    int i;

    /* No security violation by default.  */
    *sec_vio = false;

    if (!s->enabled) {
        ret.target_as = &xm->down.rw.as;
        ret.perm = IOMMU_RW;
        return ret;
    }

    /* Convert to an absolute address to simplify the compare logic.  */
    addr += s->cfg.base;

    /* Lookup if this address fits a region.  */
    for (i = NR_XMPU_REGIONS - 1; i >= 0; i--) {
        bool id_match;
        bool match;

        xmpu_decode_region(s, &xr, i);
        if (!xr.config.enable) {
            continue;
        }

        if (xr.start & s->addr_mask) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "%s: Bad region start address %" PRIx64 "\n",
                          s->prefix, xr.start);
        }

        if (xr.end & s->addr_mask) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "%s: Bad region end address %" PRIx64 "\n",
                           s->prefix, xr.end);
        }

        if (xr.start < s->cfg.base) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "%s: Too low region start address %" PRIx64 "\n",
                           s->prefix, xr.end);
        }

        xr.start &= ~s->addr_mask;
        xr.end &= ~s->addr_mask;

        id_match = (xr.master.mask & xr.master.id) ==
                       (xr.master.mask & attr.master_id);
        match = id_match && (addr >= xr.start && addr < xr.end);
        if (match) {
            nr_matched++;
            /* Determine if this region is accessible by the transactions
             * security domain.
             */
            if (xr.config.nschecktype) {
                /* In strict mode, secure accesses are not allowed to
                 * non-secure regions (and vice-versa).
                 */
                sec_access_check = (sec != xr.config.regionns);
            } else {
                /* In relaxed mode secure accesses can access any region
                 * while non-secure can only access non-secure areas.
                 */
                sec_access_check = (sec || xr.config.regionns);
            }

            if (sec_access_check) {
                if (xr.config.rdallowed) {
                    ret.perm |= IOMMU_RO;
                }
                if (xr.config.wrallowed) {
                    ret.perm |= IOMMU_WO;
                }
            } else {
                *sec_vio = true;
            }
            break;
        }
    }

    if (nr_matched == 0) {
        if (default_rd) {
            ret.perm |= IOMMU_RO;
        }
        if (default_wr) {
            ret.perm |= IOMMU_WO;
        }
    }

    ret.target_as = as_map[ret.perm];
    if (ret.perm == IOMMU_RO) {
        ret.target_as = &xm->down.none.as;
    }
#if 0
    qemu_log("%s: nr_matched=%d AS=%p addr=%lx - > %lx (%lx) perm=%x\n",
           __func__, nr_matched, ret.target_as, ret.iova,
          ret.translated_addr, (addr | ret.addr_mask) - addr + 1, ret.perm);
#endif
    return ret;
}

static uint64_t zero_read(void *opaque, hwaddr addr, unsigned size,
                          MemTxAttrs attr)
{
    XMPUMaster *xm = opaque;
    XMPU *s = xm->parent;
    bool poisoncfg = AF_EX32(s->regs, CTRL, POISONCFG);
    uint64_t value = 0;
    bool sec_vio;
    IOMMUTLBEntry ret = xmpu_master_translate(xm, addr, attr, &sec_vio);

    if (ret.perm & IOMMU_RO) {
        dma_memory_read(&xm->down.rw.as, addr, &value, size);
    } else {
        if (!(s->regs[R_ISR] & (7 << 1))) {
            s->regs[R_ERR_STATUS1] = (addr + s->cfg.base) >> 12;
        }
        if (poisoncfg) {
            AddressSpace *as = xm->parent_as;
            addr = (AF_EX32(s->regs, POISON, BASE) << 12) | (addr & 0xfff);
            dma_memory_read(as, addr, &value, size);
        }
        AF_DP32(s->regs, ERR_STATUS2, AXI_ID, attr.master_id);
        if (sec_vio) {
            AF_DP32(s->regs, ISR, SECURITYVIO, true);
        } else {
            AF_DP32(s->regs, ISR, RDPERMVIO, true);
        }
        isr_update_irq(s);
    }
    return value;
}

static void zero_write(void *opaque, hwaddr addr, uint64_t value,
                       unsigned size, MemTxAttrs attr)
{
    XMPUMaster *xm = opaque;
    XMPU *s = xm->parent;
    bool poisoncfg = AF_EX32(s->regs, CTRL, POISONCFG);
    bool sec_vio;
    IOMMUTLBEntry ret = xmpu_master_translate(xm, addr, attr, &sec_vio);

    if (ret.perm & IOMMU_WO) {
        dma_memory_write(&xm->down.rw.as, addr, &value, size);
    } else {
        if (!(s->regs[R_ISR] & (7 << 1))) {
            s->regs[R_ERR_STATUS1] = (addr + s->cfg.base) >> 12;
        }
        if (poisoncfg) {
            AddressSpace *as = xm->parent_as;
            addr = (AF_EX32(s->regs, POISON, BASE) << 12) | (addr & 0xfff);
            dma_memory_write(as, addr, &value, size);
        }
        AF_DP32(s->regs, ERR_STATUS2, AXI_ID, attr.master_id);
        if (sec_vio) {
            AF_DP32(s->regs, ISR, SECURITYVIO, true);
        } else {
            AF_DP32(s->regs, ISR, WRPERMVIO, true);
        }
        isr_update_irq(s);
    }
}

static void zero_access(MemoryTransaction *tr)
{
    MemTxAttrs attr = tr->attr;
    void *opaque = tr->opaque;
    hwaddr addr = tr->addr;
    unsigned size = tr->size;
    uint64_t value = tr->data.u64;;
    bool is_write = tr->rw;

    if (is_write) {
        zero_write(opaque, addr, value, size, attr);
    } else {
        tr->data.u64 = zero_read(opaque, addr, size, attr);
    }
}

static const MemoryRegionOps zero_ops = {
    .access = zero_access,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static IOMMUTLBEntry xmpu_translate(MemoryRegion *mr, hwaddr addr,
                                    bool is_write, MemTxAttrs attr)
{
    XMPUMaster *xm;
    IOMMUTLBEntry ret;
    bool sec_vio;

    xm = container_of(mr, XMPUMaster, iommu);
    ret = xmpu_master_translate(xm, addr, attr, &sec_vio);
#if 0
    qemu_log("%s: nr_matched=%d addr=%lx - > %lx (%lx) perm=%x\n",
           __func__, nr_matched, ret.iova,
          ret.translated_addr, (addr | ret.addr_mask) - addr + 1, ret.perm);
#endif
    ret.perm = IOMMU_RW;
    return ret;
}

static MemoryRegionIOMMUOps xmpu_iommu_ops = {
    .translate_attr = xmpu_translate,
};

#define MASK_4K  (0xfff)
#define MASK_1M  (0xfffff)
static void xmpu_realize(DeviceState *dev, Error **errp)
{
    XMPU *s = XILINX_XMPU(dev);
    unsigned int i;

    s->prefix = object_get_canonical_path(OBJECT(dev));

    for (i = 0; i < ARRAY_SIZE(xmpu_regs_info); ++i) {
        RegisterInfo *r = &s->regs_info[xmpu_regs_info[i].decode.addr/4];

        *r = (RegisterInfo) {
            .data = (uint8_t *)&s->regs[
                    xmpu_regs_info[i].decode.addr/4],
            .data_size = sizeof(uint32_t),
            .access = &xmpu_regs_info[i],
            .debug = XILINX_XMPU_ERR_DEBUG,
            .prefix = s->prefix,
            .opaque = s,
        };
    }

    s->addr_shift = s->cfg.align ? 20 : 12;
    s->addr_mask = (1ULL << s->addr_shift) - 1;

    s->masters[0].parent = s;
}

static void xmpu_init(Object *obj)
{
    XMPU *s = XILINX_XMPU(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

    sysbus_init_irq(sbd, &s->irq_isr);

    object_property_add_link(obj, "protected-mr", TYPE_MEMORY_REGION,
                             (Object **)&s->protected_mr,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);
    object_property_add_link(obj, "mr-0", TYPE_MEMORY_REGION,
                             (Object **)&s->masters[0].parent_mr,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);

    qdev_init_gpio_out(DEVICE(sbd), &s->enabled_signal, 1);
}

static bool xmpu_parse_reg(FDTGenericMMap *obj, FDTGenericRegPropInfo reg,
                           Error **errp)
{
    XMPU *s = XILINX_XMPU(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    ObjectClass *klass = object_class_by_name(TYPE_XILINX_XMPU);
    FDTGenericMMapClass *parent_fmc;
    char *name;
    unsigned int i, mid;

    parent_fmc = FDT_GENERIC_MMAP_CLASS(object_class_get_parent(klass));
    memory_region_init_io(&s->iomem, OBJECT(obj), &xmpu_ops, s,
                          TYPE_XILINX_XMPU, R_MAX * 4);
    sysbus_init_mmio(sbd, &s->iomem);

    for (i = 0; i < (reg.n - 1); i++) {
        mid = i;

        /* Create the read/write address space */
        name = g_strdup_printf("xmpu-down-rw-master%d", mid);
        memory_region_init_alias(&s->masters[mid].down.rw.mr, OBJECT(s),
                                 name, s->protected_mr,
                                 0, UINT64_MAX);
        address_space_init(&s->masters[mid].down.rw.as,
                           &s->masters[mid].down.rw.mr, name);
        g_free(name);

        /* Create the read only address space  */
        name = g_strdup_printf("xmpu-down-ro-master%d", mid);
        memory_region_init_alias(&s->masters[mid].down.ro.mr, OBJECT(s),
                                 name, s->protected_mr,
                                 0, UINT64_MAX);
        memory_region_set_readonly(&s->masters[mid].down.ro.mr, true);
        address_space_init(&s->masters[mid].down.ro.as,
                           &s->masters[mid].down.ro.mr, name);
        g_free(name);

        /* Create the no access address space */
        name = g_strdup_printf("xmpu-down-none-master\n");
        memory_region_init_io(&s->masters[mid].down.none.mr, OBJECT(s),
                              &zero_ops, &s->masters[mid],
                              name, UINT64_MAX);
        address_space_init(&s->masters[mid].down.none.as,
                           &s->masters[mid].down.none.mr, name);
        g_free(name);

        name = g_strdup_printf("xmpu-master-%d\n", mid);
        s->masters[mid].parent_as = address_space_init_shareable(
                                            s->masters[mid].parent_mr,
                                            NULL);

        memory_region_init_iommu(&s->masters[mid].iommu,
                                 OBJECT(s), &xmpu_iommu_ops,
                                 name, reg.s[i + 1]);
        g_free(name);

        name = g_strdup_printf("xmpu-mr-%d\n", mid);
        memory_region_init(&s->masters[mid].mr, OBJECT(s), name, UINT64_MAX);

        memory_region_add_subregion_overlap(&s->masters[mid].mr,
                                            0, &s->masters[mid].down.rw.mr, 0);
        memory_region_add_subregion_overlap(&s->masters[mid].mr,
                                            0, &s->masters[mid].iommu, 1);
        memory_region_set_enabled(&s->masters[mid].iommu, false);
        sysbus_init_mmio(sbd, &s->masters[mid].mr);
        g_free(name);
    }
    s->cfg.nr_masters = (i / 2) + 1;

    return parent_fmc ? parent_fmc->parse_reg(obj, reg, errp) : false;
}

static Property xmpu_properties[] = {
    DEFINE_PROP_BOOL("align", XMPU, cfg.align, 0),
    DEFINE_PROP_BOOL("poison", XMPU, cfg.poison, 0),
    DEFINE_PROP_UINT64("protected-base", XMPU, cfg.base, 0),
    DEFINE_PROP_END_OF_LIST(),
};

static const VMStateDescription vmstate_xmpu = {
    .name = TYPE_XILINX_XMPU,
    .version_id = 1,
    .minimum_version_id = 1,
    .minimum_version_id_old = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, XMPU, R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static void xmpu_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    FDTGenericMMapClass *fmc = FDT_GENERIC_MMAP_CLASS(klass);

    dc->reset = xmpu_reset;
    dc->realize = xmpu_realize;
    dc->vmsd = &vmstate_xmpu;
    dc->props = xmpu_properties;
    fmc->parse_reg = xmpu_parse_reg;
}

static const TypeInfo xmpu_info = {
    .name          = TYPE_XILINX_XMPU,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(XMPU),
    .class_init    = xmpu_class_init,
    .instance_init = xmpu_init,
    .interfaces    = (InterfaceInfo[]) {
        { TYPE_FDT_GENERIC_MMAP },
        { },
    },
};

static void xmpu_register_types(void)
{
    type_register_static(&xmpu_info);
}

type_init(xmpu_register_types)
