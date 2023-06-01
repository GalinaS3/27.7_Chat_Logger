#pragma once
#include<string>
#include<iostream>


char mainMenu();
char menuMessage();
std::string inputName();
std::string inputLogin();
std::string inputPass();
std::string inputTo();
std::string massageText();
void incorrectInputMenuMessage();
bool incorrectInputMenu(char choice_menu);
void noMessages();


