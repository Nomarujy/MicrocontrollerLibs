#pragma once
#include <cstdint>
#include "Microcontroller/AbstractMicrocontroller/MicrocontrollerPin.h"
#include "InputChannel.h"

class HX711
{
private:
	MicrocontrollerPin* _DOut;
	MicrocontrollerPin* _PD_SCK;

	void MakePulse();
	uint8_t ReadByte();
public:
	HX711(MicrocontrollerPin* DOUT, MicrocontrollerPin* PD_SCK);
	bool IsReady();
	uint32_t ReadData(InputChunnelEnum nextConversionChannel);
};

