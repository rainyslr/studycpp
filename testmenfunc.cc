#include <iostream>
#include <string>
using namespace std;

class App {
public:
    App();
    App(int data);
    void getdata();
private:
    int m_i;
};

App::App()
{
 m_i = 0;
}
App::App(int data)
{
 m_i = data;
}

void  App::getdata()
{
 cout << "data of app is:"<<m_i<<endl;
 return ;
}

int main(){
    App app,a1(100);
    void(App::*ptrfun)(void) = 0;
    //a1.getdata();



   ptrfun = &App::getdata;
   (a1.*ptrfun)();
    return 0;
}
