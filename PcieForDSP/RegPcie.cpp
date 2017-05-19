#include "Driver.h"
#include "RegPcie.tmh"


ULONG
PcieDeviceReadReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address
)
// hu 读取PCIE设备寄存器值
{
	ULONG ret = 0;

//#ifdef DEBUG_HU
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
//#endif

	ret = READ_REGISTER_ULONG((PULONG)((ULONG_PTR)BarXBase + Address));

//#ifdef DEBUG_HU
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
//		"address 0x%x data 0x%x", (ULONG_PTR)BarXBase + Address, ret);
//
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
//#endif
	return ret;
}

VOID
PcieDeviceWriteReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address,
_In_ ULONG Data
)
// hu 写入PCIE设备寄存器值
{
	WRITE_REGISTER_ULONG((PULONG)((ULONG_PTR)BarXBase + Address), Data);
	DbgPrint("zhu:BaseAddr:[%I64X]  OffAdd:0x%x  data:%u/n", (ULONG_PTR)BarXBase, Address, Data);

}