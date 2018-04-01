#include <iostream>
#include <string>
#include <fstream>
#include <vector>
// #include <ofstream>

using namespace std;

class Grammar{
	private:
		vector<string> variables;
		vector<vector<string> > rules;
		ifstream ifs;
		ofstream ofs;
	public:
		Grammar(string ifname, string ofname);
		~Grammar();
};
Grammar::Grammar(string ifname, string ofname)
	:ifs("grammarTest.g4"), ofs("syntactic.cpp"){
	// variables = new vector<string>();
	// rules = new vector<string>()[];
	string line, lineaux;
	int i;
	while(getline(ifs, line)){
		if(line == "" || line[0] == '/')continue;
		vector<string> aux;
		i = line.find('\t');
		variables.push_back(line.substr(0, i));
		i = line.find(':')+1;
		while(line[i]=='\t' || line[i]==' ')i++;
		line = line.substr(i);
		i = 0;
		while(line != ""){
			i = line.find(' ');
			lineaux = i==-1?line:line.substr(0, i);
			aux.push_back(lineaux);
			line = i==-1?"":line.substr(i+1);
		}
		rules.push_back(aux);
	}
	for(int i=0; i<variables.size(); i++){
		cout << "[" << variables[i] << "]";
		for(int j=0; j<rules[i].size(); j++)
			cout << "(" << rules[i][j] << ")";
		cout << endl;
	}
}
Grammar::~Grammar(){
	ifs.close();
}

// void generate first
int main(){
	Grammar* G = new Grammar("grammarTest.g4", "syntactic.cpp");
	delete G;
}
