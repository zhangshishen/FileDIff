//
//  diff.cpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/9/5.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "diff.h"

/*
 "dir" and "dir" same directory
 
 binnary file "dir" and "dir" differs
 
 diff "" ""
 nCn
 
 
 */
// get the name from file full directory
char* getName(char* word){
    
    auto p = word;
    //int count =0;
    
    while(*word!=0)
    {
        if(*word=='/') p=word;
        word++;
    }
    
    return p+1;
    
}

// turn a string to Diff
Diff stringToDiff(const string& name,const string& str){
    Diff dif;
    auto c = separateString(str,'\n');
    if(c.size()%2){
        cerr<<"file "<<name<<" diff size is odd\n";
    }
    for(int i = 0;i<c.size();i++){
        dif.diffContent.push_back(pair<string,int>(c[i],1));
    }
    return dif;
}
// get the directory of file full directory

std::string getDir(char* word){
    
    auto init = word;
    auto p = word;
    while(*word!=0){
        if(*word=='/'){
            p = word;
        }
        word++;
    }
    
    return std::string(init,0,p-init);
    
}

char* getFormat(char* word){
    
    int pBegin = 0;
    int res = 0;

    while(word[pBegin]!=0)
    {
	
	    if(word[pBegin]=='.'){
		    res = pBegin;	
	    }
        pBegin++;
    }
    if(res==0) return NULL;

        return word+res;
}

//main diff function read a line from word
char buf[102400];
char separator[256];
char sqlSeparator[256];
//diff for common file

template<class T>
void initSeparator(const std::initializer_list<T>& t,char* dst){
    for(auto& param:t){
        dst[param] = 1;
    }
}

void commonDiff(std::ifstream& file,Diff& dif,int flag){    // get the particular diff content from the result of "diff" command between two directory
    
    int diffLine[4];
    
    initSeparator({'>' , '<' , '(' , ')' , ';' , ',' , '{' , '}' , '[' , ']' , ' ' , '\t'},separator);
    initSeparator({'>' , '<' , '(' , ')' , ';' , ',' , '{' , '}' , '[' , ']' , ' ' , '\t'},sqlSeparator);
    separator['>']=1;
    std::unordered_map<std::string,int> map1;
    std::unordered_map<std::string,int> map2;
    
    while(1){
        //file pointer
        int lineByte = file.tellg();
        file.getline(buf,102400);
        //judge if current file diff finished
        if(buf[0]>='0'&&buf[0]<='9'){
            
        }else{
            file.seekg(lineByte);
            break;
        }
        
        std::string line(buf);
    
        char mid = lineNum(line, diffLine);
    
    //file 1 keyword extract
        
        if(mid=='c'||mid=='d'){
        for(int i = diffLine[0];i<=diffLine[1];i++){
        
            lineByte = file.tellg();
            file.getline(buf,102400);
            line = buf;
            if(flag==FLAT) {
                map1[line] = 0;
                /*
                 
                 TODO
                 
                 */
            }
            else extractKey(line,separator,map1,lineByte);
        
        }
        // \ No newline at end of file
        
        int tempL = file.tellg();
        char temp;
        file.get(temp);
        if(temp == '\\') file.getline(buf,102400);
        else file.seekg(tempL);
        
        }
        if(mid=='c')
            file.getline(buf,102400);
        
        if(mid=='a'||mid=='c'){
        for(int i = diffLine[2];i<=diffLine[3];i++){
        
            lineByte = file.tellg();
            file.getline(buf,102400);
            line = buf;
            if(flag==FLAT) {    //sqlite diff
                //map2[line] = 0;
                /**
                 
                 TODO
                 
                 **/
                extractKey(line,separator,map2,lineByte);
            }
            else extractKey(line,separator,map2,lineByte);
        
        }
        int tempL = file.tellg();
        char temp;
        file.get(temp);
        if(temp == '\\') file.getline(buf,102400);
        else file.seekg(tempL);
        }

    }
    
    dif.diffContent = testKey(map1,map2);
    
}

void Diff::print(){
        cout<<"File Name:\t"<<name<<endl;
        cout<<"Diff Content:\t"<<endl;
            for(auto& n:diffContent){
                cout<<n.first<<endl;
            }
        cout<<endl;
        
}
int diff(char **word,int n,std::ifstream &file,std::vector<Diff>& resVec,int flag){
    
    if(flag==1){    //diff

    }
    char* fName = getName(word[2]);
    char* fFormat = getFormat(fName);
    
    Diff dif;
    
    dif.path1 = getDir(word[2]);
    dif.path2 = getDir(word[3]);
    
    dif.name = fName;
    if(fFormat==NULL){
        //no format
        if(flag==1){
            commonDiff(file,dif,1);
        }
    }else
    if(strcmp(fFormat,".json")==0||strcmp(fFormat,".JSON")==0)
    {
        
        //JSON file differ sub-program
    }else if(strcmp(fFormat,".XML")==0||strcmp(fFormat,".xml")==0)
    {
        //xmlfile for
        //XML file differ sub-program
    }else if(strcmp(fFormat,".sqlite")==0||strcmp(fFormat,".SQLITE")==0){

        auto m = getDiffOfSqlite(word,dif.name);
        dif = stringToDiff(fName,m);
        dif.name = fName;
        

    }else if(strcmp(fFormat,".txt")==0||strcmp(fFormat,".js")==0||flag==1)
    {
        commonDiff(file,dif,1);
    }
    
    resVec.emplace_back(dif);
    
    return 0;
    
}

//read diff file and output diff content

std::vector<Diff> mainDetector(std::ifstream &file){
    
    char* word[30];
    std::vector<Diff> resVec;
    while(!file.eof()){
        file.getline(buf, 102400);
        //if(strlen(buf)>1000)
        int length = readLine(word, buf);
        if(length>=10){     //long line
            
        }
        int sentence = sentenceFormat(word);
    
        switch(sentence){
            case DIFF:
                diff(word,length,file,resVec,1);
                break;
            case BIN:
                //strcpy(word[0],word[1]);
                //strcpy(word[1],word[2]);
     		    //strcpy(word[2],word[4]);
                diff(word,length,file,resVec,0);
                break;
            case ONLY:
                //file.getline(buf,102400);
                break;
            default:
                break;
        }
    }
    return resVec;
    
}

//test if two key set has different key

std::vector<std::pair<std::string,int>> testKey(std::unordered_map<std::string,int>&key1,std::unordered_map<std::string,int>&key2)
{
    std::vector<std::pair<std::string,int>> res;
    
    for(auto& c:key1){
        auto m =key2.find(c.first);
        if(m==key2.end()){
            res.push_back(c);
        }
    }
    for(auto& c:key2){
        auto m =key1.find(c.first);
        if(m==key1.end()){
            res.push_back(c);
        }
    }
    return res;
}