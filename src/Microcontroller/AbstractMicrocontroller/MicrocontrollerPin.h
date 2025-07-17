#pragma once

class MicrocontrollerPin
{
public:
	virtual bool Read() = 0;
	virtual void Write(bool value) = 0;

	void Togle();
};

