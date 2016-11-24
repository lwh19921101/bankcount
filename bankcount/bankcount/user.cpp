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
    cout<<"����������"<<name<<endl;
}
void User::showBalance(string prompt)
{
    cout<<prompt<<" "<<balance<<" Ԫ"<<endl;
}
bool User::passwordIsRight()
{
    int iPass;
    bool right = true;
    cout<<"�������룺";
    iPass=inputPassword();
    if(iPass!=password)
    {
        right = false;
        cout<<"����������󣬲��ܼ���������"<<endl;
    }
    return right;
}
 
bool User::isNormalUser()
{
    bool normal = true;
    if(status!=0)
    {
        normal = false;
        cout<<"���˻�����"<<(status==1?"��ʧ":"����")<<"״̬�����ܼ�������..."<<endl;
    }
    return normal;
}