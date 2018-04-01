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
		void printRules();
		void printFirst();
		bool isVariable(string str);
		bool isTerminal(string str);
		void appendWithoutEpsilon(vector<string> aux, vector<string> aux2);
		void appendWithoutDuplicates(vector<string> aux, string terminal);
		bool hasTerminal(vector<string> rule, string terminal);
		int getNonTerminalPosition(string str);
		vector<string> generateFirst(string str);
		void generateFirsts();
};
Grammar::Grammar(string ifname, string ofname)
	:ifs("grammar.g4"), ofs("syntactic.cpp"){
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
void Grammar::printRules(){
	for(int i=0; i<variables.size(); i++){
		cout << "[" << variables[i] << "]";
		for(int k=0; k<rules[i].size(); k++){
			cout << "{";
			for(int j=0; j<rules[i][k].size(); j++)
				cout << "<" << rules[i][k][j] << ">";
			cout << "}";
		}
		cout << endl;
	}
}
void Grammar::printFirst(){
	for(int i=0; i<variables.size(); i++){
		cout << "[" << variables[i] << "]";
		for(int j=0; j<first[i].size(); j++){
			cout << "<" << first[i][j] << ">";
		}
		cout << endl;
	}
}
bool Grammar::isVariable(string str){
	if(str[0] == '\'' && str[str.length()-1] == '\'')return false;
	return true;
}
bool Grammar::isTerminal(string str){
	if(str[0] == '\'' && str[str.length()-1] == '\'')return true;
	return false;
}
void Grammar::appendWithoutEpsilon(vector<string> aux, vector<string> aux2){
	for(int i=0; i<aux.size(); i++){
		if(aux2[i] != "epsilon")
			appendWithoutDuplicates(aux, aux2[i]);
	}
}
void Grammar::appendWithoutDuplicates(vector<string> aux, string terminal){
	for(int i=0; i<aux.size(); i++){
		if(aux[i] == terminal)
		return;
	}
	aux.push_back(terminal);
}
bool Grammar::hasTerminal(vector<string> rule, string terminal){
	for (int i=0; i<rule.size(); i++)
		if(rule[i] == terminal)return true;
	return false;
}
int Grammar::getNonTerminalPosition(string str){
	for(int i=0; i<variables.size(); i++)
		if(variables[i] == str)return i;
}
vector<string> Grammar::generateFirst(string str){
	int i = getNonTerminalPosition(str);
	vector<string> ret;
	for(int j=0; j<rules[i].size(); j++){
		if(isTerminal(rules[i][j][0])){
			appendWithoutDuplicates(ret, rules[i][j][0]);
			continue;
		}
		for(int k=0; k<rules[i][j].size(); k++){
			vector<string> aux2 = generateFirst(rules[i][j][k]);
			// appendWithoutEpsilon(ret, aux2);
			break;
			// if(hasTerminal(aux2, 'epsilon')){
			// 	if(k==rules[i][j].size()-1)
			// 		appendWithoutDuplicates(ret, "epsilon");
			// 	}else{
			// 		if(isTerminal(rules[i][j][k+1])){
			// 			appendWithoutDuplicates(ret, rules[i][j][k+1])
			// 	}
			// }else break;
		}

		// for(int k=0; k<rules[i][j].size(); k++){}
	}
	return ret;
}
void Grammar::generateFirsts(){
	for(int i=0; i<=variables.size(); i++){
		first.push_back(generateFirst(variables[i]));
	}
}

// void generate first
int main(){
	Grammar* G = new Grammar("grammar.g4", "syntactic.cpp");
	// G->printRules();
	G->generateFirsts();
	G->printFirst();
	// G->printRules();
	delete G;
}
