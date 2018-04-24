#include "fstream"

#include "vector"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>


using namespace std;

class Filter{
public:
    virtual string filter(const string&) const=0;
    virtual bool SeparatorSelector(char c) const=0;
    virtual bool isTargetFile(const string&) const=0;
};


void stringToFile(const string& fileName,const string& content);
vector<string> separateString(const string& str,char separator);
string fileToString(const string& fileName);
bool isSeparator(char c);
std::string exec(const char* cmd);
bool isDirectory(const string& name);

string wordScanner(const string& in,const Filter& filter);
bool stringMatch(const string& src,const string& dst);
string makeTempFolder(const string& name);