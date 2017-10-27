//
//  keyExtract.cpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/9/5.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//


#include "keyExtract.h"


int isHeader(char* word){
    //test if correspond to NcN
    
    int res = 0,flag = 0;
    if(*word=='-') return 1;
    
    while(*word!=0)
    {
        if(*word>='0'&&*word<='9')
        {
            if(flag == 0||flag==1)
            {
                flag = 1;
            }else if(flag == 2||flag == 3 )
                flag = 3;
            else
                return false;
            
        }else if(*word=='c'||*word=='a'||*word=='d')
        {
            if(flag==1)
                flag = 2;
            else return false;
        }else {
            if(flag==3)
            return 1;
            else return 0;
        }
        word++;
    }
    if(flag==3) return 1;
    return 0;
}

//capture the key from one line of one of the two differ files

int extractKey(std::string& str,char separator[],std::unordered_map<std::string,int>& map,int line)
{
    std::string temp;
    int count = 0;
    
    for(auto c:str){
        
    
            //detect every character of one line, extract the key
        if(separator[c]!=1){
            temp+=c;    //is not separator
        }else{
            if(!temp.empty()){
                map[temp]=line+count;
                temp.clear();
            }
            
        }
        count++;
    }
    if(!temp.empty()){
        map[temp]=line+count;
        temp.clear();
    }
    
    
    return 0;
    
}
