
#include "kripto.cpp"
#include <iostream>
#include <string>


using namespace std;

int main() {

    ReadJsonFile(fileName, schemaName, tuplesLimit, *jsonStructure, *keys);
    pushInfo();


    while (false)
    {
        string http;
        string str = "";
        getline(cin, http);

    
    }

    MyArr<string>* info = MCREATE<string>(10);
    MSET<string>(*info, "POST /user Eva");
    MSET<string>(*info, "POST /user Sasha");
    //MSET<string>(*info, "GET /balance 1234");
    //MSET<string>(*info, "GET /pair");
    //MSET<string>(*info, "GET /lot");
    //MSET<string>(*info, "POST /order 1234566");
    //MSET<string>(*info, "POST /order 1804289383 1 200 0.01 sell");
    //MSET<string>(*info, "POST /order 846930886 1 300 0.015 buy");
    //MSET<string>(*info, "POST /order 1804289383 1 300 0.01 sell");
    //MSET<string>(*info, "POST /order 846930886 1 200 0.015 buy");
    MSET<string>(*info, "POST /order 846930886 1 200 0.015 buy");
    MSET<string>(*info, "POST /order 1804289383 1 300 0.01 sell");
    MSET<string>(*info, "GET /order");
    MSET<string>(*info, "DELETE /order 1804289383 3");
    



    string str = "1";
    
    for (int i = 0; i < (info->len); i++) {
        string sql = info->data[i];
        kripto(str, sql); 
        cout << str;
    }
/*  
    string http;
    getline(cin, http);

    vector<vector<string>> A;
    get(A);
    cout << A[0].size();

    for (int i = 0; i < A[0].size(); i++) {
        cout << i << " "<< A[0][i] << endl;
    }
  
    kripto(str, http);
*/

    return 0;
}


