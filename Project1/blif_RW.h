#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

extern ofstream fout;

extern multimap<string ,string> edge;
extern set<string> vertex;

void file_format(string s,vector<string> &n);
void str_split(string str,vector<string>&in);
void relationship(vector<string> &in);
void addvertex(vector<string>&n);
void file_RW(string file);