#include "ReadBuffer.h"
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define  MAX_DWBYTESTREAD (260)

ReadBuffer::ReadBuffer() {
}

bool ReadBuffer::read(HANDLE *SerialPortHandle) {
typedef enum {
	ST_STX = 0,
	ST_CMD,
	ST_QTD,
	ST_DATA,
	ST_CHK,
	ST_ETX,
	ST_VERIFICADADOS
} States;//utilizado para inicializar maquina de estados. 
 States state = ST_STX;
/******************************************/
	DWORD dwBytesToRead = 255;
	DWORD dwBytestRead  = 255;
/******************************************/
	int filed_number = 0;
	int contador     = 0;
	int QtdVerifica  = 0;
	int QtdBuffer	 = 0;
	int size		 = 0;
/******************************************/
	bool isAck		= false;
	bool isVerifica = false;
/******************************************/
	char inicio		= 0x40;
	char fim		= 0x21;
	char write		= 0x31;
	char read		= 0x02;
	char buffer		 [255];
	char bufferCarga [255];
/******************************************/	
	memset(buffer, 0, 255);
	state = ST_STX;
/******************************************/
	while (true) {
		if (isVerifica)
			break;

		if (!ReadFile(*SerialPortHandle, (void*)buffer, dwBytesToRead, &dwBytestRead, NULL)) {
			printf("********************************************\n");
			printf("Falha na leitura dos dados\n");
			printf("********************************************\n");
		}
		
		if (dwBytestRead > 0) {
			printf("\n********************************************\n");
			printf("Analisando dados \n");
			printf("dwBytestRead: %d\n", dwBytestRead);
			for (int i = 0; i < dwBytestRead; i++)
			{
				printf("%02x", buffer[i]);
			}
			printf("\n********************************************\n");
			for (int i = 0; i <= dwBytestRead; i++)
			{
				switch (state)
				{
				case ST_STX:
					if (buffer[0] == inicio) {
						bufferCarga[i] = buffer[i];
						state = ST_CMD;
					}
					else {
						i = MAX_DWBYTESTREAD;
					}
					break;
				case ST_CMD:
					if (buffer[1] == write) {
						bufferCarga[i] = buffer[i];
						state = ST_QTD;
					}
					else if (buffer[1] == read) {
						bufferCarga[i] = buffer[i];
						state = ST_QTD;
					}
					else
					{
						i = MAX_DWBYTESTREAD;
					}
					break;
				case ST_QTD:
					QtdBuffer = buffer[i];
					bufferCarga[i] = buffer[i];
					state = ST_DATA;
					break;
				case ST_DATA:
					while (contador != QtdBuffer)
					{
						bufferCarga[i] = buffer[i];// fazer um memcpy;
						contador++;
						i++;
					}
					i = i - 1;

					//state = ST_CHK;//Utilizar 
					state = ST_ETX;
					break;
				case ST_ETX:
					if (buffer[i] == fim) {
						bufferCarga[i] = buffer[i];
						isAck = true;
						state = ST_VERIFICADADOS;
						size = i;						
					}
					else
					{
						isAck = false;
					}

					break;
				case ST_VERIFICADADOS:					
					for (int t = 0; t < size; t++)
					{
						if (buffer[t] == bufferCarga[t]) {
							QtdVerifica++;
						}
					}				

					if (size == QtdVerifica) {
						isVerifica = true;
					}
					else {
						isVerifica = false;
					}

					if (isVerifica) {
						printf("********************************************\n");
						for (int i = 0; i < size; i++)
						{
							printf("%02x", bufferCarga[i]);
						}
						printf("\n********************************************\n");
						i = MAX_DWBYTESTREAD;
					}
					else {
						isAck = false;
					}
					break;
				default:
					printf("Erro na maquina de estados\n");
					isAck = false;
					break;
				}
			}
		}
		else {
		printf("Esperando resposta....\n");
		}
		Sleep(500);
	}

	return  isAck;
}
ReadBuffer::~ReadBuffer() {
}

/*
| STX | QTD_DADOS | DADOS | CHK | ETX |

STX			(1 Byte)->Inicio da transmissão(0x40)
QTD_DADOS	(1 Byte)->Quantidade de dados
DADOS		(N Bytes)->Dados
CHK			(1 Byte)->Checksum da transmissão
ETX			(1 Byte)->Fim da transmissão(0x21)
*/
/* possiveis estados */
