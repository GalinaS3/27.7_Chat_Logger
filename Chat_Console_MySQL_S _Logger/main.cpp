#include"Chat.h"
//#include"File.h"

int main()
{
	
	std::string login;
	char choice_menu;
	std::string str;
	Chat chat;
	
	Network netConnect;
	auto connectNet = netConnect.connectServerOpen();
	std::cout << "CONNECTION:  " << connectNet << std::endl;
	Logger logger;
	std::thread t1 ([&logger] () {
		logger.loggerWrite("Соединение установлено.");  //пишем в log.txt
		}); 
	if(t1.joinable())	
		t1.join();
	
	if (connectNet == -1)
	{
		std::cout << "Сбой сети!" << std::endl;
		std::thread t2 ([&logger] () {     //пишем в log.txt
		logger.loggerWrite("Сбой сети!");
		
		});
		if(t2.joinable())	
			t2.join();
		
		exit(-1);
	}

	chat.connectMySQL();
	
	do
	{
		str = netConnect.reseiveMessage(connectNet);
		
		if(strncmp("1", str.c_str(), 1) == 0) 
		{
			choice_menu = '1';
		}	
		if(strncmp("2", str.c_str(), 1) == 0) 
		{
			choice_menu = '2';
		}	
		if(strncmp("3", str.c_str(), 1) == 0) 
		{
			choice_menu = '3';
		}		
		
		if (choice_menu == '1')
		{
			login = chat.signUp(connectNet);
			
			if (login != "error")
			{
				chat.messageWriteRead(connectNet, login);
			}
		}
		if (choice_menu == '2')
		{
			auto loginIn = chat.entrance(connectNet);
			
			if (loginIn != "error")
			{
				chat.messageWriteRead(connectNet, loginIn);
			}
		}
	} while (choice_menu != '3');
	
	Logger logger1;
	
	std::thread t ([&logger1] () {  //читаем две строки
		logger1.loggerRead();
	}); 
	
	chat.disconnectMySQL();
	netConnect.connectClose(connectNet);
	
	if(t.joinable())	
		t.join();
	
	
	return 0;
}


