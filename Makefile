main_run:
	g++ -std=c++11 main.cc -o main -lpthread
	./main

loadtest_run:
	g++ -std=c++11 loadtest.cc -o loadtest -lpthread -lcurl
	./loadtest 10 10