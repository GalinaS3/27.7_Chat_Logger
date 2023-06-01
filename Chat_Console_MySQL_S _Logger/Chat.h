#pragma once
#include<cassert>
#include"Network.h"
#include"Data.h"

class Chat
{
	Data _data;
		
public:
	Chat();
	~Chat();
	void connectMySQL();
	void disconnectMySQL();
	std::string signUp(int connection);
	std::string entrance(int connection);
	void abonentList(int connection, const std::string &login_from);
	bool correctInputAbonent(int connection, const std::string& login_to);
	void messageInputAll(int connection, const std::string& login_from);
	void messageInputFromTo(int connection, const std::string& login_from);
	void messageReadPersonal(int connection, const std::string& login_from);
	void messageReadAll(int connection);
	void messageWriteRead(int connection, const std::string& login_from);
	
};