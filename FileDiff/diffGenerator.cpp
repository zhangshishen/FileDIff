//
//  diffGenerator.cpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/11/27.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "diffGenerator.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char buf[10240];
int getDirectory2(char* dir,char fname[]){
    FILE* fs;
    //char fname[2][256];
    memset(buf,0,sizeof(buf));
    char d[256]="ls ";
    strcpy(d+3,dir);
    fs=popen(d,"r");
    int r = fread(buf,sizeof(char),sizeof(buf),fs);
    //printf("%s\n",buf);
    if(r<1024){
        int c=0,start=0;
        while(buf[c]!=0){
            while(buf[c]!='\n'&&buf[c]!=0)	c++;
            if(buf[c-1]=='t'){
                buf[c]=0;
            }else if(buf[c]==0) ;
            else {start=c+1;c++;continue;}
            strcpy(fname,buf+start);
            start=c+1;
            c++;
        }
        pclose(fs);
        return 1;
    }
    pclose(fs);
    return -1;
}
int getDirectory(char fname[][256]){
    FILE* fs;
    //char fname[2][256];
    memset(buf,0,sizeof(buf));
    fs=popen("ls /var/lib/docker/overlay2","r");
    int r = fread(buf,sizeof(char),sizeof(buf),fs);
    //printf("%s\n",buf);
    if(r<10240){
        int c=0,start=0,fnamen=0;
        while(buf[c]!=0){
            while(buf[c]!='\n'&&buf[c]!=0)	c++;
            if(buf[c-1]=='t'){
                buf[c-5]=0;
            }else if(buf[c]==0) ;
            else {start=c+1;c++;continue;}
            strcpy(fname[fnamen++],buf+start);
            start=c+1;
            c++;
        }
        pclose(fs);
        return fnamen;
    }
    pclose(fs);
    return -1;
}
int createDirectory(char* s,char* ret){
    char *m= "/var/lib/docker/overlay2/";
    char *n="/diff/root/.mozilla/firefox/";
    strcpy(ret,m);
    strcpy(ret+strlen(m),s);
    strcpy(ret+strlen(m)+strlen(s),n);
    char a[64];
    getDirectory2(ret,a);
    strcpy(ret+strlen(ret),a);
    return 1;
}
int out_log(FILE* input,const char* out){
    FILE* log;
    memset(buf,0,sizeof(buf));
    log=fopen(out,"w+");
    int r;
    while(r=fread(buf,1,sizeof(buf),input))
        fwrite(buf,1,r,log);
    return fclose(log);
}
void commonGenerator(const char* out){
    char fname[4][256];
    char browse1[256];
    char browse2[256];
    getDirectory(fname);
    createDirectory(fname[0],browse1);
    int temp = strlen(browse1);
    browse1[temp]=' ';
    browse1[temp+1]=0;
    createDirectory(fname[1],browse2);
    char command[512]="diff ";
    strcpy(command+5,browse1);
    int i = strlen(command);
    strcpy(command+i,browse2);
    printf("%s\n",command);
    FILE* f = popen(command,"r");
    out_log(f,out);
    pclose(f);
}
void paticularGenerator(const char* f1,const char* f2,const char* out){
    
    char command[512]="diff ";
    strcpy(command+5,f1);
    int i = strlen(command);
    strcpy(command+i,f2);
    FILE* f = popen(command,"r");
    out_log(f,out);
    pclose(f);
}
int main(){
    char fname[4][256];
    char browse1[256];
    char browse2[256];
    getDirectory(fname);
    createDirectory(fname[0],browse1);
    int temp = strlen(browse1);
    browse1[temp]=' ';
    browse1[temp+1]=0;
    createDirectory(fname[1],browse2);
    char command[512]="diff ";
    strcpy(command+5,browse1);
    int i = strlen(command);
    strcpy(command+i,browse2);
    printf("%s\n",command);
    FILE* f = popen(command,"r");
    out_log(f,"log.txt");
    pclose(f);
}
///var/lib/docker/overlay/694c7cebf61379ee36d7c0058f819ecf99f546e4c73c6356aafd8b47469e1e99/upper/home/developer/.mozilla
