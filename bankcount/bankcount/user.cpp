#include <iostream>
#include "bank.h"
using namespace std;
 
void User::setUser(int acc, string nam, int pw, double bal,int sta)
{
    account=acc;
    password=pw;
    name=nam;
    balance=bal;
    status=sta;
}
void User::showName()
{
    cout<<"户主姓名："<<name<<endl;
}
void User::showBalance(string prompt)
{
    cout<<prompt<<" "<<balance<<" 元"<<endl;
}
bool User::passwordIsRight()
{
    int iPass;
    bool right = true;
    cout<<"输入密码：";
    iPass=inputPassword();
    if(iPass!=password)
    {
        right = false;
        cout<<"输入密码错误，不能继续操作！"<<endl;
    }
    return right;
}
 
bool User::isNormalUser()
{
    bool normal = true;
    if(status!=0)
    {
        normal = false;
        cout<<"该账户处于"<<(status==1?"挂失":"销户")<<"状态，不能继续操作..."<<endl;
    }
    return normal;
}