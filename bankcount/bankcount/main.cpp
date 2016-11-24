#include <iostream>
#include "bank.h"
using namespace std;
/*主函数：*/
int main()
{
    cout<<"+----------------------+\n";
    cout<<"+    欢迎光临CSDN银行  +\n";
    cout<<"+----------------------+\n";
    Bank b;
    if (pass())
    {
        //Bank b;   //原参考中多创建了一个Bank对象，造成一个诡异的Bug，详细解释见下面“注”处的链接
        b.work();
    }
    return 0;
}