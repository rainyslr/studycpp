#include <iostream>
using namespace std;

#define TEST(pid) (cout<<para##pid<<endl);
#define TEST2(p) (cout<<#p<<endl);
#define TEST3(p) (cout<<p<<endl);

int main()
{
    int para3 = 30;
    int para2 = 20;
    TEST(2);    //<==>equal to "cout << para2 << endl" .输出结果为20;
    TEST(3);    //<==>equal to "cout << para3 << endl" .输出结果为30;
    // TEST(haha);报错，连接后等效于 "cout << parahaha << endl"。系统报错：use of undeclared identifier 'parahaha'
    TEST2("test2");    //等价于cout<<""test2""<<endl;，输出：“test2”
    TEST3("test2");    //等价于out<<test2"<<endl;输出：test2
    TEST2(para3);     //输出：para3
    TEST3(para3);     //输出：20
    TEST2(test)        //输出：test
    return 0;
}