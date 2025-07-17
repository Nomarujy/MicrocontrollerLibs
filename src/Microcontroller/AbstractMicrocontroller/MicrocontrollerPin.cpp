#include "MicrocontrollerPin.h"

void MicrocontrollerPin::Togle()
{
	Write(!Read());
}
