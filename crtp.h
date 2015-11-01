#include<iostream>
#include<stddef.h>
using namespace std;
template<class Derived>
struct base  
{  
	  void interface()  
		    {  
				cout <<"come from interface"<<endl;      
				// 转换为子类指针，编译期将绑定至子类方法  
				      static_cast<Derived*>(this)->implementation(); 
					    }  
	         
	    static void static_interface()  
			  {  
				        // 编译期将绑定至子类方法  
				  cout <<"come from static interface"<<endl;
				       Derived::static_implementation();  
						  }  

		  // 下面两个方法，默认实现可以存在，或者应该被继承子类的相同方法覆盖  
		  void implementation()
		  {
			  cout <<"base implementation"<<endl;
			  return;
		  }
		    static void static_implementation()
			{
				cout << "rfff"<<endl;
				return;
			}
};  

// The Curiously Recurring Template Pattern (CRTP)  
struct derived_1 : base<derived_1>  
{  
	  // 这里子类不实现，将使用父类的默认实现  
	 // void implementation();  

	  // 此方法将覆盖父类的方法  
	  static void static_implementation();  
};  
       
struct derived_2 : base<derived_2>  
{  
	  // 此方法将覆盖父类的方法  
	  void implementation();  

	    // 这里子类不实现，将使用父类的默认实现  
	  //  static void static_implementation();  
};  
