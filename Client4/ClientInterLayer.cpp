#include "ClientInterLayer.h"
#pragma comment( lib, "ws2_32.lib" )

ClientInterLayer::ClientInterLayer()
{
	status = c::stopped;
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
		Exit();//error, может вылететь! (закроет не открытое)
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
		Exit();//error, может вылететь!
	dest_addr.sin_family = AF_INET;
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

#pragma region Ћогика работы клиента
bool ClientInterLayer::Login(string new_IP)
{
	IP = new_IP;
	dest_addr.sin_port = htons(port);
	if (inet_addr(IP.c_str()) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	else
		Exit();

	if (connect(client_socket, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		//не могу подключитьс€
		return false;
	}
	else
	{
		//получить логин - name


		/**/name = rand();
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
	//—ервер - Logout
	name = 0;
	Disconnect();
	status = c::stopped;
	return true;
}

bool ClientInterLayer::Connect()
{
	if (connect(client_socket, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		//не могу подключитьс€
		return false;
	}
	//отправить ему свое им€ и получить подтверждение

	status = c::avalible;
	return true;
}

bool ClientInterLayer::Disconnect()
{
	//—ервер - Pause
	status = c::logged;
	return true;
}

void ClientInterLayer::Exit()
{
	closesocket(client_socket);
	WSACleanup();
	exit(0);
}
#pragma endregion