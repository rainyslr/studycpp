
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

class CKBaseClass  
{  
public:  
    CKBaseClass() {} 
    CKBaseClass(const string& str):m_content(str){}
    virtual ~CKBaseClass() {}  
    static void* createInstance() {return new CKBaseClass();}  
    // virtual void registProperty() {}  
    virtual void display() {
      cout << m_content << endl;
    } 
    // map<string, setValue> m_propertyMap ;  
    string m_content;
} ;  

#define DECLARE_CLASS(name)                                             \
  class name ## Class : public CKBaseClass                              \
  {                                                                     \
  public:                                                               \
    name ## Class ();                                                   \
    name ## Class (const string& str);                                  \
    virtual void display();                                             \
  };


  #define IMPLEMENT_CLASS(name)                                         \
  name ## Class::name ## Class ()                                       \
    : CKBaseClass("default") {}                                         \
  name ## Class::name ## Class (const string& str)                      \
    : CKBaseClass("str") {}                                             \
  void name ## Class::display () {                                      \
    cout << #name << "Class" <<  endl;                                  \
    CKBaseClass::display();                                             \
  }        

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


  DECLARE_CLASS(first)
  IMPLEMENT_CLASS(first)

  int main()
  {
    CKBaseClass* cla = new firstClass;
    // // 
    CKClassFactory::sharedClassFactory().registClass("ExampleClass", ExampleClass::createInstance);
    CKBaseClass* cla1 = (CKBaseClass*)CKClassFactory::sharedClassFactory().getClassByName("ExampleClass");
 
    cla->display();
    cla1->display();
    return 0;
  }                                                              