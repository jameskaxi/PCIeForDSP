/*++

Module Name:

    driver.h

Abstract:

    This file contains the driver definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#define INITGUID

#include <ntddk.h>
#include <wdf.h>

#include "device.h"
#include "queue.h"
#include "trace.h"
#include "RegPcie.h"

//
// WDFDRIVER Events
//

DRIVER_INITIALIZE DriverEntry;


