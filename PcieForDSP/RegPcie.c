#include "driver.h"
#include "RegPcie.tmh"


ULONG
PcieDeviceReadReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address
)
// zhu 读取PCIE设备寄存器值
{
	ULONG ret = 0;

	ret = READ_REGISTER_ULONG((PULONG)((ULONG_PTR)BarXBase + Address));

	DbgPrint("BaseAddr:0x%x  offset:0x%x   data:0x%x", (ULONG_PTR)BarXBase, Address, ret);

	return ret;
}

VOID
PcieDeviceWriteReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address,
_In_ ULONG Data
)
// zhu 写入PCIE设备寄存器值
{
	WRITE_REGISTER_ULONG((PULONG)((ULONG_PTR)BarXBase + Address), Data);
	DbgPrint("zhu:BaseAddr:0x%X  OffAdd:0x%x  data:0x%x", (ULONG_PTR)BarXBase, Address, Data);

}

/*
VOID
PcieDeviceResetHardWare(
_In_ PUCHAR BarXBase
)
// hu 初始化PCIE设备
{
	ULONG* pcieRegGPIO;
	PCIE_DMA_EXT1_REGS* pcieDmaExt1;

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif

	pcieRegGPIO = (PULONG)(BarXBase + REG_GPIO_OFFSET);
	WRITE_REGISTER_ULONG(pcieRegGPIO, 0);

	pcieDmaExt1 = (PCIE_DMA_EXT1_REGS *)(BarXBase + REG_EXT1_OFFSET);
	WRITE_REGISTER_ULONG((PULONG)&pcieDmaExt1->hostAccess, HOST_ACCESS_OK); // PC host is able to access dma registers
	WRITE_REGISTER_ULONG((PULONG)&pcieDmaExt1->opMode, OPMODE_NORMAL); // dma is working in normal mode

	PcieDeviceResetDMA(BarXBase);

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}

*/



/*
ULONG
PcieDeviceGetDMATime(
_In_ PUCHAR BarXBase
)
// hu 获取DMA传输所花时间
{
	ULONG time;
	PDMA_REGS	dmaRegs;

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif

	dmaRegs = (PCIE_DMA_REGS *)BarXBase;
	time = READ_REGISTER_ULONG((PULONG)&dmaRegs->Timer0);

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
		"DMA elapse time 0x%x", time);

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
	return time;
}
*/

ULONG
PcieDeviceGetInterrupt(
_In_ PUCHAR BarXBase
)
//zhu 获取中断标志位
{
	ULONG PcieIntStatus;
	ULONG PcieIntMask;


	//
	// Check interrupt status
	//
	PcieIntMask = PcieDeviceReadReg(BarXBase, EP_IRQ_STATUS);

	if (0 == (PcieIntMask & 0x00000001))
	{
		PcieIntStatus =  FALSE;
	}
	else
	{
		PcieIntStatus = PcieIntMask;
	}
	DbgPrint("zhu:PcieDeviceGetInterrupt status:0x%x", PcieIntStatus);
	return  PcieIntStatus;
}


VOID PcieDeviceClearInterrupt
(
_In_ PUCHAR BarXBase
)
// hu 清除中断标志位
{
//	ULONG		  PcieIntStatus;

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif

	//dmaRegs = (PCIE_DMA_REGS *)BarXBase;

//	PcieIntStatus = READ_REGISTER_ULONG((PULONG)&dmaRegs->DmaSta);
	//WRITE_REGISTER_ULONG((PULONG), PcieIntStatus);
	//WRITE_REGISTER_ULONG((PULONG)((ULONG_PTR)BarXBase + 0x18c), 0x1);
	//(PULONG)((ULONG_PTR)BarXBase + Address)
	DbgPrint("zhu:-->PcieDeviceClearInterrupt<--");
	PcieDeviceWriteReg(BarXBase,0x68,0x1);
#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}


/*
VOID
PcieDeviceTriggerInterrupt(
_In_ PUCHAR BarXBase
)
// hu 触发逻辑中断
{
	PCIE_MAILBOX_REGS *mb;
	PCIE_DMA_REGS *dmaRegs;
	DmaInt_u_t DmaInt;

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif

	dmaRegs = (PCIE_DMA_REGS *)BarXBase;

	DmaInt.ulong = 0;
	DmaInt.bits.TrigInt = TRUE;
	WRITE_REGISTER_ULONG((PULONG)&dmaRegs->DmaInt, DmaInt.ulong);

	// send command
	mb = (PCIE_MAILBOX_REGS *)(BarXBase + MAILBOX_OFFSET);
	WRITE_REGISTER_ULONG((PULONG)&mb->trig_int, TRIGGER_INT_CMD);

#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
		"data at mb->trig_int 0x%x\n",
		READ_REGISTER_ULONG((PULONG)&mb->trig_int));

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}
*/

VOID
PcieDeviceEnableInterrupt(
_In_ PUCHAR BarXBase
)
// hu 使能中断
{
	//PCIE_DMA_REGS *dmaRegs;

//#ifdef DEBUG_HU
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
//#endif
	DbgPrint("zhu:-->PcieDeviceEnableInterrupt<--");
	//dmaRegs = (PCIE_DMA_REGS *)BarXBase;

	//WRITE_REGISTER_ULONG((PULONG)&dmaRegs->DmaInt, INT_MASK_ENABLE);
	PcieDeviceWriteReg(BarXBase, 0x188, 0x1);//允许DSp向PC发中断
	

}



VOID
PcieDeviceDisableInterrupt(
_In_ PUCHAR BarXBase
)
// hu 屏蔽中断
{
//	PCIE_DMA_REGS *dmaRegs;
//
//#ifdef DEBUG_HU
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
//#endif

	//dmaRegs = (PCIE_DMA_REGS *)BarXBase;

	PcieDeviceWriteReg(BarXBase, 0x18c, 0x1);
	//WRITE_REGISTER_ULONG((PULONG)&dmaRegs->DmaInt, INT_MASK_DISABLE_ALL);

//#ifdef DEBUG_HU
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
//#endif
}
