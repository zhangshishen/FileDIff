#include "sqLiteReader.hpp"

std::vector<std::string> sqltablesName;
FILE* outfile;

int sqlReader(const char* database,const char* output){
    outfile = fopen(output,"w+");
    if(outfile==NULL){
        fprintf(stderr, "cannot open file %s \n",output);
        return -1;
    }
    sqlite3* db;
    int rc = sqlInit(&db, database);
    getTableName(db,rc);
    
    for(int i = 0;i< sqltablesName.size();i++){
        std::string tmp = "select * from " + sqltablesName[i]+" ;";
        readSqlCommand(db,rc,tmp.c_str());
    }
    sqltablesName.clear();
    sqlite3_close(db);
    fclose(outfile);
    return 0;
}



static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    if(argc==0) return 0;
    sqlQuery sql;
    
    //sqlDiff.push_back()
    for(i=0; i<argc; i++)
    {
        sql.setValue(azColName[i], strcmp(argv[i],"")!=0 ? argv[i] : "NULL");
        //fprintf(outfile,"%s = %s\t", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    sqlDiff.push_back(sql);
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
int readSqlCommand(sqlite3* db,int rc, const char *query){  //argv[1] database argv[2]
    
    //sqlite3 *db;
    char *zErrMsg = 0;
    //int rc;
    
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }
    rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    
    return 0;
}


void getDiffOfSqlite(char** word,string& name){

    std::string s1 = name+"1.txt",s2=name+"2.txt";
    sqlReader(word[1],s1.c_str());
    auto m = sqlDiff;
    sqlDiff.clear();
    sqlReader(word[2],s2.c_str());
    auto n = sqlDiff;
    sqlDiff.clear();
    string outName = name+"-diffout.txt";

    stringToFile(outName,getDiffofSqldiff(m,n));
    

}