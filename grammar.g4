program				:

/* Statements */

statements			:		statement '\n' | '{' '}' | '{' statement '\n' statements2 '}'
statements2 		:		statement '\n' statements2 | epsilon
statement				:		element | routine

element					:		element2 | assignment
element1				:		number | boolean | identifier | negation | function_call | gen_operation
element2				:		element1 | string | array | esp_operation

routine					:		if | while | for | function | log | leer | importar

/* If and While */

while						:		'while' condition statements
if							:		'if' condition statements else
else						:		'else' statements | epsilon
condition				:		operation | '(' ')'

/* Operations */

gen_operation		:		gen_operation1 | '(' gen_operation1 ')'
gen_operation1	:		element1 gen_operator element1 | element '==' element
gen_operator		:		'+' | '-' | '*' | '/' | '^' | '&&' | '||' | '<' | '>' | '>=' | '<='

esp_operation		:		esp_operator esp_operation1 | '(' esp_operator esp_operation1 ')'
esp_operation1	:		'+' esp_operation2 | '*' element1
esp_operation2	:		esp_operator | identifier
esp_operator		:		string | array

/* Function and Function_call */

function_call		:		identifier '(' c_parameters ')'
c_parameters		:		c_parameters1 | epsilon
c_parameters1		:		element c_parameters2
c_parameters2		:		',' c_parameters1 | epsilon

function				:		'funcion' identifier '(' parameters ')' function_stm 'end funcion'
parameters			:		parameters1 | epsilon
parameters1			:		identifier parameters2
parameters2			:		',' parameters1 | epsilon

function_stm		:		statements function_stm1
function_stm1		:		epsilon | 'retorno' return_stm '\n' function_stm
return_stm			:		element2 | epsilon

/* For */

for							:		'for' identifier 'in' element2 statements

/* Terminal Symbols and Tokens */

negation				:		'!' element1
assignment			:		identifier '=' element2
array						:		'[' array2 ']'
array2					:		element2 array3
array3					:		',' array2 | epsilon

number					:		token_integer | token_float
boolean					:		'true' | 'false'
