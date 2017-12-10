//
//  diffGenerator.hpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/11/27.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef diffGenerator_hpp
#define diffGenerator_hpp

#include <stdio.h>

#endif /* diffGenerator_hpp */

void commonGenerator(const char* out);     //generator differ file between two new container
void paticularGenerator(const char* f1,const char* f2,const char* out);

void jsonGenerator(const char* f1,const char* f2,const char* out);

int getDirectory2(char* dir,char fname[]);
int getDirectory(char fname[][256]);
int createDirectory(char* s,char* ret);
int out_log(FILE* input,const char* out);
