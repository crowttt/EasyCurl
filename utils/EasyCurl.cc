#include<iostream>
#include<map>
#include <string> 
#include <curl/curl.h>
#include <sstream>

#include "EasyCurl.h"

using namespace std;

void EasyCurl::post(map<string, string> job){
    long http_code = 0;
    auto curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, job["url"].c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, job["body"].c_str());

    size_t pos = 0;
    string token;
    struct curl_slist* headers = NULL;
    while ((pos = job["header"].find(',')) != std::string::npos) {
        token = job["header"].substr(0, pos);
        job["header"].erase(0, pos + 1);
        headers = curl_slist_append(headers, token.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    auto res = curl_easy_perform(curl);
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    cout << http_code << endl;

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}


void EasyCurl::get(map<string, string> job){
    long http_code = 0;
    auto curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, job["url"].c_str());

    size_t pos = 0;
    string token;
    struct curl_slist* headers = NULL;
    while ((pos = job["header"].find(',')) != std::string::npos) {
        token = job["header"].substr(0, pos);
        job["header"].erase(0, pos + 1);
        headers = curl_slist_append(headers, token.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    auto res = curl_easy_perform(curl);
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
    cout << http_code << endl;

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}
