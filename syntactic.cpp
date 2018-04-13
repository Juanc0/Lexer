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
	if(currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		stats();
	}else if(currentTokenType == "NULL"){
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
		array.push_back("funcion");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::stats(){
	level++;
	printAsterisks();
	cout << "stats\n";
	if(currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		stat();
		stats1();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
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
		array.push_back("funcion");
		array.push_back("}");
		array.push_back("end");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::stats1(){
	level++;
	printAsterisks();
	cout << "stats1\n";
	if(currentTokenType == "token_salto_linea"){
		match("token_salto_linea");
		stats();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("end");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::stat(){
	level++;
	printAsterisks();
	cout << "stat\n";
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno"){
		simple_stat();
	}else if(currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		compound_stat();
	}else if(currentTokenType == "token_salto_linea"){
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
		array.push_back("retorno");
		array.push_back("if");
		array.push_back("for");
		array.push_back("while");
		array.push_back("funcion");
		array.push_back("token_salto_linea");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::compound_stat(){
	level++;
	printAsterisks();
	cout << "compound_stat\n";
	if(currentTokenType == "if"){
		if_stat();
	}else if(currentTokenType == "while"){
		while_stat();
	}else if(currentTokenType == "for"){
		for_stat();
	}else if(currentTokenType == "funcion"){
		funcion();
	}else{
		vector<string> array;
		array.push_back("if");
		array.push_back("while");
		array.push_back("for");
		array.push_back("funcion");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::simple_stat(){
	level++;
	printAsterisks();
	cout << "simple_stat\n";
	if(currentTokenType == "id"){
		assignment();
	}else if(currentTokenType == "log"){
		log();
	}else if(currentTokenType == "importar" || currentTokenType == "desde"){
		importar();
	}else if(currentTokenType == "retorno"){
		retornar();
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		atom();
	}else{
		vector<string> array;
		array.push_back("id");
		array.push_back("log");
		array.push_back("importar");
		array.push_back("desde");
		array.push_back("retorno");
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
cout << endl;	level--;
}
void Syntactic::assignment(){
	level++;
	printAsterisks();
	cout << "assignment\n";
	if(currentTokenType == "id"){
		variable();
		match("token_assign");
		expr();
	}else{
		vector<string> array;
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::if_stat(){
	level++;
	printAsterisks();
	cout << "if_stat\n";
	if(currentTokenType == "if"){
		match("if");
		match("token_par_izq");
		expr();
		match("token_par_der");
		stat_block();
		C();
	}else{
		vector<string> array;
		array.push_back("if");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::C(){
	level++;
	printAsterisks();
	cout << "C\n";
	if(currentTokenType == "else"){
		match("else");
		stat_block();
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("else");
		array.push_back("token_salto_linea");
		array.push_back("}");
		array.push_back("end");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::while_stat(){
	level++;
	printAsterisks();
	cout << "while_stat\n";
	if(currentTokenType == "while"){
		match("while");
		match("token_par_izq");
		expr();
		match("token_par_der");
		stat_block();
	}else{
		vector<string> array;
		array.push_back("while");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::for_stat(){
	level++;
	printAsterisks();
	cout << "for_stat\n";
	if(currentTokenType == "for"){
		match("for");
		match("id");
		match("in");
		expr();
		stat_block();
	}else{
		vector<string> array;
		array.push_back("for");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::log(){
	level++;
	printAsterisks();
	cout << "log\n";
	if(currentTokenType == "log"){
		match("log");
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else{
		vector<string> array;
		array.push_back("log");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::funcion(){
	level++;
	printAsterisks();
	cout << "funcion\n";
	if(currentTokenType == "funcion"){
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
		array.push_back("funcion");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::E(){
	level++;
	printAsterisks();
	cout << "E\n";
	if(currentTokenType == "id"){
		parametro();
		F();
	}else if(currentTokenType == "token_par_der"){
	}else{
		vector<string> array;
		array.push_back("id");
		array.push_back(")");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::F(){
	level++;
	printAsterisks();
	cout << "F\n";
	if(currentTokenType == "token_coma"){
		match("token_coma");
		parametro();
		F();
	}else if(currentTokenType == "token_par_der"){
	}else{
		vector<string> array;
		array.push_back(",");
		array.push_back(")");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::importar(){
	level++;
	printAsterisks();
	cout << "importar\n";
	if(currentTokenType == "importar"){
		match("importar");
		match("id");
		K();
	}else if(currentTokenType == "desde"){
		match("desde");
		match("id");
		match("importar");
		match("id");
	}else{
		vector<string> array;
		array.push_back("importar");
		array.push_back("desde");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::K(){
	level++;
	printAsterisks();
	cout << "K\n";
	if(currentTokenType == "token_point"){
		match("token_point");
		match("id");
		K();
	}else if(currentTokenType == "token_par_izq" || currentTokenType == "token_assign" || currentTokenType == "token_salto_linea" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_cor_der"){
	}else{
		vector<string> array;
		array.push_back(".");
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
		array.push_back("]");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::retornar(){
	level++;
	printAsterisks();
	cout << "retornar\n";
	if(currentTokenType == "retorno"){
		match("retorno");
		match("token_par_izq");
		expr();
		match("token_par_der");
		match("token_salto_linea");
	}else{
		vector<string> array;
		array.push_back("retorno");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::stat_block(){
	level++;
	printAsterisks();
	cout << "stat_block\n";
	if(currentTokenType == "token_llave_izq"){
		match("token_llave_izq");
		stats();
		match("token_llave_der");
	}else if(currentTokenType == "token_salto_linea"){
		match("token_salto_linea");
		stat();
		match("token_salto_linea");
	}else{
		vector<string> array;
		array.push_back("{");
		array.push_back("token_salto_linea");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::array(){
	level++;
	printAsterisks();
	cout << "array\n";
	if(currentTokenType == "token_cor_izq"){
		match("token_cor_izq");
		G();
		match("token_cor_der");
	}else{
		vector<string> array;
		array.push_back("[");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::objeto(){
	level++;
	printAsterisks();
	cout << "objeto\n";
	if(currentTokenType == "token_llave_izq"){
		match("token_llave_izq");
		L();
		match("token_llave_der");
	}else{
		vector<string> array;
		array.push_back("{");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::L(){
	level++;
	printAsterisks();
	cout << "L\n";
	if(currentTokenType == "id"){
		Keyvalue();
		M();
	}else if(currentTokenType == "token_llave_der"){
	}else{
		vector<string> array;
		array.push_back("id");
		array.push_back("}");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::M(){
	level++;
	printAsterisks();
	cout << "M\n";
	if(currentTokenType == "token_coma"){
		match("token_coma");
		Keyvalue();
		M();
	}else if(currentTokenType == "token_llave_der"){
	}else{
		vector<string> array;
		array.push_back(",");
		array.push_back("}");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::Keyvalue(){
	level++;
	printAsterisks();
	cout << "Keyvalue\n";
	if(currentTokenType == "id"){
		match("id");
		match("token_dosp");
		expr();
	}else{
		vector<string> array;
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::G(){
	level++;
	printAsterisks();
	cout << "G\n";
	if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
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
		array.push_back("id");
		array.push_back(")");
		array.push_back("]");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::H(){
	level++;
	printAsterisks();
	cout << "H\n";
	if(currentTokenType == "token_coma"){
		match("token_coma");
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
	}else{
		vector<string> array;
		array.push_back(",");
		array.push_back(")");
		array.push_back("]");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::variable(){
	level++;
	printAsterisks();
	cout << "variable\n";
	if(currentTokenType == "id"){
		match("id");
		K();
		variable1();
	}else{
		vector<string> array;
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::variable1(){
	level++;
	printAsterisks();
	cout << "variable1\n";
	if(currentTokenType == "token_par_izq"){
		J();
	}else if(currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("(");
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
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::J(){
	level++;
	printAsterisks();
	cout << "J\n";
	if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		G();
		match("token_par_der");
	}else if(currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		vector<string> array;
		array.push_back("(");
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
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::parametro(){
	level++;
	printAsterisks();
	cout << "parametro\n";
	if(currentTokenType == "id"){
		match("id");
		parametro1();
	}else{
		vector<string> array;
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::parametro1(){
	level++;
	printAsterisks();
	cout << "parametro1\n";
	if(currentTokenType == "token_assign"){
		match("token_assign");
		expr();
	}else if(currentTokenType == "token_coma" || currentTokenType == "token_par_der"){
	}else{
		vector<string> array;
		array.push_back("=");
		array.push_back(",");
		array.push_back(")");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::expr(){
	level++;
	printAsterisks();
	cout << "expr\n";
	if(currentTokenType == "token_not"){
		match("token_not");
		expr();
	}else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		atom();
		op();
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
		array.push_back("id");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::op(){
	level++;
	printAsterisks();
	cout << "op\n";
	if(currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or"){
		N();
		expr();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
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
		array.push_back("||");
		array.push_back(")");
		array.push_back(",");
		array.push_back("{");
		array.push_back("token_salto_linea");
		array.push_back("]");
		array.push_back("}");
		array.push_back("end");
		array.push_back("NULL");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::N(){
	level++;
	printAsterisks();
	cout << "N\n";
	if(currentTokenType == "token_pot"){
		match("token_pot");
	}else if(currentTokenType == "token_mul"){
		match("token_mul");
	}else if(currentTokenType == "token_div"){
		match("token_div");
	}else if(currentTokenType == "token_mod"){
		match("token_mod");
	}else if(currentTokenType == "token_mas"){
		match("token_mas");
	}else if(currentTokenType == "token_menos"){
		match("token_menos");
	}else if(currentTokenType == "token_menor_igual"){
		match("token_menor_igual");
	}else if(currentTokenType == "token_mayor_igual"){
		match("token_mayor_igual");
	}else if(currentTokenType == "token_menor"){
		match("token_menor");
	}else if(currentTokenType == "token_mayor"){
		match("token_mayor");
	}else if(currentTokenType == "token_igual_num"){
		match("token_igual_num");
	}else if(currentTokenType == "token_diff_num"){
		match("token_diff_num");
	}else if(currentTokenType == "token_and"){
		match("token_and");
	}else if(currentTokenType == "token_or"){
		match("token_or");
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
		array.push_back("||");
		syntacticError(array);
	}
	printAsterisks();
cout << endl;	level--;
}
void Syntactic::atom(){
	level++;
	printAsterisks();
	cout << "atom\n";
	if(currentTokenType == "token_integer"){
		match("token_integer");
	}else if(currentTokenType == "token_float"){
		match("token_float");
	}else if(currentTokenType == "true"){
		match("true");
	}else if(currentTokenType == "false"){
		match("false");
	}else if(currentTokenType == "token_string"){
		match("token_string");
	}else if(currentTokenType == "token_cor_izq"){
		array();
	}else if(currentTokenType == "id"){
		variable();
	}else if(currentTokenType == "nil"){
		match("nil");
	}else if(currentTokenType == "token_llave_izq"){
		objeto();
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
cout << endl;	level--;
}
