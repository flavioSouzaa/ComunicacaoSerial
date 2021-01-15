#include "WriteBuffer.h"
#include <stdint.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

WriteBuffer::WriteBuffer() {
}

bool WriteBuffer::write(char buffer[], int size, HANDLE *SerialPortHandle) {
	/**********************************************/
	buffer;
	DWORD dwBytesToWrite = size;
	DWORD dwBytesWrite	 = size;
	bool isWrite = false;
	/**********************************************/

	if (!WriteFile(*SerialPortHandle, buffer, dwBytesToWrite, &dwBytesWrite, NULL)) {
		printf("ERROR: SerialHandle\n");
		isWrite = false;
	}
	else {
		byte b;
		if (dwBytesWrite >0) {
			for (int i = 0; i < dwBytesWrite; i++) {
				b = buffer[i];
				printf("%02x ", b);
			}
			isWrite = true;
		}
		else {
			isWrite = false;
		}		
		return isWrite;
	}
}


WriteBuffer::~WriteBuffer() {
}
