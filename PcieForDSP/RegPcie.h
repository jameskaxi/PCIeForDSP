#ifndef __REGPCIE_H_
#define __REGPCIE_H_

#define MAX_DMA_SIZE_COMMONBUFFER	MAX_DMABUFFER_SIZE


//-----------------------------------------------------------------------------
//DSP 相关地址及寄存器
//-----------------------------------------------------------------------------

#define MAGIC_ADDR                   0x0087FFFC

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
#define PCIE_ADLEN_8MB               (0x00800000)
#define PCIE_8MB_BITMASK             (0xFF800000)
#define LL2_START                    (0x00800000)
#define LL2_END                      (0x1087FFFF)//CorePac n L2 SRAM END
//#define LL2_START(n)                 (0x10800000 + (0X1000000 * n))//CorePac n L2 SRAM
//#define LL2_END(n)                   (0x1087FFFF + (0X1000000 * n))//CorePac n L2 SRAM END
#define MSMC_START                   (0x0C000000)  /* Shared L2 */
#define MSMC_END                     0x0C3FFFFF  /* Shared L2 END*/
#define DDR_START                    (0x80000000)
#define DDR_END                      0xFFFFFFFF  /* DDR END*/
#define PCIE_DATA                    (0x60000000)  

#define OUTBOUND_BUFFER_SIZE         (8*1024*1024)

/*EDMA registers*/
/* remap to CC1 */
#define EDMA_TPCC1_BASE_ADDRESS      0x02720000
#define DCHMAP0						 0x0100
#define DCHMAP1						 0x0104
#define DMAQNUM0                     0x0240  
#define ESR                          0x1010 
#define EESR                         0x1030                 
#define IESR                         0x1060
#define IPR                          0x1068 
#define ICR                          0x1070 
#define EMCR                         0x308               

#define PARAM_0_OPT                  0x4000
#define PARAM_0_SRC                  0x4004
#define PARAM_0_A_B_CNT              0x4008
#define PARAM_0_DST                  0x400C
#define PARAM_0_SRC_DST_BIDX         0x4010
#define PARAM_0_LINK_BCNTRLD         0x4014
#define PARAM_0_SRC_DST_CIDX         0x4018
#define PARAM_0_CCNT                 0x401C

#define PARAM_1_OPT                  0x4020
#define PARAM_1_SRC                  0x4024
#define PARAM_1_A_B_CNT              0x4028
#define PARAM_1_DST                  0x402C
#define PARAM_1_SRC_DST_BIDX         0x4030
#define PARAM_1_LINK_BCNTRLD         0x4034
#define PARAM_1_SRC_DST_CIDX         0x4038
#define PARAM_1_CCNT                 0x403C


#define PCIE_TRANSFER_SIZE           0x80               



typedef struct _EDMA_REGIST_
{
	ULONG_PTR EdmaTpcc1BaseAddress; // 0x02720000;

	ULONG DchMap0;                  //  0x0100;
	ULONG DchMap1;				    // 0x0104;
	ULONG DMAQnum0;                 // 0x0240;
	ULONG esr;                      // 0x1010;
	ULONG eesr;                     // 0x1030;
	ULONG iesr;                     // 0x1060;
	ULONG ipr;                      // 0x1068;
	ULONG icr;                      // 0x1070;

	ULONG Param_0_opt;              // 0x4000;
	ULONG Param_0_src;              // 0x4004;
	ULONG Param_0_a_b_CNT;          // 0x4008;
	ULONG Param_0_DST;              // 0x400C;
	ULONG Param_0_SRC_DST_BIDX;     // 0x4010;
	ULONG Param_0_LINK_BCNTRLD;     // 0x4014;
	ULONG Param_0_SRC_DST_CIDX;     // 0x4018;
	ULONG Param_0_CCNT;             // 0x401C;

	ULONG Param_1_OPT;              // 0x4020;
	ULONG Param_1_SRC;              // 0x4024;
	ULONG Param_1_A_B_CNT;          // 0x4028;
	ULONG Param_1_DST;              //0x402C;
	ULONG Param_1_SRC_DST_BIDX;     // 0x4030;
	ULONG Param_1_LINK_BCNTRLD;     // 0x4034;
	ULONG Param_1_SRC_DST_CIDX;     // 0x4038;
	ULONG Param_1_CCNT;             //  0x403C;
}EDMA_RegData , *PEDMA_RegData;



ULONG
PcieDeviceGetInterrupt(
_In_ PUCHAR BarXBase
);


ULONG
PcieDeviceReadReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address
);

VOID
PcieDeviceWriteReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address,
_In_ ULONG Data
);

VOID
PcieDeviceEnableInterrupt(
_In_ PUCHAR BarXBase
);

VOID
PcieDeviceClearInterrupt(
_In_ PUCHAR BarXBase
);

VOID
PcieDeviceDisableInterrupt(
_In_ PUCHAR BarXBase
);
//////////////////////////////////////////////////////
#endif  // __REGPCIE_H_