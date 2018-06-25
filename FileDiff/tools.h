#include "fstream"

#include "vector"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <array>
#include <regex>

#pragma once
using namespace std;

class Filter{
public:
    virtual string excute(const string& inFileContent,const string& inFilePath) const = 0;
    virtual string filter(const string&) const=0;
    virtual bool SeparatorSelector(char c) const=0;
    virtual bool isTargetFile(const string&) const=0;
    virtual bool matchFormat(const string&) const=0;
};


void stringToFile(const string& fileName,const string& content);
vector<string> separateString(const string& str,char separator);
string fileToString(const string& fileName);
bool isSeparator(char c);
std::string Exec(const char* cmd);
bool isDirectory(const string& name);

string wordScanner(const string& in,const Filter& filter);
bool stringMatch(const string& src,const string& dst);
string makeTempFolder(const string& name);
string changeSpace(const string& name);
bool isLongLine(const string& name);
bool isSqlite(const string& name);