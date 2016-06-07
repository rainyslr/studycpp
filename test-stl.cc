#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

void PrintVec(const vector<int>& vec)
{
	vector<int>::const_iterator iter = vec.begin();
	for(;iter != vec.end(); ++ iter)
		cout << (*iter) << " ";
	cout << endl;
	return;
}

void PrintList(const list<int>& li)
{
	list<int>::const_iterator iter = li.begin();
	for(;iter != li.end(); ++ iter)
		cout << (*iter) << " ";
	cout << endl;
	return;
}

void PrintDeque(const deque<int>& deq)
{
	deque<int>::const_iterator iter = deq.begin();
	for(;iter != deq.end(); ++ iter)
		cout << (*iter) << " ";
	cout << endl;
	return;
}

//同理的这个函数也是值传递，调用该函数传入的形参并不会发生改变
void PrintStack(stack<int> sta)
{
	while (sta.empty() == false) {
				cout << sta.top() << " ";
				sta.pop();
			}
		cout << endl;
}

void PrintStackBaseVec(stack<int,vector<int> > sta)
{
	while (sta.empty() == false) {
				cout << sta.top() << " ";
				sta.pop();
			}
		cout << endl;
}

void PrintQueue(queue<int> que)
{
	while (que.empty() == false) {
				cout << que.front() << " ";
				que.pop();
			}
		cout << endl;
}

void TestStack()
{
	 const stack<int>::size_type stk_size = 10;
		 stack<int> intStack; // empty stack
		 int ix = 0;
		 while (intStack.size() != stk_size)
			intStack.push(ix++); 
			while (intStack.empty() == false) {
				cout << intStack.top() << " ";
				intStack.pop();
			}
}



int main()
{
	vector<int> ivec;
	int i;
	for(i = 0;i < 3; ++ i)
		ivec.push_back(i);
	std::vector<int>::iterator iter  = ivec.begin();
	ivec.insert(iter,100);//此时list中的元素为，50，100，0，2，4，可以这么理解，未插入100前，iter指向容器开始元素位置
	// （假设为地址A1，也就是节点0的地址）。vector使用的是连续的内存，插入100，实际上是将所有元素后挪，然后＊A1 ＝ 100；插入50时同理。
	ivec.insert(iter,50);
	PrintVec(ivec);
	// cout << "front:" << ivec.front() << " back:" << ivec.back() << endl;

	// list<int> ilist;
	// for(i = 0;i < 3; ++ i)
	// ilist.push_back(i * 2);
	// // ilist.push_front(100);
	// list<int>::iterator liter = ilist.begin();
	// ilist.insert(liter,100);
	// ilist.insert(liter,50);//此时list中的元素为，100，50，0，2，4，可以这么理解，未插入100前，iter指向容器开始元素位置
	// // 也就是节点0的位置。list相当于是一个链表，插入节点100后。iter指向的位置仍然不变，所以50是在100和0的中间
	// PrintList(ilist);
	// cout << "front:" << ilist.front() << " back:" << ilist.back() << endl;

	deque<int> ideq;
	for(i = 0;i < 3; ++ i)
	ideq.push_back(i * 3);
	ideq.push_front(100);
	// deque<int>::iterator qiter = ideq.begin();
	// ideq.insert(qiter,100);
	// //这一句会不确定性地出现段错误，虽然我也不知到为什么，可能和deque同时支持随机访问与两端操作有关吧
	// // ideq.insert(qiter,50);
	// // cout << *qiter << endl;
	PrintDeque(ideq);
	// 	cout << "front:" << ideq.front() << " back:" << ideq.back() << endl;

	// deque<int> empty_deq;
	// // cout << empty_deq.front();段错误
	// //fill_n(ivec,3,9);
	// fill(ivec.begin(),ivec.end(),9);
	// fill_n(back_inserter(ivec),2,123);
	// PrintVec(ivec);

	// queue<int> ique;
	// for(i = 0;i < 3; ++ i)
	// ique.push_back(i);
	// PrintList(ique);

	// TestStack();
	const stack<int>::size_type stk_size = 10;
		stack<int> intStack; // empty stack
		int ix = 0;
		while (intStack.size() != stk_size)
			intStack.push(ix++); 
		 PrintStack(intStack);
		 stack<int,std::vector<int> > nstack(ivec);//将ivec中从begin开始的元素依次压入栈中。所以最后栈顶元素是2.
		 PrintStackBaseVec(nstack);//stack<int,std::vector<int> > 和stack<int>并不兼容，后者的默认实现用的是dequeue

		 queue<int> int_queue(ideq);
		 PrintQueue(int_queue);

	return 0;
}
