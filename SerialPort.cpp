#include "SerialPort.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

SerialPort::SerialPort() {
	error = 0;
	baud = 115200;
}
bool SerialPort::begin(char comport[], int _baud, HANDLE *SerialPortHandle) {
	isOpen = false;
	baud = _baud;
	DWORD BR;

	switch (baud) {
	case 9600:
		BR = CBR_9600;
		break;
	case 115200:
		BR = CBR_115200;
		break;
	default:
		BR = CBR_115200;
		break;
	}
	//Abrir a porta de comunicação com a serial.
	*SerialPortHandle = CreateFile(comport, GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	//VERIFICA SE OCORREU ERRO NA ABERTURA
	if (*SerialPortHandle == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_NOT_FOUND) {
			printf("*************************************************\n");
			printf("Erro: SerialPort Porta selecionada não existe\n");
			printf("*************************************************\n");
			isOpen = false;
		}
		else {
			printf("*************************************************\n");
			printf("Erro: Invalid Handle\n");
			printf("*************************************************\n");
			isOpen = false;
		}
		error = 1;
		isOpen = false;
	}
	else {
		bool isOpen = true;
	}
	//Setando os parâmetros da porta serial.

	if (error == 0) {
		DCB dcbParamaters;

		if (!GetCommState(*SerialPortHandle, &dcbParamaters)) {
			printf("*************************************************\n");
			printf("Erro: Falha na Captura do status.\n");
			printf("*************************************************\n");
			errno = 1;
			isOpen = false;
		}

		dcbParamaters.BaudRate = BR;
		dcbParamaters.ByteSize = 8;
		dcbParamaters.StopBits = ONESTOPBIT;
		dcbParamaters.Parity = NOPARITY;

		if (!GetCommState(*SerialPortHandle, &dcbParamaters)) {
			printf("*************************************************\n");
			printf("Erro: Falha na configuracao da Serial\n");
			printf("*************************************************\n");
			error = 1;
			isOpen = false;
		}
		else
		{
			isOpen = true;
		}
	}
	//Setando o tempo de Timeout
	if (error == 0) {
		COMMTIMEOUTS timeout = { 0 };
		timeout.ReadIntervalTimeout = 40;
		timeout.ReadTotalTimeoutConstant = 40;
		timeout.ReadTotalTimeoutMultiplier = 10;
		timeout.WriteTotalTimeoutConstant = 40;
		timeout.WriteTotalTimeoutMultiplier = 10;

		if (!SetCommTimeouts(*SerialPortHandle, &timeout)) {
			printf("*************************************************\n");
			printf("Erro: Falha ao Setar o timeout\n");
			printf("*************************************************\n");
			error = 1;
			isOpen = false;
		}
	}
	return isOpen;
}

bool SerialPort::close(HANDLE *SerialPortHandle) {
	if (isOpen) {
		CloseHandle(*SerialPortHandle);
	}
	else {
		printf("*************************************************\n");
		printf("Falha ao Fechar a porta de comunicacao\n");
		printf("*************************************************\n");
		isOpen = false;
	}
	return 	isOpen;
}
SerialPort::~SerialPort() {
}
