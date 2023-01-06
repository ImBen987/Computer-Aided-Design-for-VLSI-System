#include "header.h"

void str_split(string str,vector<string>&in){
    while (str.find(" ")!=str.npos){
        in.push_back(str.substr(0, str.find(" ")));
        str.erase(0,str.find(" ")+1);
    }
    if(str!="#")
        in.push_back(str);
}
void relationship(vector<string> &in){
    //node's relationship
    for(int i=0;i<in.size()-1;i++){
        if(find(inputV.begin(), inputV.end(), in[i]) != inputV.end())
            continue;
        else
            edge.insert({in[in.size()-1],in[i]});
    }
}

void file_RW(string file){

    ifstream ifs(file, ios::in);;
    vector<string> names;
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        string s;
        int i=1;
        while (!ifs.eof()) {
            int input=0,single_output=0;
            if(s.find(".inputs ")!=s.npos){
                s.erase(0,s.find(" ")+1);
                str_split(s,names);
                while(names[names.size()-1]=="\\"){
                    names[names.size()-1].pop_back();
                    getline(ifs, s);
                    str_split(s,names);
                }
                for(int i=0;i<names.size();i++){
                    inputV.push_back(names[i]);
                }
                getline(ifs, s);
            }
            else if(s.find(".names ")!=s.npos){
                s.erase(0,s.find(" ")+1);
                str_split(s,names);
                while(names[names.size()-1]=="\\"){
                    names.pop_back();
                    getline(ifs, s);
                    str_split(s,names);
                }
                input = names.size()-1;
                relationship(names);
                getline(ifs, s);
                if(s.find(".names ")!=s.npos){
                    names.clear();
                    continue;
                }
                single_output=1;
               
                while (getline(ifs, s)){
                    if(s.find(".names ")==s.npos and s.find(".end")==s.npos){                        
                       single_output+=1;
                    }
                    else break;
                }
                area.insert({names[names.size()-1],input+single_output});
                vertex.insert(names[names.size()-1]);
                
            
            }
            else getline(ifs, s);
            names.clear();
        }
        ifs.close();
    }

}