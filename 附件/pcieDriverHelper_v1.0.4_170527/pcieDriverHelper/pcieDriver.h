#pragma once

#include <Windows.h>

#ifdef _EXPORTING
#define DRIVER_DECLSPEC    __declspec(dllexport)
#else
#define DRIVER_DECLSPEC    __declspec(dllimport)
#endif

DRIVER_DECLSPEC TCHAR* __stdcall GetLastDevError();
DRIVER_DECLSPEC bool __stdcall OpenPcieDev();
DRIVER_DECLSPEC void __stdcall ClosePcieDev();
DRIVER_DECLSPEC bool __stdcall DmaToDev(LPDWORD pBufferAddr,DWORD bufferSize);
DRIVER_DECLSPEC bool __stdcall DmaToDevWithMode(LPDWORD pBufferAddr,DWORD bufferSize,DWORD mode);
//DRIVER_DECLSPEC bool __stdcall DmaFromDev(LPDWORD pBufferAddr,DWORD bufferSize);
DRIVER_DECLSPEC bool __stdcall SetByCPUMode(PDWORD32 pRegAddr,DWORD32 dataNum);
DRIVER_DECLSPEC bool __stdcall SetDevRegister(DWORD32 devRegAddr,PDWORD32 pRegAddr,DWORD32 regSize);
DRIVER_DECLSPEC bool __stdcall SetDevRegister(DWORD32 devRegAddr,DWORD32 regData);
DRIVER_DECLSPEC bool __stdcall DebugRegister(DWORD32 barX,DWORD32 OfferAddr,DWORD32 data);
DRIVER_DECLSPEC bool __stdcall ReadFPGAReg(DWORD32 OfferAddr,PDWORD32 outBuffer);
DRIVER_DECLSPEC bool __stdcall Proloading(LPDWORD pFileBuf,DWORD32 bufSize);