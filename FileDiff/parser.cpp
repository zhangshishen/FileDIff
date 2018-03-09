//
//  parser.cpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/9/5.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//


#include "parser.h"



char* keyword[6]={"diff","and","Binary","file","differ","Only"};


// first line of diff command *[,*]c[,*]

char lineNum(const std::string& s,int res[4]){
    res[0]=res[1]=res[2]=res[3]=0;
    int *pt = res;
    char ret = 0;
    for(auto c:s){
        if(c>='0'&&c<='9'){
            (*pt)*=10;
            (*pt)+=c-'0';
        }else if(c==','){
            pt++;
        }else if(c=='c'||c=='a'||c=='d'){
            ret = c;
            pt=res+2;
        }else printf( "error %s on line %d\n " ,  __FILE__, __LINE__);
        
    }
    if(res[1]==0) res[1]=res[0];
    if(res[3]==0) res[3]=res[2];
    return ret;
    
}


int sentenceFormat(char **word){
    if(strcmp(word[0],keyword[0])==0){
        return DIFF;
    }else if(strcmp(word[0],keyword[5])==0){
        
    }
    else if(strcmp(word[0],keyword[2])==0){
        return BIN;
    }else if(strcmp(word[4],keyword[4])==0){
        //return BIN;
    }
    return -1;
}


//read a line frome file stream

int readLine(char **word,char* buf){
    
    int i = 0,j = 0;
    int index = 0;
    
    char* pBuf = buf;
    
    while(*pBuf!=0)
    {
        if(*pBuf==' ')
        {
            word[index] = (char*) malloc(256);
            int temp = 0;
            
            while(i!=j){
                
                word[index][temp] = buf[i];
                i++;
                temp++;
                
            }
            
            word[index][temp] = 0;
            index++;
            i++;j++;
            pBuf++;
        }
        else
        {
            pBuf++;
            j++;
            
        }
    }
    
    
    word[index] = (char*) malloc(j-i+1);
    int temp = 0;
    
    
    while(i!=j){
        word[index][temp] = buf[i];
        i++;
        temp++;
    }
    word[index][temp] =0;
    
    
    return index+1;
    
}


