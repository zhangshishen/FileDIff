#include "tools.h"




std::string Exec(const char* cmd) {
    std::array<char, 256> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 256, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

bool stringMatch(const string& src,const string& dst = "(?i:cache)"){
    
    if(src.size()<dst.size()) return false;

    return regex_match(src,regex(dst));

}



string fileFormat(const string& name){
    return Exec((string("file ")+name).c_str());
}

bool isDirectory(const string& name){
    auto res = fileFormat(name);
    auto words = separateString(res,':');
    if(words.size()<2){
        perror("file format test failed\n");
    }
    if(words[1]==" directory"){
        return true;
    }else return false;
}


void stringToFile(const string& fileName,const string& content){
    std::ofstream out(fileName);
    out<<content;
    out.close();
}

string makeTempFolder(const string& name){
    string out = name+"-tmp";
    Exec((string("mkdir ")+out).c_str());
    return out;
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

bool isSeparator(char c){
    switch(c){
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case ',':
        case '"':
        case ' ':
        case '<':
        case '>':
        case '\t':
        case '\n':
            return true;
        default:
            return false;
    }
    
}

string fileToString(const string& fileName){

    string res;
    ifstream file(fileName);

    if(!file.is_open()){
        perror("file open failed\n");
        return res;
    }
    
    while(!file.eof()){
        getline(file,res);
    }
    return res;

}



string wordScanner(const string& inFile,const Filter& filter){
    string out,tmp;

    for(auto c:inFile){

        if(filter.SeparatorSelector(c)){
            out+=filter.filter(tmp);
            tmp.clear();
        }
        else{
            tmp+=c;
        }

    }

    if(!tmp.empty()){
        out+=filter.filter(tmp);
    }

    return out;
}