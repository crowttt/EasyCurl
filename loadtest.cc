#include <iostream>
#include <thread>
#include <vector>
#include <curl/curl.h>
#include <string>
#include <time.h>


std::vector<double> response;

class job {
public:
    void operator()(int idx, int times)
    {
        clock_t timer;
        std::string file_name = std::string("./log/log_worker") += std::to_string(idx);
        FILE* fp = fopen(file_name.c_str(), "w");

        struct curl_slist* headers = curl_slist_append(NULL, "content-type: application/json");
        auto curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_URL, "https://stuapply.diploma.ncku.edu.tw/apply/record");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"stu_id\":\"P76104142\"}");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        for(int i=0;i<times;++i){
            timer = clock();
            auto res = curl_easy_perform(curl);
            response[idx] = response[idx] + (clock() -timer);
        }
        response[idx] /= times;
        response[idx] /= CLOCKS_PER_SEC;

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return;
    }
};

int main(int argc, char** argv){

    clock_t timer = clock();;

    int n_worker = atoi(argv[1]);
    int n_job = atoi(argv[2]);
    std::vector<std::thread> workers;

    response = std::vector<double>(n_worker, 0.0); 
    for(int i=0; i<n_worker; ++i){
        workers.push_back(std::thread(job(), i, n_job));
    }

    for(auto& worker : workers)
        worker.join();

    timer = clock() - timer;

    for(auto& res : response)
        std::cout << res << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << (double)timer/CLOCKS_PER_SEC << std::endl;

    return 0;
}