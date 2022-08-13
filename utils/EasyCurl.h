#include<iostream>
#include<map>


using namespace std;

class EasyCurl{
public:
    EasyCurl() = default;
    ~EasyCurl() = default;
    void post(map<string, string>);
    void get(map<string, string>);
};
