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
		return false;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		return false;

	if (connect(sock, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
	{
		//�� ���� ������������
		return false;
	}
	else
	{
		strcpy(buff, "new");
		send_buff();
		//�������� ����� - name
		if (receive()) return false;
		name = atoi(buff);
		if (name == 0)
			;/*������ �������� ���-�� ������*/

		//��������� files, users
		Update();

		status = c::avalible;
		return true;
	}
}

bool ClientInterLayer::Logout()
{
	if (status == c::logged)
	{
		if (!Connect())
		{
			//������ - Logout
			strcpy(buff, "logout");
			send_buff();
		}
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
	send_buff();

	if (receive()) return false;
	if (strcmp(buff, "done") == 0)
	{
		status = c::avalible;
		Update();
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
	send_buff();

	if (sock >= 0)
		closesocket(sock);
	status = c::logged;
	return true;
}

bool ClientInterLayer::Update()
{
	strcpy(buff, "update");
	send_buff();

	if (receive()) return false;
	files.clear();
	while (strcmp(buff, "done") != 0)
	{
		int i = 0;// , j = 0;
		while (buff[i] != '*')
		{
			string s = "";
			while (buff[i] != '|')
			{
				s += buff[i];
				i++;
			}
			files.push_back(s);
			i++;
		}
		if (receive()) return false;
	}

	if (receive()) return false;
	users.clear();
	while (strcmp(buff, "done") != 0)
	{
		int i = 0;// , j = 0;
		while (buff[i] != '*')
		{
			string s = "";
			while (buff[i] != '|')
			{
				s += buff[i];
				i++;
			}
			users.push_back(s);
			i++;
		}
		if (receive()) return false;
	}
	return true;
}

int ClientInterLayer::send_buff()
{
	return send(sock, &buff[0], strlen(buff) + 1, 0);	//�������� �������
}

int ClientInterLayer::receive()
{
	int res;
	if (res = recv(sock, &buff[0], sizeof(buff), 0) == SOCKET_ERROR)
	{
		//������ ������
		closesocket(sock);
		status = c::logged;
		return 1;
	}
	return 0;
}

void ClientInterLayer::Exit()
{
	Logout();
	WSACleanup();
	exit(0);
}
#pragma endregion