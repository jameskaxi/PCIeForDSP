
#include "stdafx.h"
#include "Public.h"
#include <windows.h>
#include <setupapi.h>
#include <stddef.h>

#ifdef CS_HU
#pragma unmanaged
#endif

HANDLE hPcieDev = INVALID_HANDLE_VALUE;
TCHAR lastError[100] = L"无错误！";

TCHAR* __stdcall GetLastDevError()
{
	return lastError;
}

bool __stdcall OpenPcieDev()
{
	bool status = false;
	HDEVINFO hDevInfo;
	SP_DEVICE_INTERFACE_DATA dia;
	dia.cbSize = sizeof(dia);
	SP_DEVINFO_DATA da;
	da.cbSize = sizeof(da);
	PSP_DEVICE_INTERFACE_DETAIL_DATA didd;//一个指向SP_DEVICE_INTERFACE_DETAIL_DATA结构的指针，该结构用于接收指定接口的信息。
	DWORD nRequiredSize;
	int ii;
	BOOL isFind;

	hDevInfo = SetupDiGetClassDevs(
		(LPGUID)&GUID_DEVINTERFACE_PcieForDSP,
		NULL,
		NULL,
		DIGCF_PRESENT|DIGCF_DEVICEINTERFACE);

	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"未扫描到PCIE设备！");
		return status;
	}

	ii = 0;
	isFind = TRUE;
	while (isFind)
	{
		isFind = SetupDiEnumDeviceInterfaces(
			hDevInfo,
			NULL,
			(LPGUID)&GUID_DEVINTERFACE_PcieForDSP,
			ii,
			&dia);
		if (isFind)
		{
			SetupDiGetDeviceInterfaceDetail(
				hDevInfo,&dia,NULL,0,&nRequiredSize,&da);

			didd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(nRequiredSize);
			didd->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			if (SetupDiGetDeviceInterfaceDetail(
				hDevInfo,&dia,didd,nRequiredSize,NULL,&da))
			{
				hPcieDev = CreateFile(
					didd->DevicePath,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL,
					OPEN_EXISTING,
					0,
					NULL);

				free((PVOID) didd);
				if (hPcieDev == INVALID_HANDLE_VALUE)
				{
					wcscpy_s(lastError, L"打开PCIE设备失败！");
					return status;
				}

				status = true;
				break;
			}
			else
				wcscpy_s(lastError, L"获取PCIE设备信息失败！");
			free((PVOID) didd);
			ii++;
		}
		else
			wcscpy_s(lastError, L"未发现PCIE设备！");
	}
	return status;
}

void __stdcall ClosePcieDev()
{
	if (hPcieDev != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hPcieDev);
		hPcieDev = INVALID_HANDLE_VALUE;
	}
}

bool __stdcall DmaToDev(LPDWORD pBufferAddr,DWORD bufferSize)
{
	DWORD outputSize;
	if (hPcieDev == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"PCIE设备未打开！");
		return false;
	}

	if (bufferSize > MAX_DMABUFFER_SIZE)
	{
		wcscpy_s(lastError, L"写入数据长度超过最大长度！");
		return false;
	}

	if (!WriteFile(hPcieDev,pBufferAddr,bufferSize,&outputSize,NULL))
	{
		wcscpy_s(lastError, L"DMA写入PCIE设备失败！");
		return false;
	}

	 if (outputSize != bufferSize)
	 {
	 	wcscpy_s(lastError, L"返回数据长度与请求数据长度不符！");
	 	return false;
	 }

	return true;
}

bool __stdcall DmaToDevWithMode(LPDWORD pBufferAddr,DWORD bufferSize,DWORD mode)
{
	DWORD outputSize;
	if (hPcieDev == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"PCIE设备未打开！");
		return false;
	}

	if (bufferSize > MAX_DMABUFFER_SIZE)
	{
		wcscpy_s(lastError, L"写入数据长度超过最大长度！");
		return false;
	}

	if (mode == 3)
	{
		DWORD32 pInputBuf[3];
		DWORD32 outputBuf;
		DWORD outputBufSize;
		pInputBuf[0] = 2;
		pInputBuf[1] = 0x8;
		pInputBuf[2] = 0x3;
		bool state = true;

		state = DeviceIoControl(hPcieDev,PCIE_IOCTL_DEBUG,pInputBuf,3*sizeof(DWORD32),&outputBuf,sizeof(DWORD32),&outputBufSize,NULL);
		if(!state)
		{
			wcscpy_s(lastError, L"写入失败！");
			return false;
		}
	} 
	else
	{
		DWORD32 pInputBuf[3];
		DWORD32 outputBuf;
		DWORD outputBufSize;
		pInputBuf[0] = 2;
		pInputBuf[1] = 0x8;
		pInputBuf[2] = 0x1;
		bool state = true;

		state = DeviceIoControl(hPcieDev,PCIE_IOCTL_DEBUG,pInputBuf,3*sizeof(DWORD32),&outputBuf,sizeof(DWORD32),&outputBufSize,NULL);
		if(!state)
		{
			wcscpy_s(lastError, L"写入失败！");
			return false;
		}
	}

	if (!WriteFile(hPcieDev,pBufferAddr,bufferSize,&outputSize,NULL))
	{
		wcscpy_s(lastError, L"DMA写入PCIE设备失败！");
		return false;
	}

	if (outputSize != bufferSize)
	{
		wcscpy_s(lastError, L"返回数据长度与请求数据长度不符！");
		return false;
	}

	return true;
}
// bool __stdcall DmaFromDev(LPDWORD pBufferAddr,DWORD bufferSize)
// {
// 	DWORD outputSize;
// 	if (hPcieDev == INVALID_HANDLE_VALUE)
// 	{
// 		wcscpy_s(lastError, L"PCIE设备未打开！");
// 		return false;
// 	}

// 	if (bufferSize > MAX_DMABUFFER_SIZE)
// 	{
// 		wcscpy_s(lastError, L"读取数据长度超过最大长度！");
// 		return false;
// 	}

// 	if (!ReadFile(hPcieDev,pBufferAddr,bufferSize,&outputSize,NULL))
// 	{
// 		wcscpy_s(lastError, L"DMA读取PCIE设备失败！");
// 		return false;
// 	}

// 	if (outputSize != bufferSize)
// 	{
// 		wcscpy_s(lastError, L"返回数据长度与请求数据长度不符！");
// 		return false;
// 	}

// 	return true;
// }


bool __stdcall SetByCPUMode(PDWORD32 pRegAddr,DWORD32 dataNum)
{
	PDWORD32 pInputBuf;
	DWORD32 inputBufNum;
	DWORD32 outputBuf;
	DWORD outputBufSize;

	if (hPcieDev == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"PCIE设备未打开！");
		return false;
	}

	inputBufNum = dataNum*2 +1;
	pInputBuf = new DWORD32[inputBufNum];

	pInputBuf[0] = dataNum*sizeof(DWORD32);

	
	//for(DWORD i=0;i< dataNum*2;i++)
	//{
	//	pInputBuf[i+1] = pRegAddr[i];
	//}
	//pInputBuf[0] = devRegAddr;
	
	memcpy(&pInputBuf[1],pRegAddr,dataNum*2*sizeof(DWORD32));
	if (!DeviceIoControl(hPcieDev,PCIeDMA_IOCTL_WRITE_REG,
		pInputBuf,inputBufNum * sizeof(DWORD32),&outputBuf,sizeof(DWORD32),&outputBufSize,NULL))
	{
		wcscpy_s(lastError, L"写入PCIE设备寄存器失败！");
		delete pInputBuf;
		return false;
	}
	
	delete pInputBuf;
	return true;
}

bool __stdcall SetDevRegister(DWORD32 devRegAddr,PDWORD32 pRegAddr,DWORD32 regSize)
{
	PDWORD32 pInputBuf;
	DWORD32 inputBufNum;
	DWORD32 outputBuf;
	DWORD outputBufSize;

	if (hPcieDev == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"PCIE设备未打开！");
		return false;
	}

	inputBufNum = regSize / sizeof(DWORD32)*2 +1;
	pInputBuf = new DWORD32[inputBufNum];

	pInputBuf[0] = regSize;//--》2017/06/27问题：准备让regSize直接为目标值，不再涉及数据类型的问题！《--
	for(DWORD i=0;i< (inputBufNum-1)/2;i++)
	{
		pInputBuf[i*2+1] = devRegAddr + i*4;
		pInputBuf[i*2+2] = pRegAddr[i];
	}
	//pInputBuf[0] = devRegAddr;
	
	//memcpy(&pInputBuf[2],pRegAddr,regSize);
	if (!DeviceIoControl(hPcieDev,PCIeDMA_IOCTL_WRITE_REG,
		pInputBuf,inputBufNum * sizeof(DWORD32),&outputBuf,sizeof(DWORD32),&outputBufSize,NULL))
	{
		wcscpy_s(lastError, L"写入PCIE设备寄存器失败！");
		delete pInputBuf;
		return false;
	}
	
	delete pInputBuf;
	return true;
}

bool __stdcall SetDevRegister(DWORD32 devRegAddr,DWORD32 regData)
{
	DWORD32 pInputBuf[3];
	DWORD32 outputBuf;
	DWORD outputBufSize;

	if (hPcieDev == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"PCIE设备未打开！");
		return false;
	}

	
	pInputBuf[0] = sizeof(DWORD32);
	pInputBuf[1] = devRegAddr;
	pInputBuf[2] = regData;
	if (!DeviceIoControl(hPcieDev,PCIeDMA_IOCTL_WRITE_REG,
		pInputBuf,3*sizeof(DWORD32),&outputBuf,sizeof(DWORD32),&outputBufSize,NULL))
	{
		wcscpy_s(lastError, L"写入PCIE设备寄存器失败！");
		return false;
	}

	return true;
}



bool __stdcall DebugRegister(DWORD32 barX,DWORD32 OfferAddr,DWORD32 data)
{
	DWORD32 pInputBuf[3];
	DWORD32 outputBuf;
	DWORD outputBufSize;
	bool state;

	if (hPcieDev == INVALID_HANDLE_VALUE)
	{
		wcscpy_s(lastError, L"PCIE设备未打开！");
		return false;
	}

	pInputBuf[0] = barX;
	pInputBuf[1] = OfferAddr;
	pInputBuf[2] = data;

	state = DeviceIoControl(hPcieDev,PCIE_IOCTL_DEBUG,pInputBuf,3*sizeof(DWORD32),&outputBuf,sizeof(DWORD32),&outputBufSize,NULL);
	if(!state)
	{
		wcscpy_s(lastError, L"写入失败！");
		return false;
	}

	return true;

}
#ifdef CS_HU
#pragma managed
#endif