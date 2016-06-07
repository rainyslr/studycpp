#include   <string> 
#include   <map> 
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
   
#define DECLARE_CLASS(className)\  
string className##Name ;        \  
static CKDynamicClass* m_className##dc ;  
   
#define IMPLEMENT_CLASS(className)  \  
CKDynamicClass* className::m_className##dc = \  
new CKDynamicClass(#className, className::createInstance) ;  


class CKBaseClass ;
typedef void (*setValue)(CKBaseClass *t, void* c) ;  
   
class CKBaseClass  
{  
private:  
    DECLARE_CLASS(CKBaseClass)  
   
public:  
    CKBaseClass() {}  
    virtual ~CKBaseClass() {}  
    static void* createInstance() {return new CKBaseClass();}  
    virtual void registProperty() {}  
    virtual void display() {}  
    map<string, setValue> m_propertyMap ;  
} ;  
   
// #define SYNTHESIZE(classType, varType, varName)    \  
// public:                                             \  
// inline static void set##varName(CKBaseClass*cp, void*value){ \  
//     classType* tp = (classType*)cp ;                        \  
//     tp->varName = (varType)value ;                      \  
// }                                                       \  
// inline varType get##varName(void) const {                \  
//     return varName ;                                      \  
// }  
 IMPLEMENT_CLASS(CKBaseClass)  

class CKHelloClass
{
private:  
    DECLARE_CLASS(CKBaseClass)  
public:  
    // SYNTHESIZE(CKHelloClass, int*, m_pValue)  
   
    CKHelloClass() {}  
    virtual ~CKHelloClass(){}  
    static void* createInstance()  
    {  
        return new CKHelloClass() ;  
    }  
    // virtual void registProperty()  
    // {  
    //     m_propertyMap.inset(pair<string, setValue>("setm_pValue", setm_pValue)) ;  
    // }  
    virtual void display()  
    {  
        // cout << *getm_pValue() << endl ;  
        cout << "hello" << endl ;  
    }  
protected:  
    int *m_pValue ;  
   
} ;  
IMPLEMENT_CLASS(CKHelloClass)  

int main()
{


    CKBaseClass *pVar = (CKBaseClass*)CKClassFactory::sharedClassFactory().getClassByName("CKHelloClass") ;  
        // pVar->registProperty() ;  
       
        // int pValue = 123456 ;  
       
        // pVar->m_propertyMap["setm_pValue"](pVar, &pValue) ;  
        pVar->display() ; 
	return 0;
}