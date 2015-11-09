#include<iostream>
#include<math.h>
#include<sys/times.h>
#include<string>
#include<unistd.h>
using namespace std;
#define TIME_LOOP_NUM 1000000*20
void TimingFunc(void){
	unsigned int i = 0;
	double y = 0.0;
	for(;i < TIME_LOOP_NUM;i ++)
		y = sin((double)i);
}
void print(const string name,const tms& cti)
{
	cout << "value of "<< name << endl;
	cout << "tms_utime="<< cti.tms_utime<<endl;
	cout << "tms_stime="<<cti.tms_stime<<endl;
	cout << "tms_cutime="<<cti.tms_cutime<<endl;
	cout << "tms_cstime="<<cti.tms_cstime<<endl;
	return;
}
//该函数执行后，tsend.tms_utime = 128,ftime = 1.28。输出sysconf(_SC_CLK_TCK)为100；
void timestest(void){
	clock_t tBeginTime,tEndTime;
	struct tms tsstart,tsend;
	tBeginTime = times(&tsstart);
	TimingFunc();
	tEndTime = times(&tsend);
	//計算程序花費的秒數
	double ftime = (double)(tEndTime - tBeginTime)/sysconf(_SC_CLK_TCK);
	print("tsstart",tsstart);
	print("tsend",tsend);
	cout<<"total use time:"<<ftime<<endl;
	cout << "_SC_CLK_TCK:" << sysconf(_SC_CLK_TCK) << endl;
	return;
}
int main()
{
	timestest();
}
