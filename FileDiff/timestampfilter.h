#include "tools.h"
#include <string>
#include "diff.h"

using namespace std;

typedef string(*filterFunc)(const string&);

string mainTimeStampFilter(const string& in);

class TimeStampFilter:public Filter{
    virtual string filter(const string&) const;
    virtual bool SeparatorSelector(char c) const;
    virtual bool isTargetFile(const string&) const;
    virtual bool matchFormat(const string&) const;
    virtual string excute(const string& inFileContent,const string& inFilePath) const;
};
string timeStampFilter(const string& s,const string& targetTimeStamp);
//string wordScanner(const string& inFile,filterFunc filter);
