class Syntactic{
	public:
		Lexer* lexer;
		Token currentToken;
		string currentTokenType;
		Syntactic();
		~Syntactic();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
}
Syntactic::~Syntactic(bool useFile, string str){
	delete lexer;
}
void Syntactic::match(Token waitedToken){
	;
}
void Syntactic::program(){
	if(currentTokenType == "n" || currentTokenType == "statements2" || currentTokenType == "n"){
		n();
		statements2();
		n();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::statements(){
	if(currentTokenType == "n" || currentTokenType == "token_llave_izq" || currentTokenType == "n" || currentTokenType == "statements2" || currentTokenType == "n" || currentTokenType == "token_llave_der" || currentTokenType == "enter"){
		n();
		match("token_llave_izq");
		n();
		statements2();
		n();
		match("token_llave_der");
		enter();
	}	else if(currentTokenType == "enter" || currentTokenType == "statement" || currentTokenType == "enter"){
		enter();
		statement();
		enter();
	}
}
void Syntactic::statements2(){
	if(currentTokenType == "statement" || currentTokenType == "statements3"){
		statement();
		statements3();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::statements3(){
	if(currentTokenType == "enter" || currentTokenType == "statements2"){
		enter();
		statements2();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::statement(){
	if(currentTokenType == "element"){
		element();
	}	else if(currentTokenType == "routine"){
		routine();
	}
}
void Syntactic::element(){
	if(currentTokenType == "element2"){
		element2();
	}	else if(currentTokenType == "assignment"){
		assignment();
	}
}
void Syntactic::element1(){
	if(currentTokenType == "number"){
		number();
	}	else if(currentTokenType == "boolean"){
		boolean();
	}	else if(currentTokenType == "identifier"){
		match("identifier");
	}	else if(currentTokenType == "negation"){
		negation();
	}	else if(currentTokenType == "function_call"){
		function_call();
	}	else if(currentTokenType == "gen_operation"){
		gen_operation();
	}
}
void Syntactic::element2(){
	if(currentTokenType == "element1"){
		element1();
	}	else if(currentTokenType == "string"){
		match("string");
	}	else if(currentTokenType == "array"){
		array();
	}	else if(currentTokenType == "esp_operation"){
		esp_operation();
	}	else if(currentTokenType == "nil"){
		match("nil");
	}
}
void Syntactic::routine(){
	if(currentTokenType == "if"){
		if();
	}	else if(currentTokenType == "while"){
		while();
	}	else if(currentTokenType == "for"){
		for();
	}	else if(currentTokenType == "function"){
		function();
	}	else if(currentTokenType == "log"){
		log();
	}	else if(currentTokenType == "leer"){
		leer();
	}	else if(currentTokenType == "importar"){
		importar();
	}
}
void Syntactic::gen_operation(){
	if(currentTokenType == "gen_operation1"){
		gen_operation1();
	}	else if(currentTokenType == "token_par_izq" || currentTokenType == "gen_operation1" || currentTokenType == "token_par_der"){
		match("token_par_izq");
		gen_operation1();
		match("token_par_der");
	}
}
void Syntactic::gen_operation1(){
	if(currentTokenType == "element1" || currentTokenType == "gen_operator" || currentTokenType == "element1"){
		element1();
		gen_operator();
		element1();
	}	else if(currentTokenType == "element" || currentTokenType == "token_igual_num" || currentTokenType == "element"){
		element();
		match("token_igual_num");
		element();
	}	else if(currentTokenType == "element" || currentTokenType == "token_diff_num" || currentTokenType == "element"){
		element();
		match("token_diff_num");
		element();
	}	else if(currentTokenType == "element" || currentTokenType == "token_and" || currentTokenType == "element"){
		element();
		match("token_and");
		element();
	}	else if(currentTokenType == "element" || currentTokenType == "token_or" || currentTokenType == "element"){
		element();
		match("token_or");
		element();
	}
}
void Syntactic::gen_operator(){
	if(currentTokenType == "token_mas"){
		match("token_mas");
	}	else if(currentTokenType == "token_menos"){
		match("token_menos");
	}	else if(currentTokenType == "token_mul"){
		match("token_mul");
	}	else if(currentTokenType == "token_div"){
		match("token_div");
	}	else if(currentTokenType == "token_pot"){
		match("token_pot");
	}	else if(currentTokenType == "token_menor"){
		match("token_menor");
	}	else if(currentTokenType == "token_mayor"){
		match("token_mayor");
	}	else if(currentTokenType == "token_mayor_igual"){
		match("token_mayor_igual");
	}	else if(currentTokenType == "token_menor_igual"){
		match("token_menor_igual");
	}
}
void Syntactic::esp_operation(){
	if(currentTokenType == "esp_operator" || currentTokenType == "esp_operation1"){
		esp_operator();
		esp_operation1();
	}	else if(currentTokenType == "token_par_izq" || currentTokenType == "esp_operator" || currentTokenType == "esp_operation1" || currentTokenType == "token_par_der"){
		match("token_par_izq");
		esp_operator();
		esp_operation1();
		match("token_par_der");
	}
}
void Syntactic::esp_operation1(){
	if(currentTokenType == "token_mas" || currentTokenType == "esp_operation2"){
		match("token_mas");
		esp_operation2();
	}	else if(currentTokenType == "token_mul" || currentTokenType == "element1"){
		match("token_mul");
		element1();
	}
}
void Syntactic::esp_operation2(){
	if(currentTokenType == "esp_operator"){
		esp_operator();
	}	else if(currentTokenType == "identifier"){
		match("identifier");
	}
}
void Syntactic::esp_operator(){
	if(currentTokenType == "string"){
		match("string");
	}	else if(currentTokenType == "array"){
		array();
	}
}
void Syntactic::for(){
	if(currentTokenType == "for" || currentTokenType == "identifier" || currentTokenType == "in" || currentTokenType == "for_param" || currentTokenType == "statements"){
		match("for");
		match("identifier");
		match("in");
		for_param();
		statements();
	}
}
void Syntactic::for_param(){
	if(currentTokenType == "esp_operator"){
		esp_operator();
	}	else if(currentTokenType == "esp_operation"){
		esp_operation();
	}	else if(currentTokenType == "identifier"){
		match("identifier");
	}	else if(currentTokenType == "function_call"){
		function_call();
	}
}
void Syntactic::while(){
	if(currentTokenType == "while" || currentTokenType == "condition" || currentTokenType == "statements"){
		match("while");
		condition();
		statements();
	}
}
void Syntactic::if(){
	if(currentTokenType == "if" || currentTokenType == "condition" || currentTokenType == "statements" || currentTokenType == "else"){
		match("if");
		condition();
		statements();
		else();
	}
}
void Syntactic::else(){
	if(currentTokenType == "else" || currentTokenType == "statements"){
		match("else");
		statements();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::condition(){
	if(currentTokenType == "element2"){
		element2();
	}	else if(currentTokenType == "token_par_izq" || currentTokenType == "token_par_der"){
		match("token_par_izq");
		match("token_par_der");
	}
}
void Syntactic::condition1(){
	if(currentTokenType == "token_par_izq" || currentTokenType == "condition" || currentTokenType == "token_par_der"){
		match("token_par_izq");
		condition();
		match("token_par_der");
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::log(){
	if(currentTokenType == "log" || currentTokenType == "token_par_izq" || currentTokenType == "element2" || currentTokenType == "token_par_der"){
		log();
		match("token_par_izq");
		element2();
		match("token_par_der");
	}
}
void Syntactic::leer(){
	if(currentTokenType == "leer" || currentTokenType == "token_par_izq" || currentTokenType == "identifier" || currentTokenType == "token_par_der"){
		leer();
		match("token_par_izq");
		match("identifier");
		match("token_par_der");
	}
}
void Syntactic::importar(){
	if(currentTokenType == "importar" || currentTokenType == "importar1"){
		match("importar");
		importar1();
	}	else if(currentTokenType == "desde" || currentTokenType == "importar1" || currentTokenType == "importar" || currentTokenType == "identifier"){
		match("desde");
		importar1();
		match("importar");
		match("identifier");
	}
}
void Syntactic::importar1(){
	if(currentTokenType == "identifier" || currentTokenType == "importar2"){
		match("identifier");
		importar2();
	}
}
void Syntactic::importar2(){
	if(currentTokenType == "token_point" || currentTokenType == "importar1"){
		match("token_point");
		importar1();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::function_call(){
	if(currentTokenType == "identifier" || currentTokenType == "token_par_izq" || currentTokenType == "c_parameters" || currentTokenType == "token_par_der"){
		match("identifier");
		match("token_par_izq");
		c_parameters();
		match("token_par_der");
	}
}
void Syntactic::c_parameters(){
	if(currentTokenType == "c_parameters1"){
		c_parameters1();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::c_parameters1(){
	if(currentTokenType == "element" || currentTokenType == "c_parameters2"){
		element();
		c_parameters2();
	}
}
void Syntactic::c_parameters2(){
	if(currentTokenType == "token_coma" || currentTokenType == "c_parameters1"){
		match("token_coma");
		c_parameters1();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::function(){
	if(currentTokenType == "funcion" || currentTokenType == "identifier" || currentTokenType == "token_par_izq" || currentTokenType == "parameters" || currentTokenType == "token_par_der" || currentTokenType == "function_stm" || currentTokenType == "end" || currentTokenType == "funcion"){
		match("funcion");
		match("identifier");
		match("token_par_izq");
		parameters();
		match("token_par_der");
		function_stm();
		match("end");
		match("funcion");
	}
}
void Syntactic::parameters(){
	if(currentTokenType == "parameters1"){
		parameters1();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::parameters1(){
	if(currentTokenType == "identifier" || currentTokenType == "parameters2"){
		match("identifier");
		parameters2();
	}
}
void Syntactic::parameters2(){
	if(currentTokenType == "token_coma" || currentTokenType == "parameters1"){
		match("token_coma");
		parameters1();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::function_stm(){
	if(currentTokenType == "enter" || currentTokenType == "statements2" || currentTokenType == "function_stm1"){
		enter();
		statements2();
		function_stm1();
	}
}
void Syntactic::function_stm1(){
	if(currentTokenType == "retorno" || currentTokenType == "return_stm" || currentTokenType == "enter" || currentTokenType == "function_stm"){
		match("retorno");
		return_stm();
		enter();
		function_stm();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::return_stm(){
	if(currentTokenType == "element2"){
		element2();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::negation(){
	if(currentTokenType == "token_not" || currentTokenType == "element1"){
		match("token_not");
		element1();
	}
}
void Syntactic::assignment(){
	if(currentTokenType == "identifier" || currentTokenType == "token_assign" || currentTokenType == "element2"){
		match("identifier");
		match("token_assign");
		element2();
	}
}
void Syntactic::array(){
	if(currentTokenType == "token_cor_izq" || currentTokenType == "array2" || currentTokenType == "token_cor_der"){
		match("token_cor_izq");
		array2();
		match("token_cor_der");
	}
}
void Syntactic::array2(){
	if(currentTokenType == "element2" || currentTokenType == "array3"){
		element2();
		array3();
	}
}
void Syntactic::array3(){
	if(currentTokenType == "token_coma" || currentTokenType == "array2"){
		match("token_coma");
		array2();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
void Syntactic::number(){
	if(currentTokenType == "token_integer"){
		match("token_integer");
	}	else if(currentTokenType == "token_float"){
		match("token_float");
	}
}
void Syntactic::string (){
	if(currentTokenType == "token_string"){
		match("token_string");
	}
}
void Syntactic::boolean(){
	if(currentTokenType == "true"){
		match("true");
	}	else if(currentTokenType == "false"){
		match("false");
	}
}
void Syntactic::enter(){
	if(currentTokenType == "\n" || currentTokenType == "n"){
		match("\n");
		n();
	}
}
void Syntactic::n(){
	if(currentTokenType == "enter"){
		enter();
	}	else if(currentTokenType == "epsilon"){
		match("epsilon");
	}
}
