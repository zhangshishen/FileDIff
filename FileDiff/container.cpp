#include "container.h"

using namespace std;

const string dockerIdCommand = "docker ps -n 2 -q ";
const string dockerDiffdirCommand = "docker inspect --format='{{.GraphDriver.Data.UpperDir}}' " ;


string getContainerId(){
    return Exec(dockerIdCommand.c_str());
}

string getContainerPath(const string containerID){
    return Exec((dockerDiffdirCommand+containerID).c_str());
}

vector<string> recentOpenedContainer(int number = 2){

    vector<string> s;
    string result = getContainerId();

    s = separateString(result,{'\n'});

    if(s.size()<number){
        printf("container number less than %d",number);
    }

    return s;

}