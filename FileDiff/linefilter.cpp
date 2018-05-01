#include "linefilter.h"

string Linefilter::excute(const string& inFileContent,const string& inFilePath) const{
    if(!isLongLine(inFilePath)){
        return inFileContent;
    }
    return wordScanner(inFileContent,*this);
}

string Linefilter::filter(const string&) const{

}

bool Linefilter::SeparatorSelector(char c) const{
    
}

bool Linefilter::isTargetFile(const string& fullpath) const{

    if(isLongLine(fullpath)){
        return true;
    }
    return false;

}

bool Linefilter::matchFormat(const string& format) const{
    
    return false;
}