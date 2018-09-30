#include "ClientInterLayer.h"
#pragma comment( lib, "ws2_32.lib" )

ClientInterLayer::ClientInterLayer()
{
	status = c::stopped;
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
		Exit();//error, ����� ��������! (������� �� ��������)
	hMutex_Log = CreateMutex(NULL, false, NULL);
	InitializeCriticalSection(&cs_buf);
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
}

#pragma region get- � set-������
/*bool ClientInterLayer::clean_check()
{
	for (int i = 0; i < size_block; i++)
		check[i] = '-';
}*/

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

vector<string> ClientInterLayer::getFiles()
{
	return files;
}

vector<string> ClientInterLayer::getUsers()
{
	return users;
}

void ClientInterLayer::pushLog(string message)
{
	WaitForSingleObject(hMutex_Log, INFINITE);
	this->log.push_back(message+"\n");
	ReleaseMutex(hMutex_Log);
}

string ClientInterLayer::popLog()
{
	WaitForSingleObject(hMutex_Log, INFINITE);
	string s = this->log.front();
	this->log.pop_front();
	ReleaseMutex(hMutex_Log);
	return s;
}

bool ClientInterLayer::Log_isEmpty()
{
	return this->log.empty();
}

long ClientInterLayer::getPos()
{
	return pos;
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
			pushLog("������ ������� ��������� ���");/*������ �������� ���-�� ������*/

		//��������� files, users
		if (!Update()) return false;

		status = c::avalible;
		return true;
	}
}

bool ClientInterLayer::Logout()
{
	if (status == c::logged)
	{
		if (Connect())
		{
			//������ - Logout
			strcpy(buff, "logout");
			send_buff();
		}
	}
	else if (status == c::avalible)
	{
		//������ - Logout
		strcpy(buff, "logout");
		send_buff();
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
	isOutDated_DownloadFiles = true;
	isOutDated_UploadUsers = true;
	return true;
}

int ClientInterLayer::send_buff()
{
	EnterCriticalSection(&cs_buf);
	int i = send(sock, &buff[0], strlen(buff) + 1, 0);	//�������� �������
	LeaveCriticalSection(&cs_buf);
	return i;
}

int ClientInterLayer::receive()
{
	EnterCriticalSection(&cs_buf);
	int res = recv(sock, &buff[0], sizeof(buff), 0);
	if (res == SOCKET_ERROR)
	{
		LeaveCriticalSection(&cs_buf);
		//������ ������
		closesocket(sock);
		status = c::logged;
		return 1;
	}
	LeaveCriticalSection(&cs_buf);
	return 0;
}

bool ClientInterLayer::UploadFile(string puth_name, a type_access, vector<string> users)
{
	WaitForSingleObject(hMutex_Users_Files, INFINITE);
	FILE * file;
	file = fopen(puth_name.c_str(), "rb+");
	if (file == NULL) { pushLog("������! ���� �� ������. �������� ����������"); ReleaseMutex(hMutex_Users_Files); return false; }
	strcpy(buff, "upload|");
	string puth, name;
	int i = puth_name.length() - 1;
	while (puth_name[i] != '\\' && i > 0)
		i--;
	if (i == 0) { pushLog("��������� ���� � �����! �������� ����������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
	puth = puth_name.substr(0, i + 1);
	name = puth_name.substr(i + 1);
	strcat(buff, name.c_str());
	strcat(buff, "|");
	if (type_access == a::a_private)
		strcat(buff, "private|*");
	else if (type_access == a::a_public)
		strcat(buff, "public|*");
	else
	{
		strcat(buff, "protected|");
		for each (string user in users)
		{
			strcat(buff, user.c_str());
			strcat(buff, "|");
		}
		strcat(buff, "*");
	}
	send_buff();
	if (receive()) { pushLog("������ ������, �������� ��������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
	if (strcmp(buff, "ready") != 0) { pushLog("���� ���������� ���������: ������ ������� ������������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
	//� ������ ����� ������ - �������� �����
	fseek(file, 0, SEEK_END);
	long size_file = ftell(file);
	fseek(file, 0, SEEK_SET);

	itoa(size_file, buff, 10);
	send_buff();
	//start_block = 0;
	//clean_check();
	for (long pos = 0; pos < size_file; )
	{
		fread(&buff, sizeof(buff), 1, file);
		send_buff();
		if (receive()) { pushLog("������ ������, �������� ��������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
		if (strcmp(buff, "ok")) { pushLog("������ ���������� ��������: ������ ������� ������������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }

		//��������� ����������� �����, ���� ������ pause/next
		//�������� pause

		strcpy(buff, "next");
		send_buff();
		if (receive()) { pushLog("������ ������, �������� ��������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
		if (!strcmp(buff, "next"))
			pos += sizeof(buff);//��������� ��������� ����
		else if (!strcmp(buff, "repeat"))
			fseek(file, pos, SEEK_SET); //��������� �������� ����� �����
		else
		{
			pushLog("������ ���������� ��������: ������ ������� ������������"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false;
		}
	}
	fclose(file);
	strcpy(buff, "end");
	send_buff();
	if (receive()) { pushLog("������ ������ ����� �������� �����"); ReleaseMutex(hMutex_Users_Files); return false; }
	if (!strcmp(buff, "end"))
		//���-�� �� ��
	{
		pushLog("���� ��������");
		ReleaseMutex(hMutex_Users_Files);
		return true;
	}
	else
	{
		pushLog("������ ������� ��������� ������ ��� ����� �������� �����");
		ReleaseMutex(hMutex_Users_Files);
		return false;
	}
}

bool ClientInterLayer::DownloadFile(string name, string puth)
{
	WaitForSingleObject(hMutex_Users_Files, INFINITE);
	strcpy(buff, "download|");
	strcat(buff, name.c_str());
	strcat(buff, "*");
	send_buff();

	//� ������ ����� ���� ���� ���������
	//���� ������ ������� ��, ��
	ofstream file(puth + name);
	if (!file.is_open()) { pushLog("������! ���� ���������� �������. ���������� ����������"); return false; }


	ReleaseMutex(hMutex_Users_Files);
}

void ClientInterLayer::Exit()
{
	Logout();
	WSACleanup();
	exit(0);
}
#pragma endregion