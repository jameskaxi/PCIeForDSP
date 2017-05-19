#ifndef __REGPCIE_H_
#define __REGPCIE_H_

#define MAX_DMA_SIZE_COMMONBUFFER	MAX_DMABUFFER_SIZE


//-----------------------------------------------------------------------------
//Outbound操作相关地址及寄存器
//-----------------------------------------------------------------------------
#define PCIE_BASE_ADDRESS            (0x21800000)
#define OB_SIZE                      (0x30)
#define PRIORITY                     (0x3C)
#define EP_IRQ_CLR                   (0x68)
#define EP_IRQ_STATUS                (0x6C)
#define LEGACY_A_IRQ_STATUS_RAW      (0x180)
#define LEGACY_A_IRQ_ENABLE_SET      (0x188)
#define LEGACY_A_IRQ_ENABLE_CLR      (0x18C)
#define OB_OFFSET_INDEX(n)           (0x200 + (8 * (n)))
#define OB_OFFSET_HI(n)              (0x204 + (8 * (n)))
#define IB_BAR(n)                    (0x300 + (0x10 * (n)))
#define IB_START_LO(n)               (0x304 + (0x10 * (n)))
#define IB_START_HI(n)               (0x308 + (0x10 * (n)))
#define IB_OFFSET(n)                 (0x30C + (0x10 * (n)))
#define CMD_STATUS			 0X4
/* For 1MB outbound translation window size */
#define PCIE_ADLEN_1MB               (0x00100000)
#define PCIE_1MB_BITMASK             (0xFFF00000)
#define LL2_START                    (0x00800000)
#define MSMC_START                   (0x0C000000)  /* Shared L2 */
#define DDR_START                    (0x80000000)
#define PCIE_DATA                    (0x60000000)  

#define OUTBOUND_BUFFER_SIZE         (8*1024*1024)



//////////////////////////////////////////////////////
#endif  // __REGPCIE_H_