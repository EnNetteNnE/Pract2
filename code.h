#include <iostream>
#include <fstream>

#include "hash.h"
#include "arr.h"

#include "data.h"
//#include "lock.h"
//#include "help.h"
#include "select_.h"
#include <future>

using namespace std;

mutex mtx;

int code(string& str, string sql, MyHash<string, MyArr<string>*>& jsonStructure, MyHash<string, int>& numb, string schemaName, int tuplesLimit, MyArr<string>& keys) {

    mtx.lock();

    if (SizeIndex(sql, 0, 12) == "INSERT INTO ") {
        int a = Insert(sql, jsonStructure, numb, schemaName, tuplesLimit, keys);
        if (a == 1) {
            str = "The addition was successful";
        }
    }
    else if (SizeIndex(sql, 0, 12) == "DELETE FROM ") {
        int a = Delet(sql, jsonStructure, numb, schemaName, keys);
        if (a == 1) {
            str = "The deletion was successful";
        }
    }
    else if (SizeIndex(sql, 0, 7) == "SELECT ") {
        Select(sql, jsonStructure, numb, schemaName, keys, str);
    }
    else {
        str = "Попробуйте ввести запрос ещё раз)";
    }

    mtx.unlock();

    return 1;
}

