#include "timestampfilter.h"


using namespace std;

#define TIMESHAKE 100
#define STRICTTIMESHAKE 100000000


#define SEC_TO_UNIX_EPOCH 11644473600000000L
#define WINEPOCH "11644473600000000"

bool isTimeStamp(const string& s){          //the current time format, 0 is not good

    if(s.find_first_not_of( "0123456789" ) != string::npos){
        return false;
    }

    if(s.size()>17||s.size()<9){
        return false;
    }
    
    return true;
}

bool inline overflowInt(const string& s){    //if a string can be 

    if(s>to_string(INT64_MAX)){
        return true;
    }

    return false;
    
}

bool isStandardTimestamp(const string& standard,const string& src){
    int lengthDiff = standard.size()-src.size();
    return lengthDiff == 0 || lengthDiff == -3 || lengthDiff == -6 || lengthDiff == -7;
}

void formatAdaptor(string target,string& src){        //timestamp is only prefix, just fill in zero or remove zero

    if(!isTimeStamp(target)||!isTimeStamp(src)){
        //perror("string is not timeStamp\n");
        return;
    }

    while(src.size()>target.size()){
        //perror("target size less than src");
        src.pop_back();
    }

    while(src.size()<target.size()){
        src.push_back('0');
    }
    
}

bool isClientTimestamp(const string& s,const string& targetTimeStamp){
    if(targetTimeStamp ==""){
        //perror("standard timestamp not been set\n");
        return false;
    }
    return targetTimeStamp != timeStampFilter(s,targetTimeStamp);
}

long int isWinEpoch(const string& targetTimeStamp,const string& time){   //check if is windows timestamp and return the appropriate unix timestamp
    string tmp = time;
    formatAdaptor(targetTimeStamp,tmp);
    long int target = stol(targetTimeStamp);
    long int src = stol(tmp);

    if(src>target){
        src-=target;
    }else{
        return -1;
    }
    return src;
}


string timeStampFilter(const string& s,const string& targetTimeStamp){
    if(targetTimeStamp ==""){
        //perror("standard timestamp not been set\n");
        return s;
    }
    if(!isTimeStamp(s)){
        //perror("string is not timeStamp\n");
        return s;
    }
    if(overflowInt(s)){
        return s;
    }

    long int target = stol(targetTimeStamp);
    long int src = stol(s);

    long int uEpoch = isWinEpoch(WINEPOCH,s);
    uEpoch/=1000000;
    if(uEpoch>=0&&(abs(uEpoch-stol(targetTimeStamp))<STRICTTIMESHAKE)){
        src = uEpoch;
    }

    string mid = to_string(src);


    if(!isStandardTimestamp(targetTimeStamp,mid)){
        return s;
    }
    
    formatAdaptor(targetTimeStamp,mid);

    src = stol(mid);

    if(abs(target-src) < STRICTTIMESHAKE ){
        return targetTimeStamp;
    }else{
        return s;
    }

}
string timeStampFilter(const string& s,int targetTimeStamp){
    
    return timeStampFilter(s,to_string(targetTimeStamp));

}

string mainTimeStampFilter(const string& in){
    static string s;
    if(s=="") {
        auto m = getenv("TIMESTAMP");
        if(m!=NULL) s = m;
        
    }

    if(s==""){
        //perror("timestamp not set,use default timestamp");
        auto m = exec("date +%s");
        if(m[m.size()-1]=='\n') m.pop_back();
        s = m;
    }

    string out = timeStampFilter(in,s);
    
    if(out==in){
        //no change
        return in;
    }else{
        return "*TIMESTAMP*";
    }

}

string TimeStampFilter::excute(const string& inFileContent,const string& inFilePath) const{
    return wordScanner(inFileContent,*this);
}

string TimeStampFilter::filter(const string& in) const{
    return mainTimeStampFilter(in);
}
bool TimeStampFilter::SeparatorSelector(char c) const{
    return c<'0'||c>'9';
}
bool TimeStampFilter::isTargetFile(const string& fileName) const{

    string s = "file ";
    s+=changeSpace(fileName);

    if(stringMatch(exec(s.c_str()),"([\\s\\S]*)text([\\s\\S]*)")||stringMatch(exec(s.c_str()),"([\\s\\S]*)SQLite([\\s\\S]*)"))
        return true;
    
    return false;
}

bool TimeStampFilter::matchFormat(const string& format) const{
    //if(format==".sqlite"){
        return true;
    //}
    //return false;
}