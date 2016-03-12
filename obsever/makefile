test-observer:test-observer.o observer.o subject.o
	g++ test-observer.o observer.o  subject.o -o test-observer
test-observer.o:test-observer.cc observer.h subject.h
	g++ -c test-observer.cc
observer.o:observer.cc observer.h
	g++ -c observer.cc
subject.o:subject.cc subject.h
	g++ -c subject.cc	
clean:
	rm *.o
