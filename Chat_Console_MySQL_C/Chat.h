#pragma once
//#include<vector>
#include"Func.h"
#include<cassert>
#include"Network.h"

class Chat
{	
public:
	Chat();
	~Chat();

	void ReadFiles();
	void WriteFiles();
	std::string signUp(int connection);
	std::string entrance(int connection);
	void abonentList(int connection, const std::string &login_from);
	bool correctInputAbonent(int connection, const std::string& login_to);
	void messageInputAll(int connection);
	void messageInputFromTo(int connection, const std::string& login_from);
	void messageReadPersonal(int connection, const std::string& login_from);
	void messageReadAll(int connection);
	void messageWriteRead(int connection, const std::string& login_from);
	
};