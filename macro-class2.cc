
#include <string>
#include <map>
#include   <iostream>
using namespace std;

typedef void* (*createClass)(void) ; 

class CKClassFactory  
{  
public:  
    CKClassFactory(){}
   
    virtual ~CKClassFactory(){}
   
    void* getClassByName(string className) ;  
   
    void registClass(string name, createClass method) ;  
   
    static CKClassFactory& sharedClassFactory() ;  
   
private:  
    map<string, createClass> m_classMap ;  
} ;  

void* CKClassFactory::getClassByName(string className)  
{  
    map<string, createClass>::const_iterator iter ;  
   
    iter = m_classMap.find(className) ;  
    if ( iter == m_classMap.end() )  
        return NULL ;  
    else  
        return iter->second() ;  
}  
   
void CKClassFactory::registClass(string name, createClass method)  
{  
    m_classMap.insert(pair<string, createClass>(name, method)) ;  
}  
   
CKClassFactory& CKClassFactory::sharedClassFactory()  
{  
    static CKClassFactory _sharedClassFactory ;  
    return _sharedClassFactory ;  
}  

class CKDynamicClass  
{  
public:  
    CKDynamicClass(string name, createClass method)  
    {  
        CKClassFactory::sharedClassFactory().registClass(name, method) ;  
    }  
} ;  

class CKBaseClass  
{  
public:  
    CKBaseClass() {} 
    CKBaseClass(const string& str):m_content(str){}
    virtual ~CKBaseClass() {}  
    static void* createInstance() {return new CKBaseClass();}  
    // virtual void registProperty() {}  
    virtual void display() {
      cout << "CKBaseClass" << endl;
    } 
    static CKDynamicClass* m_CKBaseClassDc ;//注册类实例，在初始化该类变量时实现CKBaseClass的注册。
    // map<string, setValue> m_propertyMap ;  
    string m_content;
} ;  

//初始化类变量
CKDynamicClass* CKBaseClass::m_CKBaseClassDc = new CKDynamicClass("CKBaseClass", CKBaseClass::createInstance) ;  

#define DECLARE_CLASS(name)                                             \
  class name ## Class : public CKBaseClass                              \
  {                                                                     \
  public:                                                               \
    name ## Class ();                                                   \
    name ## Class (const string& str);                                  \
    static void* createInstance();                                      \
    static CKDynamicClass* m_name##ClassDc ;                            \
    virtual void display();                                             \
  };


  #define IMPLEMENT_CLASS(name)                                         \
  name ## Class::name ## Class ()                                       \
    : CKBaseClass("default") {}                                         \
  name ## Class::name ## Class (const string& str)                      \
    : CKBaseClass("str") {}                                             \
  void* name ## Class::createInstance() {                               \
     return new name ## Class();                                        \
  }                                                                     \
  void name ## Class::display () {                                      \
    cout << #name << "Class" <<  endl;                                  \
  }                                                                     \
  CKDynamicClass* name ## Class::m_name##ClassDc = new CKDynamicClass(#name"Class", name ## Class::createInstance) ;

  class ExampleClass : public  CKBaseClass
  {  
  private:  
      DECLARE_CLASS(ExampleClass)  
     
  public:  
      ExampleClass() {}  
      virtual ~ExampleClass() {}  
      static void* createInstance();
      virtual void registProperty() {}  
      virtual void display() {
        cout << "ExampleClass" << endl;
      }  
  } ;  

  void* ExampleClass::createInstance()
   {return new ExampleClass();}  


  // DECLARE_CLASS(first)
  // IMPLEMENT_CLASS(first)
  // 不知道为什么，下面这句话不能发在这里，报错：expected function body after function declarator
  // CKClassFactory::sharedClassFactory().registClass("ExampleClass", ExampleClass::createInstance);
  DECLARE_CLASS(Second)
  IMPLEMENT_CLASS(Second)

  int main()
  {
    // CKBaseClass* cla = new firstClass;
    // // 
    // CKClassFactory::sharedClassFactory().registClass("ExampleClass", ExampleClass::createInstance);
    // CKBaseClass* cla1 = (CKBaseClass*)CKClassFactory::sharedClassFactory().getClassByName("ExampleClass");
    

    // CKBaseClass* cla2 = (CKBaseClass*)CKClassFactory::sharedClassFactory().getClassByName("CKBaseClass");

    // cla->display();
    // cla1->display();
    // cla2->display();


    CKBaseClass* cla2 = (SecondClass*)CKClassFactory::sharedClassFactory().getClassByName("SecondClass");
    cla2->display();
    return 0;
  }                                                              