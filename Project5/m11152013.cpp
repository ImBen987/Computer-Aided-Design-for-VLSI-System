#include "header.h"
#include <fstream>
#include <iomanip>
vector<string> inputV;
multimap<string ,string> edge;
map<string,int> area;
set<string>  vertex;

int GetIndex(string K)
{
 
    // To store the index of K
    int Index = 1;
 
    // Traverse the Set
    for (auto &u :vertex) {
        if (u == K)
            return Index;
 
        Index++;
    }
    return -1;
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

int main(){

    ofstream fout;
    fout.open("graph.hgr");

    string command;
    vector<string> splitcmd;
    getline(cin,command);
    //command="par pcle.blif 0.52";
    str_split(command,splitcmd);
    file_RW(splitcmd[1]);
    int cycle=0;
    for(auto &x :vertex)
        if(edge.count(x)>=1)
            cycle+=1;

    fout<< to_string(cycle) + " " + to_string(vertex.size())+" 10\n";
    int h=0;
    for(auto &x : vertex){
        int t=0;
  //      if(edge.count(x)>0)
  //          fout <<edge.count(x)<<" ";
        for(auto &y : edge){
            if(y.first == x){
                int index = GetIndex(y.second);
                if(index>=0){
                    
                    fout <<index<< " "<<flush;           
                    t=1;
                } 
            }
        }
        if(t==1) {
            int index = GetIndex(x);
            fout<< to_string(index) +"\n"<<flush;
        }
    }
    for(auto &x :vertex)
        fout<< area.find(x)->second<<"\n"<<flush;
    fout.close();
    string t = command.substr(command.size()-1,1);
    int fa = (stof(splitcmd[2]) -0.5) *100 +stof(t) ;
    string sx = "./hmetis.exe graph.hgr 2 "+to_string(fa) +" 20 1 1 3 0 0";
    const char *s = sx.c_str();
    shellCmd(s,t);
   // cout <<t;

    ifstream ifs("graph.hgr.part.2", ios::in);;
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        vector<string> X;
        vector<string> Y;
        double area_X=0,area_Y=0;
        int cut=0;
        for(auto x : vertex){
            string s ="";
            getline(ifs, s);
            if(s[0]=='0'){
                 X.push_back(x);
                 area_X+=area.find(x)->second;
            }
            else{ 
                Y.push_back(x);
                area_Y+=area.find(x)->second;
            }
        }
        ifs.close();

        cout<< "Partition X"<<endl;
        cout<< "Node: ";
        for(int i=0;i<X.size()-1;i++)
            cout<< X[i] << " ";
        cout<<X[X.size()-1]<<endl;
        cout<< "Area: " << area_X <<endl;
        cout<< "Ratio:"  <<setprecision(3)<<area_X/(area_X+area_Y)<<endl;

        cout<< "Partition Y"<<endl;
        cout<< "Node: ";
        for(int i=0;i<Y.size()-1;i++)
            cout<< Y[i] << " ";
        cout<<Y[Y.size()-1]<<endl;
        cout<< "Area: " << area_Y <<endl;
        cout<< "Ratio: " <<setprecision(3)<<area_Y/(area_X+area_Y)<<endl;
        for(auto &x :edge){
            if((find(X.begin(), X.end(), x.first) != X.end()) and (find(X.begin(), X.end(), x.second) == X.end()))
                    cut+=1;
            if((find(Y.begin(), Y.end(), x.first) != Y.end()) and (find(Y.begin(), Y.end(), x.second) == Y.end()))
                    cut+=1;
        }
        cout<<"Cut size: "<<cut<<endl;
        cout<<"End"<<endl;
    }
  //  system("rm graph.hgr graph.hgr.part.2");
    return 0;
}