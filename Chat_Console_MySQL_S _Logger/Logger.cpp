#include "Logger.h"

Logger::Logger()
    {
        _s_m.lock();
        _fs.open("log.txt", std::ios::in | std::ios::out | std::ios::app);
        _s_m.unlock();
    }
    Logger::~Logger()
    {
        if (_fs.is_open())
        {
            _s_m.lock();
            _fs.close();
            _s_m.unlock();
        }
    }

    std::string Logger::loggerRead() // считываем последнюю строку
    {
        std::string loggmess;
        if (!_fs.is_open())
        {
            std::cout << "Ошибка открытия файла!";
            return "eror";
        }
        else
        {   
            auto cursor = 0;
            char ch = 'p';
            _s_m.lock_shared();
        
            _fs.seekg(-2, std::ios::end);
            while (ch != '\n' && _fs.tellg()!=0)
            {
                _fs.seekg(-1, std::ios::cur);
                ch = _fs.peek();
                //std::cout << ch;
                cursor += 1;            
             }           
            _fs.seekg(-(cursor + 26), std::ios::end);
            getline(_fs, loggmess);
            std::cout << loggmess << std::endl;
            _fs.seekg(-(cursor + 1), std::ios::end);
            getline(_fs, loggmess);
            std::cout << loggmess << std::endl;
            _s_m.unlock_shared();
        
            return loggmess;
        }
    }

    void Logger::loggerWrite(const std::string &loggmess)
    {
        if (!_fs.is_open())
        {
            std::cout << "Ошибка открытия файла!";
        }
        else
        {            
            _s_m.lock();
            _fs << _time.getTime();
            _fs << loggmess << std::endl;
            //std::cout << loggmess << std::endl;
            _s_m.unlock();
        }
    }
    

