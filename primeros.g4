program					:		/n token_integer token_float true false id ! token_string array [ ( nil if while for funcion log leer importar desde epsilon
statements			:	  /n {
statements2 		:		token_integer token_float true false id ! token_string array [ ( nil if while for funcion log leer importar desde epsilon
statements3			:		/n epsilon
statement				:		token_integer token_float true false id ! token_string array [ ( nil if while for funcion log leer importar desde
element					:		token_integer token_float true false id ! token_string array [ ( nil
element1				:		token_integer token_float true false id ! token_string array [ ( nil
element2				:		token_integer token_float true false id ! token_string array [ ( nil
routine					:		if while for funcion log leer importar desde
genoperation		:		token_integer token_float true false id ! token_string array [ ( nil
genoperation1	  :		token_integer token_float true false id ! token_string array [ ( nil
fulloperator    :   == != && ||
genoperator		  :		+ - * / ^ < > >= <=
espoperation		:		token_string [ (
espoperation1	  :		+ *
espoperation2	  :		token_string [ id
espoperator		  :		token_string [
_for						:		for
forparam				:		token_string [ ( id
_while					:		while
_if							:		if
_else						:		else epsilon
condition				:		token_integer token_float true false id ! token_string array [ ( nil epsilon
condition1			:		( epsilon
log							:		log
leer						:		leer
importar				: 	importar desde
importar1				:  	id
importar2				:  	. epsilon
functioncall		:		id
cparameters		  :		token_integer token_float true false id ! token_string array [ ( nil epsilon
cparameters1		:		token_integer token_float true false id ! token_string array [ ( nil
cparameters2		:		, epsilon
function				:		funcion
parameters			:		id epsilon
parameters1			:		id
parameters2			:		, epsilon
functionstm		  :		/n
functionstm1		:		retorno
returnstm			  :		token_integer token_float true false id ! token_string array [ ( nil epsilon
negation				:		!
assignment			:		id
array						:		[
array2					:		token_integer token_float true false id ! token_string array [ ( nil
array3					:		, epsilon
number  				:		token_integer token_float
boolean					:		true false
enter						:		/n
n								:		epsilon /n
