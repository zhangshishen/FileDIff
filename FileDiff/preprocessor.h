#include <fstream>
#include "diff.h"
#include "tools.h"
#include "timestampfilter.h"
#include "sqlitefilter.h"
#include "container.h"
#include "algorithm"
#include "sqLiteReader.h"
using namespace std;



class Config{
public:
    string fileSuffix;
    string name = "pre";
    vector<string> nameFilter;
    vector<Filter*> filter;

    int matchFilter(const string& name);
    string filterData(const string& content);/*
    Config(){
        Filter* c = new timeStampFilter();
        filter.
    }*/
};

int preProcess(const string& fileName,const string& outName,const Filter& fil);
bool stringMatch(const string& src,const string& dst = "(?i:cache)");
string preProcessor(const string& folderPath,const string& outPath,Config& config);
vector<string> twinsPreProcessor();


