#include"crtp.h"
#include<iostream>
using namespace std;

void derived_1::static_implementation()
{
	cout << "static_implementation from derived_1"<<endl;
	return;
}
void derived_2::implementation()
{
	cout <<"implementation from derived_2"<<endl;
	return;
}
