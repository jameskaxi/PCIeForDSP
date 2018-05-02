// pcieDriverHelper.h

#pragma once

#include "Public.h"
#include "pcieDriver.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace pcieDriverHelper {

	public ref class PcieDriver
	{
		// TODO: Add your methods for this class here.
	public:
		literal unsigned int MAX_BUF_SIZE = MAX_DMABUFFER_SIZE;
		
		static String^ GetLastDeviceError();

		static bool OpenPcieDevice();

		static void ClosePcieDevice();

		static bool DmaToDevice(array<byte> ^inBuf);

		static bool DmaToDeviceWithMode(array<byte> ^inBuf,unsigned int mode);

		//static bool DmaFromDevice(array<byte> ^inBuf);

		static bool SetFPGARegister(array<unsigned int> ^regData,unsigned int dataNum);

		static bool SetDeviceRegister(unsigned int devRegAddr,array<unsigned int> ^regData);

		static bool SetDeviceRegister(unsigned int devRegAddr,unsigned int regData);

		static bool SetDebugRegister(unsigned int barX,unsigned int devRegAddr,unsigned int regData);
		//static bool SetFilter(unsigned int controlData);
		//static bool SetFilter(unsigned int barX,unsigned int OfferAddr,unsigned int data);
	};
}
