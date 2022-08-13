#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Parser{
public: 
    Parser(string);
    vector<map<string, string>> parse();
    ~Parser() = default;
private:
    string confName;
    map<string, string> generateWork(vector<pair<string, string>>);
};
