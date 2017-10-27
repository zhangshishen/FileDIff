//
//  detector.cpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/9/5.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "detector.h"
#define URL 0
#define PASSWORD 1
#define ID 2
#define HISTORY 3
/*
 
 detect the file's key word
 
 */

//check if the difference match key word

int stringMatch(const std::string& src,const std::string& dest){
    int i = 0;
    
    while(i<src.size()){
        
        int p = 0,j=i;
        
        while(j<src.size()&&p<dest.size()&&src[j]==dest[p])
        {
            j++;p++;
        }
        
        if(p==dest.size())
            return 1;
        i++;
    }
    return 0;
}

int isURL(const std::string& s)
{
    if(stringMatch("http",s)||stringMatch("com",s)||stringMatch("www",s))
        return 1;
    else return 0;
}

int classify(const std::string& s)
{
    return 0;
}

int isPrivacy(std::vector<std::string>& words)
{
    for(auto& s:words){
        
    }
    return 1;
}


