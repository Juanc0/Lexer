from_input : stat '\n'	'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion'
;
A : stat A	'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion'
| EPSILON	'}', 'end'
;
B : '\n' B	'\\n'
| EPSILON	'}', 'end'
;
stat : simple_stat	'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno'
| compound_stat	'if', 'for', 'while', 'funcion'
;
compound_stat : if_stat	'if'
| while_stat	'while'
| for_stat	'for'
| funcion	'funcion'
;
simple_stat : assignment	'id'
| log	'log'
| importar	'importar', 'desde'
| retornar	'retorno'
| atom '\n'	'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'id'
;
assignment : variable '=' assignment1	'id'
;
assignment1 : assignment	'id'
| expr	'!', '(', '^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'id'
;
if_stat : 'if' condition_block C	'if'
;
C : 'else' stat_block	'else'
| EPSILON	'\\n', 'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion', '}', 'end'
;
while_stat : 'while' expr stat_block	'while'
;
for_stat : 'for' 'id' 'in' expr stat_block	'for'
;
log : 'log' '(' expr ')'	'log'
;
funcion : 'funcion' 'id' '(' E ')' Z 'end' 'funcion'	'funcion'
;
Z : B	'\\n'
| A	'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion'
;
parametro : 'id' parametro1	'id'
;
parametro1 : '=' expr	'='
| EPSILON	',', ')'
;
E : parametro F	'id'
| EPSILON	')'
;
F : ',' parametro F	','
| EPSILON	')'
;
importar : 'importar' 'id' K	'importar'
| 'desde' 'id' 'importar' 'id'	'desde'
;
K : '.' 'id' K	'.'
| EPSILON	'(', '=', '\\n', 'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion', '}', 'end', ')', ',', '{', ''
;
retornar : 'retorno' '(' expr ')' '\n'	'retorno'
;
condition_block : expr condition_block1 stat_block	'!', '(', '^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'id'
| '\n'	'\\n'
| EPSILON	'{', 'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion'
;
stat_block : '{' Z '}'	'{'
| stat '\n'	'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion'
;
array : '[' G ']'	''
;
G : expr H	'!', '(', '^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'id'
| EPSILON	')', ''
;
H : ',' expr H	','
| EPSILON	')', ''
;
variable : 'id' K variable1	'id'
;
variable1 : J	'('
| EPSILON	'=', '\\n', ')', ',', '{', 'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion', '', '}', 'end'
;
J : '(' G ')'	'('
| EPSILON	'=', '\\n', ')', ',', '{', 'id', 'importar', 'desde', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'retorno', 'if', 'for', 'while', 'funcion', '', '}', 'end'
;
expr : N expr	'^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&'
| '!' expr	'!'
| '(' expr ')'	'('
| atom	'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '', 'id'
;
N : '^'	'^'
| '*'	'*'
| '/'	'/'
| '%'	'%'
| '+'	'+'
| '-'	'-'
| '<='	'<='
| '>='	'>='
| '<'	'<'
| '>'	'>'
| '=='	'=='
| '!='	'!='
| '&&'	'&&'
;
atom : 'token_integer'	'token_integer'
| 'token_float'	'token_float'
| 'true'	'true'
| 'false'	'false'
| 'token_string'	'token_string'
| array	''
| variable	'id'
| 'nil'	'nil'
;
L : Keyvalue M	'id'
| EPSILON
;
M : ',' keyvalue M	','
| EPSILON
;
Keyvalue : 'id' POINTS expr	'id'
;
