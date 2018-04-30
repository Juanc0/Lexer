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
	dfa[10][13] = indexFirstFinalState+2;
	dfa[11][13] = indexFirstFinalState+3;
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
		currentLineUsefulLength = currentLine.length() - useFile;
		row = 1;
	}if(column == currentLineUsefulLength){
		column++;
		return new Token(row, column, "token_salto_linea", "\n");
	}else if(column == currentLineUsefulLength+1){
		if(input.eof()) return NULL;
		getline(input, currentLine);

		currentLineUsefulLength = currentLine.length() - useFile;
		row++;
		column = 0;
	}
	// cout << column << " " << currentLine.length() << currentLineUsefulLength << endl;


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
					currentLineUsefulLength = currentLine.length() - useFile;
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
		void program();
		void stats();
		void stats1();
		void stat();
		void compound_stat();
		void simple_stat();
		void assignment();
		void if_stat();
		void C();
		void while_stat();
		void for_stat();
		void log();
		void funcion();
		void E();
		void F();
		void importar();
		void K();
		void retornar();
		void stat_block();
		void array();
		void objeto();
		void L();
		void M();
		void Keyvalue();
		void G();
		void H();
		void variable();
		void variable1();
		void J();
		void parametro();
		void parametro1();
		void expr();
		void op();
		void N();
		void atom();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
	currentToken = lexer->nextToken();
		cout << currentToken->getLexeme() << " " << currentToken->getType() << endl;
	currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
	level=0;
	program();
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
			exit(-1);
		}
		cout << currentToken->getLexeme() << " " << currentToken->getType() << endl;
		currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
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

void Syntactic::program(){
	level++;
	printAsterisks();
	cout << "program\n";
	if(currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion'"){
		stats();
	}else if(currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("id");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("log");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("retorno");
		array.push_back("if");
		array.push_back("for");
		array.push_back("while");
		array.push_back("funcion'");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::stats(){
	level++;
	printAsterisks();
	cout << "stats\n";
	if(currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion'"){
		stat();
		stats1();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("id");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("log");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("retorno");
		array.push_back("if");
		array.push_back("for");
		array.push_back("while");
		array.push_back("funcion'");
		array.push_back("}");
		array.push_back("end");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::stats1(){
	level++;
	printAsterisks();
	cout << "stats1\n";
	if(currentTokenType == "token_salto_linea'"){
		match("token_salto_linea");
		stats();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea'");
		array.push_back("}");
		array.push_back("end");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::stat(){
	level++;
	printAsterisks();
	cout << "stat\n";
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno'"){
		simple_stat();
	}else if(currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion'"){
		compound_stat();
	}else if(currentTokenType == "token_salto_linea'"){
		match("token_salto_linea");
	}else{
		vector<string> array;
		array.push_back("id");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("log");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("retorno'");
		array.push_back("if");
		array.push_back("for");
		array.push_back("while");
		array.push_back("funcion'");
		array.push_back("token_salto_linea'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::compound_stat(){
	level++;
	printAsterisks();
	cout << "compound_stat\n";
	if(currentTokenType == "if'"){
		if_stat();
	}else if(currentTokenType == "while'"){
		while_stat();
	}else if(currentTokenType == "for'"){
		for_stat();
	}else if(currentTokenType == "funcion'"){
		funcion();
	}else{
		vector<string> array;
		array.push_back("if'");
		array.push_back("while'");
		array.push_back("for'");
		array.push_back("funcion'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::simple_stat(){
	level++;
	printAsterisks();
	cout << "simple_stat\n";
	if(currentTokenType == "id'"){
		assignment();
	}else if(currentTokenType == "log'"){
		log();
	}else if(currentTokenType == "importar" || currentTokenType == "desde'"){
		importar();
	}else if(currentTokenType == "retorno'"){
		retornar();
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id'"){
		atom();
	}else{
		vector<string> array;
		array.push_back("id'");
		array.push_back("log'");
		array.push_back("importar");
		array.push_back("desde'");
		array.push_back("retorno'");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::assignment(){
	level++;
	printAsterisks();
	cout << "assignment\n";
	if(currentTokenType == "id'"){
		variable();
		match("token_assign");
		expr();
	}else{
		vector<string> array;
		array.push_back("id'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::if_stat(){
	level++;
	printAsterisks();
	cout << "if_stat\n";
	if(currentTokenType == "if'"){
		match("if");
		match("token_par_izq");
		expr();
		match("token_par_der");
		stat_block();
		C();
	}else{
		vector<string> array;
		array.push_back("if'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::C(){
	level++;
	printAsterisks();
	cout << "C\n";
	if(currentTokenType == "else'"){
		match("else");
		stat_block();
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("else'");
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("end");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::while_stat(){
	level++;
	printAsterisks();
	cout << "while_stat\n";
	if(currentTokenType == "while'"){
		match("while");
		match("token_par_izq");
		expr();
		match("token_par_der");
		stat_block();
	}else{
		vector<string> array;
		array.push_back("while'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::for_stat(){
	level++;
	printAsterisks();
	cout << "for_stat\n";
	if(currentTokenType == "for'"){
		match("for");
		match("id");
		match("in");
		expr();
		stat_block();
	}else{
		vector<string> array;
		array.push_back("for'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::log(){
	level++;
	printAsterisks();
	cout << "log\n";
	if(currentTokenType == "log'"){
		match("log");
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else{
		vector<string> array;
		array.push_back("log'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::funcion(){
	level++;
	printAsterisks();
	cout << "funcion\n";
	if(currentTokenType == "funcion'"){
		match("funcion");
		match("id");
		match("token_par_izq");
		E();
		match("token_par_der");
		stats();
		match("end");
		match("funcion");
	}else{
		vector<string> array;
		array.push_back("funcion'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::E(){
	level++;
	printAsterisks();
	cout << "E\n";
	if(currentTokenType == "id'"){
		parametro();
		F();
	}else if(currentTokenType == ")'"){
	}else{
		vector<string> array;
		array.push_back("id'");
		array.push_back(")'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::F(){
	level++;
	printAsterisks();
	cout << "F\n";
	if(currentTokenType == ",'"){
		match("token_coma");
		parametro();
		F();
	}else if(currentTokenType == ")'"){
	}else{
		vector<string> array;
		array.push_back(",'");
		array.push_back(")'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::importar(){
	level++;
	printAsterisks();
	cout << "importar\n";
	if(currentTokenType == "importar'"){
		match("importar");
		match("id");
		K();
	}else if(currentTokenType == "desde'"){
		match("desde");
		match("id");
		match("importar");
		match("id");
	}else{
		vector<string> array;
		array.push_back("importar'");
		array.push_back("desde'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::K(){
	level++;
	printAsterisks();
	cout << "K\n";
	if(currentTokenType == ".'"){
		match("token_point");
		match("id");
		K();
	}else if(currentTokenType == "token_par_izq" || currentTokenType == "token_assign" || currentTokenType == "token_salto_linea" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "CKEY'"){
	}else{
		vector<string> array;
		array.push_back(".'");
		array.push_back("(");
		array.push_back("=");
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("end");
		array.push_back("NULL");
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
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
		array.push_back("CKEY'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::retornar(){
	level++;
	printAsterisks();
	cout << "retornar\n";
	if(currentTokenType == "retorno'"){
		match("retorno");
		match("token_par_izq");
		expr();
		match("token_par_der");
		match("token_salto_linea");
	}else{
		vector<string> array;
		array.push_back("retorno'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::stat_block(){
	level++;
	printAsterisks();
	cout << "stat_block\n";
	if(currentTokenType == "{'"){
		match("token_llave_izq");
		stats();
		match("token_llave_der");
	}else if(currentTokenType == "token_salto_linea'"){
		match("token_salto_linea");
		stat();
		match("token_salto_linea");
	}else{
		vector<string> array;
		array.push_back("{'");
		array.push_back("token_salto_linea'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::array(){
	level++;
	printAsterisks();
	cout << "array\n";
	if(currentTokenType == "OKEY'"){
		match("token_cor_izq");
		G();
		match("token_cor_der");
	}else{
		vector<string> array;
		array.push_back("OKEY'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::objeto(){
	level++;
	printAsterisks();
	cout << "objeto\n";
	if(currentTokenType == "{'"){
		match("token_llave_izq");
		L();
		match("token_llave_der");
	}else{
		vector<string> array;
		array.push_back("{'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::L(){
	level++;
	printAsterisks();
	cout << "L\n";
	if(currentTokenType == "id'"){
		Keyvalue();
		M();
	}else if(currentTokenType == "}'"){
	}else{
		vector<string> array;
		array.push_back("id'");
		array.push_back("}'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::M(){
	level++;
	printAsterisks();
	cout << "M\n";
	if(currentTokenType == ",'"){
		match("token_coma");
		Keyvalue();
		M();
	}else if(currentTokenType == "}'"){
	}else{
		vector<string> array;
		array.push_back(",'");
		array.push_back("}'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::Keyvalue(){
	level++;
	printAsterisks();
	cout << "Keyvalue\n";
	if(currentTokenType == "id'"){
		match("id");
		match("token_dosp");
		expr();
	}else{
		vector<string> array;
		array.push_back("id'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::G(){
	level++;
	printAsterisks();
	cout << "G\n";
	if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id'"){
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "CKEY'"){
	}else{
		vector<string> array;
		array.push_back("!");
		array.push_back("(");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id'");
		array.push_back(")");
		array.push_back("CKEY'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::H(){
	level++;
	printAsterisks();
	cout << "H\n";
	if(currentTokenType == ",'"){
		match("token_coma");
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "CKEY'"){
	}else{
		vector<string> array;
		array.push_back(",'");
		array.push_back(")");
		array.push_back("CKEY'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::variable(){
	level++;
	printAsterisks();
	cout << "variable\n";
	if(currentTokenType == "id'"){
		match("id");
		K();
		variable1();
	}else{
		vector<string> array;
		array.push_back("id'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::variable1(){
	level++;
	printAsterisks();
	cout << "variable1\n";
	if(currentTokenType == "('"){
		J();
	}else if(currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("('");
		array.push_back("=");
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
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
		array.push_back("end");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::J(){
	level++;
	printAsterisks();
	cout << "J\n";
	if(currentTokenType == "('"){
		match("token_par_izq");
		G();
		match("token_par_der");
	}else if(currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("('");
		array.push_back("=");
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
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
		array.push_back("end");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::parametro(){
	level++;
	printAsterisks();
	cout << "parametro\n";
	if(currentTokenType == "id'"){
		match("id");
		parametro1();
	}else{
		vector<string> array;
		array.push_back("id'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::parametro1(){
	level++;
	printAsterisks();
	cout << "parametro1\n";
	if(currentTokenType == "='"){
		match("token_assign");
		expr();
	}else if(currentTokenType == "token_coma" || currentTokenType == ")'"){
	}else{
		vector<string> array;
		array.push_back("='");
		array.push_back(",");
		array.push_back(")'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::expr(){
	level++;
	printAsterisks();
	cout << "expr\n";
	if(currentTokenType == "!'"){
		match("token_not");
		expr();
	}else if(currentTokenType == "('"){
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id'"){
		atom();
		op();
	}else{
		vector<string> array;
		array.push_back("!'");
		array.push_back("('");
		array.push_back("token_integer");
		array.push_back("token_float");
		array.push_back("true");
		array.push_back("false");
		array.push_back("token_string");
		array.push_back("nil");
		array.push_back("[");
		array.push_back("{");
		array.push_back("id'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::op(){
	level++;
	printAsterisks();
	cout << "op\n";
	if(currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "||'"){
		N();
		expr();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "$'"){
	}else{
		vector<string> array;
		array.push_back("^");
		array.push_back("*");
		array.push_back("/");
		array.push_back("%");
		array.push_back("+");
		array.push_back("-");
		array.push_back("<=");
		array.push_back(">=");
		array.push_back("<");
		array.push_back(">");
		array.push_back("==");
		array.push_back("!=");
		array.push_back("&&");
		array.push_back("||'");
		array.push_back(")");
		array.push_back(",");
		array.push_back("{");
		array.push_back("token_salto_linea");
		array.push_back("]");
		array.push_back("}");
		array.push_back("end");
		array.push_back("$'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::N(){
	level++;
	printAsterisks();
	cout << "N\n";
	if(currentTokenType == "^'"){
		match("token_pot");
	}else if(currentTokenType == "*'"){
		match("token_mul");
	}else if(currentTokenType == "/'"){
		match("token_div");
	}else if(currentTokenType == "%'"){
		match("token_mod");
	}else if(currentTokenType == "+'"){
		match("token_mas");
	}else if(currentTokenType == "-'"){
		match("token_menos");
	}else if(currentTokenType == "<='"){
		match("token_menor_igual");
	}else if(currentTokenType == ">='"){
		match("token_mayor_igual");
	}else if(currentTokenType == "<'"){
		match("token_menor");
	}else if(currentTokenType == ">'"){
		match("token_mayor");
	}else if(currentTokenType == "=='"){
		match("token_igual_num");
	}else if(currentTokenType == "!='"){
		match("token_diff_num");
	}else if(currentTokenType == "&&'"){
		match("token_and");
	}else if(currentTokenType == "||'"){
		match("token_or");
	}else{
		vector<string> array;
		array.push_back("^'");
		array.push_back("*'");
		array.push_back("/'");
		array.push_back("%'");
		array.push_back("+'");
		array.push_back("-'");
		array.push_back("<='");
		array.push_back(">='");
		array.push_back("<'");
		array.push_back(">'");
		array.push_back("=='");
		array.push_back("!='");
		array.push_back("&&'");
		array.push_back("||'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}
void Syntactic::atom(){
	level++;
	printAsterisks();
	cout << "atom\n";
	if(currentTokenType == "token_integer'"){
		match("token_integer");
	}else if(currentTokenType == "token_float'"){
		match("token_float");
	}else if(currentTokenType == "true'"){
		match("true");
	}else if(currentTokenType == "false'"){
		match("false");
	}else if(currentTokenType == "token_string'"){
		match("token_string");
	}else if(currentTokenType == "OKEY'"){
		array();
	}else if(currentTokenType == "id'"){
		variable();
	}else if(currentTokenType == "nil'"){
		match("nil");
	}else if(currentTokenType == "{'"){
		objeto();
	}else{
		vector<string> array;
		array.push_back("token_integer'");
		array.push_back("token_float'");
		array.push_back("true'");
		array.push_back("false'");
		array.push_back("token_string'");
		array.push_back("OKEY'");
		array.push_back("id'");
		array.push_back("nil'");
		array.push_back("{'");
		syntacticError(array);
	}
	printAsterisks();
	cout << endl;
	level--;
}

int main(){
	Syntactic* S = new Syntactic(true, "input.txt");
	delete S;
	return 0;
}
