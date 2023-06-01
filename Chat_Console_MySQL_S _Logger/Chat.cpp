#include "Chat.h"

Chat::Chat() = default;
Chat::~Chat() = default;

void Chat::connectMySQL()
{
	_data.openData();
	_data.createDataTable();
}

void Chat::disconnectMySQL()
{
	_data.closeData();
}

std::string Chat::signUp(int connection)
{
	std::string name;
	std::string login;
	std::string password;

	Network netConnect;

	name = netConnect.reseiveMessage(connection);
	login = netConnect.reseiveMessage(connection);
	password = netConnect.reseiveMessage(connection);

	if (_data.insirtDataUser(name, login, password))
	{
		netConnect.sendMessage(connection, "Поздравляем, вы успешно зарегистрированы.");
		Logger logger;		
		std::thread l1 ([&logger, &login, &name] () {		
		logger.loggerWrite("Регистрация:  ");  //пишем в log.txt
		logger.loggerWrite(name);
		logger.loggerWrite(login);
		}); 
		if (l1.joinable())
			l1.join();
		return login;
	}
	else
	{
		netConnect.sendMessage(connection, "error");
		return "error";
	}
}

std::string Chat::entrance(int connection)
{
	Network netConnect;
	auto count = 0;
	std::string login = netConnect.reseiveMessage(connection);
	std::string password = netConnect.reseiveMessage(connection);

	if (_data.entranceDataUser(login, password))
	{
		netConnect.sendMessage(connection, "Вход выполнен успешно.");
		Logger logger;			
		std::thread l ([&logger, &login] () {		
		logger.loggerWrite("Вход:  ");  //пишем в log.txt
		logger.loggerWrite(login);
		}); 
		if(l.joinable())
			l.join();
		return login;
	}
	else
	{
		netConnect.sendMessage(connection, "Такого логина/пароля нет. Возможно, вы ещё не зарегистрированы.");
		return "error";
	}
}

void Chat::abonentList(int connection, const std::string &login_from)
{
	Network netConnect;
	std::string str;

	str = _data.readDataUsersLogin(login_from);
	netConnect.sendMessage(connection, str);
}

bool Chat::correctInputAbonent(int connection, const std::string &login_to)
{
	Network netConnect;
	if (_data.correctDataInputAbonent(login_to))
	{
		netConnect.sendMessage(connection, "true");
		return true;
	}
	else
	{
		netConnect.sendMessage(connection, "false");
		return false;
	}
}

void Chat::messageInputAll(int connection, const std::string &login_from)
{
	Network netConnect;
	std::string text = netConnect.reseiveMessage(connection);
	_data.insertDataMessageAll(login_from, text);	
}

void Chat::messageInputFromTo(int connection, const std::string &login_from)
{
	std::string text;
	std::string login_to;
	Network netConnect;

	abonentList(connection, login_from);
	login_to = netConnect.reseiveMessage(connection);
	if (login_to == "всем")
	{
		messageInputAll(connection, login_from);
	}
	else
	{
		if (correctInputAbonent(connection, login_to))
		{
			text = netConnect.reseiveMessage(connection);
			_data.insertDataMessage(login_from, login_to, text);
		}
	}
}

void Chat::messageReadPersonal(int connection, const std::string &login_from)
{
	auto count = 0;
	std::string str;
	Network netConnect;
	str = _data.readDataMessage(login_from);

	if (!str.empty())
	{
		netConnect.sendMessage(connection, str);
	}
	else
	{
		netConnect.sendMessage(connection, "error");
	}
}

void Chat::messageReadAll(int connection)
{
	std::string str;
	Network netConnect;

	str = _data.readDataMessageAll();
	if (!str.empty())
	{
		netConnect.sendMessage(connection, str);
	}
	else
	{
		netConnect.sendMessage(connection, "error");
	}
}

void Chat::messageWriteRead(int connection, const std::string &login_from)
{
	Network netConnect;
	const char *choice;
	std::string str;
	do
	{
		str = netConnect.reseiveMessage(connection);
		choice = str.c_str();
		
		switch (choice[0])
		{
		case '1':
			messageReadAll(connection);
			break;

		case '2':
			messageReadPersonal(connection, login_from);
			break;

		case '3':
			messageInputFromTo(connection, login_from);
			break;

		case '4':
			break;

		default:
			//incorrectInputMenuMessage();
			break;
		}
	} while (choice[0] != '4');
}
