#include "ClientInterLayer.h"
#pragma comment( lib, "ws2_32.lib" )

ClientInterLayer::ClientInterLayer()
{
	status = c::stopped;
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
		Exit();//error, может вылететь! (закроет не открытое)
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		Exit();//error, может вылететь!
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
}

#pragma region get- и set-методы
c ClientInterLayer::Status()
{
	return status;
}

int ClientInterLayer::getName()
{
	return name;
}

bool ClientInterLayer::isLogged()
{
	if (status >= c::logged)
		return true;
	else
		return false;
}

bool ClientInterLayer::isConnected()
{
	if (status >= c::connected)
		return true;
	else
		return false;
}

bool ClientInterLayer::isAvalible()
{
	if (status == c::avalible)
		return true;
	else
		return false;
}

list<string> ClientInterLayer::getFiles()
{
	return files;
}

list<string> ClientInterLayer::getUsers()
{
	return users;
}

#pragma endregion

#pragma region Логика работы клиента
bool ClientInterLayer::Login(string new_IP)
{
	IP = new_IP;
	if (inet_addr(IP.c_str()) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	else
		Exit();

	if (connect(sock, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
	{
		//не могу подключиться
		return false;
	}
	else
	{
		//получить логин - name
		if (recv(sock, &buff[0], sizeof(buff), 0) == SOCKET_ERROR)
		{
			;//ошибка сокета
		}
		else
		{
			name = atoi(buff);
			if (name == 0)
				;/*сервер отправил что-то другое*/
		}
		//загрузить files, users
		status = c::avalible;
		//		return true;
	}
	return true;
}

bool ClientInterLayer::Logout()
{
	if (status == c::logged)
	{
		Connect();
	}
	//Сервер - Logout
	name = 0;
	Disconnect();
	closesocket(sock);
	status = c::stopped;
	return true;
}

bool ClientInterLayer::Connect()
{
	if (connect(sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		//не могу подключиться
		return false;
	}
	//отправить ему свое имя и получить подтверждение

	status = c::avalible;
	return true;
}

bool ClientInterLayer::Disconnect()
{
	//Сервер - Pause
	status = c::logged;
	return true;
}

void ClientInterLayer::Exit()
{
	if (sock >= 0)
		closesocket(sock);
	WSACleanup();
	exit(0);
}
#pragma endregion