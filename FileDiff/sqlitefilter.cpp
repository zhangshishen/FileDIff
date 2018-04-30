#include "sqlitefilter.h"

string Sqlitefilter::excute(const string& inFileContent,const string& inFilePath) const{
    return sqlReader(inFilePath.c_str());
}

string Sqlitefilter::filter(const string&) const{

}

bool Sqlitefilter::SeparatorSelector(char c) const{

}

bool Sqlitefilter::isTargetFile(const string& format) const{
    return true;
}

bool Sqlitefilter::matchFormat(const string& format) const{
    if(format==".sqlite"){
        return true;
    }
    return false;
}