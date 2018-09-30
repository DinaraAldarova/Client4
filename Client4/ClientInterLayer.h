#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <cstdio>
#include <fstream>
#include < Windows.h >

using namespace std;

#define size_buff 4096
#define size_block 10

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
	char buff[size_buff];
	//char check[size_block];
	//long start_block = 0;
	long pos = 0;
	bool pause_load = false;
	SOCKET sock;
	sockaddr_in dest_addr;
	const u_short port = 665;
	//HOSTENT *hst;
	HANDLE hMutex_Log;
	HANDLE hMutex_Users_Files;
	CRITICAL_SECTION cs_buf;

public:
	bool isOutDated_UploadUsers = false;
	bool isOutDated_DownloadFiles = false;

#pragma endregion

#pragma region Get- и set- методы
private:
	//bool clean_check();

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
	long getPos();

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