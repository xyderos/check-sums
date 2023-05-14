#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "crc.h"

#define POLY 0x1021 // 0001 0000 0010 0001
// The poly is 16 bit long instead of 17, because the result of the first bit
// after xor is always zero That's equivalent to check the first bit is one then
// move left one bit and xor the next 16 bits.

int
crc_16(const char *const src, const char *const dst)
{
	unsigned short crc = 0xffff, ch[1];
	long xor_flag = 0, fdr = 0, fdw = 0, count = 0;

	if ((fdr = open(src, O_RDONLY)) == -1) {
		return 1;
	}
	if ((fdw = open(dst, O_WRONLY | O_CREAT,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
		return 1;
	}

	while ((count = read((int)fdr, ch, 1)) != -1 && count != 0) {
		unsigned short v = 0x80;
		for (size_t j = 0; j < 8; j++) {
			if (crc & 0x8000)
				xor_flag = 1;
			else
				xor_flag = 0;

			crc = crc << 1;

			if (ch[0] & v) {
				crc += 1;
			}

			if (xor_flag) {
				crc = crc ^ POLY;
			}

			v = v >> 1;
		}
	}

	for (size_t j = 0; j < 16; j++) {
		if (crc & 0x8000) {
			xor_flag = 1;
		}

		else {
			xor_flag = 0;
		}

		crc = crc << 1;

		if (xor_flag) {
			crc = crc ^ POLY;
		}
	}

	if (write((int)fdw, &crc, 2) == -1) {
		return 1;
	}
	close((int)fdr);
	close((int)fdw);

	return 0;
}
