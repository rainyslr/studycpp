#include <iostream>
#include <string>
using namespace std;
class App; //foward declaration

class ModuleA {
friend App;

public:
    void funca() {
        std::cout<<"funca of ModuleA"<<std::endl;
    }
    App *app;
    void (App::*appfun)();
    void pApp();
private:
    //ModuleA(App *app,) :app(app) {}
    ModuleA(App *tapp,void (App::*fun)()):app(tapp),appfun(fun){}
   // MoudleA() = delete; //diabled;
};



class ModuleB {
friend App;

public:
    void funcb();
    App *app;
    void (App::*appfun)();
private:
    //ModuleB(App *app) :app(app) {}
    ModuleB(App *app,void (App::*fun)()) :app(app),appfun(fun){}
   // MoudleB() = delete; //diabled;
};


class App {
public:
    App();
    App(int data);
    template<typename T>
    T* getAppPtr(const string& type);
    void getdata();
private:
    ModuleA* m_a;
    ModuleB* m_b;
    int m_i;
};

void ModuleA::pApp(){
 (app->*appfun)();
}
void ModuleB::funcb() {
    if(app) { // make sure not null
       // app->m_a->funca();
     cout <<"funcb"<<endl;
      
    }
    else cout<<"app is empty"<<endl;
     return ;
}
/*
App::App()
{
 m_i = 0;
 m_a = new ModuleA(this);
 m_b = new ModuleB(this);
}

App::App(int data)
{
 m_i = data;
 m_a = new ModuleA(this);
 m_b = new ModuleB(this);
}*/
App::App()
{
 m_i = 0;
 m_a = new ModuleA(this,&App::getdata);
 m_b = new ModuleB(this,&App::getdata);
}

App::App(int data)
{
 m_i = data;
m_a = new ModuleA(this,&App::getdata);
 m_b = new ModuleB(this,&App::getdata);
}


template<typename T>
T* App::getAppPtr(const string& type)
{
 if(type == "ModuleA"){
 return (T*)this->m_a;
 }
 else if(type == "ModuleB"){
 return (T*)(this->m_b);
 }
 else{
 cout << "type error"<<endl;   
 return 0;
 }
}

void  App::getdata()
{
 cout << "data of app is:"<<m_i<<endl;
 return ;
}

int main(){
    App app,a1(100);
   // app.m_b->funcb();
   ModuleA* ptra;
    ptra = (a1.getAppPtr<ModuleA>("ModuleA"));
   ModuleB* ptrb;
   ptrb = (app.getAppPtr<ModuleB>("ModuleB"));
   ptra->pApp();
    return 0;
}
