#include "ProcessaDados.h"
#include "WriteBuffer.h"
#include "SerialPort.h"
#include "GeraCrc16.h"
#include "ReadBuffer.h"

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define MAX_FAILED (3)
ProcessaDados::ProcessaDados() {
}

void ProcessaDados::ProcessaInformacoes(HANDLE *SerialPortHandle) {
/**********************************************/
	 SerialPortHandle;	
/**********************************************/	
	char bufferTeste[1]		   ;
	char comport[]     = "COM2";		
	char ack		   = 0x06  ;
	char nak		   = 0x15  ;	
/**********************************************/
	int  baud = 115200  ;	
	int  size		    ;
	int  failed		 = 0;	
/**********************************************/
	bool iswrite = false;
	bool isRead  = false;
	bool isOpen  = false;
/**********************************************/
	SerialPort  *OpenPort = new SerialPort ();	
	WriteBuffer *escreve  = new WriteBuffer();
	ReadBuffer  *leitura  = new ReadBuffer ();
/**********************************************/	
	//
	isOpen = OpenPort->begin(comport, baud, SerialPortHandle);

	if (isOpen == false) {
		printf("******************************************\n");
		printf("Falha na abertura da comunicacao\n");
		printf("******************************************\n");
	}
	else {
		while (true) {

			isRead = leitura->read(SerialPortHandle);

			if (isRead) {
				printf("\n******************************************\n");
				printf("Dados verificados com sucesso\n");
				printf("******************************************\n");
				size = 1;
				bufferTeste[0] = ack;

				iswrite = escreve->write(bufferTeste, size, SerialPortHandle);
				
				if (iswrite) {
					printf("\n******************************************\n");
					printf("ACK enviado com sucesso!\n");					
					printf("******************************************\n");
				}
				else {
					printf("\n******************************************\n");
					printf("ACK falha no envio do ACK!\n");
					printf("******************************************\n");
				}
			}
			else {
				printf("******************************************\n");
				printf("Erro na verificacao dos dados\n");
				printf("******************************************\n");
				size = 1;
				bufferTeste[0] = nak;
				
				iswrite = escreve->write(bufferTeste, size, SerialPortHandle);
				
				if (iswrite) {
					printf("\n******************************************\n");
					printf("NAK enviado com sucesso!\n");
					printf("******************************************\n");
				}
				else {
					printf("\n******************************************\n");
					printf("NAK falha no envio do ACK!\n");
					printf("******************************************\n");
				}
			}			
			Sleep(500);
		}
	}
}

ProcessaDados::~ProcessaDados() {
}
