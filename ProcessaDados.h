#pragma once
#include<Windows.h>
class ProcessaDados
{
public:
	ProcessaDados();
	void ProcessaInformacoes(HANDLE *SerialPortHandle);
	~ProcessaDados();
};

