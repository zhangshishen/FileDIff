#include "linefilter.h"

string Linefilter::excute(const string& inFileContent,const string& inFilePath) const{

    if(!isLongLine(inFilePath)){
        return inFileContent;
    }
    
    string s = "cat ";
    s += changeSpace(inFilePath);
    s += " | python -m json.tool";
    string ret = Exec(s.c_str());
    if(ret ==""){
        return inFileContent;
    }else return ret;
    //return wordScanner(inFileContent,*this);
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
    
    return true;
}