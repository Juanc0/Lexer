/* Statements */
program					:		n statement2 n | 'epsilon'

statements			:		n '{' n statment2 n '}' enter | enter statement enter
statements2 		:		statement statements3 | 'epsilon'
statements3			:		enter statements2 | 'epsilon'
statement				:		element | routine

element					:		element2 | assignment
element1				:		number | boolean | identifier | negation | function_call | gen_operation
element2				:		element1 | string | array | esp_operation | 'nil'

routine					:		if | while | for | function | log | leer | importar

/* Operations */

gen_operation		:		gen_operation1 | '(' gen_operation1 ')'
gen_operation1	:		element1 gen_operator element1 | element '==' element | element '!=' element | element '&&' element | element '||' element
gen_operator		:		'+' | '-' | '*' | '/' | '^' | '<' | '>' | '>=' | '<='

esp_operation		:		esp_operator esp_operation1 | '(' esp_operator esp_operation1 ')'
esp_operation1	:		'+' esp_operation2 | '*' element1
esp_operation2	:		esp_operator | identifier
esp_operator		:		string | array

/* If, for and While */

for							:		'for' identifier 'in' for_param statements
for_param				:		esp_operator | esp_operation | identifier | function_call
while						:		'while' condition statements
if							:		'if' condition statements else
else						:		'else' statements | 'epsilon'
condition				:		element2 | '(' ')'
condition1			:		'(' condition ')' | 'epsilon'

/* log, leer and importar */

log							:		log '(' element2 ')'
leer						:		leer '(' identifier ')'
importar				: 	'importar' importar1 | 'desde' importar1 'importar' identifier
importar1				: 	identifier importar2
importar2				: 	'.' importar1 | 'epsilon'

/* Function and Function_call */

function_call		:		identifier '(' c_parameters ')'
c_parameters		:		c_parameters1 | 'epsilon'
c_parameters1		:		element c_parameters2
c_parameters2		:		',' c_parameters1 | 'epsilon'

function				:		'funcion' identifier '(' parameters ')' function_stm 'end' 'funcion'
parameters			:		parameters1 | 'epsilon'
parameters1			:		identifier parameters2
parameters2			:		',' parameters1 | 'epsilon'

function_stm		:		enter statements2 function_stm1
function_stm1		:		'retorno' return_stm enter function_stm | 'epsilon'
return_stm			:		element2 | 'epsilon'

/* Terminal Symbols and Tokens */

negation				:		'!' element1
assignment			:		identifier '=' element2
array						:		[ array2 ]
array2					:		element2 array3
array3					:		',' array2 | 'epsilon'

number					:		token_integer | token_float
string 					:		token_string
boolean					:		'true' | 'false'

enter						:		'\n' n
n								:		enter | 'epsilon'
