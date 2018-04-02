/* Statements */

program					:		n statements2 n

statements			:		n '{' n statements2 n '}' enter | enter statement enter
statements2 		:		statement statements3 | 'epsilon'
statements3			:		enter statements2 | 'epsilon'
statement				:		element | routine

element					:		element2 | assignment
element1				:		number | boolean | 'id' | negation | functioncall | genoperation
element2				:		element1 | 'token_string' | array | espoperation | 'nil'

routine					:		_if | _while | _for | function | log | leer | importar

/* Operations */

genoperation		:		genoperation1 | '(' genoperation1 ')'
genoperation1	  :		element1 genoperator element1 | element2 fulloperator element2
fulloperator    :   '==' | '!=' | '&&' | ' || '
genoperator		  :		'+' | '-' | '*' | '/' | '^' | '<' | '>' | '>=' | '<='

espoperation		:		espoperator espoperation1 | '(' espoperator espoperation1 ')'
espoperation1	  :		'+' espoperation2 | '*' element1
espoperation2	  :		espoperator | 'id'
espoperator		  :		'token_string' | array

/* If, for and While */

_for						:		'for' 'id' 'in' forparam statements
forparam				:		espoperator | espoperation | 'id' | functioncall
_while					:		'while' condition statements
_if							:		'if' condition statements _else
_else						:		'else' statements | 'epsilon'
condition				:		element2 | '(' condition1 ')'
condition1			:		condition | 'epsilon'

/* log, leer and importar */

log							:		'log' '(' element2 ')'
leer						:		'leer' '(' 'id' ')'
importar				: 	'importar' importar1 | 'desde' importar1 'importar' 'id'
importar1				:  	'id' importar2
importar2				:  	'.' importar1 | 'epsilon'

/* Function and Function_call */

functioncall		:		'id' '(' cparameters ')'
cparameters		  :		cparameters1 | 'epsilon'
cparameters1		:		element2 cparameters2
cparameters2		:		',' cparameters1 | 'epsilon'

function				:		'funcion' 'id' '(' parameters ')' functionstm 'end' 'funcion'
parameters			:		parameters1 | 'epsilon'
parameters1			:		'id' parameters2
parameters2			:		',' parameters1 | 'epsilon'

functionstm		  :		enter statements2 functionstm1
functionstm1		:		'retorno' returnstm enter functionstm | 'epsilon'
returnstm			  :		element2 | 'epsilon'

/* Terminal Symbols and Tokens */

negation				:		'!' element1
assignment			:		'id' '=' element2
array						:		'[' array2 ']'
array2					:		element2 array3
array3					:		',' array2 | 'epsilon'

number  				:		'token_integer' | 'token_float'
boolean					:		'true' | 'false'

enter						:		'/n' n
n								:		enter | 'epsilon'
