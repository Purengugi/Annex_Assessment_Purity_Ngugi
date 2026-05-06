#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

static size_t writeCallback(void* contents, size_t size, size_t nmemb, string* out) {
    out->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

static string fetchPage(int pageNumber) {
    CURL* curl = curl_easy_init();
    if (!curl)
        throw runtime_error("curl_easy_init() failed");

    string url = "https://jsonmock.hackerrank.com/api/articles?page=" + to_string(pageNumber);
    string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        throw runtime_error(string("curl error: ") + curl_easy_strerror(res));

    return response;
}

struct Article {
    string name;
    int    numComments;
};

static void parsePage(const json& data, vector<Article>& articles) {
    for (const auto& item : data) {
        string name;

        // prefer title, fall back to story_title, skip if both null
        if (!item["title"].is_null()) {
            name = item["title"].get<string>();
        } else if (!item["story_title"].is_null()) {
            name = item["story_title"].get<string>();
        } else {
            continue;
        }

        // treat null num_comments as 0
        int comments = 0;
        if (item.contains("num_comments") && !item["num_comments"].is_null())
            comments = item["num_comments"].get<int>();

        articles.push_back({name, comments});
    }
}

vector<string> topArticles(int limit) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    vector<Article> articles;

    // fetch first page to get total_pages
    string raw       = fetchPage(1);
    json   firstPage = json::parse(raw);

    int totalPages = firstPage["total_pages"].get<int>();
    parsePage(firstPage["data"], articles);

    for (int page = 2; page <= totalPages; ++page) {
        json pageJson = json::parse(fetchPage(page));
        parsePage(pageJson["data"], articles);
    }

    curl_global_cleanup();

    // sort by comments descending, then name descending on ties
    sort(articles.begin(), articles.end(),
         [](const Article& a, const Article& b) {
             if (a.numComments != b.numComments)
                 return a.numComments > b.numComments;
             return a.name > b.name;
         });

    vector<string> result;
    for (int i = 0; i < limit && i < static_cast<int>(articles.size()); ++i)
        result.push_back(articles[i].name);

    return result;
}

int main(void) {
    int limit;
    cin >> limit;

    try {
        vector<string> top = topArticles(limit);
        for (const string& name : top)
            cout << name << "\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
