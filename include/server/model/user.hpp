#ifndef USER_H
#define USER_H
#include<string>
using namespace std;

//匹配User表的ORM类
class User{
public:
    User(int id=-1,string name="",string pwd="",string state="offline")
    {
        this->id = id;
        this->name = name;
        this->password = pwd;
        this->state = state;
    }
    void setId(int id){this->id = id;}
    void setName(string name){this->name = name;}
    void setPassword(string password){this->password = password;}
    void setState(string state){this->state = state;}

    int getId(){return id;}
    string getName(){return name;}
    string getPassword(){return password;}
    string getSate(){return state;}
private:
    int id;
    string password;
    string name;
    string state;
        
};

#endif