#include<iostream>
#include<map>
#include<string>
using namespace std;
int main()
{
	map<string,int> vmap;
	pair<map<string,int>::iterator,bool>ret;
	int i = 0;
	string word;
	for(;i < 4;i ++){
		cin >> word;
		ret = vmap.insert(make_pair(word,1));
		cout << "for word "<< word<<"insert flag is:"<< ret.second<<endl;
	}
}
