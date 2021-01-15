#ifndef SERIALPORT_H
#pragma once
#include <Windows.h>

class SerialPort
{
public:
	SerialPort();
	bool begin(char comport[], int _baud, HANDLE *SerialPortHandle);
	bool close(HANDLE *SerialPortHandle);
	~SerialPort();

private:
	int error;
	int baud;
	bool isOpen = false;
	HANDLE SerialPortHandle;
};

#endif // !SERIALPORT_H
