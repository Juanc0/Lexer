from_input : stat '\n'
A : stat A | EPSILON
B : '\n' B | EPSILON
stat : simple_stat | compound_stat
compound_stat : if_stat | while_stat | for_stat | funcion
simple_stat : assignment | log | importar | retornar | atom '\n'
assignment : variable '=' assignment1
assignment1 : assignment | expr
if_stat : 'if' condition_block C
C : 'else' stat_block | EPSILON
while_stat : 'while' expr stat_block
for_stat : 'for' 'id' 'in' expr stat_block
log : 'log' '(' expr ')'
funcion : 'funcion' 'id' '(' E ')' Z 'end' 'funcion'
Z : B | A
E : parametro F | EPSILON
F : ',' parametro F | EPSILON
importar : 'importar' 'id' K| 'desde' 'id' 'importar' 'id'
K : '.' 'id' K | EPSILON
retornar : 'retorno' '(' expr ')' '\n'
condition_block : expr condition_block1 stat_block
condition_block1 : '\n' | EPSILON
stat_block : '{' Z '}' | stat '\n'
array : '[' G ']'
G : expr H | EPSILON
H : ',' expr H | EPSILON
variable : 'id' K variable1
variable1 : J | EPSILON
J : '(' G ')' | EPSILON
parametro : 'id' parametro1
parametro1 : '=' expr | EPSILON
expr : N expr | '!' expr | '(' expr ')' | atom
N : '^' | '*' | '/' | '%' | '+' | '-' | '<=' | '>=' | '<' | '>' | '==' | '!=' | '&&' | '||'
atom : 'token_integer' | 'token_float' | 'true' | 'false' | 'token_string' | array | variable | 'nil'
L : Keyvalue M | EPSILON
M : ',' keyvalue M | EPSILON
Keyvalue : 'id' POINTS expr
