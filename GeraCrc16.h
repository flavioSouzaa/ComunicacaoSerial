#pragma once
class GeraCrc16
{
public:
	GeraCrc16();
	unsigned int getCrc16(char *buffer, unsigned int startPosition, unsigned int endPosition);
	~GeraCrc16();
};
