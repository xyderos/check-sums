#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fletcher.h"

#define LIMIT 255

int
fletcher(char *const src, const char *const dst)
{
	int fdr = 0, fdw = 0, fletcher_a = 0, fletcher_b = 0;
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
		if (buff[0] != '\n') {
			fletcher_a = (buff[0] - '0' + fletcher_a) % LIMIT;
			fletcher_b = (fletcher_a + fletcher_b) % LIMIT;
		}
	}

	if (write(fdw, &fletcher_b, 4) == -1) {
		return 1;
	}

	close(fdr);
	close(fdw);
	return 0;
}
