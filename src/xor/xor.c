#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "xor.h"

int xor (const char *const src, const char *const dst) {
	unsigned char xor = 0;
	int fdr = 0, fdw = 0;
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
		if (buff[0] != '\n')
			xor ^= (buff[0] - '0');
	}

	if (write(fdw, &xor, 1) == -1) {
		return 1;
	}

	close(fdr);
	close(fdw);

	return 0;
}
