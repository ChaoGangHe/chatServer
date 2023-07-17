#include"json.hpp"

#include<iostream>
#include<vector>
using json = nlohmann::json;
using namespace std;

//序列化实例1
string func1()
{
    json js;
    js["type"] = 2;
    js["from"] = "张三";
    js["to"] = "lisi";
    js["msg"] = "hello,what are you doing now?";
    string sendbuf = js.dump();
    // cout<<sendbuf.c_str()<<endl;
    return sendbuf;
}

//序列化实例2
string func2()
{
    json js;
    js["id"] = {1,2,3,4,5};
    js["name"] = "zhangsan";
    js["msg"]["zhangsan"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    //js["msg"] = {{"zhangsan","hello world"},{"liu shuo","hello china"}};
    //cout<<js<<endl;
    return js.dump();
}

//序列化实例3
void func3()
{
    json js;
    
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    js["list"] = vec;

    map<int,string>m;
    m.insert({1,"黄山"});
    m.insert({2,"华山"});
    m.insert({3,"泰山"});
    js["path"] = m;
    string sendbuf = js.dump();
    cout<<sendbuf<<endl;
}
int main()
{
    string recvbuf = func1();
    //数据反序列化 json字符串 =》反序列化 数据对象
    json jsbuf = json::parse(recvbuf);
    cout<<jsbuf<<endl;
    return 0;
}