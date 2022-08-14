#include<iostream>
#include<map>
#include <curl/curl.h>

#include "EasyCurl.h"

using namespace std;

void EasyCurl::post(map<string, string> job){
    // std::string file_name = std::string("./log/log_worker") += std::to_string(idx);
    // FILE* fp = fopen(file_name.c_str(), "w");
    long http_code = 0;
    string readBuffer;

    struct curl_slist* headers = curl_slist_append(NULL, "content-type:application/json");
    auto curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, job["url"].c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, job["body"].c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);


    for(int i=0; i<stoi(job["workers"]); ++i){
        auto res = curl_easy_perform(curl);
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
        cout << http_code << endl;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}