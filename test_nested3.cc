#include <iostream>
#include <string>
using namespace std;
class App; //foward declaration

class ModuleA {
friend App;

public:
    void funca();
   ~ModuleA(){cout <<"destructor ModuleA"<<endl;}
    App *app;
    ModuleA(App *app) :app(app) {}
};



class ModuleB {
friend App;

public:
    ~ModuleB(){cout <<"destructor ModuleB"<<endl;}
    void funcb();
    App *app;
    void (App::*appfun)();
    ModuleB(App *app) :app(app) {}
};


class App {
public:
    App();
    ~App(){
    delete m_a;
    delete m_b;
    }
    App(int data);
    void getdata();
    ModuleA* m_a;
    ModuleB* m_b;
    int m_i;
};
void ModuleA::funca()
 {
        std::cout<<"funca of ModuleA"<<std::endl;
        app->m_b->funcb();
    }
void ModuleB::funcb() {
    if(app) { // make sure not null
     app->getdata();
     cout <<"funcb"<<endl;
      
    }
    else cout<<"app is empty"<<endl;
     return ;
}


App::App()
{
 m_i = 0;
 //(m_a->app) = this;
 //(m_b->app) = this;
 m_a = new ModuleA(this);
 m_b = new ModuleB(this);
}

App::App(int data)
{
 m_i = data;
// (m_a->app) = this;
 //(m_b->app) = this;
 m_a = new ModuleA(this);
 m_b = new ModuleB(this);
}


void  App::getdata()
{
 cout << "data of app is:"<<m_i<<endl;
 return ;
}

int main(){
  // ModuleA ma;
    App a1(100);
   // app.m_b->funcb();
   a1.m_a->funca();
    return 0;
}
