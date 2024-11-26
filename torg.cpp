#include "http_client.cpp"
#include "help copy.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main() {
    //cout << 0;
    HttpClient client("localhost", "8080");
    string http = "POST /user Market";
    //getline(std::cin, http);
    string str = "";
    str = client.sendRequest(http);
    //cout << str;

    for(int i = 0; i < 10; i++) {
        float price = (rand() % 1000 + 1) * 1.0 / 10000.0;
        string price_str = to_string(price);

        int val = rand() % 6 + 1;
        string val_str = to_string(val);

        string post = "POST /order " + str + " " + val_str + " 100 " + price_str + " sell";
        //string post = "POST /order" + str + " 1 10 1.5 sell";
        client.sendRequest(post);

        sleep(1);
    }



    //std::cout << "Response body:\n" << str;
    return 0;
}