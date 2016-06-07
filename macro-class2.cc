
#include <string>
#include <map>
#include   <iostream>
using namespace std;

typedef void* (*createClass)(void) ; 

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
    : CKBaseClass("str") {}                                                \
  void name ## Class::display () {                             \
    cout << #name << "Class" <<  endl;                                               \
    CKBaseClass::display();                                             \
  }        

  DECLARE_CLASS(first)
  IMPLEMENT_CLASS(first)

  int main()
  {
    CKBaseClass* cla = new firstClass;
    // // CKBaseClass* cla = (CKBaseClass*)(firstClass::createInstance());

    cla->display();
    return 0;
  }                                                              