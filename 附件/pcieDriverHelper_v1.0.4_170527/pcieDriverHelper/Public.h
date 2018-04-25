/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

#include "initguid.h"

//
// Define an Interface Guid so that app can find the device and talk to it.
//
/*
DEFINE_GUID (GUID_DEVINTERFACE_PcieForDSP,
    0xc2303380,0xd20c,0x4107,0xb0,0xa0,0xfc,0x8a,0x4a,0xf3,0xd3,0x48);
// {c2303380-d20c-4107-b0a0-fc8a4af3d348}
*/

DEFINE_GUID(GUID_DEVINTERFACE_PcieForDSP,
	0x76c326d4, 0xd26b, 0x4c7e, 0x91, 0x53, 0x70, 0xef, 0xfc, 0xe2, 0x2d, 0x4f);
// {76c326d4-d26b-4c7e-9153-70effce22d4f}


#define MAX_DMABUFFER_SIZE         (16*1024*1024)

//#define PCIeDMA_IOCTL_GET_TIME				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
//#define PCIeDMA_IOCTL_GET_VERSION			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
//#define PCIeDMA_IOCTL_TRIG_INT				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define PCIeDMA_IOCTL_WRITE_REG		    	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define PCIeDMA_IOCTL_READ_REG  			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define PCIE_IOCTL_DEBUG                    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)