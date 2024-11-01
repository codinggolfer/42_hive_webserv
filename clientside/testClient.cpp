#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


int main() {
	//client socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	//server config and port
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	//connect to server
	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connect failed");
        return 1;
    }
	std::cout	<< " port: "
				<< serverAddress.sin_port
				<< " s_addr: " << serverAddress.sin_addr.s_addr << std::endl;
	//massage server
	std::string line;
	while (true)
	{
		char buffer[1024] = {0};
		std::cout << "Enter message: ";
		std::getline(std::cin, line);
		if (std::cin.eof()) {
			if (send(clientSocket, nullptr, 1, 0) < 0) {
			std::cout << "failed to send the message" << std::endl;
			break ;
		}
		}
		//std::cout << line.c_str() << std::endl;
		if (send(clientSocket, line.c_str(), line.size(), 0) < 0) {
			std::cout << "failed to send the message" << std::endl;
		}
		recv(clientSocket, buffer, sizeof(buffer), 0);
		system(buffer);
	}
	close (clientSocket);
	return 0;
}