/*++

Module Name:

    queue.c

Abstract:

    This file contains the queue entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "driver.h"
#include "queue.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, PcieForDSPQueueInitialize)
//#pragma alloc_test (PAGE, PcieForDSPEvtIoDeviceControl)
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


	// hu 初始化缺省队列配置，设置I/O请求分发处理方式为串行
	WDF_IO_QUEUE_CONFIG_INIT(&queueConfig, WdfIoQueueDispatchSequential);

	queueConfig.EvtIoWrite = PcieEvtIoWrite;

	status = WdfIoQueueCreate(DevExt->Device,
		&queueConfig,
		WDF_NO_OBJECT_ATTRIBUTES,
		&DevExt->WriteQueue);

	if (!NT_SUCCESS(status)) {
//#ifdef DEBUG_ZHU
//		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
//			"WdfIoQueueCreate failed: %!STATUS!", status);
//#endif
		return status;
	}

	//
	// Set the Write Queue forwarding for IRP_MJ_WRITE requests.
	//
	status = WdfDeviceConfigureRequestDispatching(DevExt->Device,
		DevExt->WriteQueue,
		WdfRequestTypeWrite);

	if (!NT_SUCCESS(status)) {
//#ifdef DEBUG_ZHU
//		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
//			"WdfDeviceConfigureRequestDispatching failed: %!STATUS!", status);
//#endif
		return status;
	}

	//
	// Create a new IO Queue for IRP_MJ_READ requests in sequential mode.
	//
//	WDF_IO_QUEUE_CONFIG_INIT(&queueConfig, WdfIoQueueDispatchSequential);
//
//	queueConfig.EvtIoRead = PcieEvtIoRead;
//
//	status = WdfIoQueueCreate(DevExt->Device,
//		&queueConfig,
//		WDF_NO_OBJECT_ATTRIBUTES,
//		&DevExt->ReadQueue);
//
//	if (!NT_SUCCESS(status)) {
////#ifdef DEBUG_ZHU
////		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
////			"WdfIoQueueCreate failed: %!STATUS!", status);
////#endif
//		return status;
//	}
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
//#ifdef DEBUG_ZHU
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

	DbgPrint("zhu:-->PcieEvtIoDeviceControl()<--");
	

	devExt = DeviceGetContext(WdfIoQueueGetDevice(Queue));

	status = WdfRequestRetrieveOutputBuffer(Request, 1, &out_buffer, &out_bufsize);
	if (!NT_SUCCESS(status)){
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		return;
	}

	status = WdfRequestRetrieveInputBuffer(Request, 1, &in_buffer, &in_bufsize);
	if (!NT_SUCCESS(status)){
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		#ifdef DEBUG_ZHU
				TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
					"WdfRequestRetrieveInputBuffer failed: %!STATUS!", status);
		#endif
		return;
	}

	#ifdef DEBUG_ZHU
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
		ULONG size = ptr[0] / sizeof(ULONG);
		PULONG data = &ptr[1];
		ULONG i;


		//向 bar2 的  0x8 发 2 表示CPU方式
		PcieDeviceWriteReg(devExt->MemBar2Base, 0x8, 2);
		//向 bar2 的  0xc 发 CPU方式的数据长度（真实的数据长度，地址不算在内）
		PcieDeviceWriteReg(devExt->MemBar2Base, 0xc,size);

		//从 bar1 的 0x100 开始发地址和数据，以一个地址一个数据的方式依次发送
		if (devExt->MemBar1Base)
		{
			for (i = 0; i < size; i++)
			{
				//地址
				PcieDeviceWriteReg(devExt->MemBar1Base, 0x100 + i*2*sizeof(ULONG), data[i*2]);
				//数据
				PcieDeviceWriteReg(devExt->MemBar1Base, 0x104 + i*2*sizeof(ULONG), data[i*2 +1]);
			}
			status = STATUS_SUCCESS;
		}

		//发送中断，通知DSP开始向FPGA搬数据
		PcieDeviceEnableInterrupt(devExt->MemBar0Base);
		PcieDeviceWriteReg(devExt->MemBar0Base, 0x180, 0x1);
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		break;
	}
	case PCIeDMA_IOCTL_READ_REG:
	{
		DbgPrint("zhu:-->PCIeDMA_IOCTL_READ_REG<--");
		ULONG *ptr = (PULONG)in_buffer;
		ULONG addr = ptr[0];

		devExt->ReadRequest = Request;
		devExt->CurrentRequest = Request;
		devExt->ReadBuffer = out_buffer;

		//向 bar2 的  0x8 发 4 表示CPU方式
		PcieDeviceWriteReg(devExt->MemBar2Base, 0x8, 0x4);
		//向DSP写入需读取的地址
		PcieDeviceWriteReg(devExt->MemBar1Base, 0x100, addr);
		//发送中断，通知DSP开始向FPGA搬数据
		PcieDeviceEnableInterrupt(devExt->MemBar0Base);
		PcieDeviceWriteReg(devExt->MemBar0Base, 0x180, 0x1);

		//启动定时器
		devExt->ReadTimeout = FALSE;
		PcieTimerStart(devExt->ReadTimer, 5000);


		break;
	}
	case PCIE_IOCTL_DEBUG:
	{

		DbgPrint("zhu:-->PCIE_IOCTL_DEBUG<--");

		ULONG *ptr = (PULONG)in_buffer;
		ULONG barX = ptr[0];
		ULONG addr = ptr[1];
		ULONG data = ptr[2];

		if (barX == 0)
		{
			PcieDeviceWriteReg(devExt->MemBar0Base, addr, data);
			status = STATUS_SUCCESS;
		}
		else if (barX == 1)
		{
			PcieDeviceWriteReg(devExt->MemBar1Base, addr, data);
			status = STATUS_SUCCESS;
		}
		else if (barX == 2)
		{
			PcieDeviceWriteReg(devExt->MemBar2Base,addr, data);
			status = STATUS_SUCCESS;
		}
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		break;
	}
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		WdfRequestCompleteWithInformation(Request, status, ret_length);
		break;
	}

	

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
#ifdef DEBUG_ZHU
	TraceEvents(TRACE_LEVEL_INFORMATION, 
		TRACE_QUEUE,
		"!FUNC! Queue 0x%p, Request 0x%p ActionFlags %d",
		Queue, Request, ActionFlags);
#endif
	UNREFERENCED_PARAMETER(ActionFlags);
	UNREFERENCED_PARAMETER(Request);
	UNREFERENCED_PARAMETER(Queue);
    
	NTSTATUS status = STATUS_SUCCESS;
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
	WdfRequestComplete(Request, status);
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
	//UNREFERENCED_PARAMETER(Queue);
	//UNREFERENCED_PARAMETER(Request);
	//UNREFERENCED_PARAMETER(Length);

	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_CONTEXT devExt;
	PVOID 	in_buffer;
	size_t 	in_bufsize;


//#ifdef DEBUG_ZHU
//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!: Request %p", Request);
//#endif
	DbgPrint("zhu:-->PcieEvtIoWrite<-- ");

	//
	// Get the DevExt from the Queue handle
	//
	devExt = DeviceGetContext(WdfIoQueueGetDevice(Queue));

	//
	// Validate the Length parameter.
	//
	if (Length > MAX_DMA_SIZE_COMMONBUFFER)  {
		status = STATUS_INVALID_BUFFER_SIZE;
//#ifdef DEBUG_ZHU
//		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
//			"%!FUNC! failed: %!STATUS!", status);
//#endif
		WdfRequestComplete(Request, status);
		return;
	}

	status = WdfRequestRetrieveInputBuffer(Request, 1, &in_buffer, &in_bufsize);
	if (!NT_SUCCESS(status)){
//#ifdef DEBUG_ZHU
//		TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
//			"WdfRequestRetrieveInputBuffer failed: %!STATUS!", status);
//#endif
		WdfRequestComplete(Request, status);
		return;
	}

	RtlCopyMemory(devExt->CommonBufferBase, in_buffer, in_bufsize);
	devExt->WriteDmaLength = in_bufsize;
	KeMemoryBarrier();

	devExt->WriteRequest = Request;
	devExt->CurrentRequest = Request;

	devExt->WriteTimeout = FALSE;

	PcieDeviceStartDMA(devExt, devExt->Interrupt);

	PcieTimerStart(devExt->WriteTimer,20000);
	//WdfRequestComplete(Request, status);
//	devExt->WriteTimeout = FALSE;
//	PcieDMATimerStart(devExt->WriteTimer);
	return;
}

/*
 *-->说明<--
 * 进行Outbound配置操作
 */
VOID
PcieDeviceSetupDMA(
_In_ PUCHAR Bar0Base,
//_In_ PUCHAR Bar1Base,
//_In_ WDFINTERRUPT interrupt,
_In_ PHYSICAL_ADDRESS hostAddress
//_In_ ULONG size
//_In_ ULONG direction,
//_In_ BOOLEAN descLoc	// Descriptor location : 0 - external 1 - internal
)
// hu 设置DMA寄存器
{
	//DbgPrint("-->zhu:PcieDeviceSetupDMA<--");
	ULONG srcAddr;
	ULONG pageBase;


	DbgPrint("zhu:-->Outbound Start<-- ");
	srcAddr = hostAddress.LowPart;

	// zhu 进行Outbound操作
	PcieDeviceWriteReg(Bar0Base, CMD_STATUS, 0x7);
	PcieDeviceWriteReg(Bar0Base, OB_SIZE, 0x3);
	for (ULONG i = 0;i<3; i++)
	{
		pageBase = (srcAddr + (PCIE_ADLEN_8MB * i)) & PCIE_8MB_BITMASK;				
		DbgPrint("zhu:(srcAddr + (PCIE_ADLEN_8MB * %d)) & PCIE_8MB_BITMASK : 0x%x",i, pageBase);
		PcieDeviceWriteReg(Bar0Base, OB_OFFSET_INDEX(i), (pageBase | 0x1));
		PcieDeviceWriteReg(Bar0Base, OB_OFFSET_HI(i), 0x00);
	}
	DbgPrint("zhu:-->Outbound End<-- ");

	
}

VOID
PcieDeviceStartDMA(
_In_ PDEVICE_CONTEXT devExt,
//_In_ ULONG DataLength,
_In_ WDFINTERRUPT interrupt
)
// hu 开始DMA传输
{
//	NTSTATUS status = STATUS_SUCCESS;
	//ULONG uiSize;
	//ULONG uiTmp;
	ULONG srcAddr;

	DbgPrint("zhu:-->Start EDMA<--");
	UNREFERENCED_PARAMETER(interrupt);
	srcAddr = PCIE_DATA + (devExt->CommonBufferBaseLA.LowPart & ~PCIE_8MB_BITMASK);
	PcieDeviceWriteReg(devExt->MemBar2Base, 0x0, srcAddr);                //发送DMA数据地址
	PcieDeviceWriteReg(devExt->MemBar2Base, 0x4, devExt->WriteDmaLength); //发送DMA数据长度
	//PcieDeviceWriteReg(devExt->MemBar2Base, 0x8, 0x1);                    //0x1 -- DMA模式 ，0x2 -- 寄存器模式 ,0x3 -- 动态加载模式
	//WdfInterruptAcquireLock(interrupt);

	// Check if DMA busy or not?
	//DmaCtl.ulong = READ_REGISTER_ULONG((PULONG)&dmaRegs->DmaCtl);

	//允许DSP向PC发送中断
	PcieDeviceEnableInterrupt(devExt->MemBar0Base);
	PcieDeviceWriteReg(devExt->MemBar0Base, 0x180, 0x1);//向DSP发送中断
	

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
/*

ULONG
PcieDeviceReadReg(
_In_ PUCHAR BarXBase,
_In_ ULONG Address
)
// hu 读取PCIE设备寄存器值
{
	ULONG ret = 0;

	//#ifdef DEBUG_ZHU
	//	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "--> %!FUNC!");
	//#endif

	ret = READ_REGISTER_ULONG((PULONG)((ULONG_PTR)BarXBase + Address));

	DbgPrint("BaseAddr:0x%x  offset:0x%x   data:0x%x",(ULONG_PTR)BarXBase,Address,ret);
	//#ifdef DEBUG_ZHU
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
	DbgPrint("zhu:BaseAddr:0x%X  OffAdd:0x%x  data:0x%x", (ULONG_PTR)BarXBase, Address, Data);

}
*/