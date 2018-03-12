#include "dynamicInspect.h"


void makeFileByLine(const string& outName,vector<string> &content){     //create file from content
    
    std::ofstream m(outName);
    
    for(auto& c:content){
        m<<c<<endl;
    }
}

static string Log = "DiffLog" + getCurrentTime();


void getDiffByDefault(){   // get the diff file, then append to the eventually log file

    auto mid = dockerGetId();
    vector<string> containerId;
    vector<string> nameVector;

    for (auto &c:mid){
        if(dockerGetImageName(c)==containerName){
            containerId.push_back(c);
        }
    }
    if(containerId.size()!= 2){
        cerr<<"fatal error!,more than two container running";
    }
    
    for (auto &c:containerId){

        auto diffContent = dockerDiff(c);

        if(diffContent.size()==0){
            diffContent.push_back("No such different file");
        }

        string logName("tmp-dockerDiffLog-");
        logName+=getCurrentTime();

        //create docker diff out file log
        makeFileByLine(logName,diffContent);
        nameVector.push_back(logName);
    }

    string diffFileName("tmp-diffResult-");    //the out file of diff command
    diffFileName+=getCurrentTime();
    paticularGenerator(nameVector[0].c_str(),nameVector[1].c_str(),diffFileName.c_str());

    if(filesize(diffFileName.c_str())==0){  //no diff content, the same file
        return ;
    }

    std::ofstream log;
    log.open(Log,std::ios_base::app); //open the eventually log file
    log<<"Time:\t"<<getCurrentTime<<endl;
    log.close();

    fileAppend(Log.c_str(),diffFileName.c_str());

    //remove temp file
    string removeCommand = dockerCreateCommand({"rm","tmp-*"},' ');;
    exec(removeCommand.c_str());

}