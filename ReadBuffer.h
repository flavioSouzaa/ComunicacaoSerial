#pragma once
#include <Windows.h>

class ReadBuffer
{
public:
	ReadBuffer();
	bool read(HANDLE *SerialPortHandle);
	~ReadBuffer();
};
