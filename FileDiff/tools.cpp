#include "tools.h"

void stringToFile(const string& fileName,const string& content){
    std::ofstream out(fileName);
    out<<content;
    out.close();
}