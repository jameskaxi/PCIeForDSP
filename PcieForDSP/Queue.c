/*++

Module Name:

    queue.c

Abstract:

    This file contains the queue entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Driver.h"
#include "queue.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, PcieForDSPQueueInitialize)
#pragma alloc_test (PAGE, PcieForDSPEvtIoDeviceControl)
#endif

NTSTATUS
PcieForDSPQueueInitialize(
_In_ PDEVICE_CONTEXT DevExt
//    _In_ WDFDEVICE Device
    )
/*++

Routine Description:


     The I/O dispatch callbacks for the frameworks device object
     are configured in this function.

     A single default I/O Queue is configured for parallel request
     processing, and a driver context memory allocation is created
     to hold our structure QUEUE_CONTEXT.

Arguments:

    Device - Handle to a framework device object.

Return Value:

    VOID

--*/
{
//    WDFQUEUE queue;
    NTSTATUS status;
    WDF_IO_QUEUE_CONFIG    queueConfig;

    PAGED_CODE();
    
    //
    // Configure a default queue so that requests that are not
    // configure-fowarded using WdfDeviceConfigureRequestDispatching to goto
    // other queues get dispatched here.
    //
	//
    /*WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(
         &queueConfig,
        WdfIoQueueDispatchParallel
        );  */

	// Create a new IO Dispatch Queue for IRP_MJ_DEVICE_CONTROL  requests in sequential mode.
	//
	WDF_IO_QUEUE_CONFIG_INIT(&queueConfig, WdfIoQueueDispatchSequential);//zhu

    queueConfig.EvtIoDeviceControl = PcieForDSPEvtIoDeviceControl;
    queueConfig.EvtIoStop = PcieForDSPEvtIoStop;

    status = WdfIoQueueCreate(
                 DevExt->Device,
                 &queueConfig,
                 WDF_NO_OBJECT_ATTRIBUTES,
                 &DevExt->IoDispatchQueue
                 );

    if( !NT_SUCCESS(status) ) {
       // TraceEvents(TRACE_LEVEL_ERROR, TRACE_QUEUE, "WdfIoQueueCreate failed %!STATUS!", status);
        return status;
    }

	// Set the IO Dispatch Queue forwarding for IRP_MJ_DEVICE_CONTROL requests.
	//
	status = WdfDeviceConfigureRequestDispatching(DevExt->Device,
		DevExt->IoDispatchQueue,
		WdfRequestTypeDeviceControl);

	if (!NT_SUCCESS(status)) {
//#ifdef DEBUG_HU
//		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
//			"WdfDeviceConfigureRequestDispatching failed: %!STATUS!", status);
//#endif
		return status;
	}

    return status;
}

VOID
PcieForDSPEvtIoDeviceControl(
    _In_ WDFQUEUE Queue,
    _In_ WDFREQUEST Request,
    _In_ size_t OutputBufferLength,
    _In_ size_t InputBufferLength,
    _In_ ULONG IoControlCode
    )
/*++

Routine Description:

    This event is invoked when the framework receives IRP_MJ_DEVICE_CONTROL request.

Arguments:

    Queue -  Handle to the framework queue object that is associated with the
             I/O request.

    Request - Handle to a framework request object.

    OutputBufferLength - Size of the output buffer in bytes

    InputBufferLength - Size of the input buffer in bytes

    IoControlCode - I/O control code.

Return Value:

    VOID

--*/
{
    //TraceEvents(TRACE_LEVEL_INFORMATION, 
    //            TRACE_QUEUE, 
    //            "!FUNC! Queue 0x%p, Request 0x%p OutputBufferLength %d InputBufferLength %d IoControlCode %d", 
    //            Queue, Request, (int) OutputBufferLength, (int) InputBufferLength, IoControlCode);

    //WdfRequestComplete(Request, STATUS_SUCCESS);

	NTSTATUS  status = STATUS_SUCCESS;
	PDEVICE_CONTEXT devExt = NULL;

	int ret_length = 0;
	PVOID out_buffer;
	size_t out_bufsize;
	PVOID in_buffer;
	size_t in_bufsize;

	UNREFERENCED_PARAMETER(OutputBufferLength);
	UNREFERENCED_PARAMETER(InputBufferLength);

	DbgPrint("zhu:Get in PcieEvtIoDeviceControl()/n");

	devExt = DeviceGetContext(WdfIoQueueGetDevice(Queue));

	status = WdfRequestRetrieveOutputBuffer(Request, 1, &out_buffer, &out_bufsize);
	if (!NT_SUCCESS(status)){
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		return;
	}

	status = WdfRequestRetrieveInputBuffer(Request, 1, &in_buffer, &in_bufsize);
	if (!NT_SUCCESS(status)){
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		#ifdef DEBUG_HU
				TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
					"WdfRequestRetrieveInputBuffer failed: %!STATUS!", status);
		#endif
		return;
	}

	#ifdef DEBUG_HU
		TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
			"PcieEvtIoDeviceControl: in_buffer 0x%x in_bufsize 0x%x",
			(unsigned int)in_buffer, in_bufsize);
	
		TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
			"PcieEvtIoDeviceControl: out_buffer 0x%x out_bufsize 0x%x",
			(unsigned int)out_buffer, out_bufsize);
	#endif

	switch (IoControlCode)
	{
	case PCIeDMA_IOCTL_WRITE_REG:
	{
		DbgPrint("zhu:-->PCIeDMA_IOCTL_WRITE_REG<--");

		ULONG *ptr = (PULONG)in_buffer;
		ULONG address = ptr[0];
		ULONG size = ptr[1] / sizeof(ULONG);
		PULONG data = &ptr[2];
		ULONG i = 0;

		if (devExt->MemBar0Base){
			for (i = 0; i < size; i++)
			{
				PcieDeviceWriteReg(devExt->MemBar0Base, address + i*sizeof(ULONG), data[0]);
			}
			status = STATUS_SUCCESS;
		}


		break;
	}
	case PCIeDMA_IOCTL_READ_REG:
	{
		DbgPrint("zhu:-->PCIeDMA_IOCTL_READ_REG<--");
	}
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

	WdfRequestCompleteWithInformation(Request, status, ret_length);

    return;
}

VOID
PcieForDSPEvtIoStop(
    _In_ WDFQUEUE Queue,
    _In_ WDFREQUEST Request,
    _In_ ULONG ActionFlags
)
/*++

Routine Description:

    This event is invoked for a power-managed queue before the device leaves the working state (D0).

Arguments:

    Queue -  Handle to the framework queue object that is associated with the
             I/O request.

    Request - Handle to a framework request object.

    ActionFlags - A bitwise OR of one or more WDF_REQUEST_STOP_ACTION_FLAGS-typed flags
                  that identify the reason that the callback function is being called
                  and whether the request is cancelable.

Return Value:

    VOID

--*/
{
#ifdef DEBUG_HU
	TraceEvents(TRACE_LEVEL_INFORMATION, 
		TRACE_QUEUE,
		"!FUNC! Queue 0x%p, Request 0x%p ActionFlags %d",
		Queue, Request, ActionFlags);
#endif
	UNREFERENCED_PARAMETER(ActionFlags);
	UNREFERENCED_PARAMETER(Request);
	UNREFERENCED_PARAMETER(Queue);
    //
    // In most cases, the EvtIoStop callback function completes, cancels, or postpones
    // further processing of the I/O request.
    //
    // Typically, the driver uses the following rules:
    //
    // - If the driver owns the I/O request, it calls WdfRequestUnmarkCancelable
    //   (if the request is cancelable) and either calls WdfRequestStopAcknowledge
    //   with a Requeue value of TRUE, or it calls WdfRequestComplete with a
    //   completion status value of STATUS_SUCCESS or STATUS_CANCELLED.
    //
    //   Before it can call these methods safely, the driver must make sure that
    //   its implementation of EvtIoStop has exclusive access to the request.
    //
    //   In order to do that, the driver must synchronize access to the request
    //   to prevent other threads from manipulating the request concurrently.
    //   The synchronization method you choose will depend on your driver's design.
    //
    //   For example, if the request is held in a shared context, the EvtIoStop callback
    //   might acquire an internal driver lock, take the request from the shared context,
    //   and then release the lock. At this point, the EvtIoStop callback owns the request
    //   and can safely complete or requeue the request.
    //
    // - If the driver has forwarded the I/O request to an I/O target, it either calls
    //   WdfRequestCancelSentRequest to attempt to cancel the request, or it postpones
    //   further processing of the request and calls WdfRequestStopAcknowledge with
    //   a Requeue value of FALSE.
    //
    // A driver might choose to take no action in EvtIoStop for requests that are
    // guaranteed to complete in a small amount of time.
    //
    // In this case, the framework waits until the specified request is complete
    // before moving the device (or system) to a lower power state or removing the device.
    // Potentially, this inaction can prevent a system from entering its hibernation state
    // or another low system power state. In extreme cases, it can cause the system
    // to crash with bugcheck code 9F.
    //
	DbgPrint("zhu:-->PcieForDSPEvtIoStop<-- ");
	return;
}

VOID
PcieEvtIoWrite(
_In_ WDFQUEUE         Queue,
_In_ WDFREQUEST       Request,
_In_ size_t           Length
)
/*++

Routine Description:

Called by the framework as soon as it receives a write request.
If the device is not ready, fail the request.
Otherwise get scatter-gather list for this request and send the
packet to the hardware for DMA.

Arguments:

Queue - Handle to the framework queue object that is associated
with the I/O request.
Request - Handle to a framework request object.

Length - Length of the IO operation
The default property of the queue is to not dispatch
zero lenght read & write requests to the driver and
complete is with status success. So we will never get
a zero length request.

Return Value:

--*/
{
	UNREFERENCED_PARAMETER(Queue);
	UNREFERENCED_PARAMETER(Request);
	UNREFERENCED_PARAMETER(Length);
	DbgPrint("zhu:-->PcieEvtIoWrite<-- ");
	return;
}


VOID
PcieEvtIoRead(
_In_ WDFQUEUE         Queue,
_In_ WDFREQUEST       Request,
_In_ size_t           Length
)
/*++

Routine Description:

Called by the framework as soon as it receives a read request.
If the device is not ready, fail the request.
Otherwise get scatter-gather list for this request and send the
packet to the hardware for DMA.

Arguments:

Queue   	- Default queue handle
Request  	- Handle to the write request
Lenght 		- Length of the data buffer associated with the request.
The default property of the queue is to not dispatch
zero lenght read & write requests to the driver and
complete is with status success. So we will never get
a zero length request.

Return Value:

--*/
{
	UNREFERENCED_PARAMETER(Queue);
	UNREFERENCED_PARAMETER(Request);
	UNREFERENCED_PARAMETER(Length);
	DbgPrint("zhu:-->PcieEvtIoRead<-- ");
	return;
}

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
	DbgPrint("zhu:BaseAddr:[%I64X]  OffAdd:0x%x  data:%d/n", (ULONG_PTR)BarXBase, Address, Data);

}