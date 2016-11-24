
#ifndef BANK_H_INCLUDEDINCLUDED
#define BANK_H_INCLUDEDINCLUDED
#include <cstring>
using namespace std;
const int upNum=2000; //ϵͳ������ɵ��û���
class Bank;
class User
{
public:
    void setUser(int acc, string nam, int pw, double bal,int sta);
    void showName();
    void showBalance(string prompt); //��ʾ��ǰ�������ʾ��prompt
    bool passwordIsRight();   //У�����룬�����������ȷ�򷵻�true
    bool isNormalUser(); //��ȡ�ת�ʵȹ��ܣ���Ҫ�˻�����������̬����������״̬ʱ����true���������η���false����ʾ
    friend class Bank;   //��Bank����Ϊ��Ԫ�࣬������������ݳ�Ա
private:
    int account; //�˺�
    int password;  //����
    string name;   //�û���
    double balance;  //�˻����
    int status;  //״̬ 0-����  1-��ʧ  2-����
};
 
class Bank
{
public:
    Bank();  //��ʼǰ���ļ��ж����ݣ�����������
    ~Bank();   //�������ǰ���������е�����д�뵽�ļ���
    void work();  //ҵ������
    void openAccount(); //����
    void cancelAccount();  //ע���˻�
    void save();   //���
    void withdraw();   //ȡ��
    void showAccount(); //��ѯ���
    void transferAccounts();  //ת��
    void reportLoss();  //��ʧ
    void cancelLoss();  //�����ʧ
    void updatePassword();   //��������
    int getUser();  //�����˺Ų�ѯ�û��������û��ڶ��������е��±�
private:
    int N;  //ʵ�ʵ��û���Ŀ
    User users[upNum];  //User���飬�Ŀռ䰡���Ľ�������1.����ָ�����飻2. ��̬���飻3. ����
};
 
int pass();  //ҵ��Ա��¼
int chooseInMenu(); //��ʾ�˵�����ҵ��Աѡ��
int inputPassword();   //���ؼ������������
 
#endif // BANK_H_INCLUDEDINCLUDED