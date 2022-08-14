#include <iostream>
#include <thread>

#include "utils/ConfigParse.h"
#include "utils/EasyCurl.h"

using namespace std;

int main(int args, char** argv){
    Parser parser("work1.conf");
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
        // cout << "1111111111111" << endl;
        if(work["method"]=="POST")
            workers.push_back(thread(&EasyCurl::post, EasyCurl(), work));
        // else if(work["method"]=="GET")
        //     workers.push_back(thread(&EasyCurl::get, EasyCurl(), work));
    }
        
    for(auto& worker : workers)
        worker.join();

    return 0;
}