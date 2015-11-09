#include <iostream>
#include <string>
using namespace std;
class App; //foward declaration

class ModuleA {
friend App;

public:
    ModuleA(App* papp):m_ptrapp(papp){}
    void funca(); 
private:
    template<typename T>
    T* GetModule(const string& type);
    App* m_ptrapp;
};

class ModuleB {
friend App;

public:
    ModuleB(App* papp):m_ptrapp(papp){}
    void funcb();
private:
    template<typename T>
    T* GetModule(const string& type);
    App* m_ptrapp;
};

class ModuleC {
friend App;

public:
    ModuleC(App* papp):m_ptrapp(papp){}
    void funcc() {
        std::cout<<"funca of Modulec"<<std::endl;
    }
private: 
    template<typename T>
    T* GetModule(const string& type);
    App* m_ptrapp;
};

class App {
 template<typename T>
 friend T* ModuleA::GetModule(const string& type);
template<typename T>
 friend T* ModuleB::GetModule(const string& type);
template<typename T>
 friend T* ModuleC::GetModule(const string& type);
public:
    App();
    App(int data);
    void GetData();
    void tryfuncb();
private:
    ModuleA* m_a;
    ModuleB* m_b;
    ModuleC* m_c;
    int m_i;
};
 void ModuleA::funca() {
        std::cout<<"funca of ModuleA"<<std::endl;
        m_ptrapp->GetData();
    }
 template<typename T>
 T* ModuleA::GetModule(const string& type){
 if(type == "ModuleA"){
 return (T*)(m_ptrapp->m_a);
 }
 else if(type == "ModuleB"){
 return (T*)(m_ptrapp->m_b);
 }
 else if(type == "ModuleC"){
 return (T*)(m_ptrapp->m_c);
 }
 else{
 cout << "type error"<<endl;   
 return 0;
 }
}

template<typename T>
 T* ModuleB::GetModule(const string& type){
 if(type == "ModuleA"){
 return (T*)(m_ptrapp->m_a);
 }
 else if(type == "ModuleB"){
 return (T*)(m_ptrapp->m_b);
 }
 else if(type == "ModuleC"){
 return (T*)(m_ptrapp->m_c);
 }
 else{
 cout << "type error"<<endl;   
 return 0;
 }
}

void ModuleB::funcb() {
    if(m_ptrapp) { // make sure not null
    ModuleA* tempa;
    tempa = GetModule<ModuleA>("ModuleA");
    tempa->funca();
    cout <<"funcb"<<endl; 
    }
    else cout<<"app is empty"<<endl;
     return ;
}

template<typename T>
 T* ModuleC::GetModule(const string& type){
 if(type == "ModuleA"){
 return (T*)(m_ptrapp->m_a);
 }
 else if(type == "ModuleB"){
 return (T*)(m_ptrapp->m_b);
 }
 else if(type == "ModuleC"){
 return (T*)(m_ptrapp->m_c);
 }
 else{
 cout << "type error"<<endl;   
 return 0;
 }
}
App::App()
{
 m_i = 0;
 m_a = new ModuleA(this);
 m_b = new ModuleB(this);
 m_c = new ModuleC(this);
}

App::App(int data)
{
 m_i = data;
 m_a = new ModuleA(this);
 m_b = new ModuleB(this);
 m_c = new ModuleC(this);
}

void App::tryfuncb()
{
  m_b->funcb();
}

void App::GetData()
{
 cout << m_i<<endl;
 return;
}


int main(){
    App app,a1(100);
    a1.tryfuncb();
    return 0;
}
