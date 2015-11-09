#include<iostream>
#include<math.h>
#include<sys/times.h>
#include<string>
#include<unistd.h>
#include<stdio.h>
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
#define RDTSC(low, high)  asm volatile("rdtsc" : "=a" (low), "=d" (high))
#define RDTSC_L(low)      asm volatile("rdtsc" : "=a" (low) : : "edx")
#define RDTSC_LL(val)     asm volatile("rdtsc" : "=A" (val))
void AccessCounter(unsigned *hi, unsigned *lo){
     asm volatile("rdtsc; movl %%edx,%0; movl %%eax, %1"
    : "=r" (*hi), "=r" (*lo)
     : /* No input */
     : "%edx", "%eax");
 }
 
 typedef unsigned long long cycle_t;
 /* Record the current value of the cycle counter. */
 inline cycle_t CurrentCycle(void){
     cycle_t tRdtscRes;
     asm volatile("rdtsc" : "=A" (tRdtscRes));
     return tRdtscRes;
 }
 inline cycle_t CurrentCycle2(void){
     unsigned hi, lo;  
     asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));  
     return ((cycle_t)lo) | (((cycle_t)hi)<<32);  
 }

 unsigned gCpuFreqInHz = 0; //Record Cpu Frequency for later use
 void CalcCpuFreq2(void){
     cycle_t tStart = CurrentCycle();
     sleep(1); //调用sleep时，进程挂起直到1秒睡眠时间到达。这期间经过的周期是被其他进程执行的。
     cycle_t tEnd = CurrentCycle();
     gCpuFreqInHz = tEnd - tStart;
     printf("CPU Frequency: %dMHz\n", gCpuFreqInHz/1000000);
 }

 void RdtscTiming(void){
     CalcCpuFreq2();
     cycle_t tStartCyc = CurrentCycle();
     TimingFunc();
     cycle_t tEndCyc = CurrentCycle();
     cout << "tStartCyc:"<<tStartCyc<<endl;
     cout << "tEndCyc:"<<tEndCyc<<endl;
     cout << "gCpuFreqInHz:"<<gCpuFreqInHz<<endl;
     double fCostTime = (double)(tEndCyc-tStartCyc) /gCpuFreqInHz;
     printf("[rdtsc]Cost Time = %fSec\n", fCostTime);
 }
//测试说明
//第一次运行时返回１秒多，但是如果很频繁的运行第二次，返回结果就是错的（tEndCyc>tStartCyc)
int main()
{
	RdtscTiming();
}
