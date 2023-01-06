#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

void str_split(string str,vector<string>&in){
    while (str.find(" ")!=str.npos){
        in.push_back(str.substr(0, str.find(" ")));
        str.erase(0,str.find(" ")+1);
    }
    in.push_back(str);
}

void create_file(string file,int fa,int fb){
    
    ifstream ifs(file, ios::in);;
    
    ofstream a,b;
    a.open("a.pla");
    b.open("b.pla");
    
    string s;
    while (!ifs.eof()){
        vector<string> temp;
        getline(ifs, s);
        if(s.find(".o ")!=s.npos){
            a<<".o 1"<<endl;
            b<<".o 1"<<endl;
        }
        else if(s.find(".ob ")!=s.npos){            
            str_split(s,temp);
            a<<".ob "<<temp[fa]<<endl;
            b<<".ob "<<temp[fb]<<endl;
        }
        else if(s[0]=='0' or s[0]=='1' or s[0]=='-'){
            str_split(s,temp);
            string out = temp[1];
            a<<temp[0]<<" "<<out[fa-1]<<endl;
            b<<temp[0]<<" "<<out[fb-1]<<endl;
        }
        else{
            a<<s<<endl;
            b<<s<<endl;
        }
    }
    a.close();
    b.close();
}

bool shellCmd(const string &cmd, string &result) {
    char buffer[512];
    result = "";

    // Open pipe to file
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return false;
    }

    // read till end of process:
    while (!feof(pipe)) {
        // use buffer to read and add to result
        if (fgets(buffer, sizeof(buffer), pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return true;
}


void write_pla(string result ,string file){
    ofstream f;
    f.open(file);
    f<<result;
    f.close();
}
void bool_or(){
    string temp;
    system("./espresso -Dunion a.pla b.pla > or.pla");
    shellCmd("./espresso -Dexact or.pla", temp);
    write_pla(temp,"or.pla");
}

void bool_and(){
    string temp;
    system("./espresso -Dintersect a.pla b.pla  > and.pla");
    shellCmd("./espresso -Dexact and.pla", temp);
    write_pla(temp,"and.pla");
}

void bool_xor(){
    string temp;
    system("./espresso -Dxor a.pla b.pla  > xor.pla");
    shellCmd("./espresso -Dexact xor.pla", temp);
    write_pla(temp,"xor.pla");
}

int main(){
    
    string command;
    vector<string> splitcmd;
    getline(cin,command);
    str_split(command,splitcmd);
    
    
    create_file(splitcmd[1],stoi(splitcmd[2]),stoi(splitcmd[3]));
    

    string temp;
    shellCmd("./espresso -Dexact a.pla", temp);
    write_pla(temp,"a.pla");
    shellCmd("./espresso -Dexact b.pla", temp);
    write_pla(temp,"b.pla");    
    
    bool_or();
    bool_and();
    bool_xor();
    
    
    
    return 0;
    

}