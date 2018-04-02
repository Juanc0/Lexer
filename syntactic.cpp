class Syntactic{
	public:
		Lexer* lexer;
		static Token currentToken;
		static string currentTokenType;
		Syntactic();
		~Syntactic();
};
Syntactic::Syntactic(bool useFile, string str){
	lexer = new Lexer(useFile, str);
}
Syntactic::~Syntactic(bool useFile, string str){
	delete lexer;
}
void program(){
	if(currentTokenType == n || currentTokenType == statement2 || currentTokenType == n){
		gatito
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void statements(){
	if(currentTokenType == n || currentTokenType == '{' || currentTokenType == n || currentTokenType == statment2 || currentTokenType == n || currentTokenType == '}' || currentTokenType == enter){
		gatito
		gatito
		gatito
		gatito
		gatito
		gatito
		gatito
	}	else if(currentTokenType == enter || currentTokenType == statement || currentTokenType == enter){
		gatito
		gatito
		gatito
	}
}
void statements2 (){
	if(currentTokenType == statement || currentTokenType == statements3){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void statements3(){
	if(currentTokenType == enter || currentTokenType == statements2){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void statement(){
	if(currentTokenType == element){
		gatito
	}	else if(currentTokenType == routine){
		gatito
	}
}
void element(){
	if(currentTokenType == element2){
		gatito
	}	else if(currentTokenType == assignment){
		gatito
	}
}
void element1(){
	if(currentTokenType == number){
		gatito
	}	else if(currentTokenType == boolean){
		gatito
	}	else if(currentTokenType == identifier){
		gatito
	}	else if(currentTokenType == negation){
		gatito
	}	else if(currentTokenType == function_call){
		gatito
	}	else if(currentTokenType == gen_operation){
		gatito
	}
}
void element2(){
	if(currentTokenType == element1){
		gatito
	}	else if(currentTokenType == string){
		gatito
	}	else if(currentTokenType == array){
		gatito
	}	else if(currentTokenType == esp_operation){
		gatito
	}	else if(currentTokenType == 'nil'){
		gatito
	}
}
void routine(){
	if(currentTokenType == if){
		gatito
	}	else if(currentTokenType == while){
		gatito
	}	else if(currentTokenType == for){
		gatito
	}	else if(currentTokenType == function){
		gatito
	}	else if(currentTokenType == log){
		gatito
	}	else if(currentTokenType == leer){
		gatito
	}	else if(currentTokenType == importar){
		gatito
	}
}
void gen_operation(){
	if(currentTokenType == gen_operation1){
		gatito
	}	else if(currentTokenType == '(' || currentTokenType == gen_operation1 || currentTokenType == ')'){
		gatito
		gatito
		gatito
	}
}
void gen_operation1(){
	if(currentTokenType == element1 || currentTokenType == gen_operator || currentTokenType == element1){
		gatito
		gatito
		gatito
	}	else if(currentTokenType == element || currentTokenType == '==' || currentTokenType == element){
		gatito
		gatito
		gatito
	}	else if(currentTokenType == element || currentTokenType == '!=' || currentTokenType == element){
		gatito
		gatito
		gatito
	}	else if(currentTokenType == element || currentTokenType == '&&' || currentTokenType == element){
		gatito
		gatito
		gatito
	}	else if(currentTokenType == element || currentTokenType == '||' || currentTokenType == element){
		gatito
		gatito
		gatito
	}
}
void gen_operator(){
	if(currentTokenType == '+'){
		gatito
	}	else if(currentTokenType == '-'){
		gatito
	}	else if(currentTokenType == '*'){
		gatito
	}	else if(currentTokenType == '/'){
		gatito
	}	else if(currentTokenType == '^'){
		gatito
	}	else if(currentTokenType == '<'){
		gatito
	}	else if(currentTokenType == '>'){
		gatito
	}	else if(currentTokenType == '>='){
		gatito
	}	else if(currentTokenType == '<='){
		gatito
	}
}
void esp_operation(){
	if(currentTokenType == esp_operator || currentTokenType == esp_operation1){
		gatito
		gatito
	}	else if(currentTokenType == '(' || currentTokenType == esp_operator || currentTokenType == esp_operation1 || currentTokenType == ')'){
		gatito
		gatito
		gatito
		gatito
	}
}
void esp_operation1(){
	if(currentTokenType == '+' || currentTokenType == esp_operation2){
		gatito
		gatito
	}	else if(currentTokenType == '*' || currentTokenType == element1){
		gatito
		gatito
	}
}
void esp_operation2(){
	if(currentTokenType == esp_operator){
		gatito
	}	else if(currentTokenType == identifier){
		gatito
	}
}
void esp_operator(){
	if(currentTokenType == string){
		gatito
	}	else if(currentTokenType == array){
		gatito
	}
}
void for(){
	if(currentTokenType == 'for' || currentTokenType == identifier || currentTokenType == 'in' || currentTokenType == for_param || currentTokenType == statements){
		gatito
		gatito
		gatito
		gatito
		gatito
	}
}
void for_param(){
	if(currentTokenType == esp_operator){
		gatito
	}	else if(currentTokenType == esp_operation){
		gatito
	}	else if(currentTokenType == identifier){
		gatito
	}	else if(currentTokenType == function_call){
		gatito
	}
}
void while(){
	if(currentTokenType == 'while' || currentTokenType == condition || currentTokenType == statements){
		gatito
		gatito
		gatito
	}
}
void if(){
	if(currentTokenType == 'if' || currentTokenType == condition || currentTokenType == statements || currentTokenType == else){
		gatito
		gatito
		gatito
		gatito
	}
}
void else(){
	if(currentTokenType == 'else' || currentTokenType == statements){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void condition(){
	if(currentTokenType == element2){
		gatito
	}	else if(currentTokenType == '(' || currentTokenType == ')'){
		gatito
		gatito
	}
}
void condition1(){
	if(currentTokenType == '(' || currentTokenType == condition || currentTokenType == ')'){
		gatito
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void log(){
	if(currentTokenType == log || currentTokenType == '(' || currentTokenType == element2 || currentTokenType == ')'){
		gatito
		gatito
		gatito
		gatito
	}
}
void leer(){
	if(currentTokenType == leer || currentTokenType == '(' || currentTokenType == identifier || currentTokenType == ')'){
		gatito
		gatito
		gatito
		gatito
	}
}
void importar(){
	if(currentTokenType == 'importar' || currentTokenType == importar1){
		gatito
		gatito
	}	else if(currentTokenType == 'desde' || currentTokenType == importar1 || currentTokenType == 'importar' || currentTokenType == identifier){
		gatito
		gatito
		gatito
		gatito
	}
}
void importar1(){
	if(currentTokenType == identifier || currentTokenType == importar2){
		gatito
		gatito
	}
}
void importar2(){
	if(currentTokenType == '.' || currentTokenType == importar1){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void function_call(){
	if(currentTokenType == identifier || currentTokenType == '(' || currentTokenType == c_parameters || currentTokenType == ')'){
		gatito
		gatito
		gatito
		gatito
	}
}
void c_parameters(){
	if(currentTokenType == c_parameters1){
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void c_parameters1(){
	if(currentTokenType == element || currentTokenType == c_parameters2){
		gatito
		gatito
	}
}
void c_parameters2(){
	if(currentTokenType == ',' || currentTokenType == c_parameters1){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void function(){
	if(currentTokenType == 'funcion' || currentTokenType == identifier || currentTokenType == '(' || currentTokenType == parameters || currentTokenType == ')' || currentTokenType == function_stm || currentTokenType == 'end' || currentTokenType == 'funcion'){
		gatito
		gatito
		gatito
		gatito
		gatito
		gatito
		gatito
		gatito
	}
}
void parameters(){
	if(currentTokenType == parameters1){
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void parameters1(){
	if(currentTokenType == identifier || currentTokenType == parameters2){
		gatito
		gatito
	}
}
void parameters2(){
	if(currentTokenType == ',' || currentTokenType == parameters1){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void function_stm(){
	if(currentTokenType == enter || currentTokenType == statements2 || currentTokenType == function_stm1){
		gatito
		gatito
		gatito
	}
}
void function_stm1(){
	if(currentTokenType == 'retorno' || currentTokenType == return_stm || currentTokenType == enter || currentTokenType == function_stm){
		gatito
		gatito
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void return_stm(){
	if(currentTokenType == element2){
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void negation(){
	if(currentTokenType == '!' || currentTokenType == element1){
		gatito
		gatito
	}
}
void assignment(){
	if(currentTokenType == identifier || currentTokenType == '=' || currentTokenType == element2){
		gatito
		gatito
		gatito
	}
}
void array(){
	if(currentTokenType == token_cor_izq || currentTokenType == array2 || currentTokenType == token_cor_der){
		gatito
		gatito
		gatito
	}
}
void array2(){
	if(currentTokenType == element2 || currentTokenType == array3){
		gatito
		gatito
	}
}
void array3(){
	if(currentTokenType == ',' || currentTokenType == array2){
		gatito
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
void number(){
	if(currentTokenType == token_integer){
		gatito
	}	else if(currentTokenType == token_float){
		gatito
	}
}
void string (){
	if(currentTokenType == token_string){
		gatito
	}
}
void boolean(){
	if(currentTokenType == 'true'){
		gatito
	}	else if(currentTokenType == 'false'){
		gatito
	}
}
void enter(){
	if(currentTokenType == '\n' || currentTokenType == n){
		gatito
		gatito
	}
}
void n(){
	if(currentTokenType == enter){
		gatito
	}	else if(currentTokenType == 'epsilon'){
		gatito
	}
}
