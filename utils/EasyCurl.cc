#include<iostream>
#include<map>
#include <curl/curl.h>

#include "EasyCurl.h"

using namespace std;

void EasyCurl::post(map<string, string> job){
    // std::string file_name = std::string("./log/log_worker") += std::to_string(idx);
    // FILE* fp = fopen(file_name.c_str(), "w");

    struct curl_slist* headers = curl_slist_append(NULL, job["header"].c_str());
    auto curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, job["url"]);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, job["body"]);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    for(int i=0; i<stoi(job["workers"]); ++i){
        auto res = curl_easy_perform(curl);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}