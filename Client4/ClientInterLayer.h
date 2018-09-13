#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include < Windows.h >

using namespace std;

enum class c {stopped, logged, connected, avalible};
enum class a {a_private, a_protected, a_public};

class ClientInterLayer
{
#pragma region Атрибуты
private:
	c status;
	string IP = "127.0.0.1";
	int name;
	vector<string> files = {};
	vector<string> users = {};
	list <string> log;
	string puth = "D:\\Client";
	char buff[4096];
	SOCKET sock;
	sockaddr_in dest_addr;
	const u_short port = 665;
	//HOSTENT *hst;
	HANDLE hMutex_Log;
	HANDLE hMutex_Users_Files;

public:
	bool isOutDated_UploadUsers = false;
	bool isOutDated_DownloadFiles = false;

#pragma endregion

#pragma region Get- и set- методы
private:

public:
	ClientInterLayer();
	c Status();
	int	 getName();
	bool isLogged();
	bool isConnected();
	bool isAvalible();
	vector<string> getFiles();
	vector<string> getUsers();
	void pushLog(string message);
	string popLog();
	bool Log_isEmpty();

#pragma endregion

#pragma region Логика работы клиента
private:
	
	
public:
	bool Login(string IP);
	bool Logout();
	bool Connect();
	bool Disconnect();
	bool Update();
	int send_buff();
	int receive();
	bool UploadFile(string puth_name, a type_access, vector<string> users = {});
	bool DownloadFile(string name, string puth);
	void Exit();

#pragma endregion

};