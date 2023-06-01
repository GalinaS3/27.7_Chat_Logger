#pragma once
#include"Func.h"
#include<mysql/mysql.h>

class Data
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

public:
    Data();
    ~Data();

    void openData();
    void createDataTable();
    bool insirtDataUser(const std::string &name, const std::string &login, const std::string &password);
    bool entranceDataUser(const std::string &login, const std::string &password);
    bool insertDataMessage(const std::string &from, const std::string &to, const std::string &text);
    bool insertDataMessageAll(const std::string &from, const std::string &text);
    std::string readDataUsersLogin(const std::string &login);
    bool correctDataInputAbonent(const std::string& login_to);
    std::string readDataMessage(const std::string &login);
    std::string readDataMessageAll();
    void closeData();
};