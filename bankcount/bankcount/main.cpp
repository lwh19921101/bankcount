#include <iostream>
#include "bank.h"
using namespace std;
/*��������*/
int main()
{
    cout<<"+----------------------+\n";
    cout<<"+    ��ӭ����CSDN����  +\n";
    cout<<"+----------------------+\n";
    Bank b;
    if (pass())
    {
        //Bank b;   //ԭ�ο��жഴ����һ��Bank�������һ�������Bug����ϸ���ͼ����桰ע����������
        b.work();
    }
    return 0;
}