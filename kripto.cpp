#include <iostream>
#include <string>
#include "code.h"

int user_id = 1;
int order_id = 1;

int PostUser(string& str, string http) {
    int key = rand();
    string key_str = to_string(key);
    string user_id_str = to_string(user_id);

    code(str, "INSERT INTO user VALUES ('" + user_id_str + "', '" + http + "', '" + key_str + "')");
    user_id++;

    for(int i = 1; i < 6; i++) {
        code(str, "INSERT INTO user_lot VALUES ('" + user_id_str + "', '" + to_string(i) + "', '1000')");
    }

    str = "key: " + key_str + "\n";

    return 0;
}

int PostOrder(string& str, string http) {
    vector<string> splitHttp = splitProbel(http);
    code(str, "SELECT lot.lot_id, user.user_id FROM lot, user WHERE user.key = '" + splitHttp[0] + "' AND lot.lot_id = '1'");
    string user_id_str = SizeIndex(str, str.length() - 2, str.length() - 1);
    string order_id_str = to_string(order_id);
    order_id++;

    vector<vector<string>> abba;
    get(abba);
    /*
    for(int i = 0; i < abba.size(); i++) {
        for(int j = 0; j < abba[0].size(); j++) {
            cout << abba[i][j] << " ";
        }
        cout << "\n";
    }
    */

    int pair_id = stoi(splitHttp[1]);
    float quantity = stof(splitHttp[2]);
    float price = stof(splitHttp[3]);
    string type = splitHttp[4];
    int oy = 0;

    int stop = abba.size();
    for (int i = 0; i < stop; i++) {
        /*
        cout << abba[i][3] << " " << splitHttp[1] << endl;
        cout << abba[i][6] << " " << inverse(type) << endl;
        cout << abba[i][7] << endl;
        cout << price << " " << stof(abba[i][5]) << endl;
        cout << (stoi(abba[i][3]) == stoi(splitHttp[1]));
        cout << (abba[i][6] == inverse(type));
        cout << (abba[i][7] == "-");
        cout << (((type == "buy") ? (price <= stof(abba[i][5])) : (stof(abba[i][5]) <= price)));
        */
        if (stoi(abba[i][3]) == stoi(splitHttp[1]) && abba[i][6] == inverse(type) && abba[i][7] == "-" && ((type == "sell") ? (price <= stof(abba[i][5])) : (stof(abba[i][5]) <= price))) {
            string PO = "";
    
                //cout << quantity - stof(abba[i][4]);
                if(quantity - stof(abba[i][4]) > 0){
                    float d = quantity - stof(abba[i][4]);
                    abba[i][7] = SizeIndex((getCurrentTime()), 10, 16);
                    vector<string> ab;
                    ab.push_back("0");
                    ab.push_back(order_id_str);
                    ab.push_back(user_id_str);
                    ab.push_back(splitHttp[1]);
                    ab.push_back(abba[i][4]);
                    ab.push_back(abba[i][5]);
                    ab.push_back(splitHttp[4]);
                    ab.push_back(abba[i][7]);
                    
                    abba.push_back(ab);

                    changeBalanse(stoi(user_id_str), stoi(abba[i][2]), pair_id, stof(abba[i][4]), stof(abba[i][5]));

                    PO = splitHttp[0] + " " +  splitHttp[1] + " " + to_string(d) + " " + splitHttp[3] + " " + splitHttp[4];
                    /*
                    ab.clear();
                    ab.push_back("0");
                    ab.push_back(to_string(order_id));
                    order_id++;
                    ab.push_back(user_id_str);
                    ab.push_back(splitHttp[1]);
                    ab.push_back(to_string(d));
                    ab.push_back(splitHttp[3]);
                    ab.push_back(splitHttp[4]);
                    ab.push_back("-");

                    abba.push_back(ab);
                    */

                } else if(quantity - stof(abba[i][4]) < 0){
                    float d = stof(abba[i][4]) - quantity;

                    abba[i][7] = SizeIndex((getCurrentTime()), 10, 16);
                    abba[i][4] = splitHttp[2];

                    vector<string> ab;
                    ab.push_back("0");
                    ab.push_back(order_id_str);
                    ab.push_back(user_id_str);
                    ab.push_back(splitHttp[1]);
                    ab.push_back(to_string(quantity));
                    ab.push_back(abba[i][5]);
                    ab.push_back(splitHttp[4]);
                    ab.push_back(abba[i][7]);
                    
                    abba.push_back(ab);

                    changeBalanse(stoi(user_id_str), stoi(abba[i][2]), pair_id, quantity, stof(abba[i][5]));

                    //PostOrder(str, splitHttp[0] + " " +  splitHttp[1] + " " + splitHttp[0] + " " + splitHttp[3] + " " + splitHttp[4]);
                    ab.clear();
                    ab.push_back("0");
                    ab.push_back(to_string(order_id));
                    order_id++;
                    ab.push_back(abba[i][2]);
                    ab.push_back(abba[i][3]);
                    ab.push_back(to_string(d));
                    ab.push_back(abba[i][5]);
                    ab.push_back(abba[i][6]);
                    ab.push_back("-");

                    abba.push_back(ab);

                } else {
                    abba[i][7] = SizeIndex((getCurrentTime()), 10, 16);
                    vector<string> ab;
                    ab.push_back("0");
                    ab.push_back(order_id_str);
                    ab.push_back(user_id_str);
                    ab.push_back(splitHttp[1]);
                    ab.push_back(abba[i][4]);
                    ab.push_back(abba[i][5]);
                    ab.push_back(splitHttp[4]);
                    ab.push_back(abba[i][7]);
                    
                    abba.push_back(ab);

                    changeBalanse(stoi(user_id_str), stoi(abba[i][2]), pair_id, stof(abba[i][4]), stof(abba[i][5]));
                }

            
            oy = 1;
            code(str, "DELETE FROM order WHERE order.type = 'buy'");
            code(str, "DELETE FROM order WHERE order.type = 'sell'");
            for (int j = 0; j < abba.size(); j++) {
                code(str, "INSERT INTO order VALUES ('" + abba[j][1] + "', '" + abba[j][2] + "', '" + abba[j][3] + "', '" + abba[j][4] + "', '" + abba[j][5] + "', '" + abba[j][6] + "', '" + abba[j][7] + "')");
            }
            //cout << PO.size();
            if (PO.size() > 0) {
                PostOrder(str, PO);
            }
            break;
        }
    }

    if (oy == 0) {
        //cout << "Eva";
        code(str, "INSERT INTO order VALUES ('" + order_id_str + "', '" + user_id_str + "', '" + splitHttp[1] + "', '" + splitHttp[2] + "', '" + splitHttp[3] + "', '" + splitHttp[4] + "', '-')");
    }

    str = "";
    return 0;
}

int GetOrder(string& str) {  
    code(str, "SELECT order.order_id, user.user_id FROM order, user WHERE user.user_id = '1'");
    vector<vector<string>> abba;
    str = "";
    get(abba);
    for(int i = 0; i < abba.size(); i++) {
        for(int j = 0; j < abba[0].size(); j++) {
            str += (abba[i][j] + " ");
        }
        str += "\n";
    }
    return 0;
}

int DeleteOrder(string& str, string http) {
    vector<string> splitHttp = splitProbel(http);
    code(str, "SELECT lot.lot_id, user.user_id FROM lot, user WHERE user.key = '" + splitHttp[0] + "' AND lot.lot_id = '1'");
    string user_id_str = SizeIndex(str, str.length() - 2, str.length() - 1);
    string order_id_str = splitHttp[1];
    vector<vector<string>> abba;
    get(abba);
    int order_for_delete = -1;
    for(int i = 0; i < abba.size(); i++) {
        if (abba[i][1] == order_id_str) {
            if (abba[i][2] == user_id_str) {
                order_for_delete = i;
            }
        }
    }
    if (order_for_delete != -1) {
        abba.erase(abba.begin() + order_for_delete);
    }
    code(str, "DELETE FROM order WHERE order.type = 'buy'");
    code(str, "DELETE FROM order WHERE order.type = 'sell'");
    for (int j = 0; j < abba.size(); j++) {
        code(str, "INSERT INTO order VALUES ('" + abba[j][1] + "', '" + abba[j][2] + "', '" + abba[j][3] + "', '" + abba[j][4] + "', '" + abba[j][5] + "', '" + abba[j][6] + "', '" + abba[j][7] + "')");
    }

    return 0;
}

int GetLot(string& str) {
    string str1 = "";
    string str2 = "";
    code(str1, "SELECT user.user_id, lot.lot_id FROM user, lot WHERE user.user_id = '1'");
    code(str2, "SELECT user.user_id, lot.name FROM user, lot WHERE user.user_id = '1'");

    vector<string> Stroki1 = splitPerenos(str1);
    vector<string> Stroki2 = splitPerenos(str2);
    for (int i = 0; i < Stroki1.size(); i++) {
        vector<string> PodStroki1 = splitProbel(Stroki1[i]);
        vector<string> PodStroki2 = splitProbel(Stroki2[i]);
        str = str + PodStroki1[3] + "  " + PodStroki2[3] + "\n";
    }

    return 0;
}

int GetPair(string& str) {
    string str1 = "";
    string str2 = "";
    code(str1, "SELECT lot.lot_id, pair.first_lot_id FROM pair, user_lot WHERE lot.lot_id = '1'");
    code(str2, "SELECT lot.lot_id, pair.second_lot_id FROM pair, user_lot WHERE lot.lot_id = '1'");

    vector<string> Stroki1 = splitPerenos(str1);
    vector<string> Stroki2 = splitPerenos(str2);
    for (int i = 0; i < Stroki1.size(); i++) {
        vector<string> PodStroki1 = splitProbel(Stroki1[i]);
        vector<string> PodStroki2 = splitProbel(Stroki2[i]);
        str = str + PodStroki1[2] + "  " + PodStroki1[3] + "  " + PodStroki2[3] + "\n";
    }

    return 0;
}

int GetBalance(string& str, string http) {
    code(str, "SELECT lot.lot_id, user.user_id FROM lot, user WHERE user.key = '" + http + "' AND lot.lot_id = '1'");

    string user_id_str = SizeIndex(str, str.length() - 2, str.length() - 1);
    
    str = "";
    code(str, "SELECT lot.lot_id, user_lot.quantity FROM lot, user_lot WHERE user_lot.user_id = '" + user_id_str + "' AND lot.lot_id = user_lot.lot_id");

    vector<string> Stroki = splitPerenos(str);
    str = "";
    for (int i = 0; i < Stroki.size(); i++) {
        vector<string> PodStroki = splitProbel(Stroki[i]);
        str = str + PodStroki[1] + "  " + PodStroki[3] + "\n";
    }
    str += "\n";

    return 0;
}

void kripto(string& str, string http) {
    str = "";

    if (SizeIndex(http, 0, 11) == "POST /user ") {
        PostUser(str, SizeIndex(http, 11, http.length()));
    }
    else if (SizeIndex(http, 0, 12) == "POST /order ") {
        PostOrder(str, SizeIndex(http, 12, http.length()));
    }
    else if (http == "GET /order") {
        GetOrder(str);
    }
    else if (SizeIndex(http, 0, 14) == "DELETE /order ") {
        DeleteOrder(str, SizeIndex(http, 14, http.length()));
    }
    else if (http == "GET /lot") {
        GetLot(str);
    }
    else if (http == "GET /pair") {
        GetPair(str);
    }
    else if (SizeIndex(http, 0, 13) == "GET /balance ") {
        GetBalance(str, SizeIndex(http, 13, http.length()));
    }
    else {
        str = "Попробуйте ввести запрос ещё раз)";
    }


}