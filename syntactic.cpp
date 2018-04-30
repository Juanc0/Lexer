#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

//	Compile with
//	g++ -std=c++0x lexer.cpp -o lexer

class Token{
	private:
		int row;
		int column;
		string type;
		string lexeme;
	public:
		Token(int row, int column, string type, string lexeme);
		int getRow();
		int getColumn();
		string getType();
		string getLexeme();
		void print();
};
Token::Token(int _row, int _column, string _type, string _lexeme){
	row = _row;
	column = _column;
	type = _type;
	lexeme = _lexeme;
}
void Token::print(){
	// if(lexeme == "\n")return;
	cout << "<";
	if(type != "rw")
		cout << type << ",";
	if(type == "rw"
		|| type == "token_string"
		|| type == "token_integer"
		|| type == "token_float"
		|| type == "id")
		cout << lexeme << ",";
	cout << row << "," << column << ">" << endl;
}
int Token::getRow(){return row;}
int Token::getColumn(){return column;}
string Token::getType(){return type;}
string Token::getLexeme(){return lexeme;}


class Lexer{
	private:
		short numNonFinalsStates;
		short numCharacters;
		short indexFirstFinalState;
		string availableCharacters;
		short numAvailableCharacters;
		short** dfa;
		long row;
		long column;
		string currentLine;
		long currentLineUsefulLength;
		unordered_map<string, string> tokenTypes;
		unordered_set<string> reservedWords;
		bool useFile;
		ifstream ifs;

	public:
		Lexer(bool useFile, string str);
		~Lexer();

		short getNumNonFinalsStates();
		short getNumCharacters();
		short getIndexFirstFinalState();
		string getAvailableCharacters();
		short getNumAvailableCharacters();
		short** getDfa();
		long getRow();
		long getColumn();
		string getCurrentLine();

		short transition(short state, short character);
		void printDfa();
		Token* nextToken();
};
Lexer::Lexer(bool _useFile, string str)
	: ifs(str){
	useFile = _useFile;

	numNonFinalsStates = 15;
	numCharacters = 128;
	indexFirstFinalState = 20;
	availableCharacters = "()[]{}*/%^#:;,_><=!&|+-.~ \"\n\tabcdefghijklmniopqrstuvwxyzABCDEFGHIJKLMNIOPQRSTUVWXYZ0123456789";
	numAvailableCharacters = availableCharacters.length();
	//	Initialize all matrix element with zero (0)
	dfa = new short*[numNonFinalsStates];
	for(short i=0; i<numNonFinalsStates; i++){
		dfa[i] = new short[numCharacters];
		for(short j=0; j< numCharacters; j++)
			dfa[i][j] = 0;
	}

	row = 0;
	column = 0;
	currentLine = "";
	currentLineUsefulLength = 0;

	//	Initialize tokenTypes hashmap
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
		{"_","token_guion_bajo"}
	});
	//	Initialize reservedWords hashset
	reservedWords.insert({
		{"desde"},
		{"importar"},
		{"funcion"},
		{"end"},
		{"true"},
		{"false"},
		{"if"},
		{"else"},
		{"while"},
		{"for"},
		{"in"},
		{"log"},
		{"leer"},
		{"nil"},
		{"retorno"},
		{"todo"},
	});



	//	Unit tokens with unique match
	//	TODO:	 Take it to any character loop
	for(short i=0; i<=14; i++){
		// cout << availableCharacters[i] << (short)availableCharacters[i] << endl;
		dfa[0][(short)availableCharacters[i]] = indexFirstFinalState;
	}
	//	Mixed tokens with multiple matches consideration (Float number case #1: without a number before)
	for(short i=15; i<=22; i++)
		dfa[0][(short)availableCharacters[i]] = i-14;
	//	TODO: check this error -1 or 0
	dfa[0][(short)' '] = indexFirstFinalState+6;
	dfa[0][(short)'\t'] = indexFirstFinalState+6;
	dfa[0][(short)'.'] = 9;

	// Two element token match
	for(short i=1; i<=4; i++)
		dfa[i][(short)'='] = indexFirstFinalState;
	dfa[5][(short)'&'] = indexFirstFinalState;
	dfa[6][(short)'|'] = indexFirstFinalState;
	dfa[7][(short)'+'] = indexFirstFinalState;
	dfa[8][(short)'-'] = indexFirstFinalState;



	//	Float number (case #2 with a number before)
	dfa[11][(short)'.'] = 12;

	//	"Strings"
	dfa[0][(short)'\"'] = 14;
	for(short i=0; i<numCharacters; i++)
		if(i != (short)'\"')
			dfa[14][i] = 14; // 14 --> 14 loop alphanumeric + ' '
		else
			dfa[14][i] = indexFirstFinalState+5;

	//	Alphabetical loop
	for(short i=65; i<=90; i++){
		dfa[0][i] = 10;
		dfa[0][i+32] = 10;
		dfa[10][i] = 10;
		dfa[10][i+32] = 10;
	}
	//	Numeric loop
	for(short i=48; i<=57; i++){
		dfa[0][i] = 11;
		dfa[11][i] = 11;
		dfa[10][i] = 10;
		//dfa[9][i] = 13; // float without a number before
		dfa[12][i] = 13; // float with a number before
		dfa[13][i] = 13;
	}
	//	Identifiers with '-' or '_' characters
	dfa[10][(short)'_'] = 10;
	dfa[10][(short)'-'] = 10;

	//	Any character loop
	short increment;
	for(short j=0; j<numAvailableCharacters; j++){
		//	Unit tokens with multiple match check
		for(short i=1; i<=13; i++){
			//	TODO: Check if [0-9]'.' map to an integer or a double number or error
			// cout << i << "\t" << j << "\t" << (short)availableCharacters[j] << "\t" << availableCharacters[j] << "\t" << dfa[i][(short)availableCharacters[j]] << endl;
			if(i==12 || i==5 || i== 6)continue;
			if(dfa[i][(short)availableCharacters[j]] == 0){
				increment = (i<10? 1: i-8);
				// increment = (i>=10? i-5: 2);
				//	TODO:	 Think about it when i==13
				if(i==13)increment--;
				dfa[i][(short)availableCharacters[j]] = indexFirstFinalState+increment;
			}
		}
		if(dfa[14][(short)availableCharacters[j]] == 0)
			dfa[14][(short)availableCharacters[j]] = indexFirstFinalState+5;

	}

	//	I'm not sure what this does
	for(int i=0; i<numNonFinalsStates; i++){
		if(i==12 || i==5 || i== 6)continue;
		if(dfa[i][0] == 0)
			increment = (i<10? 1: i-8);
		if(i==13)increment--;
		dfa[i][0] = indexFirstFinalState+increment;
	}
	//	Throw a lexical error for non-closed strings (readin from console)
	dfa[14][0] = 0;
	//	For waited word alert the end of line reading from file
	// dfa[10][13] = indexFirstFinalState+2;
	// dfa[11][13] = indexFirstFinalState+3;
}
Lexer::~Lexer(){
	ifs.close();
	for(short i=0; i<numNonFinalsStates; i++)
		delete dfa[i];
	delete dfa;
}
string Lexer::getAvailableCharacters(){return availableCharacters;}
// unordered_map<string, string> Lexer::getTokenTypes(){return tokentypes;}
// unordered_set<string> Lexer::getReservedWords(){return reservedWords;}
short Lexer::transition(short state, short character){return dfa[state][character];}
void Lexer::printDfa(){
	for(int i=0; i<numNonFinalsStates; i++){
		for(int j=10; j< numCharacters; j++){
			printf("%2i ",dfa[i][j]);
			// if(!((j+1)%10)) printf("\t");
		}
		printf("\n");
	}
}
// Token* Lexer::nextToken(ifstream& ifs){
Token* Lexer::nextToken(){
	istream& input = useFile?ifs:cin;
	//	CurrentLine ckeck
	// cout << column << " " << currentLine.length() << endl;
	if(row == 0){
		// if(input.eof()) return NULL;
		getline(input, currentLine);
		row = 1;
	}if(column == currentLine.length()){
		column++;
		return new Token(row, column, "token_salto_linea", "\n");
	}else if(column == currentLine.length()+1){
		if(input.eof()) return NULL;
		getline(input, currentLine);
		row++;
		column = 0;
	}
	// cout << column << " " << currentLine.length() << currentLine.length() << endl;


	//	find next token
	short currentState = 0;
	short i = 0;
	string tokenType;
	string lexeme;
	while(true){
		// cout << currentState;
		currentState = transition(currentState, (short)currentLine[column+i]);
		// cout << "\t(" << currentLine[column+i] << ")\t" << (int)currentLine[column+i] << "\t" << currentState<< endl;

		switch (currentState) {
			case 0:
				cout << ">>> Error lexico(linea:" << row << ",posicion:" << column+1 << ")" << endl;
				return NULL;
			case 24:
				//	Float number
				tokenType = "token_float";
				break;
			case 23:
				//	integer
				tokenType = "token_integer";
				break;
			case 22:
				//	identifiers <id, nombre, row, col>
				lexeme = currentLine.substr(column, i);
				tokenType = reservedWords.find(lexeme) != reservedWords.end()? "rw" : "id";
				break;
			case 21:
				//	tokens with an additional character
				i--;
			case 20:
				//	complete tokens (with one and two characters)
				lexeme = currentLine.substr(column, i+1);
				tokenType = tokenTypes[lexeme];
				// tokenType = tokenTypes.find(lexeme);

				if(currentLine[column] == '#'){
					if(input.eof())	return NULL;

					Token* token = new Token(row, column+1, tokenType, lexeme);
					getline(input, currentLine);
					row++;
					column = 0;
					i=0;
					currentState = 0;
					continue;
				}

				i++;
				break;
			case 25:
				//	String
				tokenType = "token_string";
				i++;
				break;
			case 26:
				column++;
				currentState = 0;
				continue;
			default:
				i++;
				continue;
		}
		i--;
		lexeme = currentLine.substr(column, i+1);
		if(currentState == indexFirstFinalState+5)
			lexeme = currentLine.substr(column+1, i-1);

		Token* token = new Token(row, column+1, tokenType, lexeme);
		column += i+1;
		currentState = 0;
		if(lexeme == "")return nextToken();
		return token;
	}
}

class Syntactic{
	public:
		Lexer* lexer;
		Token* currentToken;
		string currentTokenType;
		int level;
		Syntactic(bool useFile, string str);
		~Syntactic();
		void printAsterisks();
		void match(string waitedToken);
		void syntacticError(vector<string> &v);
		string program();
		string stats();
		string stats1();
		string stat();
		string simple_stat();
		string compound_stat();
		string log();
		string leer();
		string importar();
		string funcion();
		string funcion_stats();
		string funcion_stats1();
		string funcion_stat();
		string retorno_block();
		string parametros();
		string parametro();
		string while_stat();
		string for_stat();
		string if_stat();
		string else_block();
		string else_stats();
		string stat_block();
		string B();
		string variable();
		string array();
		string objeto();
		string Keyvalue();
		string K();
		string L();
		string M();
		string G();
		string H();
		string J();
		string expr();
		string op();
		string N();
		string atom();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
	currentToken = lexer->nextToken();
	currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
	level=0;
	cout << program();
}
Syntactic::~Syntactic(){
	delete lexer;
}
void Syntactic::printAsterisks(){
	int i=0;
	for(i=0; i<level; i++)
		cout << '*';
}
void Syntactic::match(string waitedTokenType){
	cout << "match function, curreentTokenType: (" << currentTokenType << "), waitedTokenType: (" << waitedTokenType << ")\n";
	if(currentTokenType == waitedTokenType){
		currentToken = lexer->nextToken();
		if(currentToken == NULL){
			cout << "El analisis sintactico ha finalizado correctamente.";
			currentTokenType = "NULL";
			//exit(-1);
		}else{
			cout << currentToken->getLexeme() << " " << currentToken->getType() << endl;
			currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
		}
	}else{
		vector<string> array;
		array.push_back(waitedTokenType);
		syntacticError(array);
	}
}
void Syntactic::syntacticError(vector<string> &v){
	cout << "<" << currentToken->getRow() << ":" << currentToken->getColumn() << "> Error sintactico. Encontrado: {" << currentToken->getLexeme() << "}; se esperaba: {";
	if(v.size() != 0);
		cout << v[0];
	for(int i=1; i<v.size(); i++)
		cout << ", " << v[i];
	cout << "}";
	exit(-1);
}

string Syntactic::program(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "program" << currentTokenType << "\n";
	if(currentTokenType == "token_salto_linea" || currentTokenType == "log" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "leer" || currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "funcion" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "if"){
		aux += stats();
	}else if(currentTokenType == "NULL"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("leer");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back("funcion");
		array.push_back("for");
		array.push_back("while");
		array.push_back("if");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::stats(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "stats" << currentTokenType << "\n";
	if(currentTokenType == "token_salto_linea" || currentTokenType == "log" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "leer" || currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "funcion" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "if"){
		aux += B();
		aux += stat();
		aux += stats1();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "NULL"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("leer");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back("funcion");
		array.push_back("for");
		array.push_back("while");
		array.push_back("if");
		array.push_back("}");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::stats1(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "stats1" << currentTokenType << "\n";
	if(currentTokenType == "token_salto_linea"){
		aux += "token_salto_linea";
		match("token_salto_linea");
		aux += stats();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "NULL"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "stat" << currentTokenType << "\n";
	if(currentTokenType == "log" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "leer" || currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		aux += simple_stat();
	}else if(currentTokenType == "funcion" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "if"){
		aux += compound_stat();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("leer");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back("funcion");
		array.push_back("for");
		array.push_back("while");
		array.push_back("if");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::simple_stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "simple_stat" << currentTokenType << "\n";
	if(currentTokenType == "log"){
		aux += log();
	}else if(currentTokenType == "leer"){
		aux += leer();
	}else if(currentTokenType == "importar" || currentTokenType == "desde"){
		aux += importar();
	}else if(currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		aux += expr();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("log");
		array.push_back("leer");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::compound_stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "compound_stat" << currentTokenType << "\n";
	if(currentTokenType == "funcion"){
		aux += funcion();
	}else if(currentTokenType == "while"){
		aux += while_stat();
	}else if(currentTokenType == "for"){
		aux += for_stat();
	}else if(currentTokenType == "if"){
		aux += if_stat();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("funcion");
		array.push_back("while");
		array.push_back("for");
		array.push_back("if");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::log(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "log" << currentTokenType << "\n";
	if(currentTokenType == "log"){
		aux += "log";
		match("log");
		aux += "token_par_izq";
		match("token_par_izq");
		aux += expr();
		aux += "token_par_der";
		match("token_par_der");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("log");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::leer(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "leer" << currentTokenType << "\n";
	if(currentTokenType == "leer"){
		aux += "leer";
		match("leer");
		aux += "token_par_izq";
		match("token_par_izq");
		aux += variable();
		aux += "token_par_der";
		match("token_par_der");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("leer");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::importar(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "importar" << currentTokenType << "\n";
	if(currentTokenType == "importar"){
		aux += "importar";
		match("importar");
		aux += "id";
		match("id");
		aux += K();
	}else if(currentTokenType == "desde"){
		aux += "desde";
		match("desde");
		aux += "id";
		match("id");
		aux += "importar";
		match("importar");
		aux += "id";
		match("id");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("importar");
		array.push_back("desde");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::funcion(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "funcion" << currentTokenType << "\n";
	if(currentTokenType == "funcion"){
		aux += "funcion";
		match("funcion");
		aux += "id";
		match("id");
		aux += "token_par_izq";
		match("token_par_izq");
		aux += parametros();
		aux += "token_par_der";
		match("token_par_der");
		aux += funcion_stats();
		aux += "end";
		match("end");
		aux += "funcion";
		match("funcion");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("funcion");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::funcion_stats(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "funcion_stats" << currentTokenType << "\n";
	if(currentTokenType == "token_salto_linea" || currentTokenType == "log" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "leer" || currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "funcion" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "if" || currentTokenType == "retorno"){
		aux += B();
		aux += funcion_stat();
		aux += funcion_stats1();
	}else if(currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("leer");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back("funcion");
		array.push_back("for");
		array.push_back("while");
		array.push_back("if");
		array.push_back("retorno");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::funcion_stats1(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "funcion_stats1" << currentTokenType << "\n";
	if(currentTokenType == "token_salto_linea"){
		aux += "token_salto_linea";
		match("token_salto_linea");
		aux += funcion_stats();
	}else if(currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::funcion_stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "funcion_stat" << currentTokenType << "\n";
	if(currentTokenType == "log" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "leer" || currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "funcion" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "if"){
		aux += stat();
	}else if(currentTokenType == "retorno"){
		aux += retorno_block();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("leer");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back("funcion");
		array.push_back("for");
		array.push_back("while");
		array.push_back("if");
		array.push_back("retorno");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::retorno_block(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "retorno_block" << currentTokenType << "\n";
	if(currentTokenType == "retorno"){
		aux += "retorno";
		match("retorno");
		aux += "token_par_izq";
		match("token_par_izq");
		aux += expr();
		aux += "token_par_der";
		match("token_par_der");
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("retorno");
		array.push_back("token_salto_linea");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::parametros(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "parametros" << currentTokenType << "\n";
	if(currentTokenType == "id"){
		aux += "id";
		match("id");
		aux += parametro();
	}else if(currentTokenType == "token_par_der"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("id");
		array.push_back(")");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::parametro(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "parametro" << currentTokenType << "\n";
	if(currentTokenType == "token_coma"){
		aux += "token_coma";
		match("token_coma");
		aux += "id";
		match("id");
		aux += parametro();
	}else if(currentTokenType == "token_par_der"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back(",");
		array.push_back(")");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::while_stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "while_stat" << currentTokenType << "\n";
	if(currentTokenType == "while"){
		aux += "while";
		match("while");
		aux += expr();
		aux += stat_block();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("while");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::for_stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "for_stat" << currentTokenType << "\n";
	if(currentTokenType == "for"){
		aux += "for";
		match("for");
		aux += "id";
		match("id");
		aux += "in";
		match("in");
		aux += expr();
		aux += stat_block();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("for");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::if_stat(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "if_stat" << currentTokenType << "\n";
	if(currentTokenType == "if"){
		aux += "if";
		match("if");
		aux += "token_par_izq";
		match("token_par_izq");
		aux += expr();
		aux += "token_par_der";
		match("token_par_der");
		aux += stat_block();
		aux += else_block();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("if");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::else_block(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "else_block" << currentTokenType << "\n";
	if(currentTokenType == "else"){
		aux += "else";
		match("else");
		aux += else_stats();
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "token_llave_der" || currentTokenType == "NULL" || currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("else");
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("NULL");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::else_stats(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "else_stats" << currentTokenType << "\n";
	if(currentTokenType == "if"){
		aux += if_stat();
	}else if(currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea"){
		aux += stat_block();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("if");
		array.push_back("{");
		array.push_back("token_salto_linea");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::stat_block(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "stat_block" << currentTokenType << "\n";
	if(currentTokenType == "token_llave_izq"){
		aux += "token_llave_izq";
		match("token_llave_izq");
		aux += stats();
		aux += "token_llave_der";
		match("token_llave_der");
	}else if(currentTokenType == "token_salto_linea"){
		aux += "token_salto_linea";
		match("token_salto_linea");
		aux += stat();
		aux += "token_salto_linea";
		match("token_salto_linea");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("{");
		array.push_back("token_salto_linea");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::B(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "B" << currentTokenType << "\n";
	if(currentTokenType == "token_salto_linea"){
		aux += "token_salto_linea";
		match("token_salto_linea");
		aux += B();
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "log" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "leer" || currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "funcion" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "if" || currentTokenType == "retorno" || currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("token_salto_linea");
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("leer");
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back("funcion");
		array.push_back("for");
		array.push_back("while");
		array.push_back("if");
		array.push_back("retorno");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::variable(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "variable" << currentTokenType << "\n";
	if(currentTokenType == "id"){
		aux += "id";
		match("id");
		aux += K();
		aux += J();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::array(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "array" << currentTokenType << "\n";
	if(currentTokenType == "token_cor_izq"){
		aux += "token_cor_izq";
		match("token_cor_izq");
		aux += G();
		aux += "token_cor_der";
		match("token_cor_der");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("[");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::objeto(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "objeto" << currentTokenType << "\n";
	if(currentTokenType == "token_llave_izq"){
		aux += "token_llave_izq";
		match("token_llave_izq");
		aux += L();
		aux += "token_llave_der";
		match("token_llave_der");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("{");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::Keyvalue(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "Keyvalue" << currentTokenType << "\n";
	if(currentTokenType == "id"){
		aux += "id";
		match("id");
		aux += "token_dosp";
		match("token_dosp");
		aux += expr();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::K(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "K" << currentTokenType << "\n";
	if(currentTokenType == "token_point"){
		aux += "token_point";
		match("token_point");
		aux += "id";
		match("id");
		aux += K();
	}else if(currentTokenType == "token_par_izq" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_der" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_assign" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_salto_linea" || currentTokenType == "token_llave_der" || currentTokenType == "NULL" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_cor_der" || currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back(".");
		array.push_back("(");
		array.push_back("[");
		array.push_back(")");
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
		array.push_back("=");
		array.push_back("<=");
		array.push_back(">=");
		array.push_back("<");
		array.push_back(">");
		array.push_back("==");
		array.push_back("!=");
		array.push_back("&&");
		array.push_back("||");
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("NULL");
		array.push_back(",");
		array.push_back("{");
		array.push_back("]");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::L(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "L" << currentTokenType << "\n";
	if(currentTokenType == "id"){
		aux += Keyvalue();
		aux += M();
	}else if(currentTokenType == "token_llave_der"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("id");
		array.push_back("}");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::M(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "M" << currentTokenType << "\n";
	if(currentTokenType == "token_coma"){
		aux += "token_coma";
		match("token_coma");
		aux += Keyvalue();
		aux += M();
	}else if(currentTokenType == "token_llave_der"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back(",");
		array.push_back("}");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::G(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "G" << currentTokenType << "\n";
	if(currentTokenType == "token_not" || currentTokenType == "token_menos" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		aux += expr();
		aux += H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		array.push_back(")");
		array.push_back("]");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::H(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "H" << currentTokenType << "\n";
	if(currentTokenType == "token_coma"){
		aux += "token_coma";
		match("token_coma");
		aux += expr();
		aux += H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back(",");
		array.push_back(")");
		array.push_back("]");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::J(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "J" << currentTokenType << "\n";
	if(currentTokenType == "token_par_izq"){
		aux += "token_par_izq";
		match("token_par_izq");
		aux += G();
		aux += "token_par_der";
		match("token_par_der");
	}else if(currentTokenType == "token_cor_izq"){
		aux += array();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_assign" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "NULL" || currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("(");
		array.push_back("[");
		array.push_back(")");
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
		array.push_back("=");
		array.push_back("<=");
		array.push_back(">=");
		array.push_back("<");
		array.push_back(">");
		array.push_back("==");
		array.push_back("!=");
		array.push_back("&&");
		array.push_back("||");
		array.push_back(",");
		array.push_back("{");
		array.push_back("token_salto_linea");
		array.push_back("]");
		array.push_back("}");
		array.push_back("NULL");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::expr(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "expr" << currentTokenType << "\n";
	if(currentTokenType == "token_not"){
		aux += "token_not";
		match("token_not");
		aux += expr();
	}else if(currentTokenType == "token_menos"){
		aux += "token_menos";
		match("token_menos");
		aux += expr();
	}else if(currentTokenType == "token_par_izq"){
		aux += "token_par_izq";
		match("token_par_izq");
		aux += expr();
		aux += "token_par_der";
		match("token_par_der");
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		aux += atom();
		aux += op();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("!");
		array.push_back("-");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::op(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "op" << currentTokenType << "\n";
	if(currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_assign" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or"){
		aux += N();
		aux += expr();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "NULL" || currentTokenType == "end"){
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
		array.push_back("=");
		array.push_back("<=");
		array.push_back(">=");
		array.push_back("<");
		array.push_back(">");
		array.push_back("==");
		array.push_back("!=");
		array.push_back("&&");
		array.push_back("||");
		array.push_back(")");
		array.push_back(",");
		array.push_back("{");
		array.push_back("token_salto_linea");
		array.push_back("]");
		array.push_back("}");
		array.push_back("NULL");
		array.push_back("end");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::N(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "N" << currentTokenType << "\n";
	if(currentTokenType == "token_pot"){
		aux += "token_pot";
		match("token_pot");
	}else if(currentTokenType == "token_mul"){
		aux += "token_mul";
		match("token_mul");
	}else if(currentTokenType == "token_div"){
		aux += "token_div";
		match("token_div");
	}else if(currentTokenType == "token_mod"){
		aux += "token_mod";
		match("token_mod");
	}else if(currentTokenType == "token_mas"){
		aux += "token_mas";
		match("token_mas");
	}else if(currentTokenType == "token_menos"){
		aux += "token_menos";
		match("token_menos");
	}else if(currentTokenType == "token_assign"){
		aux += "token_assign";
		match("token_assign");
	}else if(currentTokenType == "token_menor_igual"){
		aux += "token_menor_igual";
		match("token_menor_igual");
	}else if(currentTokenType == "token_mayor_igual"){
		aux += "token_mayor_igual";
		match("token_mayor_igual");
	}else if(currentTokenType == "token_menor"){
		aux += "token_menor";
		match("token_menor");
	}else if(currentTokenType == "token_mayor"){
		aux += "token_mayor";
		match("token_mayor");
	}else if(currentTokenType == "token_igual_num"){
		aux += "token_igual_num";
		match("token_igual_num");
	}else if(currentTokenType == "token_diff_num"){
		aux += "token_diff_num";
		match("token_diff_num");
	}else if(currentTokenType == "token_and"){
		aux += "token_and";
		match("token_and");
	}else if(currentTokenType == "token_or"){
		aux += "token_or";
		match("token_or");
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
		array.push_back("=");
		array.push_back("<=");
		array.push_back(">=");
		array.push_back("<");
		array.push_back(">");
		array.push_back("==");
		array.push_back("!=");
		array.push_back("&&");
		array.push_back("||");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}
string Syntactic::atom(){
	string aux = "";
	level++;
	printAsterisks();
	cout << "atom" << currentTokenType << "\n";
	if(currentTokenType == "token_integer"){
		aux += "token_integer";
		match("token_integer");
	}else if(currentTokenType == "token_float"){
		aux += "token_float";
		match("token_float");
	}else if(currentTokenType == "true"){
		aux += "true";
		match("true");
	}else if(currentTokenType == "false"){
		aux += "false";
		match("false");
	}else if(currentTokenType == "token_string"){
		aux += "token_string";
		match("token_string");
	}else if(currentTokenType == "token_cor_izq"){
		aux += array();
	}else if(currentTokenType == "id"){
		aux += variable();
	}else if(currentTokenType == "nil"){
		aux += "nil";
		match("nil");
	}else if(currentTokenType == "token_llave_izq"){
		aux += objeto();
	}else if(currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("[");
		array.push_back("id");
		array.push_back("nil");
		array.push_back("{");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
	return aux;
}

int main(){
	Syntactic* S = new Syntactic(true, "input.txt");
	delete S;
	return 0;
}
