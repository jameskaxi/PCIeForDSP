// This is the main DLL file.

#include "stdafx.h"

#include "pcieDriverHelper.h"

namespace pcieDriverHelper {

	String^ PcieDriver::GetLastDeviceError()
	{
		return String(GetLastDevError()).ToString();
	}

	bool PcieDriver::OpenPcieDevice()
	{
		return OpenPcieDev();
	}

	void PcieDriver::ClosePcieDevice()
	{
		ClosePcieDev();
	}

	bool PcieDriver::DmaToDevice(array<byte> ^inBuf)
	{
		bool status = false;
		DWORD inBufSize = inBuf->Length;
		pin_ptr<byte> pInBuf = &inBuf[0];

		status = DmaToDev((LPDWORD)pInBuf,inBufSize);
		pInBuf = nullptr;
		return status;
	}

	bool PcieDriver::DmaToDeviceWithMode(array<byte> ^inBuf,unsigned int mode)
	{
		bool status = false;
		DWORD inBufSize = inBuf->Length;
		pin_ptr<byte> pInBuf = &inBuf[0];

		status = DmaToDevWithMode((LPDWORD)pInBuf,inBufSize,mode);
		//status = DmaToDev((LPDWORD)pInBuf,inBufSize);
		pInBuf = nullptr;
		return status;
	}
	//bool PcieDriver::DmaFromDevice(array<byte> ^inBuf)
	//{
	//	bool status = false;
	//	DWORD inBufSize = inBuf->Length;
	//	pin_ptr<byte> pInBuf = &inBuf[0];

	//	status = DmaFromDev((LPDWORD)pInBuf,inBufSize);
	//	pInBuf = nullptr;
	//	return status;
	//}

	bool PcieDriver::SetFPGARegister(array<unsigned int> ^regData,unsigned int dataNum)
	{
		bool status = false;
		pin_ptr<unsigned int> pRegAddr = &regData[0];

		status = SetByCPUMode((PDWORD32)pRegAddr,dataNum);
		pRegAddr = nullptr;
		return status;
	}

	bool PcieDriver::SetDeviceRegister(unsigned int devRegAddr,array<unsigned int> ^regData)
	{
		bool status = false;
		DWORD32 regSize = regData->Length * sizeof(unsigned int);
		pin_ptr<unsigned int> pRegAddr = &regData[0];

		status = SetDevRegister(devRegAddr,(PDWORD32)pRegAddr,regSize);
		pRegAddr = nullptr;
		return status;
	}

	bool PcieDriver::SetDeviceRegister(unsigned int devRegAddr,unsigned int regData)
	{
		return SetDevRegister(devRegAddr,regData);
	}

	bool PcieDriver::SetDebugRegister(unsigned int barX, unsigned int devRegAddr,unsigned int regData)
	{
		return DebugRegister(barX,devRegAddr,regData);
	}

	bool PcieDriver::ReadPFGARegister(unsigned int devRegAddr,array<unsigned int> ^outBuf)
	{
		bool status = false;
		pin_ptr<unsigned int> pOutBuffer = &outBuf[0];

		status = ReadFPGAReg(devRegAddr,pOutBuffer);
		pOutBuffer = nullptr;
		return status;
	}

	bool PcieDriver::DspProloading(array<byte> ^inBuf)
	{
		bool status = false;
		DWORD inBufSize = inBuf->Length;
		pin_ptr<byte> pInBuf = &inBuf[0];

		status = Proloading((LPDWORD)pInBuf,inBufSize);
		pInBuf = nullptr;
		return status;
	}
	/*bool PcieDriver::SetFilter(unsigned int barX,unsigned int OfferAddr,unsigned int data)
	{
		return DebugRegister(barX,OfferAddr,data);
	}*/
}