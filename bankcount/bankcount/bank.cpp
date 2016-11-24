#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bankcounter.h"
#include <ctype.h>
using namespace std;
 
 
/*
功能：用构造函数读取文件中保存的业务数据
*/
Bank::Bank()
{
    ifstream infile("account.dat",ios::in);
    if(!infile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    int i=0;
    int acc;   //账号
    string nam;   //姓名
    int pw;   //密码
    double bal;   //金额
    int sta;   //状态
    while(infile>>acc>>nam>>pw>>bal>>sta)   //当读取成功……
    {
        users[i].setUser(acc,nam,pw,bal,sta);
        i++;
    }
    N = i; //用静态数据成员
    infile.close();
}
 
/*
功能：用析构函数，在退出系统时，将数据保存到文件中
*/
Bank::~Bank()
{
    ofstream outfile("account.dat",ios::out);
    if(!outfile)    //测试文件打开操作是否成功，不成功则提示后退出。
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    int i;
    for(i=0; i<N; i++)
    {
        outfile<<users[i].account<<" ";
        outfile<<users[i].name<<" ";
        outfile<<users[i].password<<" ";
        outfile<<users[i].balance<<" ";
        outfile<<users[i].status<<" ";
    }
    outfile.close();
}
 
/*
功能：办理业务
*/
void Bank::work()
{
    int iChoice;   //用于选择系统功能
    //办理业务
    do
    {
        iChoice = chooseInMenu();  //从菜单中获得功能代码
        switch(iChoice)
        {
        case 1:
            openAccount(); //开户
            break;
        case 2:
            cancelAccount();  //注销账户
            break;
        case 3:
            save();  //存款
            break;
        case 4:
            withdraw();   //取款
            break;
        case 5:
            showAccount(); //查询余额
            break;
        case 6:
            transferAccounts();  //转账
            break;
        case 7:
            reportLoss();  //挂失
            break;
        case 8:
            cancelLoss();  //解除挂失
            break;
        case 9:
            updatePassword();   //更改密码
            break;
        case 0:
            cout<<"欢迎您再来. "<<endl;
        }
    }
    while(iChoice);
}
 
/*
功能：开户
说明：在进入系统时，在读入数据过程中，已经记录了用户数为N，在数组中对应下标为0~N-1
  开户时要增加一个用户，只要为下标为N的数组元素置值，并在成功之后令N++即可。
  账号由系统自动生成(10001+序号)，保证其连续，这样在顺序增加的时候，就保证了其有序。
*/
void Bank::openAccount()
{
    if(N==upNum)
    {
        cout<<"银行用户数已经达到上限，不能再开户";
        return;
    }
    //下面正常办理开户业务
    int acc;   //账号
    string nam;   //姓名
    int pw;   //密码
    double bal;   //金额
    int sta;   //状态
    cout<<"正在开户"<<endl;
    acc=10001+N;
    cout<<"账号："<<acc<<endl;
    cout<<"户主姓名：";
    cin>>nam;
    int iPass1, iPass2;
    cout<<"密码：";
    iPass1=inputPassword();  //输入密码1
    cout<<"确认密码：";
    iPass2=inputPassword();  //输入密码2
    if(iPass1==iPass2)
    {
        pw=iPass1;
        sta=0; //账户状态为“正常”
        cout<<"存入金额：";
        cin>>bal;
        users[N].setUser(acc, nam, pw, bal, sta);
        N++; //正式用户数增加1，确认了新用户已经加入
        cout<<"成功开户！"<<endl;
    }
    else
    {
        cout<<"两次密码不一致，未成功开户！"<<endl; //没有N++，则读入的值无效
    }
}
 
/*
功能：注销账户
说明：找到账户，并将其状态改为2-注销即可。
注销前应该检查余额，应该先取款再注销
*/
void Bank::cancelAccount()
{
    int who;  //查找到该账号在数组中对应的下标
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            users[who].showBalance("余额");   //提示"余额"二字，显示金额
            cout<<"确认销户（y/n）？";
            if(tolower(getchar())=='y')
            {
                users[who].showBalance("销户成功！本次取款金额为");
                users[who].balance=0;  //取款后余额变0
                users[who].status=2;  //状态变为注销
            }
            else
            {
                cout<<"你取消了操作，销户失败！"<<endl;
            }
            fflush(stdin);  //清除了getchar()时在键盘缓存中的遗留，以免影响后续操作
        }
    }
}
 
/*
功能：存款
说明：需要保证账户存在，且处于正常状态
*/
void Bank::save()
{
    int who;
    double money;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        if(users[who].status==0)
        {
            users[who].showName();
            cout<<"输入存款额：";
            cin>>money;
            users[who].balance+=money;
            users[who].showBalance("存款后，您有");
        }
        else if(users[who].status==1)
        {
            cout<<"该用户处于挂失状态，存款失败！"<<endl;
        }
        else
        {
            cout<<"该用户已经销户，存款失败！"<<endl;
        }
    }
    return;
}
 
/*
功能：取款
说明：需要保证账户存在，且处于正常状态，另外，余额要足够取
*/
void Bank::withdraw()
{
    int who;
    double money;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        if(users[who].isNormalUser())
        {
            users[who].showName();
            if(users[who].passwordIsRight())
            {
                cout<<"输入取款额：";
                cin>>money;
                if(money>users[who].balance)  //亲，不玩透支
                {
                    cout<<"余额不足，取款失败！"<<endl;
                }
                else
                {
                    users[who].balance-=money;
                    users[who].showBalance("取款后，还有");
                }
            }
        }
 
    }
    return;
}
 
/*
功能：查询账户
说明：显示账户信息
*/
void Bank::showAccount()
{
    int who;
    string sta[3]= {"正常","挂失","已经销户"};
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            users[who].showBalance("余额");
            cout<<"状态："<<sta[users[who].status]<<endl;
        }
    }
    return;
}
 
/*
功能：转账
说明：需要保证两个账户都存在，且处于正常状态，另外，转出账户的余额要足够
*/
void Bank::transferAccounts()
{
    int whoout, whoin;
    double money;
    cout<<"转出自";
    whoout = getUser();  //根据账号查询用户，返回用户的下标
    if(whoout>=0)   //说明id账户存在
    {
        if(users[whoout].isNormalUser())
        {
            users[whoout].showName();
            if(users[whoout].passwordIsRight())
            {
                cout<<"输入转账金额：";
                cin>>money;
                if(money>users[whoout].balance)  //亲，不玩透支
                {
                    cout<<"余额不足，转账失败！"<<endl;
                }
                else
                {
                    cout<<"转出到";
                    whoin = getUser();  //根据账号查询用户，返回用户的下标
                    if(whoin>=0)   //说明id账户存在
                    {
                        if(users[whoin].isNormalUser())
                        {
                            users[whoout].balance-=money;
                            users[whoin].balance+=money;
                            users[whoout].showBalance("转账后，您还有");
                        }
                    }
                }
            }
        }
    }
    return;
}
 
/*
功能：挂失账户
*/
void Bank::reportLoss()
{
    int who;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            if(users[who].status==0)
            {
                users[who].status=1;
                cout<<"挂失成功"<<endl;
            }
            else if(users[who].status==1)
            {
                cout<<"该账户已经处于挂失状态"<<endl;
            }
            else
            {
                cout<<"该账户已销户，不能挂失"<<endl;
            }
        }
    }
    return;
}
 
/*
功能：解除挂失
*/
void Bank::cancelLoss()
{
    int who;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            if(users[who].status==0)
            {
                cout<<"该账户处于正常状态，不需要解除挂失"<<endl;
            }
            else if(users[who].status==1)
            {
                users[who].status=0;
                cout<<"解除挂失成功"<<endl;
            }
            else
            {
                cout<<"该账户已销户，操作无效"<<endl;
            }
        }
    }
    return;
}
 
/*
功能：改密码
*/
void Bank::updatePassword()
{
    int who;
    int iPass1, iPass2;
    who = getUser();  //根据账号查询用户，返回用户的下标
    if(who>=0)   //说明id账户存在
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            cout<<"新密码：";
            iPass1=inputPassword();  //输入密码1
            cout<<"确认密码：";
            iPass2=inputPassword();  //输入密码2
            if(iPass1==iPass2)
            {
                users[who].password=iPass1;
                cout<<"修改成功！"<<endl;
            }
            else
            {
                cout<<"两次输入不同，修改失败！"<<endl;
            }
        }
    }
    return;
}
 
/*
功能：输入账号查询用户，返回用户在数组中的下标
入口参数：要查询用户的账号
返回值：如果该用户存在，返回该用户在数组中的下标，否则，返回一个负数（-1）
说明：
  由账号自动产生，使按账号有序，本模块采用二分查找
*/
int Bank::getUser()
{
    int id;
    cout<<"账号：";
    cin>>id;
    int index=-1;
    int low=0, high=N-1, mid;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(users[mid].account==id)
        {
            index=mid;
            break;   //找到了，立即退出循环
        }
        else if (users[mid].account>id)
            high=mid-1;
        else
            low=mid+1;
    }
    if (index<0)
        cout<<"该用户不存在，本次操作失败！"<<endl;
    return index; //若找到，其值在0~N-1间，否则，保持-1
}