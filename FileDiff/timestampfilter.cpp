#include <timestampfilter.h>


using namespace std;

#define TIMESHAKE 100
#define DEFAULTTIMESTAMP "1500000000000000"



bool isTimeStamp(const string& s){          //the current time format, 0 is not good

    if(s.find_first_not_of( "0123456789" ) != string::npos){
        return false;
    }

    if(s.size()>16){
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
    return lengthDiff == 0 || lengthDiff == 3 || lengthDiff == 6 || lengthDiff == 9;
}

void formatAdaptor(string target,string& src){        //timestamp is only prefix, just fill in zero or remove zero

    if(!isTimeStamp(target)||!isTimeStamp(src)){
        perror("string is not timeStamp\n");
        return;
    }

    while(src.size()>target.size()){
        perror("target size less than src");
        src.pop_back();
    }

    while(src.size()<target.size()){
        src.push_back('0');
    }
    
}

bool isClientTimestamp(const string& s,const string& targetTimeStamp){
    if(targetTimeStamp ==""){
        perror("standard timestamp not been set\n");
        return false;
    }
    return targetTimeStamp != timeStampFilter(s,targetTimeStamp);
}

string timeStampFilter(const string& s,const string& targetTimeStamp){
    if(targetTimeStamp ==""){
        perror("standard timestamp not been set\n");
        return s;
    }
    if(!isTimeStamp(s)){
        perror("string is not timeStamp\n");
        return s;
    }
    if(overflowInt(s)){
        return s;
    }
    if(!isStandardTimestamp(targetTimeStamp,s)){
        return s;
    }
    
    string out = s;
    formatAdaptor(targetTimeStamp,out);

    long int target = stol(targetTimeStamp);
    long int src = stol(out);

    if(abs(target-src) < TIMESHAKE ){
        return targetTimeStamp;
    }else{
        return s;
    }

}
string timeStampFilter(const string& s,int targetTimeStamp){
    
    return timeStampFilter(s,to_string(targetTimeStamp));

}

string mainTimeStampFilter(const string& in){
    char* s = getenv("TIMESTAMP");

    if(s==NULL){
        perror("timestamp not set,use default timestamp");
        s=DEFAULTTIMESTAMP;
    }
    string out = timeStampFilter(in,s);
    
    if(out==in){
        //no change
        return in;
    }else{
        return "*TIMESTAMP*";
    }

}
string timeStampFilter::filter(const string& in) const{
    return mainTimeStampFilter(in);
}
bool timeStampFilter::SeparatorSelector(char c) const{
    return isSeparator(c);
}
bool timeStampFilter::isTargetFile(const string& fileName) const{
    return true;
    //string sFormat = getFormat(fileName.c_str());
    //if(sFormat)
}