#include "HX711.h"


void HX711::MakePulse()
{
	_PD_SCK->Write(1);
	_PD_SCK->Write(0);
}

uint8_t HX711::ReadByte()
{
	uint8_t data = 0;
	for (std::size_t i = 0; i < 8; i++)
	{
		MakePulse();

		bool bit = _DOut->Read();

		data |= bit << (7 - i);
	}

	return data;
}

HX711::HX711(MicrocontrollerPin* DOUT, MicrocontrollerPin* PD_SCK)
{
	_DOut = DOUT;
	_PD_SCK = PD_SCK;
}

bool HX711::IsReady()
{
	return _DOut->Read() == 0;
}

const uint8_t dataBits = 24;
const uint8_t bitsInByte = 8;
const uint8_t bufferSize = dataBits / bitsInByte;

/// <summary>
/// 
/// </summary>
/// <param name="nextConversionChannel"></param>
/// <returns>24 bit data or empty if converter not ready</returns>
uint32_t HX711::ReadData(InputChunnelEnum nextConversionChannel)
{
	uint32_t data = 0;

	if (IsReady())
	{
		for (int8_t bitOffset = 16; bitOffset >= 0; bitOffset -= 8)
		{
			data |= ((uint32_t)ReadByte()) << bitOffset;
		}

		for (std::size_t i = 0; i < (uint8_t)nextConversionChannel; i++)
		{
			MakePulse();
		}
	}

	return data;
}
