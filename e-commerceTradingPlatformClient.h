#ifndef _ECOMMERCETRADINGPLATFORMCLIENT_H_
#define _ECOMMERCETRADINGPLATFORMCLIENT_H_

#ifdef _WIN32 /* for Windows Visual Studio */

#include <winsock2.h>
#include <io.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <ws2tcpip.h>
//#define getopt_long getopt_int
#define stricmp _stricmp
static void socket_init(void);
#pragma comment(lib,"wsock32.lib")

#else /* for Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define stricmp strcasecmp
#define socket_init()
#define WSAGetLastError() 0

#endif

#include <iostream>
#include <cstring>
#include <unistd.h>

#define ERROR1 1
#define SUCCESS 0
#define BUFSIZE 10240

class Client {
public:
    static int socketInit();
    static int read(std::string &string);
    static int write(std::string &string);
    static int client;
protected:
private:
};

#endif