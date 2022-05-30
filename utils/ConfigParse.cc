#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "ConfigParse.h"

using namespace std;

Parser::Parser(string filename){
    confName = filename;
}

vector<vector<pair<string, string>>> Parser::parse(){
    // bool inSection = false;
    string line, sectionValue, sectionKey;
    vector<vector<pair<string, string>>> requests;
    fstream configFp;
    configFp.open(confName, ios::in);
    while(getline(configFp, line)){
        if(line == "") continue;
        else if(line.find("[work]") != string::npos){
            requests.push_back(vector<pair<string, string>>());
            continue;
        }
        else if(line.find("}") != string::npos){
            sectionValue.append(line);
            requests.back().push_back(pair<string, string>(sectionKey, sectionValue));
            sectionValue.clear();
            // inSection = false;
            continue;
        }
        else if(line.find("=") != string::npos){
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            size_t spliter = line.find('=');
            string key = line.substr(0, spliter);
            string value = line.erase(0, spliter + 1);

            if(value.find("{") != string::npos){
                sectionValue.append(value);
                sectionKey = key;
                // inSection = true;
            }
            else
                requests.back().push_back(pair<string, string>(key, value));
        }
        else{
            sectionValue.append(line);
        }

    }
    return requests;
}


// vector<ParserNode> Parser::parseTree(){
//     fstream configFp;
//     vector<string> configLines;
//     vector<ParserNode> forest;
//     stack<ParserNode> rootStack;
//     string line;
//     int level=0;
//     configFp.open(confName, ios::in);
    
//     if(!configFp.is_open()){
//         cout << "config file not exist" << endl;
//         exit();
//     }
//     while(getline(configFp, line)){
//         if(line == "") continue;
//         if(line.find("work{") != string::npos)
//             ParserNode root("work", NULL);
//             forest.push_back(root);
//             rootStack.push(forest.back());
        
//         else if(line.find("=") != string::npos){
//             line.erase(remove(line.begin(), line.end(), ' '), line.end());
//             size_t spliter = line.find('=');
//             string key = line.substr(0, spliter);
//             string value = line.erase(0, spliter + 1);

//             if(value.find("{") == string::npos)
//                 ParserNode newchild(key, value);
//                 ParserNode root = rootStack.top();
//                 root.children.push_back(newchild);
//             else:
//                 ParserNode newchild(key, NULL);
//                 ParserNode root = rootStack.top();
//                 root.children.push_back(newchild);
//                 rootStack.push(newchild);
//         }
//         else if(line.find("}") != string::npos) rootStack.pop();//level -= 1;
//     }
//     return forest;
// }

// void Parser::travelTree(vector<ParserNode>forest){
//     for(auto& tree : forest){
//         stack<ParserNode> rootStack;
//         rootStack.push(tree);
//         // for(auto& node : rootStack.pop().children){
//         while(!rootStack.empty()){
//             for(auto& node : rootStack.top().children){
//                 if(node.value != NULL)
//                     // fill data
//                     cout << node.key << " : " << node.value << endl;
//                 else:
//                     cout << node.key << endl << '\t';
//                     rootStack.push(node);
//             }
//         }
//     }
// }


// ParserNode::ParserNode(string key, string value){
//     key = key;
//     value = value;
// }

