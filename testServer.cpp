#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
	//hardcoded config
	const char* host = "127.0.0.1";
    const int port = 8080;
    const int maxConnections = 100;

	//create socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == 0) {
		std::cout << "failed to create the socket" << std::endl;
		exit (1);
	}
	std::cout << "socket created" << std::endl;

	//defining server address	
	sockaddr_in serverAdrs;
	serverAdrs.sin_family = AF_INET;
	serverAdrs.sin_port = htons(port);
	serverAdrs.sin_addr.s_addr = INADDR_ANY;

	//bind determines where the server will be accessible for the client
	bind(socket_fd, (struct sockaddr*)&serverAdrs, sizeof(serverAdrs));

	std::cout << "Port : " << serverAdrs.sin_port << " and server: " << serverAdrs.sin_addr.s_addr << " binded." << std::endl;

	listen(socket_fd, maxConnections);

	std::cout << "Server listening on: " << serverAdrs.sin_family << std::endl;

	int clientSocket = accept(socket_fd, nullptr, nullptr);

	std::cout << "client socket accecpted: " << clientSocket << std::endl;

	char buffer[1024] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);
	std::cout << "Message from client: " << buffer << std::endl;
}