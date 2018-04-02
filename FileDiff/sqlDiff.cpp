#include "sqlDiff.h"




vector<sqlQuery> sqlDiff;

int sqlQuery::getDiff(const sqlQuery& sql) const{
        int res = 0;
        if(this->column.size()!=sql.column.size()){
            return 10000;
        }
        for(int i = 0;i<column.size();i++){
            if(column[i]!=sql.column[i]){
                return 10000;
            }
            if(value[i]!=sql.value[i]){
                res++;
            }
        }
        return res;
}



string sqlQuery::outDiff(const sqlQuery& sql) const{
        string res;
        for(int i = 0;i<column.size();i++){
            if(value[i]!=sql.value[i]){
                res+=value[i];
                res+="\n";
                res+=sql.value[i];
                res+='\n';
            }
        }
        return res;
}
string sqlQuery::outData() const{
    string res;
    for(int i = 0;i<column.size();i++){
        res+=column[i];
                res+=" = ";
                res+=value[i];
                res+=" , ";
        
    }
    return res;
}
void sqlQuery::setValue(const string& Key,const string& Value){
    column.push_back(Key);
    value.push_back(Value);
}

string sqlQuery::GetString() const{
    string res;
    for(auto& s:value){
        res+=s;
    }
    return res;
}

string getDiffofSqldiff(const vector<sqlQuery> &d1,const vector<sqlQuery>& d2){
    if(d1.size()>d2.size()){
        cerr<<"cookie size not equal\n";
    }
    string res;
    for(int i = 0;i<d1.size();i++){
        int curMax = 10000;
        int index = 0;
        for(int j = 0;j<d2.size();j++){
            if(d1[i].getDiff(d2[j])<curMax){
                curMax = d1[i].getDiff(d2[j]);
                index = j;
            }
        }
        if(curMax!=10000){
            res+=d1[i].outDiff(d2[index]);
        }else{
            res+=d1[i].outData()+" no matching item \n";
        }
    }
    return res;
}

bool sqlCompare::operator()(const sqlQuery& sql1,const sqlQuery& sql2){
    return sql1.GetString()<sql2.GetString();
}


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

