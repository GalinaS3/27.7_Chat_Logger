#pragma once
#include <iostream>
#include<fstream>
#include<shared_mutex>
#include <string>
#include"CurrentTime.h"

class Logger
{
private:
    std::fstream _fs;
    std::shared_mutex _s_m;
    CurrentTime _time;
    
public:
    Logger();    
    ~Logger();    
    std::string loggerRead(); // считываем последнюю строку 
    void loggerWrite(const std::string& loggmess);

};
