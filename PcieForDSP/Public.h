/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_PcieForDSP,
    0xc2303380,0xd20c,0x4107,0xb0,0xa0,0xfc,0x8a,0x4a,0xf3,0xd3,0x48);
// {c2303380-d20c-4107-b0a0-fc8a4af3d348}
