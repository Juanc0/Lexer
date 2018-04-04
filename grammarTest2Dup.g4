from_input : stat NEWLINE
;
A : stat A
| EPSILON
;
B : NEWLINE B
| EPSILON
;
stat : simple_stat
| compound_stat
;
compound_stat : if_stat
| while_stat
| for_stat
| funcion
;
simple_stat : assignment
| log
| IMPORTAR
| retornar
| atom NEWLINE
assignment : variable ASSIGN assignment1
assignment1 : assignment
| expr
;
if_stat : IF condition_block C
;
C : ELSE stat_block
| EPSILON
while_stat : WHILE expr stat_block
;
for_stat : FOR ID IN expr stat_block
;
log : LOG OPAR expr CPAR
;
funcion : FUNCION ID OPAR E CPAR Z END
;
Z : B
| A
;
E : parametro F  EPSILON
;
F : COMMA parametro F \n
| dsf EPSILON
;
IMPORTAR : IMPORT ID K
| FROM ID IMPORT ID
;
K : POINT ID K
| EPSILON
;
retornar : RETORNO OPAR expr CPAR NEWLINE
;
condition_block : expr condition_block1 stat_block
;
condition_block1 : NEWLINE
| EPSILON
;
stat_block : OBRACE Z CBRACE
| stat NEWLINE
;
array : OKEY G CKEY
;
G : expr H
| EPSILON
;
H : COMMA expr H
| EPSILON
;
variable : ID K variable1
;
variable1 : J
| EPSILON
;
J : OPAR G CPAR
| EPSILON
;
parametro : ID parametro1
;
parametro1 : ASSIGN expr
| EPSILON
;
expr : N expr
| NOT expr
| OPAR expr CPAR
| atom
;
N : POW
| MULT
| DIV
| MOD
| PLUS
| MINUS
| LTEQ
| GTEQ
| LT
| GT
| EQ
| NEQ
| AND
| OR
;
atom : INT
| FLOAT
| TRUE
| FALSE
| STRING
| array
| variable
| NIL
;
L : Keyvalue M
| EPSILON
;
M : COMMA keyvalue M
| EPSILON
;
Keyvalue : ID POINTS expr
;

OR : '||'
;
AND : '&&'
;
EQ : '=='
;
NEQ : '!='
;
GT : '>'
;
LT : '<'
;
GTEQ : '>='
;
LTEQ : '<='
;
PLUS : '+'
;
MINUS : '-'
;
MULT : '*'
;
DIV : '/'
;
MOD : '%'
;
POW : '^'
;
NOT : '!'
;
ASSIGN : '='
;
OPAR : '('
;
CPAR : ')'
;
OBRACE : '{'
;
CBRACE : '}'
;
OKEY : '['
;
CKEY : ']'
;
COMMA : ','
;
POINTS : ':'
;

TRUE : 'true'
;
FALSE : 'false'
;
NIL : 'nil'
;
IF : 'if'
;
ELSE : 'else'
;
WHILE : 'while'
;
LOG : 'log'
;
FOR : 'for'
;
IN : 'in'
;
FUNCION : 'funcion'
;
END : 'end'
;
RETORNO : 'retorno'
;
IMPORT : 'importar'
;
FROM : 'desde'
;
POINT : '.'
;

ID : 'id'
;
INT : 'token_integer'
;
FLOAT : 'token_float'
;
STRING : 'token_string'
;
NEWLINE : '\n'
;
