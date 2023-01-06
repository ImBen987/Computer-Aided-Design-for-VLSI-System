#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

extern vector<string> inputV;

extern multimap<string ,string> edge;
extern map<string,int> area;
extern set<string> vertex;

void str_split(string str,vector<string>&in);
void relationship(vector<string> &in);
void file_RW(string file);
