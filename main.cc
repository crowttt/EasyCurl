#include <iostream>

#include "utils/ConfigParse.h"

int main(int args, char** argv){
    Parser parser("work1.conf");
    auto works = parser.parse();
    // for(auto& data : datas){
    //     for(auto& info : data){
    //         cout << info.first << " | " << info.second << endl;
    //     }
    // }
    for(auto& work : works){
        work
        /*
        std::thread(curl.post(), work));
        */
    }
    return 0;
}