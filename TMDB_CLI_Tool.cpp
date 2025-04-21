#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h> 
using namespace std;


const string KEY_API = "eyJhbGciOiJIUzI1NiJ9.eyJhdWQiOiJlMGM5ZjNiMWVkMTIxZDQyZGFjMmIzZGQ5ZjUxOThjZSIsIm5iZiI6MTc0NTIzMDM2Mi4xNjcsInN1YiI6IjY4MDYxYTFhMDU5ZmJjZWNmNmFhYzJhNiIsInNjb3BlcyI6WyJhcGlfcmVhZCJdLCJ2ZXJzaW9uIjoxfQ.ewRIAwZtfEXSczLRA-uakozN0nfetZRiEv1aLkV1bSY";


size_t writeCallBack(void* contest, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contest, totalSize);
    return totalSize;
}

void get_movies(string& url) {
    string readBuffer;
    CURL* hnd = curl_easy_init();
    if (hnd) {
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, (url).c_str());

        // Set request headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "accept: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + KEY_API).c_str());
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

        // Setting up the recording function
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer); // Pointer to the output string

        CURLcode ret = curl_easy_perform(hnd);

        if (ret != CURLE_OK) {
            cerr << "error: " << curl_easy_strerror(ret) << endl;
        }
        else {
            // Parse the JSON response
            Json::Value root;
            Json::CharReaderBuilder readerBuilder;
            string errs;
            stringstream ss(readBuffer);  // Convert the response string into a stringstream

            if (Json::parseFromStream(readerBuilder, ss, &root, &errs)) {
                for (const auto& movie : root["results"]) {
                    cout << "Title: " << movie["title"].asString() << endl;
                    cout << "Release Date: " << movie["release_date"].asString() << endl;
                    cout << "--------------------------" << endl;
                }
            }
            else {
                cerr << "error parsing JSON: " << errs << endl;
            }
        }

        curl_easy_cleanup(hnd);
        curl_slist_free_all(headers);
    }
}

// Function to fetch and display now playing movies
void playing_movie() {
    string url = "https://api.themoviedb.org/3/movie/now_playing?language=en-US&page=1";
    get_movies(url);
}

// Function to fetch and display popular movies
void popular_movie() {
    string url = "https://api.themoviedb.org/3/movie/popular?language=en-US&page=1";
    get_movies(url);
    
}
// Function to fetch and display top rated movies
void top_movie() {
    string url = "https://api.themoviedb.org/3/movie/top_rated?language=en-US&page=1";
    get_movies(url);
    
}

// Function to fetch and display upcoming movies
void upcoming_movie() {
    string url = "https://api.themoviedb.org/3/movie/upcoming?language=en-US&page=1";
    get_movies(url);
    
}

int main(int argc, char* argv[]) {
    if (argc != 3 || string(argv[1]) != "--type") {
        cerr << "Usage: tmdb-app --type [playing|popular|top|upcoming]" << endl;
        return 1;
    }

    string type = argv[2];
    if (type == "playing") {
        playing_movie();
    }
    else if (type == "popular") {
        popular_movie();
    }
    else if (type == "top") {
        top_movie();
    }
    else if (type == "upcoming") {
        upcoming_movie();
    }
    else {
        cerr << "Invalid type of film category." << endl;
        return 1;
    }

    return 0;
}

