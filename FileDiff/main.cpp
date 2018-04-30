#include "iostream"
#include "vector"
#include "string"
#include "stdio.h"
#include "stdlib.h" 
#include "diff.h"

#include "container.h"

#include "preprocessor.h"
using namespace std;

#define OUT_FILE_PATH "log.txt"



int main(int argc, char *argv[])
{
    //initLog();

    vector<string> path = twinsPreProcessor();

    if(path.size()!=2){
        printf("path size is not 2\n");
        return 0;
    }

    paticularGenerator(path[0].c_str(),path[1].c_str(),OUT_FILE_PATH);




           // stringToFile(inContent,outPath+'/'+fileName+config.fileSuffix);
          /* 
    commonGenerator("log.txt");
    
    std::string Path = "log.txt";
    
    ifstream fa(OUT_FILE_PATH);

    ofstream of("outa.txt");
    streambuf* fileBuf = of.rdbuf();
    
    cout.rdbuf(fileBuf);
    

    auto m = mainDetector(fa);
*/
/*
string inContent = fileToString("cookies.sqlite1.txt");
inContent = wordScanner(inContent,TimeStampFilter());
stringToFile(inContent,"cookies.sqlite1.txt.filter");
*/
    /*
    for(auto& c:m){
        c.print();
    }*/
    //of.close();

    return 0;
    
}
