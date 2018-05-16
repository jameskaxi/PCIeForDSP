#include "driver.h"
#include "Timer.tmh"

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
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
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
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
	return status;
}

BOOLEAN
PcieTimerStart(
_In_ WDFTIMER Timer,
_In_ ULONGLONG timeByMs
)
{
	BOOLEAN status;

#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif
	DbgPrint("zhu:-->PcieDMATimerStart<--  before WdfTimerStart");

	status = WdfTimerStart(Timer, WDF_REL_TIMEOUT_IN_MS(timeByMs));

#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
	DbgPrint("zhu:-->PcieDMATimerStart<--  %d", status);
	return status;
}

BOOLEAN
PcieTimerStop(
_In_ WDFTIMER Timer
)
{
	BOOLEAN status;

#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
#endif
	DbgPrint("zhu:-->PcieDMATimerStop<--");
	status = WdfTimerStop(Timer, FALSE);
	DbgPrint("zhu:-->PcieDMATimerStop<--  %d", status);
#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
	return status;
}


VOID
DmaWriteTimerEventFunc(
_In_ WDFTIMER Timer
)
{
	PDEVICE_CONTEXT devExt;


#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "DmaWrite timeout\n");
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
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}

VOID
ReadTimerEventFunc(
_In_ WDFTIMER Timer
)
{
	PDEVICE_CONTEXT devExt;

#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "DmaRead timeout\n");
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
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "<-- %!FUNC!");
#endif
}