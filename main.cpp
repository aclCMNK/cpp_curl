#include<iostream>
#include<curl/curl.h>
#include "includes/json.hpp"

using JSON = nlohmann::json;
//INSTALL CURL:
//sudo apt install libcurl4-openssl-dev
//curl-config --cflags
//compile cpp program as: g++ [cpp_file].cpp -o [app_name] -lcurl
//
//CURL doc:
//https://curl.se/libcurl/c/libcurl-tutorial.html
//https://curl.se/libcurl/c/example.html
//https://curl.se/libcurl/c/simplepost.html
//https://curl.se/libcurl/c/http-post.html
//
//JSON NLOHMANN:
//https://github.com/nlohmann/json
//
//WEB ASSEMBLY DOC:
//https://ihsavru.medium.com/calling-javascript-code-from-c-c-using-webassembly-a9445c11bc6d
//
//V8:
//https://v8.dev/docs/embed
//
//GLFW:
//https://www.glfw.org/docs/3.3/quick.html

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void parsero(std::string str){
	std::cout << str << std::endl;
	JSON json_data = JSON::parse(str);
	//std::cout << json_data.at("id") << std::endl;
	for(auto& row : json_data){
		row["test1"] = 12123123;
		for(auto& item : row.items()){
			std::cout << "[" << item.key() << "] = " << item.value() << std::endl;
		}
		std::cout << "---------------------" << std::endl;
	}
}
int main (int argc, char *argv[]) {
	CURL* _curl;
	CURLcode _curl_code;
	std::string readBuffer;
	curl_global_init(CURL_GLOBAL_ALL);
	_curl = curl_easy_init();
	if(_curl){
		curl_easy_setopt(_curl, CURLOPT_URL, "https://api.restful-api.dev/objects");
		curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &readBuffer);
		_curl_code = curl_easy_perform(_curl);
		std::cout << _curl_code << std::endl;
		curl_easy_cleanup(_curl);
	}
	curl_global_cleanup();
	parsero(readBuffer);

	std::cout << "end" << std::endl;
	return 0;
}
