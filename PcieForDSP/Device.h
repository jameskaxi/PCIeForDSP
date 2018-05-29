/*++

Module Name:

    device.h

Abstract:

    This file contains the device definitions.
	zhu  与硬件相关的参数、结构体、物理地址、偏移地址等都写在这里

Environment:

    Kernel-mode Driver Framework

--*/

#include "public.h"

//
// The device context performs the same job as
// a WDM device extension in the driver frameworks
//
typedef struct _DEVICE_CONTEXT
{
	WDFDEVICE               Device;             
	ULONG                   PhysicalAddressRegister;

	PUCHAR                  MemBar0Base;      	//zhu: bar0 Registers base address (must be 32bit align)
	ULONG                   MemBar0Length;    	//zhu  bar0 Registers base length

	PUCHAR                  MemBar1Base;      	//zhu: bar1 Registers base address (must be 32bit align)
	ULONG                   MemBar1Length;    	//zhu：bar1 Registers base length

	PUCHAR                  MemBar2Base;      	//zhu：bar2  Registers base address (must be 32bit align)
	ULONG                   MemBar2Length;    	//zhu：bar2  Registers base length

	PUCHAR                  MemBar3Base;      	//zhu：bar3  Registers base address (must be 32bit align)
	ULONG                   MemBar3Length;    	//zhu：bar3  Registers base length

	WDFDMAENABLER           DmaEnabler;         //
	WDFCOMMONBUFFER         CommonBuffer;       // 为 DMA 申请的一个 16M 的内存空间
	size_t                  CommonBufferSize;   // 空间大小 16M
	PUCHAR                  CommonBufferBase;   // 驱动程序可以访问的缓冲区的虚拟地址
	PHYSICAL_ADDRESS        CommonBufferBaseLA; // 设备可以访问的缓冲区的逻辑地址

	WDFQUEUE                WriteQueue;         //write queue for DMA
	WDFREQUEST				WriteRequest;       //DMA请求
	ULONG					WriteDmaLength;     //DMA  数据长度
	WDFTIMER                WriteTimer;         //预防 DMA 反馈超时的定时器
	BOOLEAN                 WriteTimeout;       //定时器是否超时
	
	WDFREQUEST				ReadRequest;        // 读请求
	PULONG					ReadBuffer;         // 读操作的 buffer指针
	WDFTIMER                ReadTimer;          // 预防 读操作 反馈超时的定时器
	BOOLEAN                 ReadTimeout;        // 定时器是否超时

	ULONG					CurrentRequestMode; // 当前请求模式： 0x0-- DMA方式；0xf--读取模式； 0xff--写模式

	WDFINTERRUPT            Interrupt;     	    // Returned by InterruptCreate DSP的反馈中断
	PKINTERRUPT             InterruptObject;    // address of interrupt object
	ULONG                   IntStatus;          // 中断状态，（未使用）

	WDFQUEUE                IoDispatchQueue;    // 写操作的 queue
	WDFREQUEST				IoWriteRequest;     // 写操作请求
	BOOLEAN                 IoWriteTimeout;     // 预防 写操作 反馈超时的定时器
	WDFTIMER                IoWriteTimer;       // 定时器是否超时


} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

//
// This macro will generate an inline function called DeviceGetContext
// which will be used to get a pointer to the device context memory
// in a type safe manner.
//
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

//
// Function to initialize the device and its callbacks
//

//NTSTATUS
//PcieForDSPCreateDevice(
//    _Inout_ PWDFDEVICE_INIT DeviceInit
//    );

NTSTATUS
PcieInitializeDeviceContext(
//_In_ PWDF_OBJECT_ATTRIBUTES Attributes,
_In_ PDEVICE_CONTEXT DevExt
);

NTSTATUS
PcieInitializeDMA(
_In_ PDEVICE_CONTEXT DevExt
);

EVT_WDF_DRIVER_DEVICE_ADD PcieForDSPEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP PcieForDSPEvtDriverContextCleanup;

EVT_WDF_DEVICE_D0_ENTRY PcieForDspDeviceD0Entry;
EVT_WDF_DEVICE_D0_EXIT PcieForDspDeviceD0Exit;
EVT_WDF_DEVICE_PREPARE_HARDWARE PcieForDspPreparaHardware;
EVT_WDF_DEVICE_RELEASE_HARDWARE PcieForDspReleaseHardware;