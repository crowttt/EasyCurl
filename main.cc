#include <iostream>
#include <thread>

#include "utils/ConfigParse.h"
#include "utils/EasyCurl.h"

using namespace std;

int main(int args, char** argv){
    Parser parser("work_list.conf");
    auto works = parser.parse();
    vector<thread> workers;
    // for(auto& data : works){
    //     cout << data["workers"] << endl;
    //     cout << data["method"] << endl;
    //     cout << data["header"] << endl;
    //     cout << data["body"] << endl;
    //     cout << "----------------" << endl;
    // }

    for(auto& work : works){
        if(work["method"]=="POST"){
            for(int i=0; i < stoi(work["workers"]); ++i){
                workers.push_back(thread(&EasyCurl::post, EasyCurl(), work));
            }
        }
        else if(work["method"]=="GET"){
            for(int i=0; i < stoi(work["workers"]); ++i){
                workers.push_back(thread(&EasyCurl::get, EasyCurl(), work));
            }
        }
    }
        
    for(auto& worker : workers)
        worker.join();

    return 0;
}