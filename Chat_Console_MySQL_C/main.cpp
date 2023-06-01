#include"Chat.h"


int main()
{	
	std::string login;
	char choice_menu;
	Chat chat;
	std::string str;
	
	Network netConnect;
	auto connectNet = netConnect.connectClientOpen();
	std::cout << "CONNECTION:  " << connectNet << std::endl;
	if (connectNet == -1)
	{
		std::cout << "Сбой сети!" << std::endl;
		exit(-1);
	}
	
	do
	{
		choice_menu = mainMenu();		
		
		if(incorrectInputMenu(choice_menu))
			{
				str = choice_menu;
				netConnect.sendMessage(connectNet, str);
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
	
	netConnect.connectClose(connectNet);

	return 0;
}


