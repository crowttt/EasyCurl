#include <iostream>
#include <thread>

#include "utils/ConfigParse.h"
#include "utils/EasyCurl.h"

using namespace std;

int main(int args, char** argv){
    Parser parser("work1.conf");
    auto works = parser.parse();
    vector<thread> workers;
    // for(auto& data : datas){
    //     cout << data["workers"] << endl;
    // }

    for(auto& work : works){
        if(work["method"]=="POST")
            workers.push_back(thread(&EasyCurl::post, EasyCurl(), work));
        // else if(work["method"]=="GET")
        //     workers.push_back(thread(&EasyCurl::get, EasyCurl(), work));
    }
        
    
    return 0;
}