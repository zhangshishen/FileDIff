#include "tools.h"

void stringToFile(const string& fileName,const string& content){
    std::ofstream out(fileName);
    out<<content;
    out.close();
}

vector<string> separateString(const string& str,char separator){
    vector<string> res;
    string tmp;
    for(int i = 0;i<str.size();i++){
        if(str[i]==separator){
            if(tmp!="") res.push_back(tmp);
            tmp.clear();
        }else{
            tmp+=str[i];
        }
    }
    if(tmp!="") res.push_back(tmp);
    return res;
}
