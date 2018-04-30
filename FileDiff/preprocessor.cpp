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

string getName(const string& folderPath){
    string out;
    for(int i = folderPath.size()-1;i>=0;i--){
        if(folderPath[i]=='/'){
            break;
        }else out.push_back(folderPath[i]);
    }
    reverse(out.begin(),out.end());
    return out;
}

string preProcessor(const string& folderPath,const string& outPath,Config& config){

    string folderName = getName(folderPath);

    string res = outPath;
    /*
    if(config.mutableFlag==0){
        config.mutableFlag = 1;
    }
    */
    //list all the file in folder
    auto fileList = separateString(exec((string("ls -1a ")+folderPath).c_str()),'\n');

    for(string& fileName:fileList){
        //cout<<"open file "<<fileName<<endl;
        /*
        if(config.matchFilter(fileName)){
            continue;
        }
*/
/*

        const char* format = getFormat(fileName.c_str());
        if(format!=NULL&&strcmp(".sqlite",format)==0){
            //sqlitefile
            getSqldump(folderPath+'/'+fileName,fileName+"-dump");
            //fileName = fileName+"-dump";
        }
*/


        if(isDirectory(folderPath+'/'+fileName)){

            if(fileName=="."||fileName==".."){
                continue;
            }

            string res = makeTempFolder(outPath+'/'+fileName);
            preProcessor(string(folderPath+'/'+fileName),string(outPath+'/'+fileName+config.fileSuffix),config);

        }else{

            //TODO

            auto inContent = fileToString(folderPath+'/'+fileName);

                //inContent = fileToString(fileName+"-dump");

            for(auto pFilter:config.filter){
                string mid;
                const char* format = getFormat(fileName.c_str());
                if(format==NULL){
                    mid ="";
                }else mid = format;
                if(pFilter->matchFormat(mid)){
                    inContent = pFilter->excute(inContent,folderPath+'/'+fileName);
                }
            }

            stringToFile(inContent,outPath+'/'+fileName+config.fileSuffix);
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

    TimeStampFilter tf;
    Sqlitefilter sf;

    Config config;

    config.filter.push_back(&sf);
    config.filter.push_back(&tf);


    config.nameFilter.push_back("([\\s\\S]*).cache([\\s\\S]*)");


    config.name = "pre";

    
    
    string path = getContainerPath(idList[0]);
    string outPath1 = makeTempFolder("./diff1"),outPath2 = makeTempFolder("./diff2");

    res.push_back(preProcessor(path+"/root/.mozilla/firefox",outPath1,config));
    //config.mutableFlag = 1;
    path = getContainerPath(idList[1]);
    res.push_back(preProcessor(path+"/root/.mozilla/firefox",outPath2,config));

    return res;

}