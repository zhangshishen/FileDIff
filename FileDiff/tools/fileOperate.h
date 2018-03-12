#include "iostream"
#include "string"
#include "fstream"

using namespace std;

std::streampos filesize(const char* filename);
void fileAppend(const string& dst,const string& src);