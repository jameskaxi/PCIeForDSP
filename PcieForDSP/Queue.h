/*++

Module Name:

    queue.h

Abstract:

    This file contains the queue definitions.

Environment:

    Kernel-mode Driver Framework

--*/

//
// This is the context that can be placed per queue
// and would contain per queue information.
//
typedef struct _QUEUE_CONTEXT {

    ULONG PrivateDeviceData;  // just a placeholder

} QUEUE_CONTEXT, *PQUEUE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(QUEUE_CONTEXT, QueueGetContext)

NTSTATUS
PcieForDSPQueueInitialize(
_In_ PDEVICE_CONTEXT DevExt
    );
/*
ULONG
PcieDeviceReadReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address
);

VOID
PcieDeviceWriteReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address, 
_In_ ULONG Data);
*/
VOID
PcieDeviceSetupDMA(
_In_ PUCHAR Bar0Base,
//_In_ PUCHAR Bar1Base,
_In_ WDFINTERRUPT interrupt,
_In_ PHYSICAL_ADDRESS hostAddress
//_In_ ULONG size
);

VOID
PcieDeviceStartDMA(
_In_ PDEVICE_CONTEXT devExt,
//_In_ PUCHAR Bar1Base,
_In_ WDFINTERRUPT interrupt
);

// Events from the IoQueue object
//
EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL PcieForDSPEvtIoDeviceControl;
EVT_WDF_IO_QUEUE_IO_STOP PcieForDSPEvtIoStop;
EVT_WDF_IO_QUEUE_IO_READ PcieEvtIoRead;
EVT_WDF_IO_QUEUE_IO_WRITE PcieEvtIoWrite;

