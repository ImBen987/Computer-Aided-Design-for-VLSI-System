#include "blif_RW.h"

void file_format(string s,vector<string> &n){
    string out = s.substr(s.find(" ")+1,s.length());
    string op = s.substr(0,s.find(" "));

    if(out=="0" and op.find('-')== op.npos and stoi(op)!=0) fout <<"( " ;
    for(int i=0;i<op.length();i++){
        if(op[i]=='-') continue;
        fout <<n[i];
        if(op[i]=='0' and !(stoi(out)==0 and stoi(op)==0)) fout<<"'";
        fout<<" ";
    }
    if(out=="0" and op.find('-')== op.npos and stoi(op)!=0) fout <<")'" ;
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
    addvertex(in);
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
        fout.open("function.out");
        fout<< "Node function:"<<endl;
        string s;
        while (!ifs.eof()) {

            if(s.find(".inputs ")!=s.npos or s.find(".outputs ")!=s.npos){
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
                getline(ifs, s);
                if(s.find(".names ")!=s.npos){
                    names.clear();
                     continue;
                }
                fout << names.back() << " = " ;
                file_format(s,names);

                while (getline(ifs, s)){
                    if(s.find(".names ")==s.npos and s.find(".end")==s.npos){
                        fout<< "+ ";
                        file_format(s,names);   
                    }
                    else break;
                }
                fout<< endl;
            }
            else getline(ifs, s);
            names.clear();
        }
        ifs.close();
        fout<<"END"<<endl;
        fout.close();
    }

}