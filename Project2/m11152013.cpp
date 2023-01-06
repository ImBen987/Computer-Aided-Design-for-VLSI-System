#include "blif_RW.h"

multimap<string ,string> edge;
map<string,string> output;
set<string> vertex;

int main(){
    string command;
    vector<string> splitcmd;
    getline(cin,command);
    //command="list -l case2.blif 7 11 1";
    str_split(command,splitcmd);

    file_RW(splitcmd[2]);
    
    if(splitcmd[1]=="-l")
        ML_RCS(stoi(splitcmd[3]),stoi(splitcmd[4]),stoi(splitcmd[5]));//and,or,not
    if(splitcmd[1]=="-r") 
        MR_LCS(stoi(splitcmd[3]));//lantency
    
    return 0;
}