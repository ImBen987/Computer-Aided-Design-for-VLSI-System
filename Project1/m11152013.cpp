#include "blif_RW.h"

ofstream fout;
multimap<string ,string> edge;
set<string> vertex;

int main(){
    
    string file ;
    cout<< "blif_parser> ";
    cin>>file;
    file_RW(file);
    while(1){
        string n;
        cout<<"Please input a node: ";
        cin >> n;
        if(n=="0") break;
        else if(!vertex.count(n)) cout<< "node " << n<<" does not exist"<<endl;
        else{
            int count = 0;
            cout<<"predecessor: ";
            for(auto x = edge.begin(); x != edge.end(); ++x){
                if(x->first==n){
                    count+=1;
                    if (count>1 and (x!=edge.end()))cout<<", ";
                    cout<<x->second;
                }
            }
            if(!count) cout<<"-";   
            
            cout<< endl <<"successor: ";
            count = 0;
            for(auto x = edge.begin(); x != edge.end(); ++x){
                if(x->second==n){
                    count+=1;
                    if (count>1 and (x!=edge.end())) cout<<", ";
                    cout<<x->first;
                }
            }
            if(!count) cout<<"-";        
            cout<<endl;
        }
    }
    return 0;
}