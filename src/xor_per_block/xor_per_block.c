#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "xor_per_block.h"

int
xor_per_block(const char *const src, const char *const dst)
{
	unsigned char xor = 0;
	int fdr, fdw;
	char buff[1] = "";
	ssize_t count = 0;

	if ((fdr = open(src, O_RDONLY)) == -1) {
		return 1;
	}

	if ((fdw = open(dst, O_WRONLY | O_CREAT,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
		return 1;
	}

	while ((count = read(fdr, buff, 1)) != -1 && count != 0) {
		for (ssize_t i = 0; i < count; i++) {
			xor ^= buff[i];
		}

		if (write(fdw, &xor, 1) == -1) {
			return 1;
		}
	}

	close(fdr);
	close(fdw);

	return 0;
}
