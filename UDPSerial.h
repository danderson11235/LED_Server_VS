#pragma once

#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

class UDPSerial
{
public:
	UDPSerial();
	~UDPSerial();
	int begin();
	int print(std::string msg);
	int write(char* msg);

private:
	std::string server = "192.168.1.18";
	int bufflen = 512;
	int port = 4210;
	struct sockaddr_in si_other;
	int s, slen;
	WSADATA wsa;
};

