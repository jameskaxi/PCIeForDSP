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

	ULONG                  PhysicalAddressRegister;

	PUCHAR                  MemBar0Base;      	//zhu: bar0 Registers base address (must be 32bit align)
	ULONG                   MemBar0Length;    	//zhu  bar0 Registers base length
	PUCHAR                  MemBar1Base;      	//zhu: bar1 Registers base address (must be 32bit align)
	ULONG                   MemBar1Length;    	//zhu  bar0 Registers base length
	PUCHAR                  MemBar2Base;      	// Registers base address (must be 32bit align)
	ULONG                   MemBar2Length;    	// Registers base length


	WDFDMAENABLER           DmaEnabler;
	WDFCOMMONBUFFER         CommonBuffer;
	size_t                  CommonBufferSize;
	PUCHAR                  CommonBufferBase;
	PHYSICAL_ADDRESS        CommonBufferBaseLA;   // Logical Address

	WDFQUEUE                WriteQueue;
	WDFREQUEST				WriteRequest;
	ULONG					WriteDmaLength;
	WDFTIMER                WriteTimer;
	BOOLEAN                 WriteTimeout;
	

	//WDFQUEUE                ReadQueue;
	WDFREQUEST				ReadRequest;
	//ULONG					ReadDmaLength;
	PULONG					ReadBuffer;
	WDFTIMER                ReadTimer;
	BOOLEAN                 ReadTimeout;

	ULONG					CurrentRequestMode; // 0xf--读取模式 ， 0x0-- DMA方式，动态加载,0xff--写模式
	//WDFMEMORY               MemoryBuffer;
	//PVOID                   BufferPointer;

	WDFINTERRUPT            Interrupt;     	// Returned by InterruptCreate

	PKINTERRUPT             InterruptObject;			// address of interrupt object
	ULONG                   IntStatus;

	WDFQUEUE                IoDispatchQueue;
	WDFREQUEST				IoWriteRequest;


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
//NTSTATUS
//PcieForDspApplyMemoryBuffer(
//_In_ PWDF_OBJECT_ATTRIBUTES Attributes,
//_In_ PDEVICE_CONTEXT DevExt
//);
//
// WDFDRIVER Events
//

EVT_WDF_DRIVER_DEVICE_ADD PcieForDSPEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP PcieForDSPEvtDriverContextCleanup;

EVT_WDF_DEVICE_D0_ENTRY PcieForDspDeviceD0Entry;
EVT_WDF_DEVICE_D0_EXIT PcieForDspDeviceD0Exit;
EVT_WDF_DEVICE_PREPARE_HARDWARE PcieForDspPreparaHardware;
EVT_WDF_DEVICE_RELEASE_HARDWARE PcieForDspReleaseHardware;