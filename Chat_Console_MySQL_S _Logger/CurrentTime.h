#pragma once
#include <iostream>
#include<time.h>

struct CurrentTime {
    
    time_t now;
    time_t currentTime = time(&now);
    CurrentTime(){}
    ~CurrentTime(){}

    std::string getTime()
    {     
        std::string tmp = ctime(&currentTime);   
        return tmp;
    }
};