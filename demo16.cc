#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

#define BZERO(addr, size) memset(addr, 0, size)
#define MAX 128

int main(int argc, char **argv)
{
	int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in si;

	BZERO(&si, sizeof(si));
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = inet_addr("127.0.0.1");
	si.sin_port = htons(1234);

	bind(server_socket, (struct sockaddr *)&si, sizeof(si));
	listen(server_socket, 5);

	struct sockaddr_in client_addr;
	socklen_t client_addr_size = sizeof(client_addr);
	int client_sock = accept(server_socket, (struct sockaddr *)&client_addr,
							 &client_addr_size);

	// get file full-path
	char fn[MAX];
	BZERO(fn, MAX);
	recv(client_sock, fn, MAX, 0);
	char rootp[MAX];
	rootp[0] = '\0';
	strcat(strcat(rootp, argv[1]), fn);

	std::ifstream ifs(rootp, std::ios::binary);
	char buffer[MAX];
	ifs.read(buffer, MAX);
	int l = ifs.gcount();
	send(client_sock, buffer, l, 0);

	close(client_sock);
	close(server_socket);
	ifs.close();
	return 0;
}
