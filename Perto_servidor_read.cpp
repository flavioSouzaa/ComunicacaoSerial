#include <iostream>
#include "ProcessaDados.h"
#include "SerialPort.h"
#include <Windows.h>

int main()
{
/******************************************/
	ProcessaDados *Processa = new ProcessaDados();
	SerialPort	  *Serial	= new SerialPort();
/******************************************/
	bool Open = false;
	HANDLE SerialPortHandle;
/******************************************/
	printf("********************************************\n");
	printf("Bem Vindo a Tela de Servidor\n");
	printf("********************************************\n");
	while (true) {
		Processa->ProcessaInformacoes(&SerialPortHandle);		
	}
}
