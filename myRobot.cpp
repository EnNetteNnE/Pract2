#include "http_client.cpp"
#include "help copy.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main() {
    //cout << 0;
    HttpClient client("localhost", "8080");
    string http = "POST /user Eva";
    //getline(std::cin, http);
    string str = "";
    str = client.sendRequest(http);

    int stop = 0;
    
    for(int i = 0; i < 100; i++) {
        string ord = client.sendRequest("GET /order");
        //cout << ord;
        vector<string> orde = splitPerenos(ord);
        if(stop == orde.size()) {
            break;
        }
        stop = orde.size();
        vector<vector<string>> orders;
        for (string i : orde) {
            orders.push_back(splitProbel(i));
        }

        vector<vector<float>> shet;
        for (int i = 0; i < 6; i++) {
            float u = 0;
            vector<float> tuy;
            tuy.push_back(u);
            tuy.push_back(u);
            tuy.push_back(u);
            shet.push_back(tuy);
        }

        for (int i = 0; i < orders.size(); i++) { // заполняем сумму и количество
            int index = stoi(orders[i][3]) - 1;
            shet[index][0] += stof(orders[i][5]);
            shet[index][1] += 1;
        }

        for (int i = 0; i < 6; i++) { // заполняем среднее арифметическое
            shet[i][2] = shet[i][0] / shet[i][1];
        }

        for (int i = 0; i < orders.size(); i++) { // 
            int index = stoi(orders[i][3]) - 1;
            if ((stof(orders[i][5]) < shet[index][2]) && (orders[i][7] == "-")) {
                string post = "POST /order " + str + " " + orders[i][3] + " " + orders[i][4] + " " + orders[i][5] + " buy";
                client.sendRequest(post);
            }
        }


        sleep(2);
    }

    return 0;
}