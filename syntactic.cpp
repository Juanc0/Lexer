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
		void stats();
		void stats1();
		void A();
		void B();
		void stat();
		void compound_stat();
		void simple_stat();
		void assignment();
		void assignment1();
		void if_stat();
		void C();
		void while_stat();
		void for_stat();
		void log();
		void funcion();
		void Z();
		void E();
		void F();
		void importar();
		void K();
		void retornar();
		void condition_block();
		void condition_block1();
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
void Syntactic::program(){
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		stats();
	}else if(currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stats(){
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		stat();
		stats1();
	}else if(currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stats1(){
	if(currentTokenType == "\n"){
		match("");
		match("token_dosp");
		match("\n");
		stats();
	}else if(currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::A(){
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		stat();
		A();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::B(){
	if(currentTokenType == "\n"){
		match("");
		match("token_dosp");
		match("\n");
		B();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stat(){
	if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno"){
		match("");
		match("token_dosp");
		simple_stat();
	}else if(currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		compound_stat();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::compound_stat(){
	if(currentTokenType == "if"){
		match("");
		match("token_dosp");
		if_stat();
	}else if(currentTokenType == "while"){
		match("");
		match("token_dosp");
		while_stat();
	}else if(currentTokenType == "for"){
		match("");
		match("token_dosp");
		for_stat();
	}else if(currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		funcion();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::simple_stat(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		assignment();
	}else if(currentTokenType == "log"){
		match("");
		match("token_dosp");
		log();
	}else if(currentTokenType == "importar" || currentTokenType == "desde"){
		match("");
		match("token_dosp");
		importar();
	}else if(currentTokenType == "retorno"){
		match("");
		match("token_dosp");
		retornar();
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		match("");
		match("token_dosp");
		atom();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::assignment(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		variable();
		match("token_assign");
		assignment1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::assignment1(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		assignment();
	}else if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		match("");
		match("token_dosp");
		expr();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::if_stat(){
	if(currentTokenType == "if"){
		match("");
		match("token_dosp");
		match("if");
		condition_block();
		C();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::C(){
	if(currentTokenType == "else"){
		match("");
		match("token_dosp");
		match("else");
		stat_block();
	}else if(currentTokenType == "\n" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::while_stat(){
	if(currentTokenType == "while"){
		match("");
		match("token_dosp");
		match("while");
		expr();
		stat_block();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::for_stat(){
	if(currentTokenType == "for"){
		match("");
		match("token_dosp");
		match("for");
		match("id");
		match("in");
		expr();
		stat_block();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::log(){
	if(currentTokenType == "log"){
		match("");
		match("token_dosp");
		match("log");
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::funcion(){
	if(currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		match("funcion");
		match("id");
		match("token_par_izq");
		E();
		match("token_par_der");
		Z();
		match("end");
		match("funcion");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::Z(){
	if(currentTokenType == "\n"){
		match("");
		match("token_dosp");
		B();
	}else if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		A();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::E(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		parametro();
		F();
	}else if(currentTokenType == "token_par_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::F(){
	if(currentTokenType == "token_coma"){
		match("");
		match("token_dosp");
		match("token_coma");
		parametro();
		F();
	}else if(currentTokenType == "token_par_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::importar(){
	if(currentTokenType == "importar"){
		match("");
		match("token_dosp");
		match("importar");
		match("id");
		K();
	}else if(currentTokenType == "desde"){
		match("");
		match("token_dosp");
		match("desde");
		match("id");
		match("importar");
		match("id");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::K(){
	if(currentTokenType == "token_point"){
		match("");
		match("token_dosp");
		match("token_point");
		match("id");
		K();
	}else if(currentTokenType == "token_par_izq" || currentTokenType == "token_assign" || currentTokenType == "\n" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_cor_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::retornar(){
	if(currentTokenType == "retorno"){
		match("");
		match("token_dosp");
		match("retorno");
		match("token_par_izq");
		expr();
		match("token_par_der");
		match("\n");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::condition_block(){
	if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		match("");
		match("token_dosp");
		expr();
		condition_block1();
		stat_block();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::condition_block1(){
	if(currentTokenType == "\n"){
		match("");
		match("token_dosp");
		match("\n");
	}else if(currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stat_block(){
	if(currentTokenType == "token_llave_izq"){
		match("");
		match("token_dosp");
		match("token_llave_izq");
		Z();
		match("token_llave_der");
	}else if(currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		match("");
		match("token_dosp");
		stat();
		match("\n");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::array(){
	if(currentTokenType == "token_cor_izq"){
		match("");
		match("token_dosp");
		match("token_cor_izq");
		G();
		match("token_cor_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::objeto(){
	if(currentTokenType == "token_llave_izq"){
		match("");
		match("token_dosp");
		match("token_llave_izq");
		L();
		match("token_llave_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::L(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		Keyvalue();
		M();
	}else if(currentTokenType == "token_llave_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::M(){
	if(currentTokenType == "token_coma"){
		match("");
		match("token_dosp");
		match("token_coma");
		Keyvalue();
		M();
	}else if(currentTokenType == "token_llave_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::Keyvalue(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		match("id");
		match("token_dosp");
		expr();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::G(){
	if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		match("");
		match("token_dosp");
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::H(){
	if(currentTokenType == "token_coma"){
		match("");
		match("token_dosp");
		match("token_coma");
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::variable(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		match("id");
		K();
		variable1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::variable1(){
	if(currentTokenType == "token_par_izq"){
		match("");
		match("token_dosp");
		J();
	}else if(currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "\n" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::J(){
	if(currentTokenType == "token_par_izq"){
		match("");
		match("token_dosp");
		match("token_par_izq");
		G();
		match("token_par_der");
	}else if(currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "\n" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parametro(){
	if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		match("id");
		parametro1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parametro1(){
	if(currentTokenType == "token_assign"){
		match("");
		match("token_dosp");
		match("token_assign");
		expr();
	}else if(currentTokenType == "token_coma" || currentTokenType == "token_par_der"){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::expr(){
	if(currentTokenType == "token_not"){
		match("");
		match("token_dosp");
		match("token_not");
		expr();
	}else if(currentTokenType == "token_par_izq"){
		match("");
		match("token_dosp");
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		match("");
		match("token_dosp");
		atom();
		op();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::op(){
	if(currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or"){
		match("");
		match("token_dosp");
		N();
		expr();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "retorno" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "\n" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == ""){
		match("");
		match("token_dosp");
		match("EPSILON");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::N(){
	if(currentTokenType == "token_pot"){
		match("");
		match("token_dosp");
		match("token_pot");
	}else if(currentTokenType == "token_mul"){
		match("");
		match("token_dosp");
		match("token_mul");
	}else if(currentTokenType == "token_div"){
		match("");
		match("token_dosp");
		match("token_div");
	}else if(currentTokenType == "token_mod"){
		match("");
		match("token_dosp");
		match("token_mod");
	}else if(currentTokenType == "token_mas"){
		match("");
		match("token_dosp");
		match("token_mas");
	}else if(currentTokenType == "token_menos"){
		match("");
		match("token_dosp");
		match("token_menos");
	}else if(currentTokenType == "token_menor_igual"){
		match("");
		match("token_dosp");
		match("token_menor_igual");
	}else if(currentTokenType == "token_mayor_igual"){
		match("");
		match("token_dosp");
		match("token_mayor_igual");
	}else if(currentTokenType == "token_menor"){
		match("");
		match("token_dosp");
		match("token_menor");
	}else if(currentTokenType == "token_mayor"){
		match("");
		match("token_dosp");
		match("token_mayor");
	}else if(currentTokenType == "token_igual_num"){
		match("");
		match("token_dosp");
		match("token_igual_num");
	}else if(currentTokenType == "token_diff_num"){
		match("");
		match("token_dosp");
		match("token_diff_num");
	}else if(currentTokenType == "token_and"){
		match("");
		match("token_dosp");
		match("token_and");
	}else if(currentTokenType == "token_or"){
		match("");
		match("token_dosp");
		match("token_or");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::atom(){
	if(currentTokenType == "token_integer"){
		match("");
		match("token_dosp");
		match("token_integer");
	}else if(currentTokenType == "token_float"){
		match("");
		match("token_dosp");
		match("token_float");
	}else if(currentTokenType == "true"){
		match("");
		match("token_dosp");
		match("true");
	}else if(currentTokenType == "false"){
		match("");
		match("token_dosp");
		match("false");
	}else if(currentTokenType == "token_string"){
		match("");
		match("token_dosp");
		match("token_string");
	}else if(currentTokenType == "token_cor_izq"){
		match("");
		match("token_dosp");
		array();
	}else if(currentTokenType == "id"){
		match("");
		match("token_dosp");
		variable();
	}else if(currentTokenType == "nil"){
		match("");
		match("token_dosp");
		match("nil");
	}else if(currentTokenType == "token_llave_izq"){
		match("");
		match("token_dosp");
		objeto();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
