#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//  Compile with
//  g++ -std=c++0x main.cpp -o main


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
    //  Initialize all matrix element with zero (0)
    dfa = new short*[numNonFinalsStates];
    for(short i=0; i<numNonFinalsStates; i++){
        dfa[i] = new short[numCharacters];
        for(short j=0; j< numCharacters; j++)
            dfa[i][j] = 0;
    }

    row = 0;
    column = 0;
    currentLine = "";

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
      {"_","token_guion_bajo"}
    });
    //  Initialize reservedWords hashset
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



    //  Unit tokens with unique match
    //  TODO:   Take it to any character loop
    for(short i=0; i<=14; i++){
        // cout << availableCharacters[i] << (short)availableCharacters[i] << endl;
        dfa[0][(short)availableCharacters[i]] = indexFirstFinalState;
    }
    //  Mixed tokens with multiple matches consideration (Float number case #1: without a number before)
    for(short i=15; i<=22; i++)
        dfa[0][(short)availableCharacters[i]] = i-14;
    //  TODO: check this error -1 or 0
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



    //  Float number (case #2 with a number before)
    dfa[11][(short)'.'] = 12;

    //  "Strings"
    dfa[0][(short)'\"'] = 14;
    for(short i=0; i<numCharacters; i++)
        if(i != (short)'\"')
            dfa[14][i] = 14; // 14 --> 14 loop alphanumeric + ' '
        else
            dfa[14][i] = indexFirstFinalState+5;

    //  Alphabetical loop
    for(short i=65; i<=90; i++){
        dfa[0][i] = 10;
        dfa[0][i+32] = 10;
        dfa[10][i] = 10;
        dfa[10][i+32] = 10;
    }
    //  Numeric loop
    for(short i=48; i<=57; i++){
        dfa[0][i] = 11;
        dfa[11][i] = 11;
        dfa[10][i] = 10;
        //dfa[9][i] = 13; // float without a number before
        dfa[12][i] = 13; // float with a number before
        dfa[13][i] = 13;
    }
    //  Identifiers with '-' or '_' characters
    dfa[10][(short)'_'] = indexFirstFinalState+2;
    dfa[10][(short)'-'] = indexFirstFinalState+2;

    //  Any character loop
    short increment;
    for(short j=0; j<numAvailableCharacters; j++){
        //  Unit tokens with multiple match check
        for(short i=1; i<=13; i++){
            //  TODO: Check if [0-9]'.' map to an integer or a double number or error
            // cout << i << "\t" << j << "\t" << (short)availableCharacters[j] << "\t" << availableCharacters[j] << "\t" << dfa[i][(short)availableCharacters[j]] << endl;
            if(i==12 || i==5 || i== 6)continue;
            if(dfa[i][(short)availableCharacters[j]] == 0){
                increment = (i<10? 1: i-8);
                // increment = (i>=10? i-5: 2);
                //  TODO:   Think about it when i==13
                if(i==13)increment--;
                dfa[i][(short)availableCharacters[j]] = indexFirstFinalState+increment;
            }
        }
        if(dfa[14][(short)availableCharacters[j]] == 0)
            dfa[14][(short)availableCharacters[j]] = indexFirstFinalState+5;

    }

    //  I'm not sure what this does
    for(int i=0; i<numNonFinalsStates; i++){
      if(i==12 || i==5 || i== 6)continue;
      if(dfa[i][0] == 0)
        increment = (i<10? 1: i-8);
      if(i==13)increment--;
      dfa[i][0] = indexFirstFinalState+increment;
    }
    //  Throw a lexical error for non-closed strings
    dfa[14][0] = 0;
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
  //  CurrentLine ckeck
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


  //  find next token
  short currentState = 0;
  short i = 0;
  string tokenType;
  string lexeme;
  while(true){
    // cout << currentState;
    currentState = transition(currentState, (short)currentLine[column+i]);
    // cout << "\t" << currentLine[column+i] << "\t" << (int)currentLine[column+i] << "\t" << currentState<< endl;

    switch (currentState) {
      case 0:
        cout << ">>> Error lexico(linea:" << row << ",posicion:" << column+1 << ")" << endl;
        return NULL;
      case 24:
        //  Float number
        tokenType = "token_float";
        break;
      case 23:
        //  integer
        tokenType = "token_integer";
        break;
      case 22:
        //  identifiers <id, nombre, row, col>
        lexeme = currentLine.substr(column, i);
        tokenType = reservedWords.find(lexeme) != reservedWords.end()? "rw" : "id";
        break;
      case 21:
        //  tokens with an additional character
        i--;
      case 20:
        //  complete tokens (with one and two characters)
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
        //  String
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
		Syntactic(bool useFile, string str);
		~Syntactic();
		void match(string waitedToken);
		void syntacticError(string* array);
		void program();
		void statements();
		void statements2();
		void statements3();
		void statement();
		void element();
		void element1();
		void element2();
		void routine();
		void genoperation();
		void genoperation1();
		void fulloperator();
		void genoperator();
		void espoperation();
		void espoperation1();
		void espoperation2();
		void espoperator();
		void _for();
		void forparam();
		void _while();
		void _if();
		void _else();
		void condition();
		void condition1();
		void log();
		void leer();
		void importar();
		void importar1();
		void importar2();
		void functioncall();
		void cparameters();
		void cparameters1();
		void cparameters2();
		void function();
		void parameters();
		void parameters1();
		void parameters2();
		void functionstm();
		void functionstm1();
		void returnstm();
		void negation();
		void assignment();
		void array();
		void array2();
		void array3();
		void number();
		void boolean();
		void enter();
		void n();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
	currentToken = lexer->nextToken();
	currentToken->print();
	currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
	cout << "currentTokenType\t" << currentTokenType << endl;
	program();
}
Syntactic::~Syntactic(){
	delete lexer;
}
void Syntactic::match(string waitedToken){
	if(currentTokenType == waitedToken){
		currentToken = lexer->nextToken();
		currentToken->print();
		cout << "lexeme " << currentToken->getLexeme() << endl;
		cout << "type " << currentToken->getType() << endl;
		currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
		cout << "currentTokenType\n" << currentTokenType << endl;
	}else{
		string array[] = {waitedToken};
		syntacticError(array);
	}
}
void Syntactic::syntacticError(string* array){
	int n = *(&array + 1) - array;
	cout << "<" << currentToken->getRow() << ":" << currentToken->getColumn() << "> Error sintactico. Encontrado: {" << currentToken->getLexeme() << "}; se esperaba: {";
	for(int i=0; i<n; i++){
		cout << array[i];
	}
	cout << "}";
}
void Syntactic::program(){
	if(currentTokenType == "\n" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil" ||
	currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "$"){
		n();
		statements2();
		n();
	} else {
		string array[] = {"\n","token_integer","token_float","true","false","id","!","token_string","array","[","(","nil","if","while","for","funcion","log","leer","importar","desde","$"};
		syntacticError(array);
	}
}
void Syntactic::statements(){
	if(currentTokenType == "\n" || currentTokenType == "token_llave_izq"){
		n();
		match("token_llave_izq");
		n();
		statements2();
		n();
		match("token_llave_der");
		enter();
	} else if(currentTokenType == "\n"){
		enter();
		statement();
		enter();
	} else {
		string array[] = {"\n","{"};
		syntacticError(array);
	}
}
void Syntactic::statements2(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil" || currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde"){
		statement();
		statements3();
	} else if(currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil","if","while","for","funcion","log","leer","importar","desde","end","}","retorno","$"};
		syntacticError(array);
	}
}
void Syntactic::statements3(){
	if(currentTokenType == "\n"){
		enter();
		statements2();
	} else if(currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	} else {
		string array[] = {"\n","end","}","retorno","$"};
		syntacticError(array);
	}
}
void Syntactic::statement(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element();
	} else if(currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde"){
		routine();
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil","while","for","funcion","log","leer","importar","desde"};
		syntacticError(array);
	}
}
void Syntactic::element(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
	} else if(currentTokenType == "id"){
		assignment();
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::element1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float"){
		number();
	} else if(currentTokenType == "true" || currentTokenType == "false"){
		boolean();
	} else if(currentTokenType == "id"){
		match("id");
	} else if(currentTokenType == "token_not"){
		negation();
	} else if(currentTokenType == "id"){
		functioncall();
	} else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		genoperation();
	} else {
		string array[] = {"token_integer","token_float","false","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::element2(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element1();
	} else if(currentTokenType == "token_string"){
		match("token_string");
	} else if(currentTokenType == "token_cor_izq"){
		array();
	} else if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq"){
		espoperation();
	} else if(currentTokenType == "nil"){
		match("nil");
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil","[","("};
		syntacticError(array);
	}
}
void Syntactic::routine(){
	if(currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde"){
		_if();
	} else if(currentTokenType == "while"){
		_while();
	} else if(currentTokenType == "for"){
		_for();
	} else if(currentTokenType == "funcion"){
		function();
	} else if(currentTokenType == "log"){
		log();
	} else if(currentTokenType == "leer"){
		leer();
	} else if(currentTokenType == "importar" || currentTokenType == "desde"){
		importar();
	} else {
		string array[] = {"if","while","for","funcion","log","leer","importar","desde","desde"};
		syntacticError(array);
	}
}
void Syntactic::genoperation(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq"){
		genoperation1();
	} else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		genoperation1();
		match("token_par_der");
	} else {
		string array[] = {"token_string","[","("};
		syntacticError(array);
	}
}
void Syntactic::genoperation1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element1();
		genoperator();
		element1();
	} else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
		fulloperator();
		element2();
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::fulloperation(){
	if(currentTokenType == "token_string" || currentTokenType == "token_par_izq" || currentTokenType == "token_cor_izq"){
		fulloperation1();
	} else if(currentTokenType == "token_diff_num"){
		match("token_par_izq");
		fulloperation1();
		match("token_par_der");
	} else {
		string array[] = {"token_string", "token_par_izq", "token_cor_izq", };
		syntacticError(array);
	}
}
void Syntactic::fulloperator(){
	if(currentTokenType == "token_igual_num"){
		match("token_igual_num");
	} else if(currentTokenType == "token_diff_num"){
		match("token_diff_num");
	} else if(currentTokenType == "token_and"){
		match("token_and");
	} else if(currentTokenType == "token_or"){
		match("token_or");
	} else {
		string array[] = {"=="};
		syntacticError(array);
	}
}
void Syntactic::genoperator(){
	if(currentTokenType == "token_mas"){
		match("token_mas");
	} else if(currentTokenType == "token_menos"){
		match("token_menos");
	} else if(currentTokenType == "token_mul"){
		match("token_mul");
	} else if(currentTokenType == "token_div"){
		match("token_div");
	} else if(currentTokenType == "token_pot"){
		match("token_pot");
	} else if(currentTokenType == "token_menor"){
		match("token_menor");
	} else if(currentTokenType == "token_mayor"){
		match("token_mayor");
	} else if(currentTokenType == "token_mayor_igual"){
		match("token_mayor_igual");
	} else if(currentTokenType == "token_menor_igual"){
		match("token_menor_igual");
	} else {
		string array[] = {"+"};
		syntacticError(array);
	}
}
void Syntactic::espoperation(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq"){
		espoperator();
		espoperation1();
	} else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		espoperator();
		espoperation1();
		match("token_par_der");
	} else {
		string array[] = {"token_string","["};
		syntacticError(array);
	}
}
void Syntactic::espoperation1(){
	if(currentTokenType == "token_mas"){
		match("token_mas");
		espoperation2();
	} else if(currentTokenType == "token_mul"){
		match("token_mul");
		element1();
	} else {
		string array[] = {"+"};
		syntacticError(array);
	}
}
void Syntactic::espoperation2(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq"){
		espoperator();
	} else if(currentTokenType == "id"){
		match("id");
	} else {
		string array[] = {"token_string","["};
		syntacticError(array);
	}
}
void Syntactic::espoperator(){
	if(currentTokenType == "token_string"){
		match("token_string");
	} else if(currentTokenType == "token_cor_izq"){
		array();
	} else {
		string array[] = {"token_string"};
		syntacticError(array);
	}
}
void Syntactic::_for(){
	if(currentTokenType == "for"){
		match("for");
		match("id");
		match("in");
		forparam();
		statements();
	} else {
		string array[] = {"for"};
		syntacticError(array);
	}
}
void Syntactic::forparam(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq"){
		espoperator();
	} else if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq"){
		espoperation();
	} else if(currentTokenType == "id"){
		match("id");
	} else if(currentTokenType == "id"){
		functioncall();
	} else {
		string array[] = {"token_string","[","[","("};
		syntacticError(array);
	}
}
void Syntactic::_while(){
	if(currentTokenType == "while"){
		match("while");
		condition();
		statements();
	} else {
		string array[] = {"while"};
		syntacticError(array);
	}
}
void Syntactic::_if(){
	if(currentTokenType == "if"){
		match("if");
		condition();
		statements();
		_else();
	} else {
		string array[] = {"if"};
		syntacticError(array);
	}
}
void Syntactic::_else(){
	if(currentTokenType == "else" || currentTokenType == "\n" || currentTokenType == "token_llave_izq"){
		match("else");
		statements();
	} else if(currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	} else {
		string array[] = {"else","\n","{","end","}","retorno","$"};
		syntacticError(array);
	}
}
void Syntactic::condition(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
	} else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		condition1();
		match("token_par_der");
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::condition1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		condition();
	} else if(currentTokenType == "token_par_der"){
		match("epsilon");
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::log(){
	if(currentTokenType == "log"){
		match("log");
		match("token_par_izq");
		element2();
		match("token_par_der");
	} else {
		string array[] = {"log"};
		syntacticError(array);
	}
}
void Syntactic::leer(){
	if(currentTokenType == "leer"){
		match("leer");
		match("token_par_izq");
		match("id");
		match("token_par_der");
	} else {
		string array[] = {"leer"};
		syntacticError(array);
	}
}
void Syntactic::importar(){
	if(currentTokenType == "importar"){
		match("importar");
		importar1();
	} else if(currentTokenType == "desde"){
		match("desde");
		importar1();
		match("importar");
		match("id");
	} else {
		string array[] = {"importar"};
		syntacticError(array);
	}
}
void Syntactic::importar1(){
	if(currentTokenType == "id"){
		match("id");
		importar2();
	} else {
		string array[] = {"id"};
		syntacticError(array);
	}
}
void Syntactic::importar2(){
	if(currentTokenType == "token_point"){
		match("token_point");
		importar1();
	} else if(currentTokenType == "importar" || currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	} else {
		string array[] = {".","\n","end","}","retorno","$"};
		syntacticError(array);
	}
}
void Syntactic::functioncall(){
	if(currentTokenType == "id"){
		match("id");
		match("token_par_izq");
		cparameters();
		match("token_par_der");
	} else {
		string array[] = {"id"};
		syntacticError(array);
	}
}
void Syntactic::cparameters(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		cparameters1();
	} else if(currentTokenType == "token_par_der"){
		match("epsilon");
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::cparameters1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
		cparameters2();
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::cparameters2(){
	if(currentTokenType == "token_coma"){
		match("token_coma");
		cparameters1();
	} else if(currentTokenType == "token_par_der"){
		match("epsilon");
	} else {
		string array[] = {","};
		syntacticError(array);
	}
}
void Syntactic::function(){
	if(currentTokenType == "funcion"){
		match("funcion");
		match("id");
		match("token_par_izq");
		parameters();
		match("token_par_der");
		functionstm();
		match("end");
		match("funcion");
	} else {
		string array[] = {"funcion"};
		syntacticError(array);
	}
}
void Syntactic::parameters(){
	if(currentTokenType == "id"){
		parameters1();
	} else if(currentTokenType == "token_par_der"){
		match("epsilon");
	} else {
		string array[] = {"id"};
		syntacticError(array);
	}
}
void Syntactic::parameters1(){
	if(currentTokenType == "id"){
		match("id");
		parameters2();
	} else {
		string array[] = {"id"};
		syntacticError(array);
	}
}
void Syntactic::parameters2(){
	if(currentTokenType == "token_coma"){
		match("token_coma");
		parameters1();
	} else if(currentTokenType == "token_par_der"){
		match("epsilon");
	} else {
		string array[] = {","};
		syntacticError(array);
	}
}
void Syntactic::functionstm(){
	if(currentTokenType == "\n"){
		enter();
		statements2();
		functionstm1();
	} else {
		string array[] = {"\n"};
		syntacticError(array);
	}
}
void Syntactic::functionstm1(){
	if(currentTokenType == "retorno"){
		match("retorno");
		returnstm();
		enter();
		functionstm();
	} else if(currentTokenType == "end"){
		match("epsilon");
	} else {
		string array[] = {"retorno"};
		syntacticError(array);
	}
}
void Syntactic::returnstm(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
	} else if(currentTokenType == "\n"){
		match("epsilon");
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::negation(){
	if(currentTokenType == "token_not"){
		match("token_not");
		element1();
	} else {
		string array[] = {"!"};
		syntacticError(array);
	}
}
void Syntactic::assignment(){
	if(currentTokenType == "id"){
		match("id");
		match("token_assign");
		element2();
	} else {
		string array[] = {"id"};
		syntacticError(array);
	}
}
void Syntactic::array(){
	if(currentTokenType == "token_cor_izq"){
		match("token_cor_izq");
		array2();
		match("token_cor_der");
	} else {
		string array[] = {"["};
		syntacticError(array);
	}
}
void Syntactic::array2(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
		array3();
	} else {
		string array[] = {"token_integer","token_float","true","false","id","!","token_string","array","[","(","nil"};
		syntacticError(array);
	}
}
void Syntactic::array3(){
	if(currentTokenType == "token_coma"){
		match("token_coma");
		array2();
	} else if(currentTokenType == "token_cor_der"){
		match("epsilon");
	} else {
		string array[] = {","};
		syntacticError(array);
	}
}
void Syntactic::number(){
	if(currentTokenType == "token_integer"){
		match("token_integer");
	} else if(currentTokenType == "token_float"){
		match("token_float");
	} else {
		string array[] = {"token_integer"};
		syntacticError(array);
	}
}
void Syntactic::boolean(){
	if(currentTokenType == "true"){
		match("true");
	} else if(currentTokenType == "false"){
		match("false");
	} else {
		string array[] = {"true"};
		syntacticError(array);
	}
}
void Syntactic::enter(){
	if(currentTokenType == "\n"){
		match("/n");
		n();
	} else {
		string array[] = {"\n"};
		syntacticError(array);
	}
}
void Syntactic::n(){
	if(currentTokenType == "\n"){
		enter();
	} else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil" || currentTokenType == "if" || currentTokenType == "else" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_izq" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	} else {
		string array[] = {"\n","token_float","true","false","id","!","token_string","array","[","(","nil","if","else","while","for","funcion","retorno","log","leer","importar","desde","\n","end","{","}","retorno","$"};
		syntacticError(array);
	}
}








int main(){

		Syntactic* S = new Syntactic(false, "proram-example.txt");

		delete S;
    // Lexer* lexer = new Lexer(false, "program-example.txt");
		//
    // Token* token;
    // while((token = lexer->nextToken()) != NULL){
    //   token->print();
    // }
    // delete lexer;
    return 0;
}

// Yeliana Torres y Juan Pablo Ovalle
