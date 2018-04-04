#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
// #include <ofstream>

//  Compile with
//  g++ -std=c++0x engine.cpp -o engine

using namespace std;

class Grammar{
	public:
		vector<string> variables;
		vector<vector<vector<string> > > rules;
		vector<vector<vector<string> > > pred;
		vector<vector<string> > first;
    unordered_map<string, string> tokenTypes;
		unordered_set<string> nonTerminals;
		ifstream ifs;
		ifstream ifspred;
		ofstream ofs;
	public:
		Grammar(string ifname, string ofname, string ifnamepred);
		~Grammar();
		void printVector(vector<string> &aux);
		// void printVector2(vector<vector<string> > &aux);
		void printRules();
		void printPred();
		void printFirst();
		bool isVariable(string str);
		bool isTerminal(string str);
		void appendWithoutEpsilon(vector<string> &aux, vector<string> &aux2);
		void appendWithoutDuplicates(vector<string> &aux, string terminal);
		bool hasTerminal(vector<string> &rule, string terminal);
		int getNonTerminalPosition(string str);
		vector<string> generateFirst(string str);
		void generateFirsts();
		void generateSyntactic();
};
Grammar::Grammar(string ifname, string ofname, string ifnamepred)
	:ifs("grammarTest2.g4"), ofs("syntactic.cpp"), ifspred("predictionTest2.g4"){
	string prevVariable = "", currVariable, line, lineaux, lineRules, linePred;
	int i;
	vector<vector<string> > aux11;
	vector<vector<string> > aux12;
	int j;
	while(getline(ifs, line)){
		cout << "(" << line << ")\n";
		i = line.find('\t');
		line = line.substr(i+1);
		cout << "(" << line << ")\n";
		i = line.find(' ');
		cout << i << " " << line << endl;
		currVariable = line.substr(0,i);
		line = line.substr(i);
		// cout << "CARAJO (" << prevVariable << ") (" << currVariable << ")\n";
		if(currVariable != prevVariable){
			if(prevVariable != ""){
				// cout << "prevVariable is not empty\n";
				vector<vector<string> > aux111 = aux11;
				vector<vector<string> > aux122 = aux12;
				rules.push_back(aux111);
				pred.push_back(aux122);
				aux11.clear();
				aux12.clear();
			}
			prevVariable = currVariable;
			variables.push_back(currVariable);
			nonTerminals.insert(currVariable);
		}
		// cout << "(" << prevVariable << ") (" << currVariable << ")\n";

		// cout << "line (" << line << ")\n";
		i = line.find('\t');
		lineRules = line.substr(3,i-3);
		linePred = line.substr(i+1);
		cout << "lineRules (" << lineRules << ")\n";
		cout << "linePred (" << linePred << ")\n";



		vector<string> aux21;
		while(lineRules != ""){
			i = lineRules.find(' ');
			lineaux = i==-1?lineRules:lineRules.substr(0, i);
			aux21.push_back(lineaux);
			lineRules = i==-1?"":lineRules.substr(i+1);
			// cout << "i " << i << "lineaux " << lineaux << "lineRules " << lineRules << "\n";
		}
		printVector(aux21);
		aux11.push_back(aux21);


		vector<string> aux22;
		while(linePred != ""){
			i = linePred.find(", ");
			lineaux = i==-1?linePred:linePred.substr(0, i);
			lineaux = lineaux.substr(1,lineaux.length()-2);
			aux22.push_back(lineaux);
			linePred = i==-1?"":linePred.substr(i+2);
			// cout << "i " << i << "lineaux " << lineaux << "linePred " << linePred << "\n";
		}
		printVector(aux22);
		aux12.push_back(aux22);
		// cout << "\t\t SIZE() AUX11 AUX12 " << aux11.size() << aux12.size() << endl;
	}
	rules.push_back(aux11);
	pred.push_back(aux12);






	// int i;
	// while(getline(ifs, line)){
	// 	if(line == "" || line[0] == '/')continue;
	// 	// cout << "line" << line << endl;
	// 	vector<vector<string> > aux1;
	// 	i = line.find('\t');
	// 	variables.push_back(line.substr(0, i));
	// 	nonTerminals.insert(line.substr(0, i));
	// 	// cout << line.substr(0, i) << " " << (nonTerminals.find(line.substr(0, i)) != nonTerminals.end()) << endl;
	// 	i = line.find(':')+1;
	// 	while(line[i]=='\t' || line[i]==' ')i++;
	// 	line = line.substr(i);
	//
	// 	while(line != ""){
	// 		vector<string> aux2;
	// 		i = line.find('|');
	// 		if(i>0 && line[i-1]=='\''){
	// 			int j = i;
	// 			string lineaux3 = line.substr(i+2);
	// 			i = lineaux3.find('|');
	// 			if(i!=-1)
	// 				i += (j + 2);
	// 		}
	// 		lineaux = i==-1?line:line.substr(0, i-1);
	// 		line = i==-1?"":line.substr(i+2);
	//
	// 		while(lineaux != ""){
	// 			i = lineaux.find(' ');
	// 			lineaux2 = i==-1?lineaux:lineaux.substr(0, i);
	// 			aux2.push_back(lineaux2);
	// 			lineaux = i==-1?"":lineaux.substr(i+1	);
	// 		}
	// 		aux1.push_back(aux2);
	// 	}
	// 	rules.push_back(aux1);
	// }
	//
	// vector<vector<string> > aux1;
	// // vector<string> aux2;
	// while(getline(ifspred, line)){
	// 	// cout << "line: " << line << endl;
	//
	// 	if(line == "" || line[0] == '/')continue;
	// 	if(line.find(';') != -1){
	// 		vector<vector<string> > aux3 = aux1;
	// 		pred.push_back(aux3);
	// 		aux1.clear();
	// 		continue;
	// 	}
	// 	if((i=line.find(':')+1)==0)
	// 		i=line.find('|')+1;
	// 	while(line[i]=='\t' || line[i]==' ')i++;
	// 	line = line.substr(i);
	// 	// cout << "line: " << line << endl;
	// 	vector<string> aux2;
	// 	while(line != ""){
	// 		i = line.find(' ');
	// 		lineaux = i==-1?line:line.substr(0, i);
	// 		aux2.push_back(lineaux);
	// 		line = i==-1?"":line.substr(i+1	);
	// 	}
	// 	// cout << "size" << aux2.size();
	// 	// printVector(aux2);
	// 	aux1.push_back(aux2);
	// }
	//
	// printRules();
	//
	// cout << "pred.size() " << pred.size() << endl;
	// for(int i=0; i<pred.size(); i++){
	// 	cout << "[" << variables[i] << "]\n";
	// 	for(int k=0; k<pred[i].size(); k++){
	// 		cout << "\t";
	// 		printVector(pred[i][k]);
	// 	}
	// 	cout << endl;
	// }

	// while(getline(ifspred, line)){
	// 	vector<string> aux;
	// 	while(line != ""){
	// 		i = line.find(' ');
	// 		lineaux = i==-1?line:line.substr(0,i);
	// 		aux.push_back(lineaux);
	// 		line = i==-1?"":line.substr(i+1);
	// 	}
	// 	pred.push_back(aux);
	// }

	// int size = pred.size();
	// int size2;
	// for(int i=0; i<size; i++){
	// 	size2 = pred[i].size();
	// 	cout << '[';
	// 	if(size!=0)
	// 		cout << pred[i][0];
	// 	for(int j=1; j<size2; j++)
	// 		cout << ',' << pred[i][j];
	// 	cout << ']' << endl;
	// }

	//  Initialize tokenTypes hashmap
	tokenTypes.insert({
		{"{","token_llave_izq"},
		{"}","token_llave_der"},
		{"#","token_com"},
		{"[","token_cor_izq"},
		{"]","token_cor_der"},
		{"(","token_par_izq"},
		{")","token_par_der"},
		{">","token_mayor"},
		{"<","token_menor"},
		{">=","token_mayor_igual"},
		{"<=","token_menor_igual"},
		{"==","token_igual_num"},
		{".","token_point"},
		{"!=","token_diff_num"},
		{"&&","token_and"},
		{"||","token_or"},
		{"!","token_not"},
		{"+","token_mas"},
		// {"++","token_add"},
		{"-","token_menos"},
		// {"--","token_less"},
		{"*","token_mul"},
		{"/","token_div"},
		{"%","token_mod"},
		{"^","token_pot"},
		{"=","token_assign"},

		// these are not defined in the restrepo table
		{":","token_dosp"},
		{";","token_punto_coma"},
		{",","token_coma"},
		{"_","token_guion_bajo"},
		{"\n","token_salto_linea"}
	});
}
Grammar::~Grammar(){
	ifs.close();
	ifspred.close();
	ofs.close();
}

void Grammar::printVector(vector<string> &aux){
	int size = aux.size();
	cout << '[';
	if(size!=0)
		cout << aux[0];
	for(int i=1; i<size; i++)
		cout << ',' << aux[i];
	cout << ']' << endl;
}
// void printVector2(vector<vector<string> > &aux){
// 	int size = aux.size();
// 	int size2;
// 	for(int i=0; i<size; i++){
// 		size2 = aux[i].size();
// 		cout << '[';
// 		if(size!=0)
// 			cout << aux[i][0];
// 		for(int j=1; j<size2; j++)
// 			cout << ',' << aux[i][j];
// 		cout << ']' << endl;
// 	}
// }
void Grammar::printRules(){
	cout << "\n\nPRINT RULES FUNCTION\n\n";
	cout << "variables.size(): (" << variables.size() << ")\trules.size(): (" << rules.size() << ")\n";
	for(int i=0; i<variables.size(); i++){
		cout << "[" << variables[i] << "]";
		cout << "rules[i].size(): (" << rules[i].size() << ")";
		for(int k=0; k<rules[i].size(); k++){
			cout << "{";
			for(int j=0; j<rules[i][k].size(); j++)
				cout << "<" << rules[i][k][j] << ">";
			cout << "}";
		}
		cout << endl;
	}
}
void Grammar::printPred(){
		cout << "\n\nPRINT PRED FUNCTION\n\n";
		cout << "variables.size(): (" << variables.size() << ")\tpred.size(): (" << pred.size() << ")\n";
		for(int i=0; i<variables.size(); i++){
			cout << "[" << variables[i] << "]";
			cout << "pred[i].size(): (" << pred[i].size() << ")";
			for(int k=0; k<pred[i].size(); k++){
				cout << "{";
				for(int j=0; j<pred[i][k].size(); j++)
					cout << "<" << pred[i][k][j] << ">";
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
void Grammar::appendWithoutEpsilon(vector<string> &aux, vector<string> &aux2){
	// cout << "dentro" << endl;
	// printVector(aux);
	// printVector(aux2);
	for(int i=0; i<aux2.size(); i++){
		if(aux2[i] != "\'epsilon\'")
			appendWithoutDuplicates(aux, aux2[i]);
	}
	// printVector(aux);
	// printVector(aux2);
	// cout << "fuera" << endl;
}
void Grammar::appendWithoutDuplicates(vector<string> &aux, string terminal){
	// cout << "dentro2" << endl;
	// printVector(aux);
	// cout << "terminal" << terminal << endl;
	for(int i=0; i<aux.size(); i++){
		// cout << "\t\ti\t\t" << i << "\t\t" << aux[i] << endl;
		if(aux[i] == terminal){
			// cout << "\t	auxilio" << endl;
			return;
		}
	}
	// printVector(aux);
	aux.push_back(terminal);
	// aux.push_back("HHHHH");
	// printVector(aux);
	// cout << terminal << endl;
	// cout << "fuera2" << endl;
}
bool Grammar::hasTerminal(vector<string> &rule, string terminal){
	for (int i=0; i<rule.size(); i++)
		if(rule[i] == terminal)return true;
	return false;
}
int Grammar::getNonTerminalPosition(string str){
	int size = variables.size();
	for(int i=0; i<size; i++){
		if(variables[i] == str){
			return i;
		}
	}
}
vector<string> Grammar::generateFirst(string str){
	// cout << "desde " << str << endl;
	int i = getNonTerminalPosition(str);
	cout << "i" << i << endl;
	vector<string> ret;
	for(int j=0; j<rules[i].size(); j++){
		if(isTerminal(rules[i][j][0])){
			cout << "\t" << rules[i][j][0] << "isTerminal" << endl;
			appendWithoutDuplicates(ret, rules[i][j][0]);
			// cout << "continue" << endl;
			continue;
		}
		cout << "\t" << rules[i][j][0] << "isnonTerminal" << endl;
		for(int k=0; k<rules[i][j].size(); k++){
			cout << "str: " << rules[i][j][k] << endl;
			vector<string> aux2 = generateFirst(rules[i][j][k]);
			cout << "primeros de " << rules[i][j][k];
			printVector(aux2);
			cout << "ret pre";
			printVector(ret);
			appendWithoutEpsilon(ret, aux2);
			cout << "ret pos";
			printVector(ret);
			break;
			if(hasTerminal(aux2, "\'epsilon\'")){
				if(k==rules[i][j].size()-1){
					appendWithoutDuplicates(ret, "\'epsilon\'");
				}else{
					if(isTerminal(rules[i][j][k+1]))
						appendWithoutDuplicates(ret, rules[i][j][k+1]);
				}
			}else break;
		}

		// for(int k=0; k<rules[i][j].size(); k++){}
	}
	cout << "retorno ";
	printVector(ret);
	// cout << endl;
	return ret;
}
void Grammar::generateFirsts(){
	for(int i=0; i<=variables.size(); i++){
		cout << "str0: " << variables[i] << endl;
		first.push_back(generateFirst(variables[i]));
		cout << "primeros de str0: " << variables[i] << endl;
		printVector(first[first.size()-1]);
	}
}
void Grammar::generateSyntactic(){
	ofs << "class Syntactic{\n";
	ofs << "\tpublic:\n";
	ofs << "\t\tLexer* lexer;\n";
	ofs << "\t\tToken* currentToken;\n";
	ofs << "\t\tstring currentTokenType;\n";
	ofs << "\t\tSyntactic(bool useFile, string str);\n";
	ofs << "\t\t~Syntactic();\n";
	ofs << "\t\tvoid match(string waitedToken);\n";
	ofs << "\t\tvoid syntacticError(string* array);\n";
	for(int i=0; i<variables.size(); i++){
		// cout << "index2 debug" << endl;
		ofs << "\t\tvoid " << variables[i] << "();\n";
	}
	ofs << "};\n";
	ofs << "Syntactic::Syntactic(bool useFile, string str){\n";
	ofs << "\tlexer = new Lexer(useFile, str);\n";
	ofs << "\tcurrentToken = lexer->nextToken();\n";
	ofs << "\t\tcout << currentToken->getLexeme() << \" \" << currentToken->getType() << endl;\n";
	ofs << "\tcurrentTokenType = currentToken->getType() == \"rw\"?currentToken->getLexeme():currentToken->getType();\n";
	ofs << "\tstats();\n";
	// ofs << "\tcurrentToken = lexer->nextToken();\n";
	ofs << "}\n";
	ofs << "Syntactic::~Syntactic(){\n";
	ofs << "\tdelete lexer;\n";
	ofs << "}\n";
	ofs << "void Syntactic::match(string waitedToken){\n";
	ofs << "\t\tcout << \"match f waitedToken \" << waitedToken << endl;\n";
	ofs << "\tif(currentTokenType == waitedToken){\n";
	ofs << "\t\tcurrentToken = lexer->nextToken();\n";
	ofs << "\t\tcout << currentToken->getLexeme() << \" \" << currentToken->getType() << endl;\n";
	ofs << "\t\tcurrentTokenType = currentToken->getType() == \"rw\"?currentToken->getLexeme():currentToken->getType();\n";
	ofs << "\t}else{\n";
	ofs << "\t\tstring array[] = {waitedToken};\n";
	ofs << "\t\tsyntacticError(array);\n";
	ofs << "\t}\n";
	ofs << "}\n";
	ofs << "void Syntactic::syntacticError(string* array){\n";
	ofs << "\tint n = *(&array + 1) - array;\n";
	ofs << "\tcout << \"<\" << currentToken->getRow() << \":\" << currentToken->getColumn() << \"> Error sintactico. Encontrado: {\" << currentToken->getLexeme() << \"}; se esperaba: {\";\n";
	ofs << "\tfor(int i=0; i<n; i++){\n";
	ofs << "\t\tcout << array[i];\n";
	ofs << "\t}\n";
	ofs << "\tcout << \"}\";\n";
	ofs << "}\n";

	string lexeme, comp;
	bool tokenExist, isNonTerminal;
	// cout << "index1 debug" << endl;
	// cout << variables.size() << endl;
	for(int i=0; i<variables.size(); i++){
		// cout << "\ni" << i << endl;
		// cout << "index2 debug" << endl;
		ofs << "void Syntactic::" << variables[i] << "(){\n\t";
		ofs << "\tcout << \"funcion " << variables[i] << " currentToken \" << currentToken << endl;\n\t";
		// cout << "void Syntactic::" << variables[i] << "(){\n\t";
		for(int j=0; j<rules[i].size(); j++){
			// cout << "========== j " << j << " ====== rules[i].size() " << rules[i].size() << "===== pred[i].size() " << pred[i].size() << endl;
			ofs << "if(";
			for(int k=0; k<pred[i][j].size(); k++){
				// cout << "~~~~~~~~~ k " << k << " ~~~~~~~~~ pred[i][j].size() " << pred[i][j].size() << endl;
				lexeme = pred[i][j][k];
				tokenExist = tokenTypes.find(lexeme) != tokenTypes.end();
				comp = tokenExist? tokenTypes[lexeme] : lexeme;
				// cout << "(" << lexeme << ")\t" << tokenExist << "\t" << comp << endl;
				ofs << "currentTokenType == \"" << comp << "\"";
				// cout << "currentTokenType == \"" << comp << "\"";
				if(k<pred[i][j].size()-1){
					ofs << " || ";
					// cout << " || ";
				}
			}
			ofs << "){\n";
		// 	cout << "){\n";
		// 	// for(int m=0; m<rules[i][j].size(); m++){
		// 		// cout << "i " << i << " m " << m << " " << rules[i][j][m] << endl;
			for(int k=0; k<rules[i][j].size(); k++){
				lexeme = rules[i][j][k];
				isNonTerminal = nonTerminals.find(lexeme) != nonTerminals.end();
				// cout <<  lexeme << "\t" << isNonTerminal << endl;
				if(isNonTerminal){
					ofs << "\t\t" << lexeme << "();\n";
					// cout << "\t\t" << lexeme << "();\n";
				}else{
					if(lexeme[0] == '\'')
						lexeme = lexeme.substr(1, lexeme.length()-2);
					tokenExist = tokenTypes.find(lexeme) != tokenTypes.end();
					comp = tokenExist? tokenTypes[lexeme] : lexeme;
					// cout << "(" << lexeme << ")\t" << tokenExist << "\t" << comp << endl;
					ofs << "\t\tmatch(\"" << comp << "\");\n";
					// cout << "\t\tmatch(\"" << comp << "\");\n";
				}
			}
			ofs << "\t}";
			// cout << "\t}";
			ofs << "else";
			if(j<rules[i].size()-1)
				ofs << " ";
		}
		ofs << "{\n";
		ofs << "\t\tstring array[] = {";
		// cout << "\tint array[] = {";
		// if(pred[0].size() != 0 && pred[0][0].size() != 0)
		// 	ofs << "\"" << pred[i][0][0] << "\"";
		// for(int j=0; j<pred[i].size(); j++)
		// 	for(int k=1; k<pred[i][j].size(); k++)
		// 		ofs << ",\"" << pred[i][j][k] << "\"";
		// ofs << "\r";
		ofs << "};\n";
		// cout << "};\n";
		ofs << "\t\tsyntacticError(array);\n";
		ofs << "\t}\n";
		ofs << "}\n";
		// cout << "}\n";
	}
}
int main(){
	Grammar* G = new Grammar("grammarTest2.g4", "syntactic.cpp", "predictionTest2.g4");
	G->generateSyntactic();
	G->printRules();
	G->printPred();
	// G->printVector2(G->pred);
	// G->printRules();
	// G->generateFirst("n");
	// int i = G->getNonTerminalPosition("statment");
	// G->printVector(G->first[i]);
	// G->generateFirsts();
	// G->printFirst();
	// G->printRules();
	delete G;
}
