1	program : stats	'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion'
2	program : EPSILON	'NULL'
3	stats : stat stats1	'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion'
4	stats : EPSILON	'NULL'
5	stats1 : ENTER stats	'token_salto_linea'
6	stats1 : EPSILON	'NULL'
7	A : stat A	'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion'
8	A : EPSILON	'}', 'end'
9	B : ENTER B	'token_salto_linea'
10	B : EPSILON	'}', 'end'
11	stat : simple_stat	'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde'
12	stat : compound_stat	'if', 'for', 'while', 'funcion'
13	compound_stat : if_stat	'if'
14	compound_stat : while_stat	'while'
15	compound_stat : for_stat	'for'
16	compound_stat : funcion	'funcion'
17	simple_stat : assignment	'id'
18	simple_stat : log	'log'
19	simple_stat : leer	'leer'
20	simple_stat : importar	'importar', 'desde'
21	simple_stat : retornar	'retorno'
22	simple_stat : atom	'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'id'
23	assignment : variable '=' assignment1	'id'
24	assignment1 : assignment	'id'
25	assignment1 : expr	'!', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'id'
26	if_stat : 'if' '(' condition_block ')' C	'if'
27	C : 'else' stat_block	'else'
28	C : EPSILON	'token_salto_linea', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion', '}', 'end', 'NULL'
29	while_stat : 'while' '(' expr ')' stat_block	'while'
30	for_stat : 'for' 'id' 'in' expr stat_block	'for'
31	log : 'log' '(' expr ')'	'log'
32	leer : 'leer' '(' variable ')'	'leer'
33	funcion : 'funcion' 'id' '(' E ')' Z 'end' 'funcion'	'funcion'
34	Z : B	'token_salto_linea'
35	Z : A	'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion'
36	E : parametro F	'id'
37	E : EPSILON	')'
38	F : ',' parametro F	','
39	F : EPSILON	')'
40	importar : 'importar' 'id' K	'importar'
41	importar : 'desde' 'id' 'importar' 'id'	'desde'
42	K : '.' 'id' K	'.'
43	K : EPSILON	'(', ')', '=', 'token_salto_linea', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion', '}', 'end', 'NULL', '^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', '||', ',', ']'
44	retornar : 'retorno' '(' expr ')' ENTER	'retorno'
45	condition_block : expr condition_block1 stat_block	'!', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'id'
46	condition_block1 : ENTER	'token_salto_linea'
47	condition_block1 : EPSILON	'{', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', 'importar', 'desde', 'if', 'for', 'while', 'funcion'
48	stat_block : '{' Z '}'	'{'
49	stat_block : stat ENTER	'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion'
50	array : '[' G ']'	'['
51	objeto : '{' L '}'	'{'
52	L : Keyvalue M	'id'
53	L : EPSILON	'}'
54	M : ',' Keyvalue M	','
55	M : EPSILON	'}'
56	Keyvalue : 'id' ':' expr	'id'
57	G : expr H	'!', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'id'
58	G : EPSILON	')', ']'
59	H : ',' expr H	','
60	H : EPSILON	')', ']'
61	variable : 'id' K variable1	'id'
62	variable1 : J	'('
63	variable1 : EPSILON	')', '=', '^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', '||', ',', '{', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', 'importar', 'desde', 'if', 'for', 'while', 'funcion', 'token_salto_linea', ']', '}', 'end', 'NULL'
64	J : '(' G ')'	'('
65	J : EPSILON	')', '=', '^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', '||', ',', '{', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', 'importar', 'desde', 'if', 'for', 'while', 'funcion', 'token_salto_linea', ']', '}', 'end', 'NULL'
66	parametro : 'id' parametro1	'id'
67	parametro1 : '=' expr	'='
68	parametro1 : EPSILON	',', ')'
69	expr : '!' expr	'!'
70	expr : '(' expr ')'	'('
71	expr : atom op	'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'id'
72	op : N expr	'^', '*', '/', '%', '+', '-', '<=', '>=', '<', '>', '==', '!=', '&&', '||'
73	op : EPSILON	')', ',', '{', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', 'importar', 'desde', 'if', 'for', 'while', 'funcion', 'token_salto_linea', ']', '}', 'end', 'NULL'
74	N : '^'	'^'
75	N : '*'	'*'
76	N : '/'	'/'
77	N : '%'	'%'
78	N : '+'	'+'
79	N : '-'	'-'
80	N : '<='	'<='
81	N : '>='	'>='
82	N : '<'	'<'
83	N : '>'	'>'
84	N : '=='	'=='
85	N : '!='	'!='
86	N : '&&'	'&&'
87	N : '||'	'||'
88	atom : 'token_integer'	'token_integer'
89	atom : 'token_float'	'token_float'
90	atom : 'true'	'true'
91	atom : 'false'	'false'
92	atom : 'token_string'	'token_string'
93	atom : array	'['
94	atom : variable	'id'
95	atom : 'nil'	'nil'
96	atom : objeto	'{'
97	ENTER : 'token_salto_linea' NEWLINE	'token_salto_linea'
98	NEWLINE : ENTER	'token_salto_linea'
99	NEWLINE : EPSILON	'token_salto_linea', 'id', 'leer', 'retorno', 'log', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', '[', '{', 'importar', 'desde', 'if', 'for', 'while', 'funcion', ')', '}', 'end', 'NULL'
