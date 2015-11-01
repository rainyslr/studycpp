#include<iostream>
using namespace std;
class Singleton
{

 private:

  Singleton();//注意:构造方法私有

  virtual ~Singleton();

  static Singleton *instance;//惟一实例

  int var;

 public:

  static Singleton *GetInstance();//工厂方法(用来获得实例)

  int getVar();

  void setVar(int);

};

Singleton::Singleton() //构造方法实现

{

 this->var=20;

 cout<<"Singleton Constructor"<<endl;

}

Singleton::~Singleton()

{

 if(instance!=NULL)

 {

  delete instance;

 }

}

Singleton *Singleton::instance=NULL;//初始化静态成员



Singleton *Singleton::GetInstance()

{

 if(instance==NULL)

 {

  instance=new Singleton();

 }

 return instance;

}

int Singleton::getVar()

{

 return(this->var);

}

void Singleton::setVar(int var)

{

 this->var=var;

}

int main(int argc,char **argv)

{

  Singleton *ton1=Singleton::GetInstance();

  Singleton *ton2=Singleton::GetInstance();

  cout<<"ton1 var="<<ton1->getVar()<<endl;      

  ton1->setVar(150);

  cout<<"ton2 var="<<ton2->getVar()<<endl;     

  return 0;

}

