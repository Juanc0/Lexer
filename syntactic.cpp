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
		void genoperator();
		void fulloperation();
		void fulloperation1();
		void fulloperator();
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
	if(currentTokenType == "\n" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil" || currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "$"){
		n();
		statements2();
		n();
	}else{
		string array[] = {};
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
	}else if(currentTokenType == "\n"){
		enter();
		statement();
		enter();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::statements2(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil" || currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde"){
		statement();
		statements3();
	}else if(currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::statements3(){
	if(currentTokenType == "\n"){
		enter();
		statements2();
	}else if(currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::statement(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element();
	}else if(currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde"){
		routine();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::element(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
	}else if(currentTokenType == "id"){
		assignment();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::element1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float"){
		number();
	}else if(currentTokenType == "true" || currentTokenType == "false"){
		boolean();
	}else if(currentTokenType == "token_not"){
		negation();
	}else if(currentTokenType == "id"){
		functioncall();
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		genoperation();
	}else if(currentTokenType == "nil"){
		fulloperation();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::element2(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element1();
	}else if(currentTokenType == "token_string"){
		match("token_string");
	}else if(currentTokenType == "token_cor_izq"){
		array();
	}else if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq"){
		espoperation();
	}else if(currentTokenType == "nil"){
		match("nil");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::routine(){
	if(currentTokenType == "if" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde"){
		_if();
	}else if(currentTokenType == "while"){
		_while();
	}else if(currentTokenType == "for"){
		_for();
	}else if(currentTokenType == "funcion"){
		function();
	}else if(currentTokenType == "log"){
		log();
	}else if(currentTokenType == "leer"){
		leer();
	}else if(currentTokenType == "importar" || currentTokenType == "desde"){
		importar();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::genoperation(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq"){
		genoperation1();
	}else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		genoperation1();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::genoperation1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element1();
		genoperator();
		element1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::genoperator(){
	if(currentTokenType == "token_mas"){
		match("token_mas");
	}else if(currentTokenType == "token_menos"){
		match("token_menos");
	}else if(currentTokenType == "token_mul"){
		match("token_mul");
	}else if(currentTokenType == "token_div"){
		match("token_div");
	}else if(currentTokenType == "token_pot"){
		match("token_pot");
	}else if(currentTokenType == "token_menor"){
		match("token_menor");
	}else if(currentTokenType == "token_mayor"){
		match("token_mayor");
	}else if(currentTokenType == "token_mayor_igual"){
		match("token_mayor_igual");
	}else if(currentTokenType == "token_menor_igual"){
		match("token_menor_igual");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::fulloperation(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		fulloperation1();
	}else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		fulloperation1();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::fulloperation1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
		fulloperator();
		element2();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::fulloperator(){
	if(currentTokenType == "token_igual_num"){
		match("token_igual_num");
	}else if(currentTokenType == "token_diff_num"){
		match("token_diff_num");
	}else if(currentTokenType == "token_and"){
		match("token_and");
	}else if(currentTokenType == "token_or"){
		match("token_or");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::espoperation(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq"){
		espoperator();
		espoperation1();
	}else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		espoperator();
		espoperation1();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::espoperation1(){
	if(currentTokenType == "token_mas"){
		match("token_mas");
		espoperation2();
	}else if(currentTokenType == "token_mul"){
		match("token_mul");
		element1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::espoperation2(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq"){
		espoperator();
	}else if(currentTokenType == "id"){
		match("id");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::espoperator(){
	if(currentTokenType == "token_string"){
		match("token_string");
	}else if(currentTokenType == "token_cor_izq"){
		array();
	}else{
		string array[] = {};
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
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::forparam(){
	if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq"){
		espoperator();
	}else if(currentTokenType == "token_string" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq"){
		espoperation();
	}else if(currentTokenType == "id"){
		functioncall();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::_while(){
	if(currentTokenType == "while"){
		match("while");
		condition();
		statements();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::_if(){
	if(currentTokenType == "if"){
		match("if");
		condition();
		statements();
		_else();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::_else(){
	if(currentTokenType == "else" || currentTokenType == "\n" || currentTokenType == "token_llave_izq"){
		match("else");
		statements();
	}else if(currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::condition(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
	}else if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		condition1();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::condition1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		condition();
	}else if(currentTokenType == "token_par_der"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::log(){
	if(currentTokenType == "log"){
		match("log");
		match("token_par_izq");
		element2();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::leer(){
	if(currentTokenType == "leer"){
		match("leer");
		match("token_par_izq");
		match("id");
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::importar(){
	if(currentTokenType == "importar"){
		match("importar");
		importar1();
	}else if(currentTokenType == "desde"){
		match("desde");
		importar1();
		match("importar");
		match("id");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::importar1(){
	if(currentTokenType == "id"){
		match("id");
		importar2();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::importar2(){
	if(currentTokenType == "token_point"){
		match("token_point");
		importar1();
	}else if(currentTokenType == "importar" || currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::functioncall(){
	if(currentTokenType == "id"){
		match("id");
		cparameters();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::cparameters(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		match("token_par_izq");
		cparameters1();
		match("token_par_der");
	}else if(currentTokenType == "token_par_der"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::cparameters1(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
		cparameters2();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::cparameters2(){
	if(currentTokenType == "token_coma"){
		match("token_coma");
		cparameters1();
	}else if(currentTokenType == "token_par_der"){
		match("epsilon");
	}else{
		string array[] = {};
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
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parameters(){
	if(currentTokenType == "id"){
		parameters1();
	}else if(currentTokenType == "token_par_der"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parameters1(){
	if(currentTokenType == "id"){
		match("id");
		parameters2();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parameters2(){
	if(currentTokenType == "token_coma"){
		match("token_coma");
		parameters1();
	}else if(currentTokenType == "token_par_der"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::functionstm(){
	if(currentTokenType == "\n"){
		enter();
		statements2();
		functionstm1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::functionstm1(){
	if(currentTokenType == "retorno"){
		match("retorno");
		returnstm();
		enter();
		functionstm();
	}else if(currentTokenType == "end"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::returnstm(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
	}else if(currentTokenType == "\n"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::negation(){
	if(currentTokenType == "token_not"){
		match("token_not");
		element1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::assignment(){
	if(currentTokenType == "id"){
		match("id");
		match("token_assign");
		element2();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::array(){
	if(currentTokenType == "token_cor_izq"){
		match("token_cor_izq");
		array2();
		match("token_cor_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::array2(){
	if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil"){
		element2();
		array3();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::array3(){
	if(currentTokenType == "token_coma"){
		match("token_coma");
		array2();
	}else if(currentTokenType == "token_cor_der"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::number(){
	if(currentTokenType == "token_integer"){
		match("token_integer");
	}else if(currentTokenType == "token_float"){
		match("token_float");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::boolean(){
	if(currentTokenType == "true"){
		match("true");
	}else if(currentTokenType == "false"){
		match("false");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::enter(){
	if(currentTokenType == "\n"){
		match("\n");
		n();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::n(){
	if(currentTokenType == "\n"){
		enter();
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "id" || currentTokenType == "token_not" || currentTokenType == "token_string" || currentTokenType == "array" || currentTokenType == "token_cor_izq" || currentTokenType == "token_par_izq" || currentTokenType == "nil" || currentTokenType == "if" || currentTokenType == "else" || currentTokenType == "while" || currentTokenType == "for" || currentTokenType == "funcion" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "leer" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "\n" || currentTokenType == "end" || currentTokenType == "token_llave_izq" || currentTokenType == "token_llave_der" || currentTokenType == "retorno" || currentTokenType == "$"){
		match("epsilon");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
