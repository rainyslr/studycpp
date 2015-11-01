~/Study/cppexcute/crtp:main_crtp.o crtp.o
	g++ main_crtp.o crtp.o -o ~/Study/cppexcute/crtp
main_crtp.o:main_crtp.cpp crtp.h
	g++ -c main_crtp.cpp
crtp.o:crtp.cpp crtp.h
	g++ -c crtp.cpp
clean:
	rm *.o
