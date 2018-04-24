#include <fstream>
#include "diff.h"
#include "tools.h"
#include "timestampfilter.h"
#include "container.h"
using namespace std;



class Config{
public:
    string fileSuffix;
    string name = "pre";
    int mutableFlag = 0;
    vector<string> nameFilter;
    vector<Filter*> filter = {new timeStampFilter()};

    int matchFilter(const string& name);
    string filterData(const string& content);

};

int preProcess(const string& fileName,const string& outName,const Filter& fil);
bool stringMatch(const string& src,const string& dst = "(?i:cache)");
string preProcessor(const string& folderPath,const string& outPath,Config& config);
vector<string> twinsPreProcessor();


