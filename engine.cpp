#include <iostream>
#include <string>
#include <fstream>
#include <vector>
// #include <ofstream>

using namespace std;

class Grammar{
	private:
		vector<string> variables;
		vector<vector<vector<string> > > rules;
		vector<vector<string> > first;
		ifstream ifs;
		ofstream ofs;
	public:
		Grammar(string ifname, string ofname);
		~Grammar();
		void print();
		bool isVariable(string str);
		bool isTerminal(string str){
		void generateFirst();
};
Grammar::Grammar(string ifname, string ofname)
	:ifs("grammarTest.g4"), ofs("syntactic.cpp"){
	string line, lineaux, lineaux2;
	int i;
	while(getline(ifs, line)){
		if(line == "" || line[0] == '/')continue;

		vector<vector<string> > aux1;
		i = line.find('\t');
		variables.push_back(line.substr(0, i));
		i = line.find(':')+1;
		while(line[i]=='\t' || line[i]==' ')i++;
		line = line.substr(i);

		while(line != ""){
			vector<string> aux2;
			i = line.find('|');
			lineaux = i==-1?line:line.substr(0, i-1);
			line = i==-1?"":line.substr(i+2);

			while(lineaux != ""){
				i = lineaux.find(' ');
				lineaux2 = i==-1?lineaux:lineaux.substr(0, i);
				aux2.push_back(lineaux2);
				lineaux = i==-1?"":lineaux.substr(i+1);
			}
			aux1.push_back(aux2);
		}
		rules.push_back(aux1);
	}
}
Grammar::~Grammar(){
	ifs.close();
}
void Grammar::print(){
	for(int i=0; i<variables.size(); i++){
		cout << "[" << variables[i] << "]";
		for(int k=0; k<rules[i].size(); k++){
			cout << "{";
			for(int j=0; j<rules[i][k].size(); j++)
				cout << "(" << rules[i][k][j] << ")";
			cout << "}";
		}
		cout << endl;
	}
}
// bool Grammar::isVariable(string str){
// 	for(int i=0; i<variables.size(); i++)
// 		if(variables[i] == str)return true;
// 	return false;
// }
bool Grammar::isVariable(string str){
	if(str[0] == '\'' && str[str.length()-1] == '\'')return false;
	return true;
}
bool Grammar::isTerminal(string str){
	if(str[0] == '\'' && str[str.length()-1] == '\'')return true;
	return false;
}
void Grammar::generateFirst(){
	for(int i=0; i<variables.size(); i++){
		for(int j=0; j<rules[i].size(); j++){
			for(int k=0; k<rules[i][j].size(); k++){

			}
		}
	}
}

// void generate first
int main(){
	Grammar* G = new Grammar("grammarTest.g4", "syntactic.cpp");
	G->print();
	G->generateFirst();
	G->print();
	delete G;
}
