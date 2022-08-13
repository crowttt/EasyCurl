main_run:
	g++ -std=c++11 main.cc -o main -lpthread
	./main

loadtest_run:
	g++ -std=c++11 loadtest.cc -o loadtest -lpthread -lcurl
	./loadtest 10 10

compile:
	g++ -std=c++11 -c utils/ConfigParse.cc
	g++ -std=c++11 -c utils/EasyCurl.cc -lcurl
	g++ -std=c++11 -c main.cc -lpthread
	g++ ConfigParse.o EasyCurl.o main.o -lcurl -lpthread