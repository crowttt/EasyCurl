config:
	g++ -std=c++11 -c utils/ConfigParse.cc
	g++ -std=c++11 -c main.cc -lpthread
	g++ ConfigParse.o main.o -lcurl -lpthread

all:
	g++ -std=c++11 -c utils/ConfigParse.cc
	g++ -std=c++11 -c utils/EasyCurl.cc -lcurl
	g++ -std=c++11 -c main.cc -lpthread
	g++ ConfigParse.o EasyCurl.o main.o -lcurl -lpthread -o loadingTest

clean:
	rm *.o
	rm loadingTest