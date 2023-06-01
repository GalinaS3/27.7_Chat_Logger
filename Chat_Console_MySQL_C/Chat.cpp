#include"Chat.h"


Chat::Chat() = default;
Chat::~Chat() = default;

std::string Chat::signUp(int connection)
{ 
	std::string name ;
	std::string login ;
	std::string password ;
	
	Network netConnect;
	name = inputName();
	netConnect.sendMessage(connection, name);
	login = inputLogin();
	netConnect.sendMessage(connection, login);
	password = inputPass();			
	netConnect.sendMessage(connection, password);		

	std::string str = netConnect.reseiveMessage(connection);			

	if(strncmp("error", str.c_str(), 5) == 0) 
	{
		std::cout << "Такие имя/логин/пароль уже зарегистрированы.\n Попробуйте еще раз. ";
		std::cout << std::endl;	
		return "error";	
	}
	else 
	{
		std::cout << str;		
		std::cout << std::endl;	
		return login;
	}	
}

std::string Chat::entrance(int connection)
{
	std::string login;
	std::string password;
	
	Network netConnect;		
	login = inputLogin();
	netConnect.sendMessage(connection, login);
	password = inputPass();
	netConnect.sendMessage(connection, password);
	
	std::string str = netConnect.reseiveMessage(connection);
			
	if(strncmp("Вход", str.c_str(), 4) == 0) 
	{	
		std::cout << str;
		std::cout << std::endl;		
		return login;
	}	
	else
	{
		std::cout << str << std::endl;
		return "error";
	}
}

void Chat::abonentList(int connection, const std::string& login_from)
{
	Network netConnect;

	std::cout << "Абоненты:   всем  / ";	
	std::string str = netConnect.reseiveMessage(connection);				
	std::cout << str << '\n';		
}

bool Chat::correctInputAbonent(int connection, const std::string& login_to)
{
	Network netConnect;
	
	std::string str = netConnect.reseiveMessage(connection);
		if(strncmp("true", str.c_str(), 4) == 0) 
		{			
			return true;
		}	
	return false;
}

void Chat::messageInputAll(int connection)
{
	std::string text = massageText();
	Network netConnect;
	netConnect.sendMessage(connection, text);	
}

void Chat::messageInputFromTo(int connection, const std::string& login_from) {
	std::string text;
	std::string login_to;
	Network netConnect;

	abonentList(connection, login_from);
	login_to = inputTo();
	
	netConnect.sendMessage(connection, login_to);

	if (login_to == "всем")
	{
		messageInputAll(connection);
	}
	else
	{
		if (correctInputAbonent(connection, login_to))
		{
			text = massageText();
			netConnect.sendMessage(connection, text);
		}	
		else
		{
			incorrectInputMenuMessage();
		}
	}
}

void Chat::messageReadPersonal(int connection, const std::string& login_from) 
{
	Network netConnect;	
	
	std::string str1 = netConnect.reseiveMessage(connection);
	if(strncmp("error", str1.c_str(), 2) == 0)	
	{
		std::cout << "Личных сообщений нет." << std::endl;	
		return;		
	}				
	std::cout << "Личные сообщения:     " << std::endl;
	std::cout << str1 << std::endl;		
}

void Chat::messageReadAll(int connection)
{	
	Network netConnect;	
	std::string str1  = netConnect.reseiveMessage(connection);
		
	if(strncmp("error", str1.c_str(), 2) == 0)	
	{
		std::cout << "Сообщений из общего чата нет. " << std::endl;	
		return;		
	}

	std::cout << "Сообщения из общего чата:     " << std::endl;
	std::cout << str1 << std:: endl;
}

void Chat::messageWriteRead(int connection, const std::string& login_from)
{
	Network netConnect;
	std::string str;
	char choice;
	do
	{
		choice = menuMessage();
		str = choice;
		netConnect.sendMessage(connection, str);
		switch (choice)
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
			incorrectInputMenuMessage();
			break;
		}
	} 
	while (choice != '4');
}

