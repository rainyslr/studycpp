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
#define TIME_ELAPSED(codeToTime) do{ \
      struct timeval beginTime, endTime; \
      gettimeofday(&beginTime, NULL); \
      {codeToTime;} \
      gettimeofday(&endTime, NULL); \
      long secTime  = endTime.tv_sec - beginTime.tv_sec; \
      long usecTime = endTime.tv_usec - beginTime.tv_usec; \
      printf("[%s(%d)]Elapsed Time: SecTime = %lds, UsecTime = %ldus!\n", __FUNCTION__, __LINE__, secTime, usecTime); \
 }while(0)
 
 void GetTimeofDayTiming(void){
     struct timeval tBeginTime, tEndTime;
     gettimeofday(&tBeginTime, NULL);
     TimingFunc();
     gettimeofday(&tEndTime, NULL);
    float fCostTime = 1000000*(tEndTime.tv_sec-tBeginTime.tv_sec)+ //先减后加避免溢出！
                       (tEndTime.tv_usec-tBeginTime.tv_usec);
     fCostTime /= 1000000;
     printf("[gettimeofday]Cost Time = %fSec\n", fCostTime);
//TestGetTimeOfToday
 }
int main()
{
	GetTimeofDayTiming();
}
