#include "driver.h"
#include "Timer.tmh"

/*******************************************************************************
*  程序描述：
*  创建定时器
*
*  参数：
*  Timer - 指向 定时器 的句柄
*  Device - 指向 设备 的句柄
*  EvtTimerFunc - 定时器的回调函数
*
*  返回值：
********************************************************************************/
NTSTATUS
PcieTimerCreate(
_In_ WDFTIMER *Timer,
_In_ WDFDEVICE Device,
_In_ PFN_WDF_TIMER EvtTimerFunc
)
{
	NTSTATUS status;
	WDF_TIMER_CONFIG timerConfig;
	WDF_OBJECT_ATTRIBUTES timerAttributes;

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif

	WDF_TIMER_CONFIG_INIT(&timerConfig, EvtTimerFunc);

	WDF_OBJECT_ATTRIBUTES_INIT(&timerAttributes);
	timerAttributes.ParentObject = Device;

	status = WdfTimerCreate(
		&timerConfig,
		&timerAttributes,
		Timer
		);

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
	return status;
}

/*******************************************************************************
*  程序描述：
*  启动定时器
*
*  参数：
*  Timer - 指向 定时器 的句柄
*  timeByMs - 定时器的时间，单位 ms
*
*  返回值：
*  TRUE	 - 成功；
*  FALSE - 失败；
********************************************************************************/
BOOLEAN
PcieTimerStart(
_In_ WDFTIMER Timer,
_In_ ULONGLONG timeByMs
)
{
	BOOLEAN status;

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
	DbgPrint("zhu:-->PcieTimerStart<--  before WdfTimerStart");
#endif
	

	status = WdfTimerStart(Timer, WDF_REL_TIMEOUT_IN_MS(timeByMs));

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
	DbgPrint("zhu:-->PcieDMATimerStart<--  %d", status);
#endif
	
	return status;
}

/*******************************************************************************
*  程序描述：
*  关闭定时器
*
*  参数：
*  Timer - 指向 定时器 的句柄
*
*  返回值：
*  TRUE	 - 成功；
*  FALSE - 失败；
********************************************************************************/
BOOLEAN
PcieTimerStop(
_In_ WDFTIMER Timer
)
{
	BOOLEAN status;

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif
	//DbgPrint("zhu:-->PcieTimerStop<--");
	status = WdfTimerStop(Timer, FALSE);
	
#ifdef DEBUG_ZHU
	DbgPrint("zhu:-->PcieTimerStop<--  %d", status);
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
	return status;
}

/*******************************************************************************
*  程序描述：
*  DMA定时器的回调函数，在DSP反馈超时后，使当前 request 完成
*
*  参数：
*  Timer - 指向定时器的句柄
*
*  返回值：
********************************************************************************/
VOID
DmaWriteTimerEventFunc(
_In_ WDFTIMER Timer
)
{
	PDEVICE_CONTEXT devExt;


#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");

	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "DmaWrite timeout\n");
#endif
	DbgPrint("zhu:-->DmaWriteTimerEventFunc<--");

	devExt = DeviceGetContext(WdfTimerGetParentObject(Timer));

	// Disable DMA interrupt
	WdfInterruptAcquireLock(devExt->Interrupt);

	devExt->WriteTimeout = TRUE;
	if (devExt->MemBar0Base){
		PcieDeviceDisableInterrupt(devExt->MemBar0Base);
		PcieDeviceClearInterrupt(devExt->MemBar0Base);
	}

	WdfInterruptReleaseLock(devExt->Interrupt);


	WdfRequestCompleteWithInformation(devExt->WriteRequest, STATUS_INVALID_DEVICE_STATE, devExt->WriteDmaLength);

	DbgPrint("zhu:-->DmaWriteTimerEventFunc<--  TimeOut And requestComplete");
#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}

/*******************************************************************************
*  程序描述：
*  读取操作的定时器的回调函数，在DSP反馈超时后，使当前 request 完成
*
*  参数：
*  Timer - 指向定时器的句柄
*
*  返回值：
********************************************************************************/
VOID
ReadTimerEventFunc(
_In_ WDFTIMER Timer
)
{
	PDEVICE_CONTEXT devExt;

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");

	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "DmaRead timeout\n");
#endif

	DbgPrint("zhu:-->DmaReadTimerEventFunc<--");

	devExt = DeviceGetContext(WdfTimerGetParentObject(Timer));

	// Disable DMA interrupt
	WdfInterruptAcquireLock(devExt->Interrupt);

	devExt->ReadTimeout = TRUE;
	if (devExt->MemBar0Base){
		PcieDeviceDisableInterrupt(devExt->MemBar0Base);
		PcieDeviceClearInterrupt(devExt->MemBar0Base);
	}

	WdfInterruptReleaseLock(devExt->Interrupt);
	if (devExt->ReadRequest)
	{
		WdfRequestCompleteWithInformation(devExt->ReadRequest, STATUS_INVALID_DEVICE_STATE, 0);
	}
	

	DbgPrint("zhu:-->DmaReadTimerEventFunc<--  TimeOut And requestComplete");

	

#ifdef DEBUG_ZHU
	//TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}

/*******************************************************************************
*  程序描述：
*  写寄存器操作的定时器的回调函数，在DSP反馈超时后，使当前 request 完成
*
*  参数：
*  Timer - 指向定时器的句柄
*
*  返回值：
********************************************************************************/
VOID
IoWriteTimerEventFunc(
_In_ WDFTIMER Timer
)
{

	PDEVICE_CONTEXT devExt;

	DbgPrint("zhu:-->IoWriteTimerEventFunc<--");

	devExt = DeviceGetContext(WdfTimerGetParentObject(Timer));

	// Disable DMA interrupt
	WdfInterruptAcquireLock(devExt->Interrupt);

	devExt->IoWriteTimeout = TRUE;
	if (devExt->MemBar0Base){
		PcieDeviceDisableInterrupt(devExt->MemBar0Base);
		PcieDeviceClearInterrupt(devExt->MemBar0Base);
	}

	WdfInterruptReleaseLock(devExt->Interrupt);
	if (devExt->IoWriteRequest)
	{
		WdfRequestCompleteWithInformation(devExt->IoWriteRequest, STATUS_INVALID_DEVICE_STATE, 0);
	}


	DbgPrint("zhu:-->IoWriteTimerEventFunc<--  TimeOut And requestComplete");

}