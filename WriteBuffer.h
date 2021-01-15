#pragma once
#include <Windows.h>
class WriteBuffer
{
public:
	WriteBuffer();
	bool write(char buffer[], int size, HANDLE *SerialPortHandle);
	~WriteBuffer();
};

