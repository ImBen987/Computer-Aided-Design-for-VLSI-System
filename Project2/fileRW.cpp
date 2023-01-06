#include "blif_RW.h"

void graph_bool(string s,string &boo){
    string out = s.substr(s.find(" ")+1,s.length());
    string op = s.substr(0,s.find(" "));
    int count=0;
    for(int i=0;i<op.length();i++){
        if(op[i]=='-') continue;
        else if(op[i]=='0' and !(stoi(out)==0 and stoi(op)==0)) boo[2]='1';
        if(op[i]!='-') count+=1;
    }
    if(count>1)boo[0]='1';
}

void str_split(string str,vector<string>&in){
    while (str.find(" ")!=str.npos){
        in.push_back(str.substr(0, str.find(" ")));
        str.erase(0,str.find(" ")+1);
    }
    if(str!="#")
        in.push_back(str);
}
void addvertex(vector<string>&n){
    for(int i=0;i<n.size();i++)
        vertex.insert(n[i]);
}

void relationship(vector<string> &in){
    //node's relationship
    for(int i=0;i<in.size()-1;i++)
        edge.insert({in[in.size()-1],in[i]});
}

void file_RW(string file){

    ifstream ifs(file, ios::in);;
    vector<string> names;
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        string s;
        while (!ifs.eof()) {
            if(s.find(".inputs ")!=s.npos){
                s.erase(0,s.find(" ")+1);
                str_split(s,names);
                while(names[names.size()-1]=="\\"){
                    names[names.size()-1].pop_back();
                    getline(ifs, s);
                    str_split(s,names);
                }
                addvertex(names);
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
                relationship(names);
                string boo="000";//[0] and_gate [1] or_gate [2] not_gate
                getline(ifs, s);
                if(s.find(".names ")!=s.npos){
                    names.clear();
                    continue;
                }
                graph_bool(s,boo);
                while (getline(ifs, s)){
                    if(s.find(".names ")==s.npos and s.find(".end")==s.npos){                        
                       graph_bool(s,boo);
                       boo[1]='1';
                    }
                    else break;
                }
                output.insert({names[names.size()-1],boo});
            }
            else getline(ifs, s);
            names.clear();
        }
        ifs.close();
    }

}