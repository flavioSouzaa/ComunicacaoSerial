#include "GeraCrc16.h"

GeraCrc16::GeraCrc16() {
}

unsigned int GeraCrc16::getCrc16(char *buffer, unsigned int startPosition, unsigned int endPosition) {
	unsigned int crc = 0, temp = 0;

	for (unsigned int i = startPosition; i <= endPosition; i++) {
		temp = buffer[i];
		temp <<= 8;
		crc = crc ^ temp;

		for (unsigned int j = 0; j < 8; j++) {
			if ((crc & 0x8000) != 0) {
				crc <<= 1;
				crc = crc ^ 0x8005;
			}
			else
				crc <<= 1;

			crc = crc & 0xFFFF;
		}
	}
	return crc & 0xFFFF;
}

GeraCrc16::~GeraCrc16() {
}
