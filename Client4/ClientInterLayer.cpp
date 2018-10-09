#include "ClientInterLayer.h"
#pragma comment( lib, "ws2_32.lib" )

ClientInterLayer * client;

ClientInterLayer::ClientInterLayer()
{
	status = c::stopped;
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
		Exit();//error, может вылететь! (закроет не открытое)
	hMutex_Log = CreateMutex(NULL, false, NULL);
	hMutex_Users_Files = CreateMutex(NULL, false, NULL);
	InitializeCriticalSection(&cs_buf);
	InitializeCriticalSection(&cs_pos);
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
	this->log.push_back(message + "\n");
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

long ClientInterLayer::getPercent()
{
	EnterCriticalSection(&cs_pos);
	long percent = pos / file_size;
	LeaveCriticalSection(&cs_pos);
	return percent;
}

void ClientInterLayer::setPauseLoad()
{
	pause_load = true;
}

bool ClientInterLayer::isEndLoad()
{
	return end_load;
}

void ClientInterLayer::setEndLoad()
{
	end_load = true;
}
#pragma endregion

//#pragma region Логика работы клиента
DWORD WINAPI UploadFileThread(LPVOID param);
DWORD WINAPI DownloadFileThread(LPVOID param);

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
		if (!receive()) return false;
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

	if (!receive()) return false;
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

	if (!receive()) return false;
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
		if (!receive()) return false;
	}

	if (!receive()) return false;
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
		if (!receive()) return false;
	}
	isOutDated_DownloadFiles = true;
	isOutDated_UploadUsers = true;
	return true;
}

int ClientInterLayer::send_buff(int i)
{
	EnterCriticalSection(&cs_buf);
	int res = send(sock, &buff[0], i /*strlen(buff) + 1*/, 0);	//отправил команду
	LeaveCriticalSection(&cs_buf);
	return res;
}

int ClientInterLayer::receive()
{
	EnterCriticalSection(&cs_buf);
	for (int i = 0; i < size_buff; i++)
		buff[i] = '/0';
	int res = recv(sock, &buff[0], sizeof(buff), 0);
	if (res == SOCKET_ERROR || res == 0)
	{
		LeaveCriticalSection(&cs_buf);
		//ошибка сокета
		closesocket(sock);
		status = c::logged;
		return 0;
	}
	LeaveCriticalSection(&cs_buf);
	return res;
}

void ClientInterLayer::UploadFile(string puth_name, a type_access, vector<string> users)
{
	client = this;
	client->puth_name = puth_name;
	client->type_access = type_access;
	client->users_access = users;
	DWORD thID;
	CreateThread(NULL, NULL, UploadFileThread, NULL, NULL, &thID);
}

DWORD WINAPI UploadFileThread(LPVOID param)
{
	WaitForSingleObject(client->hMutex_Users_Files, INFINITE);
	EnterCriticalSection(&client->cs_pos);
	client->end_load = false;
	client->pause_load = false;
	client->pos = 0;
	client->file_size = 1;
	LeaveCriticalSection(&client->cs_pos);
	FILE * file;
	file = fopen(client->puth_name.c_str(), "rb+");
	if (file == NULL) { client->pushLog("Ошибка! Файл не найден. Отправка невозможна"); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
	strcpy(client->buff, "upload|");
	string puth, name;
	int i = client->puth_name.length() - 1;
	while (client->puth_name[i] != '\\' && i > 0)
		i--;
	if (i == 0) { client->pushLog("Ошибочный путь к файлу! Отправка невозможна"); fclose(file); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
	puth = client->puth_name.substr(0, i + 1);
	name = client->puth_name.substr(i + 1);
	strcat(client->buff, name.c_str());
	strcat(client->buff, "|");
	if (client->type_access == a::a_private)
		strcat(client->buff, "private|*");
	else if (client->type_access == a::a_public)
		strcat(client->buff, "public|*");
	else
	{
		strcat(client->buff, "protected|");
		for each (string user in client->users_access)
		{
			strcat(client->buff, user.c_str());
			strcat(client->buff, "|");
		}
		strcat(client->buff, "*");
	}
	client->send_buff();
	if (!client->receive()) { client->pushLog("Ошибка сокета, загрузка прервана"); fclose(file); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
	if (strcmp(client->buff, "ready") != 0) { client->pushLog("Файл невозможно загрузить: сервер ответил отрицательно"); fclose(file); strcpy(client->buff, "error"); client->send_buff(); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }

	//а теперь самое важное - отправка файла
	EnterCriticalSection(&client->cs_pos);
	fseek(file, 0, SEEK_END);
	client->file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	itoa(client->file_size, client->buff, 10);
	client->send_buff();
	client->pos = 0;

	//start_block = 0;
	//clean_check();
	for (; client->pos < client->file_size; )
	{
		LeaveCriticalSection(&client->cs_pos);
		for (int i = 0; i < size_buff; i++)
			client->buff[i] = '\0';
		fread(&client->buff, sizeof(client->buff), 1, file);
		if (client->pos + size_buff > client->file_size)
		{
			client->send_buff(client->file_size - client->pos);
		}
		else
		{
			client->send_buff();
		}
		if (!client->receive()) { client->pushLog("Ошибка сокета, загрузка прервана"); fclose(file); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
		if (strcmp(client->buff, "ok")) { client->pushLog("Нельзя продолжить загрузку: сервер ответил отрицательно"); fclose(file); client->end_load = true; strcpy(client->buff, "error"); client->send_buff(); ReleaseMutex(client->hMutex_Users_Files); return false; }

		//вычислить контрольную сумму, пока просто pause/next
		//добавить pause

		strcpy(client->buff, "next");
		client->send_buff();
		if (!client->receive()) { client->pushLog("Ошибка сокета, загрузка прервана"); fclose(file); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }

		//Сервер « файл « Клиент
		//получил « файл « прочитал
		//посчитал » контроль » получил
		//записал « подтвердил « сравнил
		//отправил » подтвердил » сдвинул

		EnterCriticalSection(&client->cs_pos);
		if (!strcmp(client->buff, "next"))
		{
			if (client->pos + size_buff > client->file_size)
			{
				client->pos += client->file_size - client->pos;//загружаем следующий блок
			}
			else
			{
				client->pos += sizeof(client->buff);//загружаем следующий блок
			}
		}
		else if (!strcmp(client->buff, "repeat"))
			fseek(file, client->pos, SEEK_SET); //повторяем загрузку этого блока
		else
		{
			client->pushLog("Нельзя продолжить загрузку: сервер ответил отрицательно"); fclose(file); client->end_load = true; strcpy(client->buff, "error"); client->send_buff(); LeaveCriticalSection(&client->cs_pos); ReleaseMutex(client->hMutex_Users_Files); return false;
		}
	}
	client->end_load = true;
	LeaveCriticalSection(&client->cs_pos);

	fclose(file);
	strcpy(client->buff, "end");
	client->send_buff();
	if (!client->receive()) { client->pushLog("Ошибка сокета после загрузки файла"); ReleaseMutex(client->hMutex_Users_Files); return false; }
	if (!strcmp(client->buff, "end"))
	{
		client->pushLog("Файл загружен");
		ReleaseMutex(client->hMutex_Users_Files);
		return true;
	}
	else
	{
		client->pushLog("Сервер прислал ошибочные данные уже после загрузки файла");
		ReleaseMutex(client->hMutex_Users_Files);
		return false;
	}
	return 0;
}

bool ClientInterLayer::DownloadFile(string name)
{
	client = this;
	client->file_name = name;
	DWORD thID;
	CreateThread(NULL, NULL, DownloadFileThread, NULL, NULL, &thID);
	return true;
}

DWORD WINAPI DownloadFileThread(LPVOID param)
{
	WaitForSingleObject(client->hMutex_Users_Files, INFINITE);
	EnterCriticalSection(&client->cs_pos);
	client->end_load = false;
	client->pause_load = false;
	client->pos = 0;
	client->file_size = 1;
	LeaveCriticalSection(&client->cs_pos);

	strcpy(client->buff, "download|");
	strcat(client->buff, client->file_name.c_str());
	strcat(client->buff, "|*");
	client->send_buff();

	if (!client->receive()) { client->pushLog("Ошибка сокета, скачивание прервано"); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
	if (strcmp(client->buff, "ready") != 0) { client->pushLog("Файл невозможно загрузить! Сервер ответил: "); client->pushLog(client->buff); client->end_load = true; strcpy(client->buff, "error"); client->send_buff(); ReleaseMutex(client->hMutex_Users_Files); return false; }

	client->puth_name = client->puth + client->file_name;

	FILE * file;
	file = fopen(client->puth_name.c_str(), "ab+");
	if (file == NULL) { client->pushLog("Ошибка! Файл невозможно открыть. Скачивание невозможно"); client->end_load = true; strcpy(client->buff, "error"); client->send_buff(); ReleaseMutex(client->hMutex_Users_Files); return false; }

	EnterCriticalSection(&client->cs_pos);
	fseek(file, 0, SEEK_END);
	client->pos = ftell(file);
	//fseek(file, 0, SEEK_SET);

	ltoa(client->pos, client->buff, 10);
	client->send_buff();

	if (!client->receive()) { client->pushLog("Ошибка сокета, загрузка прервана"); client->end_load = true; fclose(file); ReleaseMutex(client->hMutex_Users_Files); return false; }
	client->file_size = atol(client->buff);

	char buff_2[size_buff] = "";
	//start_block = 0;
	//clean_check();
	for (; client->pos < client->file_size; )
	{
		LeaveCriticalSection(&client->cs_pos);
		if (!client->receive()) { client->pushLog("Ошибка сокета, загрузка прервана"); fclose(file); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
		strcpy(buff_2, client->buff);
		
		//контрольная сумма
		strcpy(client->buff, "ok");
		client->send_buff();

		if (!client->receive()) { client->pushLog("Ошибка сокета, загрузка прервана"); fclose(file); client->end_load = true; ReleaseMutex(client->hMutex_Users_Files); return false; }
		
		//Сервер » файл » Клиент
		//прочитал » файл » получил
		//получил « контроль « посчитал
		//сравнил » подтвердил » записал
		//сдвинул « подтвердил « отправил
		
		EnterCriticalSection(&client->cs_pos);
		if (!strcmp(client->buff, "next"))
		{
			if (client->pos + size_buff > client->file_size)
			{
				//пишем последний блок
				fwrite(&buff_2, client->file_size - client->pos, 1, file);
				client->pos += client->file_size - client->pos;
			}
			else
			{
				//пишем следующий блок
				fwrite(&buff_2, sizeof(buff_2), 1, file);
				client->pos += size_buff;
			}
			strcpy(client->buff, "next");
			client->send_buff();
		}
		else if (!strcmp(client->buff, "repeat"))
		{
			//повторяем скачивание этого блока
			strcpy(client->buff, "repeat");
			client->send_buff();
		}
		else
		{
			client->pushLog("Нельзя продолжить скачивание: сервер ответил отрицательно"); fclose(file); client->end_load = true; strcpy(client->buff, "error"); client->send_buff(); LeaveCriticalSection(&client->cs_pos); ReleaseMutex(client->hMutex_Users_Files); return false;
		}
	}
	client->end_load = true;
	LeaveCriticalSection(&client->cs_pos);
	fclose(file);

	if (!client->receive()) { client->pushLog("Ошибка сокета после скачивания файла");  strcpy(client->buff, "error"); client->send_buff(); ReleaseMutex(client->hMutex_Users_Files); return false; }
	if (!strcmp(client->buff, "end"))
	{
		client->pushLog("Файл загружен");
		strcpy(client->buff, "end");
		client->send_buff();
		ReleaseMutex(client->hMutex_Users_Files);
		return true;
	}
	else
	{
		client->pushLog("Сервер прислал ошибочные данные уже после загрузки файла");
		strcpy(client->buff, "error");
		client->send_buff();
		ReleaseMutex(client->hMutex_Users_Files);
		return false;
	}
	return 0;
}

void ClientInterLayer::Exit()
{
	Logout();
	WSACleanup();
	exit(0);
}
//#pragma endregion