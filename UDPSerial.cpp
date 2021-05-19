#include "UDPSerial.h"


UDPSerial::UDPSerial()
{
	slen = sizeof(si_other);
	s = 0;
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);
	si_other.sin_addr.S_un.S_addr = inet_addr(server.c_str());
}

UDPSerial::~UDPSerial()
{
	closesocket(s);
	WSACleanup();
}

int UDPSerial::begin()
{
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		return 1;
	}

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		return 2;
	}
	return 0;
}

int UDPSerial::print(std::string msg)
{
	if (sendto(s, msg.c_str(), strlen(msg.c_str()), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		WSAGetLastError();
		return 1;
	}
}

int UDPSerial::write(char* msg)
{
	if (sendto(s, msg, strlen(msg), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		WSAGetLastError();
		return 1;
	}
}
