1	program : stats	'token_salto_linea', 'log', 'importar', 'desde', 'leer', '!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id', 'funcion', 'for', 'while', 'if'
2	program : EPSILON	'$'
3	stats : B stat stats1	'token_salto_linea', 'log', 'importar', 'desde', 'leer', '!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id', 'funcion', 'for', 'while', 'if'
4	stats : EPSILON	'}', '$'
5	stats1 : 'token_salto_linea' stats	'token_salto_linea'
6	stats1 : EPSILON	'}', '$'
7	stat : simple_stat	'log', 'importar', 'desde', 'leer', '!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id'
8	stat : compound_stat	'funcion', 'for', 'while', 'if'
9	simple_stat : log	'log'
10	simple_stat : leer	'leer'
11	simple_stat : importar	'importar', 'desde'
12	simple_stat : expr	'!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id'
13	compound_stat : funcion	'funcion'
14	compound_stat : while_stat	'while'
15	compound_stat : for_stat	'for'
16	compound_stat : if_stat	'if'
17	log : 'log' '(' expr ')'	'log'
18	leer : 'leer' '(' variable ')'	'leer'
19	importar : 'importar' 'id' K	'importar'
20	importar : 'desde' 'id' 'importar' 'id'	'desde'
21	funcion : 'funcion' 'id' '(' parametros ')' funcion_stats 'end' 'funcion'	'funcion'
22	funcion_stats : B funcion_stat funcion_stats1	'token_salto_linea', 'log', 'importar', 'desde', 'leer', '!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id', 'funcion', 'for', 'while', 'if', 'retorno'
23	funcion_stats : EPSILON	'end'
24	funcion_stats1 : 'token_salto_linea' funcion_stats	'token_salto_linea'
25	funcion_stats1 : EPSILON	'end'
26	funcion_stat : stat	'log', 'importar', 'desde', 'leer', '!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id', 'funcion', 'for', 'while', 'if'
27	funcion_stat : retorno_block	'retorno'
28	retorno_block : 'retorno' '(' expr ')'	'retorno'
29	retorno_block : EPSILON	'token_salto_linea', 'end'
30	parametros : 'id' parametro	'id'
31	parametros : EPSILON	')'
32	parametro : ',' 'id' parametro	','
33	parametro : EPSILON	')'
34	while_stat : 'while' expr stat_block	'while'
35	for_stat : 'for' 'id' 'in' expr stat_block	'for'
36	if_stat : 'if' '(' expr ')' stat_block else_block	'if'
37	else_block : 'else' else_stats	'else'
38	else_block : EPSILON	'token_salto_linea', '}', '$', 'end'
39	else_stats : if_stat	'if'
40	else_stats : stat_block	'{', 'token_salto_linea'
41	stat_block : '{' stats '}'	'{'
42	stat_block : 'token_salto_linea' stat 'token_salto_linea'	'token_salto_linea'
43	B : 'token_salto_linea' B	'token_salto_linea'
44	B : EPSILON	'token_salto_linea', 'log', 'importar', 'desde', 'leer', '!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id', 'funcion', 'for', 'while', 'if', 'retorno', 'end'
45	variable : 'id' K J	'id'
46	array : 'OKEY' G 'CKEY'	'OKEY'
47	objeto : '{' L '}'	'{'
48	Keyvalue : 'id' ':' expr	'id'
49	K : '.' 'id' K	'.'
50	K : EPSILON	'(', 'OKEY', ')', '^', '*', '/', '%', '+', '-', '=', '<=', '>=', '<', '>', '==', '!=', '&&', 'OR', 'token_salto_linea', '}', '$', ',', '{', 'CKEY', 'end'
51	L : Keyvalue M	'id'
52	L : EPSILON	'}'
53	M : ',' Keyvalue M	','
54	M : EPSILON	'}'
55	G : expr H	'!', '-', '(', 'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id'
56	G : EPSILON	')', 'CKEY'
57	H : ',' expr H	','
58	H : EPSILON	')', 'CKEY'
59	J : '(' G ')'	'('
60	J : array	'OKEY'
61	J : EPSILON	')', '^', '*', '/', '%', '+', '-', '=', '<=', '>=', '<', '>', '==', '!=', '&&', 'OR', ',', '{', 'token_salto_linea', 'CKEY', '}', '$', 'end'
62	expr : '!' expr	'!'
63	expr : '-' expr	'-'
64	expr : '(' expr ')'	'('
65	expr : atom op	'token_integer', 'token_float', 'true', 'false', 'token_string', 'nil', 'OKEY', '{', 'id'
66	op : N expr	'^', '*', '/', '%', '+', '-', '=', '<=', '>=', '<', '>', '==', '!=', '&&', 'OR'
67	op : EPSILON	')', ',', '{', 'token_salto_linea', 'CKEY', '}', '$', 'end'
68	N : '^'	'^'
69	N : '*'	'*'
70	N : '/'	'/'
71	N : '%'	'%'
72	N : '+'	'+'
73	N : '-'	'-'
74	N : '='	'='
75	N : '<='	'<='
76	N : '>='	'>='
77	N : '<'	'<'
78	N : '>'	'>'
79	N : '=='	'=='
80	N : '!='	'!='
81	N : '&&'	'&&'
82	N : 'OR'	'OR'
83	atom : 'token_integer'	'token_integer'
84	atom : 'token_float'	'token_float'
85	atom : 'true'	'true'
86	atom : 'false'	'false'
87	atom : 'token_string'	'token_string'
88	atom : array	'OKEY'
89	atom : variable	'id'
90	atom : 'nil'	'nil'
91	atom : objeto	'{'
