#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
 
#include "bank.h"
using namespace std;
/*
功能：验证用户密码
返回值：密码正确，返回1；
        不能通过密码验证，返回0
*/
int pass()
{
    char sNameInFile[20];   //由文件中读出的业务员用户名
    char sPassInFile[20];  //文件中保存的密码，这一版本中，用字符保存密码
    ifstream infile("password.txt",ios::in);
    if(!infile)
    {
        cout<<"password file cannot open!"<<endl;
        exit(1);
    }
    infile>>sNameInFile>>sPassInFile;
    infile.close();
 
    char sName[20];   //业务员登录时输入的用户名
    char sPass[20];  //业务员登录时输入的密码
    char ch;
    int iTry=3;   //进入系统时尝试的次数
    int right = 0;  //要返回的结果：0-不正确 1-正确
 
    //进入系统，密码三次不对将退出
    do
    {
        cout<<"请输入业务员用户名:";
        cin>>sName;
        cout<<"请输入密码:";
        int i=0;
        while((ch=getch())!='\r')  //getch在接受输入后，不在屏幕上显示
        {
            sPass[i++]=ch;
            putchar('*');   //接受任何字符，屏幕上只显示*
        }
        sPass[i]='\0';
        fflush(stdin);
        cout<<endl;;
        if(strcmp(sPass,sPassInFile)==0&&strcmp(sName,sNameInFile)==0)
        {
            right = 1;
            break;
        }
        else
        {
            iTry--;
            if(iTry>0)
                cout<<"超过3次将退出，你还可以尝试"<<iTry<<"次！"<<endl;
            else
            {
                cout<<"对不起，你不能进入系统"<<endl;;
            }
        }
    }
    while(iTry);
    return right;
}
 
/*
关于getch()的一点说明：
所在头文件：conio.h
函数用途：从控制台读取一个字符，但不显示在屏幕上
函数原型：int getch(void)
返回值：读取的字符
在不同平台，输入回车，getch()将返回不同数值，而getchar()统一返回10(即\n)
1)windows平台下ENTER键会产生两个转义字符 \r\n，因此getch返回13(\r)。
2)unix、 linux系统中ENTER键只产生 \n ，因此getch返回10(\n)。
3)MAC OS中ENTER键将产生 \r ，因此getch返回13(\r)。
为避免键盘缓存区中未读出的字符影响程序，用fflush(stdin);清除输入缓存区
*/
 
 
 
/*
功能：显示菜单并由业务员选择
返回值：用户选择的功能，范围0-9
*/
int chooseInMenu()
{
    int i;
    while(1)
    {
        cout<<endl;;
        cout<<"+----------------------------+"<<endl;
        cout<<"+ 1 开户    2 销户    3 存款 +"<<endl;
        cout<<"+ 4 取款    5 查询    6 转账 +"<<endl;
        cout<<"+ 7 挂失    8 解挂    9 改密 +"<<endl;
        cout<<"+                     0 退出 +"<<endl;
        cout<<"+----------------------------+"<<endl;
        cout<<"请输入操作指令:";
        cin>>i;
        if(i>=0 && i<=9)
            break;
        else
            cout<<"请重新选择功能"<<endl;;
    }
    return i;
}
 
/*
功能：输入密码
返回值：整型的密码值
技术说明：
（1）此功能在多个模块中都要用到且功能单一，故分离出来，单独作业一个函数
（2）为了便于在输入中只显示*，接受输入时以字符形式输入，而后转为对应的整型数
（3）规定密码由不全为0的6位数字构成（当开头是'0'时，实际不足6位），一旦输入错误将重新输入
附：在实际的系统中，密码通常用字符串描述，即使只允许出现数字字符，本例仅作为参考
*/
int inputPassword()
{
    char ch;  //接收字符形式密码
    int iPass=0;   //要转换为数字
    int i;
    while(1)
    {
        for(i=0; i<6; i++)
        {
            ch=getch();  //输入但不显示
            putchar('*');   //输出*
            if(isdigit(ch))
                iPass=iPass*10+(ch-'0');
            else
            {
                iPass=0;
                break;  //退出for循环后，再次接受
            }
        }
        fflush(stdin); //清除键盘缓存区中已经有的输入
        cout<<endl;;
        if(iPass==0)  //此条件成立可能由两种情况引起：输入了非数字字符被直接重置为0，或6位全0后正常退出for循环
        {
            cout<<"密码要求全为数字，且不能全0！"<<endl;;
            cout<<"请重新输入密码: ";
        }
        else
            break;
    }
    return iPass;
}