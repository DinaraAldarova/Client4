#pragma once
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include < Windows.h >

using namespace std;

enum class c {stopped, logged, connected, avalible};

class ClientInterLayer
{
#pragma region Атрибуты
private:
	c status;
	string IP = "127.0.0.1";
	int name;
	list<string> files = {};
	list<string> users = {};
	string puth = "D:\\Client";
	char buff[4096];
	SOCKET sock;
	sockaddr_in dest_addr;
	const u_short port = 665;
	//HOSTENT *hst;

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
	list<string> getFiles();
	list<string> getUsers();

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
	void Exit();

#pragma endregion

};