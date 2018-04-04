class Syntactic{
	public:
		Lexer* lexer;
		Token* currentToken;
		string currentTokenType;
		Syntactic(bool useFile, string str);
		~Syntactic();
		void match(string waitedToken);
		void syntacticError(string* array);
		void from_input();
		void A();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
	currentToken = lexer->nextToken();
	currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
	program();
}
Syntactic::~Syntactic(){
	delete lexer;
}
void Syntactic::match(string waitedToken){
	if(currentTokenType == waitedToken){
		currentToken = lexer->nextToken();
		currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
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
void Syntactic::from_input(){
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("stat");
		match("\n");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::A(){
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("stat");
		A();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end"){
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
