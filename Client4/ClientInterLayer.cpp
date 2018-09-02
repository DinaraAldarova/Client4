#include "ClientInterLayer.h"
#pragma comment( lib, "ws2_32.lib" )

ClientInterLayer::ClientInterLayer()
{
	status = c::stopped;
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
		Exit();//error, ����� ��������! (������� �� ��������)
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
}

#pragma region get- � set-������
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

#pragma region ������ ������ �������
bool ClientInterLayer::Login(string new_IP)
{
	IP = new_IP;
	if (inet_addr(IP.c_str()) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	else
		Exit();

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		Exit();//error, ����� ��������!

	if (connect(sock, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
	{
		//�� ���� ������������
		return false;
	}
	else
	{
		strcpy(buff, "new");
		send(sock, &buff[0], strlen(buff) + 1, 0);	//�������� �������
		//�������� ����� - name
		if (recv(sock, &buff[0], sizeof(buff), 0) == SOCKET_ERROR)
		{
			;//������ ������
		}
		else
		{
			name = atoi(buff);
			if (name == 0)
				;/*������ �������� ���-�� ������*/
		}
		//��������� files, users
		status = c::avalible;
		return true;
	}
}

bool ClientInterLayer::Logout()
{
	if (status == c::logged)
	{
		Connect();
		//������ - Logout
		strcpy(buff, "logout");
		send(sock, &buff[0], strlen(buff) + 1, 0);	//�������� �������
	}

	name = 0;
	if (sock >= 0)
		closesocket(sock);
	status = c::stopped;
	return true;
}

bool ClientInterLayer::Connect()
{
	if (inet_addr(IP.c_str()) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	else
		Exit();

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		Exit();//error, ����� ��������!

	if (connect(sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		//�� ���� ������������
		return false;
	}
	//��������� ��� ���� ��� � �������� �������������
	itoa(name, buff, 10);
	send(sock, &buff[0], strlen(buff) + 1, 0);	//�������� �������

	if (recv(sock, &buff[0], sizeof(buff), 0) == SOCKET_ERROR)
	{
		;//������ ������
	}
	else if (strcmp(buff, "done") == 0)
	{
		status = c::avalible;
		return true;
	}
	else
		//���-�� ������
		return false;
}

bool ClientInterLayer::Disconnect()
{
	//������ - Pause
	strcpy(buff, "pause");
	send(sock, &buff[0], strlen(buff) + 1, 0);	//�������� �������

	if (sock >= 0)
		closesocket(sock);
	status = c::logged;
	return true;
}

void ClientInterLayer::Exit()
{
	Logout();
	WSACleanup();
	exit(0);
}
#pragma endregion