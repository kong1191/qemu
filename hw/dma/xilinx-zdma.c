/*
 * QEMU model of the ZDMA DMA designed to serve Display Port
 *
 * Copyright (c) 2014 Xilinx Inc.
 *
 * Partially autogenerated by xregqemu.py 2014-07-21.
 * Written by Edgar E. Iglesias <edgar.iglesias@xilinx.com>
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

#ifndef XILINX_ZDMA_ERR_DEBUG
#define XILINX_ZDMA_ERR_DEBUG 0
#endif

#define TYPE_XILINX_ZDMA "xlnx.zdma"

#define XILINX_ZDMA(obj) \
     OBJECT_CHECK(ZDMA, (obj), TYPE_XILINX_ZDMA)

#define ZDMA_INT_BF(REG) \
    FIELD(ZDMA_CH_ ## REG, DMA_PAUSE, 1, 11)       \
    FIELD(ZDMA_CH_ ## REG, DMA_DONE, 1, 10)        \
    FIELD(ZDMA_CH_ ## REG, AXI_WR_DATA, 1, 9)      \
    FIELD(ZDMA_CH_ ## REG, AXI_RD_DATA, 1, 8)      \
    FIELD(ZDMA_CH_ ## REG, AXI_RD_DST_DSCR, 1, 7)  \
    FIELD(ZDMA_CH_ ## REG, AXI_RD_SRC_DSCR, 1, 6)  \
    FIELD(ZDMA_CH_ ## REG, IRQ_DST_ACCT_ERR, 1, 5) \
    FIELD(ZDMA_CH_ ## REG, IRQ_SRC_ACCT_ERR, 1, 4) \
    FIELD(ZDMA_CH_ ## REG, BYTE_CNT_OVRFL, 1, 3)   \
    FIELD(ZDMA_CH_ ## REG, DST_DSCR_DONE, 1, 2)    \
    FIELD(ZDMA_CH_ ## REG, SRC_DSCR_DONE, 1, 1)    \
    FIELD(ZDMA_CH_ ## REG, INV_APB, 1, 0)

REG32(ZDMA_ERR_CTRL, 0x0)
    FIELD(ZDMA_ERR_CTRL, APB_ERR_RES, 1, 0)
REG32(ZDMA_CH_ECO, 0x4)
REG32(ZDMA_CH_ISR, 0x100)
    ZDMA_INT_BF(ISR)
REG32(ZDMA_CH_IMR, 0x104)
    ZDMA_INT_BF(IMR)
REG32(ZDMA_CH_IEN, 0x108)
    ZDMA_INT_BF(IEN)
REG32(ZDMA_CH_IDS, 0x10c)
    ZDMA_INT_BF(IDS)
REG32(ZDMA_CH_CTRL0, 0x110)
    FIELD(ZDMA_CH_CTRL0, OVR_FETCH, 1, 7)
    FIELD(ZDMA_CH_CTRL0, POINT_TYPE, 1, 6)
    FIELD(ZDMA_CH_CTRL0, MODE, 2, 4)
    FIELD(ZDMA_CH_CTRL0, RATE_CNTL, 1, 3)
    FIELD(ZDMA_CH_CTRL0, CONT_ADDR, 1, 2)
    FIELD(ZDMA_CH_CTRL0, CONT, 1, 1)
REG32(ZDMA_CH_CTRL1, 0x114)
    FIELD(ZDMA_CH_CTRL1, DST_ISSUE, 5, 5)
    FIELD(ZDMA_CH_CTRL1, SRC_ISSUE, 5, 0)
REG32(ZDMA_CH_PERIF, 0x118)
    FIELD(ZDMA_CH_PERIF, PROG_CELL_CNT, 4, 2)
    FIELD(ZDMA_CH_PERIF, SIDE, 1, 1)
    FIELD(ZDMA_CH_PERIF, EN, 1, 0)
REG32(ZDMA_CH_STATUS, 0x11c)
    FIELD(ZDMA_CH_STATUS, STATE, 2, 0)
REG32(ZDMA_CH_DATA_ATTR, 0x120)
    FIELD(ZDMA_CH_DATA_ATTR, ARBURST, 2, 26)
    FIELD(ZDMA_CH_DATA_ATTR, ARCACHE, 4, 22)
    FIELD(ZDMA_CH_DATA_ATTR, ARQOS, 4, 18)
    FIELD(ZDMA_CH_DATA_ATTR, ARLEN, 4, 14)
    FIELD(ZDMA_CH_DATA_ATTR, AWBURST, 2, 12)
    FIELD(ZDMA_CH_DATA_ATTR, AWCACHE, 4, 8)
    FIELD(ZDMA_CH_DATA_ATTR, AWQOS, 4, 4)
    FIELD(ZDMA_CH_DATA_ATTR, AWLEN, 4, 0)
REG32(ZDMA_CH_DSCR_ATTR, 0x124)
    FIELD(ZDMA_CH_DSCR_ATTR, AXCOHRNT, 1, 8)
    FIELD(ZDMA_CH_DSCR_ATTR, AXCACHE, 4, 4)
    FIELD(ZDMA_CH_DSCR_ATTR, AXQOS, 4, 0)
REG32(ZDMA_CH_SRC_DSCR_WORD0, 0x128)
REG32(ZDMA_CH_SRC_DSCR_WORD1, 0x12c)
    FIELD(ZDMA_CH_SRC_DSCR_WORD1, MSB, 17, 0)
REG32(ZDMA_CH_SRC_DSCR_WORD2, 0x130)
    FIELD(ZDMA_CH_SRC_DSCR_WORD2, SIZE, 30, 0)
REG32(ZDMA_CH_SRC_DSCR_WORD3, 0x134)
    FIELD(ZDMA_CH_SRC_DSCR_WORD3, CMD, 2, 3)
    FIELD(ZDMA_CH_SRC_DSCR_WORD3, INTR, 1, 2)
    FIELD(ZDMA_CH_SRC_DSCR_WORD3, TYPE, 1, 1)
    FIELD(ZDMA_CH_SRC_DSCR_WORD3, COHRNT, 1, 0)
REG32(ZDMA_CH_DST_DSCR_WORD0, 0x138)
REG32(ZDMA_CH_DST_DSCR_WORD1, 0x13c)
    FIELD(ZDMA_CH_DST_DSCR_WORD1, MSB, 17, 0)
REG32(ZDMA_CH_DST_DSCR_WORD2, 0x140)
    FIELD(ZDMA_CH_DST_DSCR_WORD2, SIZE, 30, 0)
REG32(ZDMA_CH_DST_DSCR_WORD3, 0x144)
    FIELD(ZDMA_CH_DST_DSCR_WORD3, INTR, 1, 2)
    FIELD(ZDMA_CH_DST_DSCR_WORD3, TYPE, 1, 1)
    FIELD(ZDMA_CH_DST_DSCR_WORD3, COHRNT, 1, 0)
REG32(ZDMA_CH_WR_ONLY_WORD0, 0x148)
REG32(ZDMA_CH_WR_ONLY_WORD1, 0x14c)
REG32(ZDMA_CH_WR_ONLY_WORD2, 0x150)
REG32(ZDMA_CH_WR_ONLY_WORD3, 0x154)
REG32(ZDMA_CH_SRC_START_LSB, 0x158)
REG32(ZDMA_CH_SRC_START_MSB, 0x15c)
    FIELD(ZDMA_CH_SRC_START_MSB, ADDR, 17, 0)
REG32(ZDMA_CH_DST_START_LSB, 0x160)
REG32(ZDMA_CH_DST_START_MSB, 0x164)
    FIELD(ZDMA_CH_DST_START_MSB, ADDR, 17, 0)
REG32(ZDMA_CH_SRC_CUR_PYLD_LSB, 0x168)
REG32(ZDMA_CH_SRC_CUR_PYLD_MSB, 0x16c)
    FIELD(ZDMA_CH_SRC_CUR_PYLD_MSB, ADDR, 17, 0)
REG32(ZDMA_CH_DST_CUR_PYLD_LSB, 0x170)
REG32(ZDMA_CH_DST_CUR_PYLD_MSB, 0x174)
    FIELD(ZDMA_CH_DST_CUR_PYLD_MSB, ADDR, 17, 0)
REG32(ZDMA_CH_SRC_CUR_DSCR_LSB, 0x178)
REG32(ZDMA_CH_SRC_CUR_DSCR_MSB, 0x17c)
    FIELD(ZDMA_CH_SRC_CUR_DSCR_MSB, ADDR, 17, 0)
REG32(ZDMA_CH_DST_CUR_DSCR_LSB, 0x180)
REG32(ZDMA_CH_DST_CUR_DSCR_MSB, 0x184)
    FIELD(ZDMA_CH_DST_CUR_DSCR_MSB, ADDR, 17, 0)
REG32(ZDMA_CH_TOTAL_BYTE, 0x188)
REG32(ZDMA_CH_RATE_CNTL, 0x18c)
    FIELD(ZDMA_CH_RATE_CNTL, CNT, 12, 0)
REG32(ZDMA_CH_IRQ_SRC_ACCT, 0x190)
    FIELD(ZDMA_CH_IRQ_SRC_ACCT, CNT, 8, 0)
REG32(ZDMA_CH_IRQ_DST_ACCT, 0x194)
    FIELD(ZDMA_CH_IRQ_DST_ACCT, CNT, 8, 0)
REG32(ZDMA_CH_DBG0, 0x198)
    FIELD(ZDMA_CH_DBG0, CMN_BUF_FREE, 9, 0)
REG32(ZDMA_CH_DBG1, 0x19c)
    FIELD(ZDMA_CH_DBG1, CMN_BUF_OCC, 9, 0)
REG32(ZDMA_CH_CTRL2, 0x200)
    FIELD(ZDMA_CH_CTRL2, EN, 1, 0)

#define R_MAX (R_ZDMA_CH_CTRL2 + 1)

typedef enum {
    DISABLED = 0,
    ENABLED = 1,
    PAUSED = 2,
} ZDMAState;

enum {
    PT_REG = 0,
    PT_MEM = 1,
};

enum {
    CMD_HALT = 1,
    CMD_STOP = 2,
};

enum {
    RW_MODE_RW = 0,
    RW_MODE_WO = 1,
    RW_MODE_RO = 2,
};

enum {
    DTYPE_LINEAR = 0,
    DTYPE_LINKED = 1,
};

enum {
    AXI_BURST_FIXED = 0,
    AXI_BURST_INCR  = 1,
};

typedef union {
    struct {
        uint64_t addr;
        uint32_t size;
        uint32_t attr;
    };
    uint32_t words[4];
} ZDMADescr;

typedef struct ZDMA {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    MemTxAttrs *attr;
    MemoryRegion *dma_mr;
    AddressSpace *dma_as;
    qemu_irq irq_zdma_ch0;

    struct {
        uint32_t bus_width;
    } cfg;

    ZDMAState state;
    bool error;

    ZDMADescr dsc_src;
    ZDMADescr dsc_dst;

    uint32_t regs[R_MAX];
    RegisterInfo regs_info[R_MAX];

    /* We don't model the common bufs. Must be at least 16 bytes
       to model write only mode.  */
    uint8_t buf[2048];
} ZDMA;

static void zdma_ch_update_irq(ZDMA *s)
{
    bool pending;

    pending = s->regs[R_ZDMA_CH_ISR] & ~s->regs[R_ZDMA_CH_IMR];

    qemu_set_irq(s->irq_zdma_ch0, pending);
}

static void zdma_ch_isr_postw(RegisterInfo *reg, uint64_t val64)
{
    ZDMA *s = XILINX_ZDMA(reg->opaque);
    zdma_ch_update_irq(s);
}

static uint64_t zdma_ch_ien_prew(RegisterInfo *reg, uint64_t val64)
{
    ZDMA *s = XILINX_ZDMA(reg->opaque);
    uint32_t val = val64;

    s->regs[R_ZDMA_CH_IMR] &= ~val;
    zdma_ch_update_irq(s);
    return 0;
}

static uint64_t zdma_ch_ids_prew(RegisterInfo *reg, uint64_t val64)
{
    ZDMA *s = XILINX_ZDMA(reg->opaque);
    uint32_t val = val64;

    s->regs[R_ZDMA_CH_IMR] |= val;
    zdma_ch_update_irq(s);
    return 0;
}

static void zdma_set_state(ZDMA *s, ZDMAState state)
{
    s->state = state;
    AF_DP32(s->regs, ZDMA_CH_STATUS, STATE, state);

    /* Signal error if we have an error condition.  */
    if (s->error) {
        AF_DP32(s->regs, ZDMA_CH_STATUS, STATE, 3);
    }
}

/* FIXME: Glue()  */
static void zdma_src_done(ZDMA *s)
{
    unsigned int cnt;
    cnt = AF_EX32(s->regs, ZDMA_CH_IRQ_SRC_ACCT, CNT);
    cnt++;
    AF_DP32(s->regs, ZDMA_CH_IRQ_SRC_ACCT, CNT, cnt);
    AF_DP32(s->regs, ZDMA_CH_ISR, SRC_DSCR_DONE, true);

    /* Did we overflow?  */
    if (cnt != AF_EX32(s->regs, ZDMA_CH_IRQ_SRC_ACCT, CNT)) {
        AF_DP32(s->regs, ZDMA_CH_ISR, IRQ_SRC_ACCT_ERR, true);
    }
    zdma_ch_update_irq(s);
}

static void zdma_dst_done(ZDMA *s)
{
    unsigned int cnt;
    cnt = AF_EX32(s->regs, ZDMA_CH_IRQ_DST_ACCT, CNT);
    cnt++;
    AF_DP32(s->regs, ZDMA_CH_IRQ_DST_ACCT, CNT, cnt);
    AF_DP32(s->regs, ZDMA_CH_ISR, DST_DSCR_DONE, true);

    /* Did we overflow?  */
    if (cnt != AF_EX32(s->regs, ZDMA_CH_IRQ_DST_ACCT, CNT)) {
        AF_DP32(s->regs, ZDMA_CH_ISR, IRQ_DST_ACCT_ERR, true);
    }
    zdma_ch_update_irq(s);
}

static uint64_t zdma_get_regaddr64(ZDMA *s, unsigned int basereg)
{
    uint64_t addr;

    addr = s->regs[basereg + 1];
    addr <<= 32;
    addr |= s->regs[basereg];

    return addr;
}

static void zdma_put_regaddr64(ZDMA *s, unsigned int basereg, uint64_t addr)
{
    s->regs[basereg] = addr;
    s->regs[basereg + 1] = addr >> 32;
}

static bool zdma_load_descriptor(ZDMA *s, uint64_t addr, void *buf)
{
    /* ZDMA descriptors must be aligned to their own size.  */
    if (addr % sizeof(ZDMADescr)) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "zdma: unaligned descriptor at %" PRIx64,
                      addr);
        memset(buf, 0xdeadbeef, sizeof(ZDMADescr));
        s->error = true;
        return false;
    }

    /* Load descriptors. FIXME: handle endiannes conversion.  */
    address_space_rw_attr(s->dma_as, addr, buf, sizeof(ZDMADescr), false,
                          *s->attr);
    return true;
}

static void zdma_load_src_descriptor(ZDMA *s)
{
    uint64_t src_addr;
    unsigned int ptype = AF_EX32(s->regs, ZDMA_CH_CTRL0, POINT_TYPE);

    if (ptype == PT_REG) {
        memcpy(&s->dsc_src, &s->regs[R_ZDMA_CH_SRC_DSCR_WORD0],
               sizeof(s->dsc_src));
        return;
    }

    src_addr = zdma_get_regaddr64(s, R_ZDMA_CH_SRC_CUR_DSCR_LSB);

    if (!zdma_load_descriptor(s, src_addr, &s->dsc_src)) {
        AF_DP32(s->regs, ZDMA_CH_ISR, AXI_RD_SRC_DSCR, true);
    }
}

static void zdma_load_dst_descriptor(ZDMA *s)
{
    uint64_t dst_addr;
    unsigned int ptype = AF_EX32(s->regs, ZDMA_CH_CTRL0, POINT_TYPE);

    if (ptype == PT_REG) {
        memcpy(&s->dsc_dst, &s->regs[R_ZDMA_CH_DST_DSCR_WORD0],
               sizeof(s->dsc_src));
        return;
    }

    dst_addr = zdma_get_regaddr64(s, R_ZDMA_CH_DST_CUR_DSCR_LSB);

    if (!zdma_load_descriptor(s, dst_addr, &s->dsc_dst)) {
        AF_DP32(s->regs, ZDMA_CH_ISR, AXI_RD_DST_DSCR, true);
    }
}

static uint64_t zdma_update_descr_addr(ZDMA *s, bool type, unsigned int basereg)
{
    uint64_t addr, next;

    if (type == DTYPE_LINEAR) {
        next = zdma_get_regaddr64(s, basereg);
        next += sizeof(s->dsc_dst);
        zdma_put_regaddr64(s, basereg, next);
    } else {
        addr = zdma_get_regaddr64(s, basereg);
        addr += sizeof(s->dsc_dst);
        address_space_rw_attr(s->dma_as, addr, (void *) &next, 8, false,
                              *s->attr);
        zdma_put_regaddr64(s, basereg, next);
    }
    return next;
}

static void zdma_write_dst(ZDMA *s, uint8_t *buf, uint32_t len)
{
    uint32_t dst_size, dlen;
    bool dst_intr, dst_type;
    unsigned int ptype = AF_EX32(s->regs, ZDMA_CH_CTRL0, POINT_TYPE);
    unsigned int rw_mode = AF_EX32(s->regs, ZDMA_CH_CTRL0, MODE);
    unsigned int burst_type = AF_EX32(s->regs, ZDMA_CH_DATA_ATTR, AWBURST);

    /* FIXED burst types are only supported in simple dma mode.  */
    if (ptype != PT_REG) {
        burst_type = AXI_BURST_INCR;
    }

    while (len) {
        dst_size = F_EX32(s->dsc_dst.words[2], ZDMA_CH_DST_DSCR_WORD2, SIZE);
        dst_type = F_EX32(s->dsc_dst.words[3], ZDMA_CH_DST_DSCR_WORD3, TYPE);
        if (dst_size == 0 && ptype == PT_MEM) {
            uint64_t next;
            next = zdma_update_descr_addr(s, dst_type, R_ZDMA_CH_DST_CUR_DSCR_LSB);
            zdma_load_descriptor(s, next, &s->dsc_dst);
            dst_size = F_EX32(s->dsc_dst.words[2], ZDMA_CH_DST_DSCR_WORD2, SIZE);
            dst_type = F_EX32(s->dsc_dst.words[3], ZDMA_CH_DST_DSCR_WORD3, TYPE);
        }

        /* Match what hardware does by ignoring the dst_size and only using
         * the src size for Simple register mode.  */
        if (ptype == PT_REG && rw_mode != RW_MODE_WO) {
            dst_size = len;
        }

        if (dst_size == 0) {
            qemu_log("Can't write to dst\n");
        }
        dst_intr = F_EX32(s->dsc_dst.words[3], ZDMA_CH_DST_DSCR_WORD3, INTR);

        dlen = len > dst_size ? dst_size : len;
        if (burst_type == AXI_BURST_FIXED) {
            if (dlen > (s->cfg.bus_width / 8)) {
                dlen = s->cfg.bus_width / 8;
            }
        }

        address_space_rw_attr(s->dma_as, s->dsc_dst.addr, buf, dlen, true,
                              *s->attr);
        if (burst_type == AXI_BURST_INCR) {
            s->dsc_dst.addr += dlen;
        }
        dst_size -= dlen;
        buf += dlen;
        len -= dlen;

        if (dst_size == 0 && dst_intr) {
            zdma_dst_done(s);
        }

        /* Write back to buffered descriptor.  */
        s->dsc_dst.words[2] = F_DP32(s->dsc_dst.words[2], ZDMA_CH_DST_DSCR_WORD2, SIZE, dst_size);
    }
}

static void zdma_process_descr(ZDMA *s)
{
    uint64_t src_addr;
    uint32_t src_size, len;
    unsigned int src_cmd;
    bool src_intr, src_type;
    unsigned int ptype = AF_EX32(s->regs, ZDMA_CH_CTRL0, POINT_TYPE);
    unsigned int rw_mode = AF_EX32(s->regs, ZDMA_CH_CTRL0, MODE);
    unsigned int burst_type = AF_EX32(s->regs, ZDMA_CH_DATA_ATTR, ARBURST);

    src_addr = s->dsc_src.addr;
    src_size = F_EX32(s->dsc_src.words[2], ZDMA_CH_SRC_DSCR_WORD2, SIZE);
    src_cmd = F_EX32(s->dsc_src.words[3], ZDMA_CH_SRC_DSCR_WORD3, CMD);
    src_type = F_EX32(s->dsc_src.words[3], ZDMA_CH_SRC_DSCR_WORD3, TYPE);
    src_intr = F_EX32(s->dsc_src.words[3], ZDMA_CH_SRC_DSCR_WORD3, INTR);

    /* FIXED burst types and non-rw modes are only supported in
     * simple dma mode.
     */
    if (ptype != PT_REG) {
        if (rw_mode != RW_MODE_RW) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "zDMA: rw-mode=%d but not simple DMA mode.\n",
                          rw_mode);
        }
        if (burst_type != AXI_BURST_INCR) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "zDMA: burst_type=%d but not simple DMA mode.\n",
                          burst_type);
        }
        burst_type = AXI_BURST_INCR;
        rw_mode = RW_MODE_RW;
    }

    if (rw_mode == RW_MODE_WO) {
        /* In Simple DMA Write-Only, we need to push DST size bytes
         * regardless of what SRC size is set to.  */
        src_size = F_EX32(s->dsc_dst.words[2], ZDMA_CH_DST_DSCR_WORD2, SIZE);
        memcpy(s->buf, &s->regs[R_ZDMA_CH_WR_ONLY_WORD0], s->cfg.bus_width / 8);
    }

    while (src_size) {
        len = src_size > ARRAY_SIZE(s->buf) ? ARRAY_SIZE(s->buf) : src_size;
        if (burst_type == AXI_BURST_FIXED) {
            if (len > (s->cfg.bus_width / 8)) {
                len = s->cfg.bus_width / 8;
            }
        }

        if (rw_mode == RW_MODE_WO) {
            if (len > s->cfg.bus_width / 8) {
                len = s->cfg.bus_width / 8;
            }
        } else {
            address_space_rw_attr(s->dma_as, src_addr, s->buf, len, false,
                                  *s->attr);
            if (burst_type == AXI_BURST_INCR) {
                src_addr += len;
            }
        }

        if (rw_mode != RW_MODE_RO) {
            zdma_write_dst(s, s->buf, len);
        }

        s->regs[R_ZDMA_CH_TOTAL_BYTE] += len;
        src_size -= len;

        if (src_size == 0) {
            AF_DP32(s->regs, ZDMA_CH_ISR, DMA_DONE, true);
        }

    }

    if (src_intr) {
        zdma_src_done(s);
    }

    /* Load next descriptor.  */
    if (ptype == PT_REG || src_cmd == CMD_STOP) {
        AF_DP32(s->regs, ZDMA_CH_CTRL2, EN, 0);
        zdma_set_state(s, DISABLED);
        return;
    }

    if (src_cmd == CMD_HALT) {
        zdma_set_state(s, PAUSED);
        AF_DP32(s->regs, ZDMA_CH_ISR, DMA_PAUSE, 1);
        zdma_ch_update_irq(s);
        return;
    }

    zdma_update_descr_addr(s, src_type, R_ZDMA_CH_SRC_CUR_DSCR_LSB);
}

static void zdma_run(ZDMA *s)
{
    while (s->state == ENABLED && !s->error) {
        zdma_load_src_descriptor(s);

        if (s->error) {
            zdma_set_state(s, DISABLED);
        } else {
            zdma_process_descr(s);
        }
    }

    zdma_ch_update_irq(s);
}

static void zdma_update_descr_addr_from_start(ZDMA *s)
{
    uint64_t src_addr, dst_addr;

    src_addr = zdma_get_regaddr64(s, R_ZDMA_CH_SRC_START_LSB);
    zdma_put_regaddr64(s, R_ZDMA_CH_SRC_CUR_DSCR_LSB, src_addr);
    dst_addr = zdma_get_regaddr64(s, R_ZDMA_CH_DST_START_LSB);
    zdma_put_regaddr64(s, R_ZDMA_CH_DST_CUR_DSCR_LSB, dst_addr);
    zdma_load_dst_descriptor(s);
}

static void zdma_ch_ctrlx_postw(RegisterInfo *reg, uint64_t val64)
{
    ZDMA *s = XILINX_ZDMA(reg->opaque);

    if (AF_EX32(s->regs, ZDMA_CH_CTRL2, EN)) {
        s->error = false;

        if (s->state == PAUSED && AF_EX32(s->regs, ZDMA_CH_CTRL0, CONT)) {
            if (AF_EX32(s->regs, ZDMA_CH_CTRL0, CONT_ADDR) == 1) {
                zdma_update_descr_addr_from_start(s);
            } else {
                /* FIXME: Not sure if this is right. With asymetric descriptor
                   setups, we rely on reusing the DST descriptor buffer.  */
                bool src_type = F_EX32(s->dsc_src.words[3],
                                       ZDMA_CH_SRC_DSCR_WORD3, TYPE);
                zdma_update_descr_addr(s, src_type,
                                          R_ZDMA_CH_SRC_CUR_DSCR_LSB);
            }
        } else {
            zdma_update_descr_addr_from_start(s);
        }
        zdma_set_state(s, ENABLED);
    } else {
        /* Leave Paused state?  */
        if (s->state == PAUSED && AF_EX32(s->regs, ZDMA_CH_CTRL0, CONT)) {
            zdma_set_state(s, DISABLED);
        }
    }

    zdma_run(s);
}

static RegisterAccessInfo zdma_regs_info[] = {
    {   .name = "ZDMA_ERR_CTRL",  .decode.addr = A_ZDMA_ERR_CTRL,
        .rsvd = 0xfffffffe,
    },{ .name = "ZDMA_CH_ECO",  .decode.addr = A_ZDMA_CH_ECO,
    },{ .name = "ZDMA_CH_ISR",  .decode.addr = A_ZDMA_CH_ISR,
        .rsvd = 0xfffff000,
        .w1c = 0xfff,
        .post_write = zdma_ch_isr_postw,
    },{ .name = "ZDMA_CH_IMR",  .decode.addr = A_ZDMA_CH_IMR,
        .reset = 0xfff,
        .rsvd = 0xfffff000,
        .ro = 0xfff,
    },{ .name = "ZDMA_CH_IEN",  .decode.addr = A_ZDMA_CH_IEN,
        .rsvd = 0xfffff000,
        .pre_write = zdma_ch_ien_prew,
    },{ .name = "ZDMA_CH_IDS",  .decode.addr = A_ZDMA_CH_IDS,
        .rsvd = 0xfffff000,
        .pre_write = zdma_ch_ids_prew,
    },{ .name = "ZDMA_CH_CTRL0",  .decode.addr = A_ZDMA_CH_CTRL0,
        .reset = 0x80,
        .rsvd = 0xffffff01,
        .post_write = zdma_ch_ctrlx_postw,
    },{ .name = "ZDMA_CH_CTRL1",  .decode.addr = A_ZDMA_CH_CTRL1,
        .reset = 0x3ff,
        .rsvd = 0xfffffc00,
    },{ .name = "ZDMA_CH_PERIF",  .decode.addr = A_ZDMA_CH_PERIF,
        .rsvd = 0xffffffc0,
    },{ .name = "ZDMA_CH_STATUS",  .decode.addr = A_ZDMA_CH_STATUS,
        .rsvd = 0xfffffffc,
        .ro = 0x3,
    },{ .name = "ZDMA_CH_DATA_ATTR",  .decode.addr = A_ZDMA_CH_DATA_ATTR,
        .reset = 0x483d20f,
        .rsvd = 0xf0000000,
    },{ .name = "ZDMA_CH_DSCR_ATTR",  .decode.addr = A_ZDMA_CH_DSCR_ATTR,
        .rsvd = 0xfffffe00,
    },{ .name = "ZDMA_CH_SRC_DSCR_WORD0",  .decode.addr = A_ZDMA_CH_SRC_DSCR_WORD0,
    },{ .name = "ZDMA_CH_SRC_DSCR_WORD1",  .decode.addr = A_ZDMA_CH_SRC_DSCR_WORD1,
        .rsvd = 0xfffe0000,
    },{ .name = "ZDMA_CH_SRC_DSCR_WORD2",  .decode.addr = A_ZDMA_CH_SRC_DSCR_WORD2,
        .rsvd = 0xc0000000,
    },{ .name = "ZDMA_CH_SRC_DSCR_WORD3",  .decode.addr = A_ZDMA_CH_SRC_DSCR_WORD3,
        .rsvd = 0xffffffe0,
    },{ .name = "ZDMA_CH_DST_DSCR_WORD0",  .decode.addr = A_ZDMA_CH_DST_DSCR_WORD0,
    },{ .name = "ZDMA_CH_DST_DSCR_WORD1",  .decode.addr = A_ZDMA_CH_DST_DSCR_WORD1,
        .rsvd = 0xfffe0000,
    },{ .name = "ZDMA_CH_DST_DSCR_WORD2",  .decode.addr = A_ZDMA_CH_DST_DSCR_WORD2,
        .rsvd = 0xc0000000,
    },{ .name = "ZDMA_CH_DST_DSCR_WORD3",  .decode.addr = A_ZDMA_CH_DST_DSCR_WORD3,
        .rsvd = 0xfffffffa,
    },{ .name = "ZDMA_CH_WR_ONLY_WORD0",  .decode.addr = A_ZDMA_CH_WR_ONLY_WORD0,
    },{ .name = "ZDMA_CH_WR_ONLY_WORD1",  .decode.addr = A_ZDMA_CH_WR_ONLY_WORD1,
    },{ .name = "ZDMA_CH_WR_ONLY_WORD2",  .decode.addr = A_ZDMA_CH_WR_ONLY_WORD2,
    },{ .name = "ZDMA_CH_WR_ONLY_WORD3",  .decode.addr = A_ZDMA_CH_WR_ONLY_WORD3,
    },{ .name = "ZDMA_CH_SRC_START_LSB",  .decode.addr = A_ZDMA_CH_SRC_START_LSB,
    },{ .name = "ZDMA_CH_SRC_START_MSB",  .decode.addr = A_ZDMA_CH_SRC_START_MSB,
        .rsvd = 0xfffe0000,
    },{ .name = "ZDMA_CH_DST_START_LSB",  .decode.addr = A_ZDMA_CH_DST_START_LSB,
    },{ .name = "ZDMA_CH_DST_START_MSB",  .decode.addr = A_ZDMA_CH_DST_START_MSB,
        .rsvd = 0xfffe0000,
    },{ .name = "ZDMA_CH_SRC_CUR_PYLD_LSB",  .decode.addr = A_ZDMA_CH_SRC_CUR_PYLD_LSB,
        .ro = 0xffffffff,
    },{ .name = "ZDMA_CH_SRC_CUR_PYLD_MSB",  .decode.addr = A_ZDMA_CH_SRC_CUR_PYLD_MSB,
        .rsvd = 0xfffe0000,
        .ro = 0x1ffff,
    },{ .name = "ZDMA_CH_DST_CUR_PYLD_LSB",  .decode.addr = A_ZDMA_CH_DST_CUR_PYLD_LSB,
        .ro = 0xffffffff,
    },{ .name = "ZDMA_CH_DST_CUR_PYLD_MSB",  .decode.addr = A_ZDMA_CH_DST_CUR_PYLD_MSB,
        .rsvd = 0xfffe0000,
        .ro = 0x1ffff,
    },{ .name = "ZDMA_CH_SRC_CUR_DSCR_LSB",  .decode.addr = A_ZDMA_CH_SRC_CUR_DSCR_LSB,
        .ro = 0xffffffff,
    },{ .name = "ZDMA_CH_SRC_CUR_DSCR_MSB",  .decode.addr = A_ZDMA_CH_SRC_CUR_DSCR_MSB,
        .rsvd = 0xfffe0000,
        .ro = 0x1ffff,
    },{ .name = "ZDMA_CH_DST_CUR_DSCR_LSB",  .decode.addr = A_ZDMA_CH_DST_CUR_DSCR_LSB,
        .ro = 0xffffffff,
    },{ .name = "ZDMA_CH_DST_CUR_DSCR_MSB",  .decode.addr = A_ZDMA_CH_DST_CUR_DSCR_MSB,
        .rsvd = 0xfffe0000,
        .ro = 0x1ffff,
    },{ .name = "ZDMA_CH_TOTAL_BYTE",  .decode.addr = A_ZDMA_CH_TOTAL_BYTE,
        .w1c = 0xffffffff,
    },{ .name = "ZDMA_CH_RATE_CNTL",  .decode.addr = A_ZDMA_CH_RATE_CNTL,
        .rsvd = 0xfffff000,
    },{ .name = "ZDMA_CH_IRQ_SRC_ACCT",  .decode.addr = A_ZDMA_CH_IRQ_SRC_ACCT,
        .rsvd = 0xffffff00,
        .ro = 0xff,
        .cor = 0xff,
    },{ .name = "ZDMA_CH_IRQ_DST_ACCT",  .decode.addr = A_ZDMA_CH_IRQ_DST_ACCT,
        .rsvd = 0xffffff00,
        .ro = 0xff,
        .cor = 0xff,
    },{ .name = "ZDMA_CH_DBG0",  .decode.addr = A_ZDMA_CH_DBG0,
        .rsvd = 0xfffffe00,
        .ro = 0x1ff,
    },{ .name = "ZDMA_CH_DBG1",  .decode.addr = A_ZDMA_CH_DBG1,
        .rsvd = 0xfffffe00,
        .ro = 0x1ff,
    },{ .name = "ZDMA_CH_CTRL2",  .decode.addr = A_ZDMA_CH_CTRL2,
        .rsvd = 0xfffffffe,
        .post_write = zdma_ch_ctrlx_postw,
    }
};

static void zdma_reset(DeviceState *dev)
{
    ZDMA *s = XILINX_ZDMA(dev);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }

    zdma_ch_update_irq(s);
}

static uint64_t zdma_read(void *opaque, hwaddr addr, unsigned size)
{
    ZDMA *s = XILINX_ZDMA(opaque);
    RegisterInfo *r = &s->regs_info[addr / 4];

    if (!r->data) {
        qemu_log("%s: Decode error: read from %" HWADDR_PRIx "\n",
                 object_get_canonical_path(OBJECT(s)),
                 addr);
        AF_DP32(s->regs, ZDMA_CH_ISR, INV_APB, true);
        zdma_ch_update_irq(s);
        return 0;
    }
    return register_read(r);
}

static void zdma_write(void *opaque, hwaddr addr, uint64_t value,
                      unsigned size)
{
    ZDMA *s = XILINX_ZDMA(opaque);
    RegisterInfo *r = &s->regs_info[addr / 4];

    if (!r->data) {
        qemu_log("%s: Decode error: write to %" HWADDR_PRIx "=%" PRIx64 "\n",
                 object_get_canonical_path(OBJECT(s)),
                 addr, value);
        AF_DP32(s->regs, ZDMA_CH_ISR, INV_APB, true);
        zdma_ch_update_irq(s);
        return;
    }
    register_write(r, value, ~0);
}

static const MemoryRegionOps zdma_ops = {
    .read = zdma_read,
    .write = zdma_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void zdma_realize(DeviceState *dev, Error **errp)
{
    ZDMA *s = XILINX_ZDMA(dev);
    const char *prefix = object_get_canonical_path(OBJECT(dev));
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(zdma_regs_info); ++i) {
        RegisterInfo *r = &s->regs_info[zdma_regs_info[i].decode.addr/4];

        *r = (RegisterInfo) {
            .data = (uint8_t *)&s->regs[
                    zdma_regs_info[i].decode.addr/4],
            .data_size = sizeof(uint32_t),
            .access = &zdma_regs_info[i],
            .debug = XILINX_ZDMA_ERR_DEBUG,
            .prefix = prefix,
            .opaque = s,
        };
    }

    s->dma_as = s->dma_mr ? address_space_init_shareable(s->dma_mr, NULL)
                          : &address_space_memory;
}

static void zdma_init(Object *obj)
{
    ZDMA *s = XILINX_ZDMA(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

    memory_region_init_io(&s->iomem, obj, &zdma_ops, s,
                          TYPE_XILINX_ZDMA, R_MAX * 4);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq_zdma_ch0);

    object_property_add_link(obj, "dma", TYPE_MEMORY_REGION,
                             (Object **)&s->dma_mr,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);
    object_property_add_link(obj, "memattr", TYPE_MEMORY_TRANSACTION_ATTR,
                             (Object **)&s->attr,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);
}

static const VMStateDescription vmstate_zdma = {
    .name = TYPE_XILINX_ZDMA,
    .version_id = 1,
    .minimum_version_id = 1,
    .minimum_version_id_old = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, ZDMA, R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static Property zdma_props[] = {
    DEFINE_PROP_UINT32("bus-width", ZDMA, cfg.bus_width, 64),
    DEFINE_PROP_END_OF_LIST(),
};

static void zdma_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = zdma_reset;
    dc->realize = zdma_realize;
    dc->props = zdma_props;
    dc->vmsd = &vmstate_zdma;
}

static const TypeInfo zdma_info = {
    .name          = TYPE_XILINX_ZDMA,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(ZDMA),
    .class_init    = zdma_class_init,
    .instance_init = zdma_init,
};

static void zdma_register_types(void)
{
    type_register_static(&zdma_info);
}

type_init(zdma_register_types)
