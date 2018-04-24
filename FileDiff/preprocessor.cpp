#include "preprocessor.h"



bool isTargetFileFormat(const string& s){
    if(s==".txt"||s==".json"||s==".JSON"||s==".xml"||s==".js"){
        return true;
    }else return false;
}


/*
string preProcess(const string& inFileContent,const Filter& fil){


    //string inFile = fileToString(fileName);
    //string outFile;



    if(!isTargetFileFormat(sFormat)){
        return inFileContent;
    }

    ifstream srcFile(fileName);
    ofstream outFile(outName);



    if(!srcFile.is_open()){
        perror("pre process src file open failed\n");
        return 0;
    }

    if(!outFile.is_open()){
        perror("pre process out file open failed\n");
        return 0;
    }

    outFile = wordScanner(inFile,fil);

    stringToFile(outName,outFile);

    return 1;
}*/
string Config::filterData(const string& content){

}
int Config::matchFilter(const string& name){

        if(nameFilter.size()==0){
            
            return 0;
        }
        
        for(auto &s:nameFilter){
            if(stringMatch(name,s)){
                return 1;
            }
        }

        return 0;
        
}



string preProcessor(const string& folderPath,const string& outPath,Config& config){

    string res = makeTempFolder(config.name+to_string(config.mutableFlag));

    if(config.mutableFlag==0){
        config.mutableFlag = 1;
    }
    

    auto fileList = separateString(exec((string("ls ")+folderPath).c_str()),'\n');

    for(string& fileName:fileList){
        
        if(config.matchFilter(fileName)){
            continue;
        }

        if(isDirectory(fileName)){

            preProcessor(string(folderPath+'/'+fileName),string(outPath+'/'+fileName+config.fileSuffix),config);

        }else{
            
            auto inContent = fileToString(fileName);
            for(auto pFilter:config.filter){
                inContent = wordScanner(inContent,*pFilter);
            }

            stringToFile(inContent,outPath+fileName+config.fileSuffix);
            //preProcess(fileName,string(outPath+config.fileSuffix),timeStampFilter());
            //auto stringOfFile = fileToString(fileName);
            
        }
    }

    return res;
}

vector<string> twinsPreProcessor(){
    vector<string> res;
    vector<string> idList = recentOpenedContainer(2);

    if(idList.size()!=2){
        printf("folder size not equal to 2\n");
        return res;
    }
    
    Config config;
    config.nameFilter.push_back("(?i:cache)");
    config.name = "pre";

    
    
    string path = getContainerPath(idList[0]);
    res.push_back(preProcessor(path,"",config));
    path = getContainerPath(idList[1]);
    res.push_back(preProcessor(path,"",config));

    return res;
}