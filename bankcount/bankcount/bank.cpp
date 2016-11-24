#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bankcounter.h"
#include <ctype.h>
using namespace std;
 
 
/*
���ܣ��ù��캯����ȡ�ļ��б����ҵ������
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
    int acc;   //�˺�
    string nam;   //����
    int pw;   //����
    double bal;   //���
    int sta;   //״̬
    while(infile>>acc>>nam>>pw>>bal>>sta)   //����ȡ�ɹ�����
    {
        users[i].setUser(acc,nam,pw,bal,sta);
        i++;
    }
    N = i; //�þ�̬���ݳ�Ա
    infile.close();
}
 
/*
���ܣ����������������˳�ϵͳʱ�������ݱ��浽�ļ���
*/
Bank::~Bank()
{
    ofstream outfile("account.dat",ios::out);
    if(!outfile)    //�����ļ��򿪲����Ƿ�ɹ������ɹ�����ʾ���˳���
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
���ܣ�����ҵ��
*/
void Bank::work()
{
    int iChoice;   //����ѡ��ϵͳ����
    //����ҵ��
    do
    {
        iChoice = chooseInMenu();  //�Ӳ˵��л�ù��ܴ���
        switch(iChoice)
        {
        case 1:
            openAccount(); //����
            break;
        case 2:
            cancelAccount();  //ע���˻�
            break;
        case 3:
            save();  //���
            break;
        case 4:
            withdraw();   //ȡ��
            break;
        case 5:
            showAccount(); //��ѯ���
            break;
        case 6:
            transferAccounts();  //ת��
            break;
        case 7:
            reportLoss();  //��ʧ
            break;
        case 8:
            cancelLoss();  //�����ʧ
            break;
        case 9:
            updatePassword();   //��������
            break;
        case 0:
            cout<<"��ӭ������. "<<endl;
        }
    }
    while(iChoice);
}
 
/*
���ܣ�����
˵�����ڽ���ϵͳʱ���ڶ������ݹ����У��Ѿ���¼���û���ΪN���������ж�Ӧ�±�Ϊ0~N-1
  ����ʱҪ����һ���û���ֻҪΪ�±�ΪN������Ԫ����ֵ�����ڳɹ�֮����N++���ɡ�
  �˺���ϵͳ�Զ�����(10001+���)����֤��������������˳�����ӵ�ʱ�򣬾ͱ�֤��������
*/
void Bank::openAccount()
{
    if(N==upNum)
    {
        cout<<"�����û����Ѿ��ﵽ���ޣ������ٿ���";
        return;
    }
    //��������������ҵ��
    int acc;   //�˺�
    string nam;   //����
    int pw;   //����
    double bal;   //���
    int sta;   //״̬
    cout<<"���ڿ���"<<endl;
    acc=10001+N;
    cout<<"�˺ţ�"<<acc<<endl;
    cout<<"����������";
    cin>>nam;
    int iPass1, iPass2;
    cout<<"���룺";
    iPass1=inputPassword();  //��������1
    cout<<"ȷ�����룺";
    iPass2=inputPassword();  //��������2
    if(iPass1==iPass2)
    {
        pw=iPass1;
        sta=0; //�˻�״̬Ϊ��������
        cout<<"�����";
        cin>>bal;
        users[N].setUser(acc, nam, pw, bal, sta);
        N++; //��ʽ�û�������1��ȷ�������û��Ѿ�����
        cout<<"�ɹ�������"<<endl;
    }
    else
    {
        cout<<"�������벻һ�£�δ�ɹ�������"<<endl; //û��N++��������ֵ��Ч
    }
}
 
/*
���ܣ�ע���˻�
˵�����ҵ��˻���������״̬��Ϊ2-ע�����ɡ�
ע��ǰӦ�ü����Ӧ����ȡ����ע��
*/
void Bank::cancelAccount()
{
    int who;  //���ҵ����˺��������ж�Ӧ���±�
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            users[who].showBalance("���");   //��ʾ"���"���֣���ʾ���
            cout<<"ȷ��������y/n����";
            if(tolower(getchar())=='y')
            {
                users[who].showBalance("�����ɹ�������ȡ����Ϊ");
                users[who].balance=0;  //ȡ�������0
                users[who].status=2;  //״̬��Ϊע��
            }
            else
            {
                cout<<"��ȡ���˲���������ʧ�ܣ�"<<endl;
            }
            fflush(stdin);  //�����getchar()ʱ�ڼ��̻����е�����������Ӱ���������
        }
    }
}
 
/*
���ܣ����
˵������Ҫ��֤�˻����ڣ��Ҵ�������״̬
*/
void Bank::save()
{
    int who;
    double money;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        if(users[who].status==0)
        {
            users[who].showName();
            cout<<"������";
            cin>>money;
            users[who].balance+=money;
            users[who].showBalance("��������");
        }
        else if(users[who].status==1)
        {
            cout<<"���û����ڹ�ʧ״̬�����ʧ�ܣ�"<<endl;
        }
        else
        {
            cout<<"���û��Ѿ����������ʧ�ܣ�"<<endl;
        }
    }
    return;
}
 
/*
���ܣ�ȡ��
˵������Ҫ��֤�˻����ڣ��Ҵ�������״̬�����⣬���Ҫ�㹻ȡ
*/
void Bank::withdraw()
{
    int who;
    double money;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        if(users[who].isNormalUser())
        {
            users[who].showName();
            if(users[who].passwordIsRight())
            {
                cout<<"����ȡ��";
                cin>>money;
                if(money>users[who].balance)  //�ף�����͸֧
                {
                    cout<<"���㣬ȡ��ʧ�ܣ�"<<endl;
                }
                else
                {
                    users[who].balance-=money;
                    users[who].showBalance("ȡ��󣬻���");
                }
            }
        }
 
    }
    return;
}
 
/*
���ܣ���ѯ�˻�
˵������ʾ�˻���Ϣ
*/
void Bank::showAccount()
{
    int who;
    string sta[3]= {"����","��ʧ","�Ѿ�����"};
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            users[who].showBalance("���");
            cout<<"״̬��"<<sta[users[who].status]<<endl;
        }
    }
    return;
}
 
/*
���ܣ�ת��
˵������Ҫ��֤�����˻������ڣ��Ҵ�������״̬�����⣬ת���˻������Ҫ�㹻
*/
void Bank::transferAccounts()
{
    int whoout, whoin;
    double money;
    cout<<"ת����";
    whoout = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(whoout>=0)   //˵��id�˻�����
    {
        if(users[whoout].isNormalUser())
        {
            users[whoout].showName();
            if(users[whoout].passwordIsRight())
            {
                cout<<"����ת�˽�";
                cin>>money;
                if(money>users[whoout].balance)  //�ף�����͸֧
                {
                    cout<<"���㣬ת��ʧ�ܣ�"<<endl;
                }
                else
                {
                    cout<<"ת����";
                    whoin = getUser();  //�����˺Ų�ѯ�û��������û����±�
                    if(whoin>=0)   //˵��id�˻�����
                    {
                        if(users[whoin].isNormalUser())
                        {
                            users[whoout].balance-=money;
                            users[whoin].balance+=money;
                            users[whoout].showBalance("ת�˺�������");
                        }
                    }
                }
            }
        }
    }
    return;
}
 
/*
���ܣ���ʧ�˻�
*/
void Bank::reportLoss()
{
    int who;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            if(users[who].status==0)
            {
                users[who].status=1;
                cout<<"��ʧ�ɹ�"<<endl;
            }
            else if(users[who].status==1)
            {
                cout<<"���˻��Ѿ����ڹ�ʧ״̬"<<endl;
            }
            else
            {
                cout<<"���˻������������ܹ�ʧ"<<endl;
            }
        }
    }
    return;
}
 
/*
���ܣ������ʧ
*/
void Bank::cancelLoss()
{
    int who;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            if(users[who].status==0)
            {
                cout<<"���˻���������״̬������Ҫ�����ʧ"<<endl;
            }
            else if(users[who].status==1)
            {
                users[who].status=0;
                cout<<"�����ʧ�ɹ�"<<endl;
            }
            else
            {
                cout<<"���˻���������������Ч"<<endl;
            }
        }
    }
    return;
}
 
/*
���ܣ�������
*/
void Bank::updatePassword()
{
    int who;
    int iPass1, iPass2;
    who = getUser();  //�����˺Ų�ѯ�û��������û����±�
    if(who>=0)   //˵��id�˻�����
    {
        users[who].showName();
        if(users[who].passwordIsRight())
        {
            cout<<"�����룺";
            iPass1=inputPassword();  //��������1
            cout<<"ȷ�����룺";
            iPass2=inputPassword();  //��������2
            if(iPass1==iPass2)
            {
                users[who].password=iPass1;
                cout<<"�޸ĳɹ���"<<endl;
            }
            else
            {
                cout<<"�������벻ͬ���޸�ʧ�ܣ�"<<endl;
            }
        }
    }
    return;
}
 
/*
���ܣ������˺Ų�ѯ�û��������û��������е��±�
��ڲ�����Ҫ��ѯ�û����˺�
����ֵ��������û����ڣ����ظ��û��������е��±꣬���򣬷���һ��������-1��
˵����
  ���˺��Զ�������ʹ���˺����򣬱�ģ����ö��ֲ���
*/
int Bank::getUser()
{
    int id;
    cout<<"�˺ţ�";
    cin>>id;
    int index=-1;
    int low=0, high=N-1, mid;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(users[mid].account==id)
        {
            index=mid;
            break;   //�ҵ��ˣ������˳�ѭ��
        }
        else if (users[mid].account>id)
            high=mid-1;
        else
            low=mid+1;
    }
    if (index<0)
        cout<<"���û������ڣ����β���ʧ�ܣ�"<<endl;
    return index; //���ҵ�����ֵ��0~N-1�䣬���򣬱���-1
}