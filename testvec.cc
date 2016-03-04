#include<iostream>
#include<vector>

//输出结果为：0，1，2.也就是说是在尾部插入的
using namespace std;
void print(const vector<int>& vec)
{
	vector<int>::const_iterator iter = vec.begin();
	for(;iter != vec.end(); ++ iter)
		cout << (*iter) << endl;
	return;
}

int main()
{
	vector<int> ivec;
	int i;
	for(i = 0;i < 3; ++ i)
		ivec.push_back(i);
	print(ivec);
	return 0;
}
