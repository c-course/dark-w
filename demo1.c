#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

int main()
{
	int i = 0;
	int o = 0;
	const char *in = "../in.txt";
	const char *out = "../out.txt";

	i = open(in, O_RDONLY);
	if (i < 0) {
		perror(in);
		exit(1);
	}
	o = open(out, O_WRONLY | O_CREAT, S_IRWXU);
	if (o < 0) {
		perror(out);
		exit(1);
	}

	char buffer[128];
	while (read(i, buffer, 1) > 0)
		write(o, buffer, 1);

	close(i);
	close(o);
	return 0;
}