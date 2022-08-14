#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include "ConfigParse.h"

using namespace std;

Parser::Parser(string filename){
    confName = filename;
}

vector<map<string, string>> Parser::parse(){
    // bool inSection = false;
    string line, sectionValue, sectionKey;
    vector<vector<pair<string, string>>> requests;
    fstream configFp;
    configFp.open(confName, ios::in);
    while(getline(configFp, line)){
        line.erase(remove_if(line.begin(), line.end(), [](unsigned char x){return std::isspace(x);}), line.end());
        if(line == "") continue;
        else if(line.find("[work]") != string::npos){
            requests.push_back(vector<pair<string, string>>());
        }
        else if(line.find("-") != string::npos){
            size_t spliter = line.find('-');
            string value = line.erase(0, spliter + 1);
            requests.back().back().second += value + string(",");
        }
        else if(line.find(":") != string::npos){
            size_t spliter = line.find(':');
            string key = line.substr(0, spliter);
            string value = line.erase(0, spliter + 1);
            requests.back().push_back(pair<string, string>(key, value));
        }
    }

    vector<map<string, string>> works;
    for(auto& request : requests){
        works.push_back(generateWork(request));
    }
    return works;
}

map<string, string> Parser::generateWork(vector<pair<string, string>> request){
    map<string, string> work;
    for(auto& ele : request){
        if(ele.first.compare("body") == 0){
            ele.second.erase(ele.second.size()-1,1);
            ele.second = "{" + ele.second + "}";
        }
        work[ele.first] = ele.second;
    }
    return work;
}
