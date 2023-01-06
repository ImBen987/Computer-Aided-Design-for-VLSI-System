#include "blif_RW.h"
#include <stack>

string and_or_not_gate(int gate,int x,vector<string>ready_node){
    string s="{";
    int g=gate;
    for(int i=0;i<ready_node.size();i++){
        string b =output.find(ready_node[i])->second;
        if(b[x]=='1' and gate>0){
            if(gate!=g) s+=" ";
            g= gate--;
            output.find(ready_node[i])->second[x] = '0';
            s+=ready_node[i];

        }
    }
    s+="}";
    return s;
}

void ready_state(vector<string> &ready_node){
    for(auto it =output.begin();it!=output.end();){
        if(it->second=="000"){
            string s = it->first;
            edge.erase(s);
            vertex.insert(s);
            output.erase(it++);       
        }
        else
            ++it;
    }
    ready_node.clear();
    for(auto &r:output){
        int count = edge.count(r.first);
        for(auto &E:edge)
            if (E.first==r.first and vertex.count(E.second))
                count-=1;
        if(count==0) ready_node.push_back(r.first);
    }
}

void ML_RCS(int a,int o,int n){

    cout<<"Resource-constrained Schediling"<<endl;
    bool result=true;
    for(auto &r:output){
        string s = r.second;
        if(int(s[0])-'0' > a or int(s[1])-'0'>o  or int(s[2])-'0'>n)
            result=false;
    }
    if(!result)
        cout<<"No feasible solution."<<endl;
    else{
        vector<string> ready_node;
        vector<string> schedul;
        ready_state(ready_node);
        while(!ready_node.empty()){
            string str;
            str=str + and_or_not_gate(a,0,ready_node)+" " \
                +and_or_not_gate(o,1,ready_node)+" " \
                +and_or_not_gate(n,2,ready_node);
            schedul.push_back(str);
            ready_state(ready_node);
        }
        for(int i=0;i<schedul.size();i++){
            cout<<i+1<<": " <<schedul[i]<<endl;
        }
        cout<<"#AND: "<<a<<endl<<"#OR: "<<o<<endl<<"#NOT: "<<n<<endl \
                <<"END"<<endl;
    }
}   

int min_path(vector<string> node,int a,int o,int n){
    int path=0;
    ready_state(node);
    while(!node.empty()){
        string str;
        str=str + and_or_not_gate(a,0,node)+" " \
                +and_or_not_gate(o,1,node)+" " \
                +and_or_not_gate(n,2,node);
        path+=1;
        ready_state(node);
    }
    return path;
}
void MR_LCS(int l){
    cout<<"Resource-constrained Schediling"<<endl;
    int a=0,o=0,n=0;
    vector<string> ready_node;
    vector<string> schedul;

    multimap<string ,string>e_t= edge;
    map<string,string>o_t= output;
    set<string>v_t= vertex;

    int min_p = min_path(ready_node,INT32_MAX,INT32_MAX,INT32_MAX);
    if (min_p>l){
        cout<<"No feasible solution."<<endl;
    }
    else{
        int max_p=0;
        edge=e_t;output=o_t;vertex=v_t; min_p=0;
        ready_state(ready_node);
        while(!ready_node.empty()){
            int x=0,j=0,k=0;
            for(int i=0;i<ready_node.size();i++){
                string s = output.find(ready_node[i])->second;
                if(int(s[0])-'0' > 0 ) x+=1; //and gate
                if(int(s[1])-'0' > 0 ) j+=1; //or  gate
                if(int(s[2])-'0' > 0 ) k+=1; //not gate
            }
            if(x>a) a=x; if (j>o) o=j; if(k>n) n=k;
            string str;
            str=str + and_or_not_gate(a,0,ready_node)+" " \
                    +and_or_not_gate(o,1,ready_node)+" " \
                    +and_or_not_gate(n,2,ready_node);
            max_p+=1;
            ready_state(ready_node);
        }
        cout<< max_p<<" "<< a<<" "<<o<<" "<< n<<endl;
        int m=0,g=0;
        char r=' ';
        while(min_p<=l){
            edge=e_t;output=o_t;vertex=v_t;
            if(a==1 and o==1 and n==1){g=1; break;}
            m =max(max(a,o),n);
            if(m==a){r='a';a-=1; min_p = min_path(ready_node,a,o,n);}
            else if(m==o){r='o';o-=1; min_p = min_path(ready_node,a,o,n);}
            else if(m==n){r='n';n-=1; min_p = min_path(ready_node,a,o,n);}
                       

        }
         cout <<min_p<<" "<< a<<" "<<o<<" "<< n<<endl;
        if(r=='a' and g!=1 ) a+=1;
        else if (r=='o' and g!=1) o+=1; 
        else if (r=='n' and g!=1) n+=1;
        edge=e_t;output=o_t;vertex=v_t;
        min_p = min_path(ready_node,a,o,n);
        while(min_p<=l and r!='a' and a>1){
            edge=e_t;output=o_t;vertex=v_t;
            int x = min_path(ready_node,a-1,o,n);
            if(x>l) break;
            else if(x<=l){
                a= a-1;
                min_p=x;
            }
        }
        edge=e_t;output=o_t;vertex=v_t;
        min_p = min_path(ready_node,a,o,n);
        while(min_p<=l and r!='o' and o>1){
            edge=e_t;output=o_t;vertex=v_t;
            int x = min_path(ready_node,a,o-1,n);
            if(x>l) break;
            else if(x<=l){
                o= o-1;
                min_p=x;
            }     
        }
        edge=e_t;output=o_t;vertex=v_t;
        min_p = min_path(ready_node,a,o,n);
        while(min_p<=l and r!='n' and n>1){
            edge=e_t;output=o_t;vertex=v_t;
            int x = min_path(ready_node,a,o,n-1);
            if(x>l) break;
            else if(x<=l){
                n= n-1;
                min_p=x;
            }      
        }
        
        edge=e_t;output=o_t;vertex=v_t;
        ready_state(ready_node);
        while(!ready_node.empty()){
            string str;
            str=str + and_or_not_gate(a,0,ready_node)+" " \
                    +and_or_not_gate(o,1,ready_node)+" " \
                    +and_or_not_gate(n,2,ready_node);
            schedul.push_back(str);
            ready_state(ready_node);
        }
        for(int i=0;i<schedul.size();i++){
            cout<<i+1<<": " <<schedul[i]<<endl;
        }
        cout<<"#AND: "<<a<<endl<<"#OR: "<<o<<endl<<"#NOT: "<<n<<endl \
            <<"END"<<endl;
    }
}