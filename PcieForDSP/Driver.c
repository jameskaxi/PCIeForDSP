
/*
 *                  ----------神兽出没------------
 *					 　　　┏┓　　　┏┓
 *					 　　┏┛┻━━━┛┻┓
 *					 　　┃　　　　　　　┃
 *					 　　┃　　　━　　　┃
 *					 　　┃　┳┛　┗┳　┃
 *					 　　┃　　　　　　　┃
 *					 　　┃　　　┻　　　┃
 *					 　　┃　　　　　　　┃
 *					 　　┗━┓　　　┏━┛
 *					 　　　　┃　　　┃
 *					 　　　　┃　　　┃
 *					 　　　　┃　　　┗━━━┓
 *					 　　　　┃　　　　　　　┣┓
 *					 　　　　┃　　　　　　　┏┛
 *					 　　　　┗┓┓┏━┳┓┏┛
 *					 　　　　　┃┫┫　┃┫┫
 *					 　　　　　┗┻┛　┗┻┛
 *
 * ━━━━━━Code is far away from bug with the animal protecting━━━━━━
 * -----------------------神兽保佑,代码无bug-----------------------------------
 */
 


/*++

Module Name:

    driver.c

Abstract:

    This file contains the driver entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "driver.h"
#include "driver.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#endif

/*******************************************************************************
*  程序描述：
*  驱动程序入口。
*
*  参数：
*  DriverObject - 
*  RegistryPath - 
*
*  返回值：
*  NT status code - failure will result in the device stack being torn down
********************************************************************************/
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:
    DriverEntry initializes the driver and is the first routine called by the
    system after the driver is loaded. DriverEntry specifies the other entry
    points in the function driver, such as EvtDevice and DriverUnload.

Parameters Description:

    DriverObject - represents the instance of the function driver that is loaded
    into memory. DriverEntry must initialize members of DriverObject before it
    returns to the caller. DriverObject is allocated by the system before the
    driver is loaded, and it is released by the system after the system unloads
    the function driver from memory.

    RegistryPath - represents the driver specific path in the Registry.
    The function driver can use the path to store driver related data between
    reboots. The path does not store hardware instance specific data.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    WDF_DRIVER_CONFIG config;
    NTSTATUS status;
    WDF_OBJECT_ATTRIBUTES attributes;

    //
    // Initialize WPP Tracing
    //
    WPP_INIT_TRACING( DriverObject, RegistryPath );

    //TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    //
    // Register a cleanup callback so that we can call WPP_CLEANUP when
    // the framework driver object is deleted during driver unload.
    //
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = PcieForDSPEvtDriverContextCleanup;

    WDF_DRIVER_CONFIG_INIT(&config,
                           PcieForDSPEvtDeviceAdd
                           );

    status = WdfDriverCreate(DriverObject,
                             RegistryPath,
                             &attributes,
                             &config,
                             WDF_NO_HANDLE
                             );

    if (!NT_SUCCESS(status)) {
        //TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER, "WdfDriverCreate failed %!STATUS!", status);
        WPP_CLEANUP(DriverObject);
        return status;
    }

    //TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}


