#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include <regex>

#include "hash.h"
#include "arr.h"

//using namespace std;

#include "json.hpp"

using json = nlohmann::json;
namespace fs = filesystem;

//int ReadJsonFile(const string fileName, string& schemaName, int& tuplesLimit, MyHash<string, MyArr<string>*>& jsonStructure);

//string SizeIndex(string str, int begin, int end);



