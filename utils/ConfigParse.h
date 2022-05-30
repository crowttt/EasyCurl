#include <iostream>
#include <vector>

using namespace std;

class Parser{
public: 
    Parser(string);
    vector<vector<pair<string, string>>> parse();
    ~Parser() = default;
private:
    string confName;
};
