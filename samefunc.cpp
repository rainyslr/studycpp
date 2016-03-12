/*this is use for testing what will happen when  subclass has the same function with its parent.*/
#include<iostream>
using namespace std;
class par
{
	public:
	void fun(){ cout <<"parent's fun"<<endl;
		return;
	}
};

class chi:public par
{
	public:
		void fun(){ cout <<"child's fun"<<endl;
			return;
		}
};

int main()
{
	par* ppar = new par;
	chi ch;
	ch.fun();
	ppar->fun();
	ppar = &ch;
	ppar->fun();
	return 0;
}
