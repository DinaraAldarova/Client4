#include "ClientInterLayer.h"
#pragma comment( lib, "ws2_32.lib" )

ClientInterLayer::ClientInterLayer()
{
	status = c::stopped;
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
		Exit();//error, может вылететь! (закроет не открытое)
	hMutex_Log = CreateMutex(NULL, false, NULL);
	InitializeCriticalSection(&cs_buf);
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
}

#pragma region get- и set-методы
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

#pragma region Логика работы клиента
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
		//не могу подключиться
		return false;
	}
	else
	{
		strcpy(buff, "new");
		send_buff();
		//получить логин - name
		if (receive()) return false;
		name = atoi(buff);
		if (name == 0)
			pushLog("Сервер прислал ошибочное имя");/*сервер отправил что-то другое*/

		//загрузить files, users
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
			//Сервер - Logout
			strcpy(buff, "logout");
			send_buff();
		}
	}
	else if (status == c::avalible)
	{
		//Сервер - Logout
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
		Exit();//error, может вылететь!

	if (connect(sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		//не могу подключиться
		return false;
	}
	//отправить ему свое имя и получить подтверждение
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
		//что-то другое
		return false;
}

bool ClientInterLayer::Disconnect()
{
	//Сервер - Pause
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
	int i = send(sock, &buff[0], strlen(buff) + 1, 0);	//отправил команду
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
		//ошибка сокета
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
	if (file == NULL) { pushLog("Ошибка! Файл не найден. Отправка невозможна"); ReleaseMutex(hMutex_Users_Files); return false; }
	strcpy(buff, "upload|");
	string puth, name;
	int i = puth_name.length() - 1;
	while (puth_name[i] != '\\' && i > 0)
		i--;
	if (i == 0) { pushLog("Ошибочный путь к файлу! Отправка невозможна"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
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
	if (receive()) { pushLog("Ошибка сокета, загрузка прервана"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
	if (strcmp(buff, "ready") != 0) { pushLog("Файл невозможно загрузить: сервер ответил отрицательно"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
	//а теперь самое важное - отправка файла
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
		if (receive()) { pushLog("Ошибка сокета, загрузка прервана"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
		if (strcmp(buff, "ok")) { pushLog("Нельзя продолжить загрузку: сервер ответил отрицательно"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }

		//вычислить контрольную сумму, пока просто pause/next
		//добавить pause

		strcpy(buff, "next");
		send_buff();
		if (receive()) { pushLog("Ошибка сокета, загрузка прервана"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false; }
		if (!strcmp(buff, "next"))
			pos += sizeof(buff);//загружаем следующий блок
		else if (!strcmp(buff, "repeat"))
			fseek(file, pos, SEEK_SET); //повторяем загрузку этого блока
		else
		{
			pushLog("Нельзя продолжить загрузку: сервер ответил отрицательно"); fclose(file); ReleaseMutex(hMutex_Users_Files); return false;
		}
	}
	fclose(file);
	strcpy(buff, "end");
	send_buff();
	if (receive()) { pushLog("Ошибка сокета после загрузки файла"); ReleaseMutex(hMutex_Users_Files); return false; }
	if (!strcmp(buff, "end"))
		//что-то не то
	{
		pushLog("Файл загружен");
		ReleaseMutex(hMutex_Users_Files);
		return true;
	}
	else
	{
		pushLog("Сервер прислал ошибочные данные уже после загрузки файла");
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

	//а теперь будем этот файл скачивать
	//если сервер прислал ок, то
	ofstream file(puth + name);
	if (!file.is_open()) { pushLog("Ошибка! Файл невозможно создать. Скачивание невозможно"); return false; }


	ReleaseMutex(hMutex_Users_Files);
}

void ClientInterLayer::Exit()
{
	Logout();
	WSACleanup();
	exit(0);
}
#pragma endregion