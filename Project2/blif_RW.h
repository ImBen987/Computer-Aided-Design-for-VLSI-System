#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;


extern multimap<string ,string> edge;
extern map<string,string> output;
extern set<string> vertex;


void graph_bool(string s,string &boo);
void str_split(string str,vector<string>&in);
void relationship(vector<string> &in);
void addvertex(vector<string>&n);
void file_RW(string file);

void ML_RCS(int a,int o,int n);
void MR_LCS(int l);