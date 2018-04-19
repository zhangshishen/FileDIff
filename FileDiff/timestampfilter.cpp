#include <string>


using namespace std;

bool isTimeStamp(const string& s){          //the current time format, 0 is not good

}

bool inline overflowInt(const string& s){    //if a string can be 
    if(s>to_string(INT32_MAX)){
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
        src.pop_back();
    }

    while(src.size()<target.size()){
        src.push_back('0');
    }
    
}

bool isClientTimestamp(const string& s,const string& targetTimeStamp){
    return targetTimeStamp != timeStampFilter(s,targetTimeStamp);
}

string timeStampFilter(const string& s,const string& targetTimeStamp){

    if(!isTimeStamp(s)){
        perror("string is not timeStamp\n");
        return s;
    }
    if(overflowInt(s)){
        return s;
    }

    
    string out = s;
    formatAdaptor(targetTimeStamp,out);
    
    int target = stoi(targetTimeStamp);
    int src = stoi(out);

    if(target-src == 0){
        return targetTimeStamp;
    }else{
        return s;
    }

}
string timeStampFilter(const string& s,int targetTimeStamp){

    return timeStampFilter(s,to_string(targetTimeStamp));

}