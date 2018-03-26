#include "sqLiteReader.hpp"

std::vector<std::string> sqltablesName;
FILE* outfile;

std::vector<sqlQuery> sqlReader(const char* database,const char* output){
    outfile = fopen(output,"w+");
    if(outfile==NULL){
        fprintf(stderr, "cannot open file %s \n",output);
        return {};
    }
    std::vector<sqlQuery> ret;
    sqlite3* db;
    int rc = sqlInit(&db, database);
    getTableName(db,rc);
    
    for(int i = 0;i< sqltablesName.size();i++){
        std::string tmp = "select * from " + sqltablesName[i]+" ;";
        readSqlCommand(db,rc,tmp.c_str(),&ret);
    }
    sqltablesName.clear();
    sqlite3_close(db);
    fclose(outfile);
    return ret;
}



static int callback(void *ret, int argc, char **argv, char **azColName){
    int i;
    if(argc==0) return 0;
    sqlQuery sql;
    
    //sqlDiff.push_back()
    for(i=0; i<argc; i++)
    {
        sql.setValue(azColName[i], argv[i] ? argv[i] : "NULL");
        fprintf(outfile,"%s = %s\t", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    ((vector<sqlQuery>*)ret)->push_back(sql);
    //sqlDiff.push_back(sqlquery);
    //fprintf(outfile,"\n");
    return 0;
}

static int getTableNameCallback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++)
    {
        sqltablesName.push_back(argv[i]);
        //printf("%s", argv[i]);
    }
    return 0;
}

int sqlInit(sqlite3** db,const char* database){
    //sqlite3 *db;
    int rc = sqlite3_open(database, db);
    return rc;
    
}
int getTableName(sqlite3* db,int rc)
{
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, "SELECT name FROM sqlite_master WHERE type='table';", getTableNameCallback, 0, &zErrMsg);
    return 0;
}
int readSqlCommand(sqlite3* db,int rc, const char *query,vector<sqlQuery>* ret){  //argv[1] database argv[2]
    
    //sqlite3 *db;
    char *zErrMsg = 0;
    //int rc;
    
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }
    rc = sqlite3_exec(db, query, callback, (void*)ret, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    
    return 0;
}


string getDiffOfSqlite(char** word,string& name){

    std::string s1 = name+"1.txt",s2=name+"2.txt";
    auto diff1 = sqlReader(word[2],s1.c_str());
    auto diff2 = sqlReader(word[4],s2.c_str());
    //sqlDiff.clear();

    //string outName = name+"-diffout.txt";

    return getDiffofSqldiff(diff1,diff2);
    

}