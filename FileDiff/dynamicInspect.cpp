#include "dynamicInspect.h"





vector<string> getDiff(){
    auto mid = dockerGetId();
    vector<string> containerId;
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
    }

    //paticularGenerator()
    string command = dockerCreateCommand({"docker","diff","-aq"},' ');
}