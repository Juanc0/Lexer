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
		void leer();
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
		void ENTER();
		void NEWLINE();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
	currentToken = lexer->nextToken();
		cout << currentToken->getLexeme() << " " << currentToken->getType() << endl;
	currentTokenType = currentToken->getType() == "rw"?currentToken->getLexeme():currentToken->getType();
	program();
}
Syntactic::~Syntactic(){
	delete lexer;
}
void Syntactic::match(string waitedToken){
		cout << "match f waitedToken " << waitedToken << endl;
	if(currentTokenType == waitedToken){
		currentToken = lexer->nextToken();
		if(currentToken == NULL){
			cout << "El analisis sintactico ha finalizado correctamente.
";
			exit(-1);
		}
		cout << currentToken->getLexeme() << " " << currentToken->getType() << endl;
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
	exit(-1);
}
void Syntactic::program(){
		cout << "funcion program currentToken " << currentToken << endl;
	if(currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		stats();
	}else if(currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stats(){
		cout << "funcion stats currentToken " << currentToken << endl;
	if(currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		stat();
		stats1();
	}else if(currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stats1(){
		cout << "funcion stats1 currentToken " << currentToken << endl;
	if(currentTokenType == "token_salto_linea"){
		ENTER();
		stats();
	}else if(currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::A(){
		cout << "funcion A currentToken " << currentToken << endl;
	if(currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		stat();
		A();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::B(){
		cout << "funcion B currentToken " << currentToken << endl;
	if(currentTokenType == "token_salto_linea"){
		ENTER();
		B();
	}else if(currentTokenType == "token_llave_der" || currentTokenType == "end"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stat(){
		cout << "funcion stat currentToken " << currentToken << endl;
	if(currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde"){
		simple_stat();
	}else if(currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		compound_stat();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::compound_stat(){
		cout << "funcion compound_stat currentToken " << currentToken << endl;
	if(currentTokenType == "if"){
		if_stat();
	}else if(currentTokenType == "while"){
		while_stat();
	}else if(currentTokenType == "for"){
		for_stat();
	}else if(currentTokenType == "funcion"){
		funcion();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::simple_stat(){
		cout << "funcion simple_stat currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		assignment();
	}else if(currentTokenType == "log"){
		log();
	}else if(currentTokenType == "leer"){
		leer();
	}else if(currentTokenType == "importar" || currentTokenType == "desde"){
		importar();
	}else if(currentTokenType == "retorno"){
		retornar();
	}else if(currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		atom();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::assignment(){
		cout << "funcion assignment currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		variable();
		match("token_assign");
		assignment1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::assignment1(){
		cout << "funcion assignment1 currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		assignment();
	}else if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		expr();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::if_stat(){
		cout << "funcion if_stat currentToken " << currentToken << endl;
	if(currentTokenType == "if"){
		match("if");
		match("token_par_izq");
		condition_block();
		match("token_par_der");
		C();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::C(){
		cout << "funcion C currentToken " << currentToken << endl;
	if(currentTokenType == "else"){
		match("else");
		stat_block();
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::while_stat(){
		cout << "funcion while_stat currentToken " << currentToken << endl;
	if(currentTokenType == "while"){
		match("while");
		match("token_par_izq");
		expr();
		match("token_par_der");
		stat_block();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::for_stat(){
		cout << "funcion for_stat currentToken " << currentToken << endl;
	if(currentTokenType == "for"){
		match("for");
		match("id");
		match("in");
		expr();
		stat_block();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::log(){
		cout << "funcion log currentToken " << currentToken << endl;
	if(currentTokenType == "log"){
		match("log");
		match("token_par_izq");
		expr();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::leer(){
		cout << "funcion leer currentToken " << currentToken << endl;
	if(currentTokenType == "leer"){
		match("leer");
		match("token_par_izq");
		variable();
		match("token_par_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::funcion(){
		cout << "funcion funcion currentToken " << currentToken << endl;
	if(currentTokenType == "funcion"){
		match("funcion");
		match("id");
		match("token_par_izq");
		E();
		match("token_par_der");
		Z();
		match("end");
		match("funcion");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::Z(){
		cout << "funcion Z currentToken " << currentToken << endl;
	if(currentTokenType == "token_salto_linea"){
		B();
	}else if(currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		A();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::E(){
		cout << "funcion E currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		parametro();
		F();
	}else if(currentTokenType == "token_par_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::F(){
		cout << "funcion F currentToken " << currentToken << endl;
	if(currentTokenType == "token_coma"){
		match("token_coma");
		parametro();
		F();
	}else if(currentTokenType == "token_par_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::importar(){
		cout << "funcion importar currentToken " << currentToken << endl;
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
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::K(){
		cout << "funcion K currentToken " << currentToken << endl;
	if(currentTokenType == "token_point"){
		match("token_point");
		match("id");
		K();
	}else if(currentTokenType == "token_par_izq" || currentTokenType == "token_par_der" || currentTokenType == "token_assign" || currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_coma" || currentTokenType == "token_cor_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::retornar(){
		cout << "funcion retornar currentToken " << currentToken << endl;
	if(currentTokenType == "retorno"){
		match("retorno");
		match("token_par_izq");
		expr();
		match("token_par_der");
		ENTER();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::condition_block(){
		cout << "funcion condition_block currentToken " << currentToken << endl;
	if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		expr();
		condition_block1();
		stat_block();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::condition_block1(){
		cout << "funcion condition_block1 currentToken " << currentToken << endl;
	if(currentTokenType == "token_salto_linea"){
		ENTER();
	}else if(currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::stat_block(){
		cout << "funcion stat_block currentToken " << currentToken << endl;
	if(currentTokenType == "token_llave_izq"){
		match("token_llave_izq");
		Z();
		match("token_llave_der");
	}else if(currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion"){
		stat();
		ENTER();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::array(){
		cout << "funcion array currentToken " << currentToken << endl;
	if(currentTokenType == "token_cor_izq"){
		match("token_cor_izq");
		G();
		match("token_cor_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::objeto(){
		cout << "funcion objeto currentToken " << currentToken << endl;
	if(currentTokenType == "token_llave_izq"){
		match("token_llave_izq");
		L();
		match("token_llave_der");
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::L(){
		cout << "funcion L currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		Keyvalue();
		M();
	}else if(currentTokenType == "token_llave_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::M(){
		cout << "funcion M currentToken " << currentToken << endl;
	if(currentTokenType == "token_coma"){
		match("token_coma");
		Keyvalue();
		M();
	}else if(currentTokenType == "token_llave_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::Keyvalue(){
		cout << "funcion Keyvalue currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		match("id");
		match("token_dosp");
		expr();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::G(){
		cout << "funcion G currentToken " << currentToken << endl;
	if(currentTokenType == "token_not" || currentTokenType == "token_par_izq" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "id"){
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::H(){
		cout << "funcion H currentToken " << currentToken << endl;
	if(currentTokenType == "token_coma"){
		match("token_coma");
		expr();
		H();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_cor_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::variable(){
		cout << "funcion variable currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		match("id");
		K();
		variable1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::variable1(){
		cout << "funcion variable1 currentToken " << currentToken << endl;
	if(currentTokenType == "token_par_izq"){
		J();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::J(){
		cout << "funcion J currentToken " << currentToken << endl;
	if(currentTokenType == "token_par_izq"){
		match("token_par_izq");
		G();
		match("token_par_der");
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_assign" || currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parametro(){
		cout << "funcion parametro currentToken " << currentToken << endl;
	if(currentTokenType == "id"){
		match("id");
		parametro1();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::parametro1(){
		cout << "funcion parametro1 currentToken " << currentToken << endl;
	if(currentTokenType == "token_assign"){
		match("token_assign");
		expr();
	}else if(currentTokenType == "token_coma" || currentTokenType == "token_par_der"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::expr(){
		cout << "funcion expr currentToken " << currentToken << endl;
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
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::op(){
		cout << "funcion op currentToken " << currentToken << endl;
	if(currentTokenType == "token_pot" || currentTokenType == "token_mul" || currentTokenType == "token_div" || currentTokenType == "token_mod" || currentTokenType == "token_mas" || currentTokenType == "token_menos" || currentTokenType == "token_menor_igual" || currentTokenType == "token_mayor_igual" || currentTokenType == "token_menor" || currentTokenType == "token_mayor" || currentTokenType == "token_igual_num" || currentTokenType == "token_diff_num" || currentTokenType == "token_and" || currentTokenType == "token_or"){
		N();
		expr();
	}else if(currentTokenType == "token_par_der" || currentTokenType == "token_coma" || currentTokenType == "token_llave_izq" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_salto_linea" || currentTokenType == "token_cor_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::N(){
		cout << "funcion N currentToken " << currentToken << endl;
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
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::atom(){
		cout << "funcion atom currentToken " << currentToken << endl;
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
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::ENTER(){
		cout << "funcion ENTER currentToken " << currentToken << endl;
	if(currentTokenType == "token_salto_linea"){
		match("token_salto_linea");
		NEWLINE();
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
void Syntactic::NEWLINE(){
		cout << "funcion NEWLINE currentToken " << currentToken << endl;
	if(currentTokenType == "token_salto_linea"){
		ENTER();
	}else if(currentTokenType == "token_salto_linea" || currentTokenType == "id" || currentTokenType == "leer" || currentTokenType == "retorno" || currentTokenType == "log" || currentTokenType == "token_integer" || currentTokenType == "token_float" || currentTokenType == "true" || currentTokenType == "false" || currentTokenType == "token_string" || currentTokenType == "nil" || currentTokenType == "token_cor_izq" || currentTokenType == "token_llave_izq" || currentTokenType == "importar" || currentTokenType == "desde" || currentTokenType == "if" || currentTokenType == "for" || currentTokenType == "while" || currentTokenType == "funcion" || currentTokenType == "token_par_der" || currentTokenType == "token_llave_der" || currentTokenType == "end" || currentTokenType == "NULL"){
	}else{
		string array[] = {};
		syntacticError(array);
	}
}
