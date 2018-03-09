#include "dynamicInspect.h"





vector<string> getDiff(){
    auto m = dockerGetId();
    int count = 0;
    vector<string> containerId;
    for (auto &c:m){
        if(dockerGetImageName(c)==containerName){
            count++;
            containerId.push_back(c);
        }
    }
    if(count != 2){
        cerr<<"fatal error!,more than two container running";
    }
    for (auto &c:m){
        
    }
    string command = dockerCreateCommand({"docker","diff","-aq"},' ');
}