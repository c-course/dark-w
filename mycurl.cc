#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <libgen.h>

#define BZERO(addr, size) memset(addr, 0, size)
#define MAX 1024

int main(int argc, char **argv)
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in server_addr;
	BZERO(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(1234);

	connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	const char *fn = argv[1];
	send(sock, fn, strlen(fn) + 1, 0);

	char buffer[MAX];
	int l = recv(sock, buffer, MAX, 0);
	const char *ofs_n = basename(fn);
	std::ofstream ofs(ofs_n, std::ios::binary);
	ofs.write(buffer, l);

	close(sock);
	ofs.close();
	return 0;
}
