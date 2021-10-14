#include "e-commerceTradingPlatformClient.h"

#ifdef _WIN32
static void socket_init(void) {
	WORD wVersionRequested;
	WSADATA WSAData;
	int status;
	wVersionRequested = MAKEWORD(1,1);
	status = WSAStartup(wVersionRequested, &WSAData);
	if (status != 0) {
		printf("Windows Socket DLL ret\n");
		exit(0);
	}
}
#endif

int Client::socketInit() {
    socket_init();
    // socket
    Client::client = socket(AF_INET, SOCK_STREAM, 0);
    if (Client::client == -1) {
        std::cout << "Error: socket" << std::endl;
        return ERROR1;
    }
    // connect
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(Client::client, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cout << "Error: connect" << std::endl;
        return ERROR1;
    }
    std::cout << "...connect" << std::endl;
    return SUCCESS;
}

int Client::read(std::string &string) {
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	std::string strin;
	int len = recv(Client::client, buf, sizeof(buf), 0);
	buf[len] = '\0';
	string = std::string(buf);
	return SUCCESS;
}

int Client::write(std::string &string) {
	char buf[BUFSIZE];
	int len = string.copy(buf, BUFSIZE);
	buf[len] = '\0';
    send(Client::client, buf, len, 0);
	return SUCCESS;
}

int Client::client;

int main(int argc, char* argv[]) {
	std::cout << "Welcome to transaction system client" << std::endl;
    int client;
    if (Client::socketInit() == ERROR1) {
        return 0;
    }
    char data[BUFSIZE];
    while (true) {
        std::string string;
        Client::read(string);
        std::cout << string << std::endl;

        std::cin >> data;
        string = std::string(data);
        Client::write(string);
        if (string == "exit") {
            std::cout << "...disconnect" << std::endl;
            break;
        }
    }
    close(client);
	return 0;
}

// lin: g++ e-commerceTradingPlatformClient.cpp -o client -g
// win: g++ e-commerceTradingPlatformClient.cpp -o client -g -lws2_32
