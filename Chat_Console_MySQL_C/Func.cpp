#include"Func.h"
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

char mainMenu()
{	
	char choice;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << " (1) Регистрация" << std::endl;
	std::cout << " (2) Вход" << std::endl;
	std::cout << " (3) Выход из программы" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	
	std::cout << "Выбор -  ";
	std::cin >> choice;
	std::cin.ignore(1, '\n');
	return choice;
}

char menuMessage()
{	
	std::cout << "******************************" << std::endl;
	std::cout << " *1* Получить сообщения из общего чата." << std::endl;
	std::cout << " *2* Получить личные сообщения." << std::endl;
	std::cout << " *3* Написать сообщение." << std::endl;
	std::cout << " *4* Выйти из учётной записи." << std::endl;
	std::cout << "******************************" << std::endl;
	
	std::cout << " Выбор -  ";
	char choice;
	std::cin >> choice;
	std::cin.ignore(100, '\n');
	return choice;
}

std::string inputName()
{
	std::string str;
	std::cout << "Имя - ";
	std::cin >> str;
	return str;
}

std::string inputLogin()
{
	std::string str;
	std::cout << "Логин - ";
	std::cin >> str;
	return str;
}

std::string inputPass()
{
	std::string str;
	std::cout << "Пароль - ";
	std::cin >> str;
	return str;
}

std::string inputTo()
{
	std::string str;
	std::cout << std::endl;
	std::cout << "Кому - ";
	/*std::cin.ignore();
	std::getline(std::cin, str);*/
	std::cin >> str;
	return str;
}

std::string massageText()
{
	std::string text;
	std::cout << ">>  ";
	std::cin.ignore();
	std::getline(std::cin, text);

	return text;
}

void incorrectInputMenuMessage()
{
	std::cout << "Некорректный ввод. Попробуйте ещё раз." << std::endl;

}

bool incorrectInputMenu(char choice_menu)
{
	if (choice_menu < 49 || choice_menu > 52)
	{
		std::cout << std::endl;
		std::cout << "Некорректный ввод. Попробуйте ещё раз." << std::endl;
		return false;
	}
	return true;
}

/*void noMessages()
{
	std::cout << "Для Вас личных сообщений нет." << std::endl;
}*/

