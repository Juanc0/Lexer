program				:

/* Statements */

statements		:		statement newLineToken | '{' '}' | '{' statement newLine statements2 '}'
statements2 	:		statement newLineToken statements2 | epsilon
statement			:		element | routine

element				:		element3 | element2 | string_op | array
element1			:		number | boolean | identifier | negation | function_call | general_op
element2			:		assignment | incremental
element3			:		element1 | string | array

routine				:		if | while | for | function | log | leer | importar

/* If and While */

while					:		'while' condition statements
if						:		'if' condition statements else
else					:		'else' statements | epsilon
condition			:		operation | '(' ')'

/* Operations */

gen_operation		:		element1 gen_operator element1 | '(' element1 gen_operator element1 ')'
gen_operator			:		'+' | '-' | '*' | '/' | '^' | '&&' | '||' | '<' | '>' | '>=' | '<=' | '=='

esp_operation		:		esp_operator esp_operation1 | '(' esp_operator esp_operation1 ')'
esp_operation1	:		'+' esp_operation2 | '*' element1
esp_operation2	:		esp_operator | identifier
esp_operator		:		string | array

/* Function and Function_call */

function_call	:		identifier '(' parameters ')' | identifier '(' element2 ')'
function			:		'funcion' identifier '(' parameters ')' function_stm 'end funcion'
parameters		:		identifier parameters2 | epsilon
parameters2		:		',' parameters | epsilon
function_stm	:		statements | statements 'retorno' function_stm
return_stm		:

/* For */

for						:		'for' identifier 'in' array statements
array					:		identifier | '[' array2 ']' | function
array2				:		number array3
array3				:		',' array2 | epsilon

/* Terminal Symbols and Tokens */

incremental		:		identifier incremental2 | incremental2 identifier
incremental2	:		'++' | '--'
negation			:		'!' element1
assignment		:		identifier '=' element3

number				:		token_integer | token_float
boolean				:		'true' | 'false'
