#include "tools.h"

#include <vector>

using namespace std;

class Linefilter:public Filter{
public:
    virtual string excute(const string& inFileContent,const string& inFilePath) const;
    virtual string filter(const string&) const;
    virtual bool SeparatorSelector(char c) const;
    virtual bool isTargetFile(const string&) const;
    virtual bool matchFormat(const string&) const;
};