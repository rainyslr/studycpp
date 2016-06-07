
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
  class name : public CKBaseClass                                       \
  {                                                                     \
  public:                                                               \
    name ();                                                            \
    name (const string& str);                                           \
    static void* createInstance();                                      \
    static CKDynamicClass* m_name##ClassDc ;                            \
    virtual void display();                                             \
  };


  #define IMPLEMENT_CLASS(name)                                         \
  name::name ()                                                         \
    : CKBaseClass("default") {}                                         \
  name::name (const string& str)                                        \
    : CKBaseClass("str") {}                                             \
  void* name::createInstance() {                                        \
     return new name();                                                 \
  }                                                                     \
  void name::display () {                                               \
    cout << "ClassName:" << #name <<  endl;                             \
  }                                                                     \
  CKDynamicClass* name::m_name##ClassDc = new CKDynamicClass(#name, name::createInstance) ;

  // 不知道为什么，假如有一个类ExampleClass，下面这句话不能放在在这里，报错：expected function body after function declarator
  // CKClassFactory::sharedClassFactory().registClass("ExampleClass", ExampleClass::createInstance);

  DECLARE_CLASS(first)
  IMPLEMENT_CLASS(first)

  DECLARE_CLASS(Second)
  IMPLEMENT_CLASS(Second)

  int main()
  {
    CKBaseClass* cla2 = (Second*)CKClassFactory::sharedClassFactory().getClassByName("Second");
    cla2->display();
    cla2 = (CKBaseClass*)CKClassFactory::sharedClassFactory().getClassByName("first");
    cla2->display();
    return 0;
  }                                                              