#include"Data.h"

Data::Data() = default;
Data::~Data() = default;

void Data::openData()
{
    mysql_init(&mysql);
    if(&mysql == nullptr)
    {
        std::cout << "Ошибка: дискритор соединения MySQL не создан." << std::endl;
        exit(1);
    }
    MYSQL *connect = mysql_real_connect(&mysql, "localhost", "root", "111", "testdb", 0, NULL, 0);
    if(connect == nullptr)
    {
        std::cout << "Невозможно подключится к базе данных. Ошибка:  " << mysql_error(&mysql) << std::endl; 
        exit(1);       
    }    
}

void Data::createDataTable()
{
    mysql_query(&mysql, "create table if not exists users (id INT AUTO_INCREMENT primary key not null, 	\
     name varchar(200) not null,	login varchar(200) unique not null, user_password varchar(200))");
    mysql_query(&mysql, "create table if not exists messages (id INT AUTO_INCREMENT primary key not null,\
	 from_id integer, foreign key (from_id) references users(id) on delete cascade on update cascade, \
     to_id integer, foreign key (to_id) references users(id) on delete cascade on update cascade,  text varchar(500))");
    mysql_query(&mysql, "create table if not exists messagesAll (id INT AUTO_INCREMENT primary key not null, \
	 from_id integer, foreign key (from_id) references users(id) on delete cascade on update cascade, text varchar(500))");       
}

bool Data::insirtDataUser(const std::string &name, const std::string &login, const std::string &password)
{        
    const std::string str = "insert into users (id, name, login, user_password) values \
     (default, '" + name + "', '" + login + "', '" + password + "')";

    mysql_query(&mysql, str.c_str());
    if(mysql_errno(&mysql))
    {
        return false;
    }
	else
    {
        return true;
    }
}

bool Data::entranceDataUser(const std::string &login, const std::string &password)
{         
    const std::string str = "select login, user_password from users where login='" + login +"' and \
	  user_password = '" + password +"'";
	mysql_query(&mysql, str.c_str());
	res=mysql_store_result(&mysql);
    if(res)
    {
        if (mysql_fetch_row(res))
        {
			return true; 
        }               
		else
        {
            return false;
        }
    }
	else
    {
        return false;            
    }        
}

bool Data::insertDataMessage(const std::string &from, const std::string &to, const std::string &text)
{
    const std::string str = "insert into messages (id, from_id, to_id, text) values (default, \
	 (select id from users where login = '" + from + "'), (select id from users where \
     login ='" + to + "'), '" + text + "')";
    mysql_query(&mysql, str.c_str());

    if(mysql_errno(&mysql))
    {
        return false;
    }
	else
    {
        return true;
    }
}

bool Data::insertDataMessageAll(const std::string &from, const std::string &text)
{
    const std::string str = "insert into messagesAll (id, from_id, text) values (default, \
	 (select id from users where login = '" + from + "'), '" + text + "')";

    mysql_query(&mysql, str.c_str());

    if(mysql_errno(&mysql))
    {
        return false;
    }
	else
    {
        return true;
    }
}

std::string Data::readDataUsersLogin(const std::string &login)
{
    const std::string str = "SELECT login FROM users where login != '" + login + "'";
    mysql_query(&mysql, str.c_str());
    std::string tmp;
    if (res = mysql_store_result(&mysql)) 
    {		    
		while (row = mysql_fetch_row(res)) 
        {						
			for (auto i = 0; i < mysql_num_fields(res); i++) 
            {
				tmp = tmp + row[i] +  " / ";
			}			
		}
	}
	    
    return tmp;
}

bool Data::correctDataInputAbonent(const std::string& login_to)
{
    const std::string str = "SELECT login FROM users ";
    mysql_query(&mysql, str.c_str());
    res = mysql_store_result(&mysql);
    if (res) 
    {		
		while (row = mysql_fetch_row(res)) 
        {						
			for (auto i = 0; i < mysql_num_fields(res); i++) 
            {
				if(row[i] == login_to)
                return true;
			}			
		}
        return false;
	}
	else
    {
        return false;
    }
}

std::string Data::readDataMessage(const std::string &login)
{        
    const std::string str = "select login, s.text from users join \
	 (select from_id, text from messages join users on messages.to_id=users.id \
	 where users.login = '" + login + "') as s where s.from_id=users.id";
        
    std::string tmp;
    mysql_query(&mysql, str.c_str());
       
    if (res = mysql_store_result(&mysql)) 
    {
		    
		while (row = mysql_fetch_row(res)) 
        {						
			for (auto i = 0; i < mysql_num_fields(res); i++) 
            {
				tmp = tmp + row[i] +  "  / ";
			}
            tmp = tmp + "\n";
		}
	}
	    
    return tmp;
}

std::string Data::readDataMessageAll()
{
    const std::string str = "select name, text from messagesAll join users on messagesAll.from_id=users.id";
        
    std::string tmp;
    mysql_query(&mysql, str.c_str());
       
    if (res = mysql_store_result(&mysql)) 
    {
		    
		while (row = mysql_fetch_row(res)) 
        {						
			for (auto i = 0; i < mysql_num_fields(res); i++) {
				tmp = tmp + row[i] +  " / ";
			}
            tmp = tmp + "\n";
		}
	}

    return tmp;                                             
}

void Data::closeData()
{
    //std::cout << "База дисконнект" << std::endl;
    mysql_close(&mysql);
}    