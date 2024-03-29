#pragma once
#ifndef MTOOLS_H
#define MTOOLS_H
#endif
#include <sys/types.h>
#include <string>
#include <fcntl.h>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
#ifdef linux
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#endif
#ifdef windows
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#endif

namespace Base
{
class TransTools
{
public:
	static unsigned char *MatToByte(cv::Mat imFrame,
									unsigned char *&imData,
									int &imRows,
									int &imCols,
									int &imSize,
									int &imTrueSize,
									int &imType);

	static cv::Mat ByteToMat(unsigned char *imByte,
							 int imRows,
							 int imCols,
							 int imType);

	static unsigned char *StringToByte(std::string strData);
	static std::string ByteToString(unsigned char *byteData);
};

class Matcom
{
public:
	static int ConvertSaveImg(std::string imName, cv::Mat imageData);
	static cv::Mat ImageGet(std::string imdataName);
};

class ConfigSetter
{
public:
	static bool CreateConfig(std::string fileName, std::string data);
	static bool ReadConfig(std::string fileName, std::string &data);
};

class Socket
{
public:
	Socket();
	~Socket();
	bool Create();
	bool Bind(int port);
	bool Bind(std::string ipAddr, int port);
	bool Listen(int maxConnections);
	bool Accept(Socket &SocketSub);
	bool Connect(std::string host, int port);
	void SocketServer(Socket &socketSub, int localPort, int maxConnection);
	void SocketClient(std::string IPAddress, int localPort, int remotePort);

#ifdef windows
	template <class _Tp>
	bool Send(_Tp *data, int sendSize)
	{
		int status = send(socketSet, data, sendSize, 0);
		if (status == -1)
		{
			std::cout << "\033[31m[SocketInfo]Send data failed ! status code -1\033[0m\n";
			return false;
		}
		else
		{
			std::cout << "\033[32m[SocketInfo]data has been send\033[0m\n";
			return true;
		}
	}

	template <class _Tp>
	bool Recv(_Tp *&data,const int recvSize)
	{
		_Tp buffer[recvSize];
		memset(buffer, 0, recvSize + 1);
		int status = recv(socketSet, buffer, recvSize, MSG_WAITALL);
		if (status == -1)
		{
			std::cout << "\033[31m[SocketInfo]Recving failed ! or recvSize error? status code is -1\033[0m\n";
			return false;
		}
		else if (status == 0)
		{
			std::cout << "\033[31m[SocketInfo]Recving failed ! or recvSize error?status code is 0\033[0m\n";
			return false;
		}
		else
		{
			data = buffer;
			std::cout << "\033[32m[SocketInfo]data recving! status code is ";
			std::cout << status;
			std::cout << "\033[0m\n";
			return true;
		}
	}
#endif

#ifdef linux
	template <class _Tp>
	bool Send(_Tp *data, int sendSize)
	{
		int status = send(m_sock, data, sendSize, 0);
		if (status == -1)
		{
			std::cout << "\033[31m[SocketInfo]Send data failed ! status code -1\033[0m\n";
			return false;
		}
		else
		{
			std::cout << "\033[32m[SocketInfo]data has been send\033[0m\n";
			return true;
		}
	}

	template <class _Tp>
	bool Recv(_Tp *&data, int recvSize)
	{
		_Tp buffer[recvSize + 1];
		memset(buffer, 0, recvSize + 1);
		int status = recv(m_sock, buffer, recvSize, MSG_WAITALL);
		if (status == -1)
		{
			std::cout << "\033[31m[SocketInfo]Recving failed ! or recvSize error? status code is -1\033[0m\n";
			return false;
		}
		else if (status == 0)
		{
			std::cout << "\033[31m[SocketInfo]Recving failed ! or recvSize error?status code is 0\033[0m\n";
			return false;
		}
		else
		{
			data = buffer;
			std::cout << "\033[32m[SocketInfo]data recving! status code is ";
			std::cout << status;
			std::cout << "\033[0m\n";
			return true;
		}
	}
#endif

private:
#ifdef windows
	SOCKET socketSet;
	SOCKADDR_IN addr;
	bool Is_valid() const { return socketSet != INVALID_SOCKET; }
#endif

#ifdef linux
	int m_sock;
	sockaddr_in m_addr;
	bool Is_valid() const { return m_sock != -1; }
#endif
};
} // namespace Base
