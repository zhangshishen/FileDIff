#include "tools.h"
#include <string>
#include "diff.h"

using namespace std;

typedef string(*filterFunc)(const string&);

string mainTimeStampFilter(const string& in);

class timeStampFilter:public Filter{
    virtual string filter(const string&) const;
    virtual bool SeparatorSelector(char c) const;
    virtual bool isTargetFile(const string&) const;
};
//string wordScanner(const string& inFile,filterFunc filter);