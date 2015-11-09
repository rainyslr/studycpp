#include<iostream>
using namespace std;

enum EventType{
    EV_EL_EVENT		= 1,  //!< event that come from Ev's electricity level.
    PS_EL_EVENT		= 2,  //!< event that come from PS's electricity level.
    PD_EL_EVENT 	= 3,  //!< event that come from PD's electricity level.
    ESDM_EL_EVENT	= 4   //!< event that come from ESDM's electricity level.
  };
//为什么想把EventType放在EventMessage类里面就不行了呢。
class EventMessage
{ 
public: 
 EventType GetType(void)const;
 EventMessage(int type);
private: 
 EventType m_type;
};
EventMessage::EventMessage(int type):m_type((EventType)type){}
EventType EventMessage::GetType()const
{
 return m_type;
}
int main()
{
 EventMessage ems(4);
 cout <<"EventType is:"<<ems.GetType()<<endl;
 return 0;
}


