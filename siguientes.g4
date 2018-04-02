program					:		$
statements			:	  /n else end } retorno $
statements2 		:		/n end } retorno $
statements3			:		/n end } retorno $
statement				:		/n end } retorno $
element					:		/n end } retorno $
element1				:		{ + - * / ^ < > >= <= ) /n end } retorno $
element2				:		{ + - * / ^ < > >= <= ) /n end } retorno $
routine					:		/n end } retorno $
genoperation		:		{ + - * / ^ < > >= <= ) /n end } retorno $
genoperation1	  :		{ + - * / ^ < > >= <= ) /n end } retorno $
fulloperator    :   token_integer token_float true false id ! token_string array [ ( nil
genoperator		  :		token_integer token_float true false id ! token_string array [ ( nil
espoperation		:		{ + - * / ^ < > >= <= ) /n end } retorno $
espoperation1	  :		{ + - * / ^ < > >= <= ) /n end } retorno $
espoperation2	  :		{ + - * / ^ < > >= <= ) /n end } retorno $
espoperator		  :		{ + - * / ^ < > >= <= ) /n end } retorno $
_for						:		/n end } retorno $
forparam				:		/n {
_while					:		/n end } retorno $
_if							:		/n end } retorno $
_else						:		/n end } retorno $
condition				:		/n { )
condition1			:		)
log							:		/n end } retorno $
leer						:		/n end } retorno $
importar				: 	/n end } retorno $
importar1				:  	importar /n end } retorno $
importar2				:  	importar /n end } retorno $
functioncall		:		{ /n end } retorno $
cparameters		  :		)
cparameters1		:		)
cparameters2		:		)
function				:		/n end } retorno $
parameters			:		)
parameters1			:		)
parameters2			:		)
functionstm		  :		end
functionstm1		:		end
returnstm			  :		/n
negation				:		{ + - * / ^ < > >= <= ) /n end } retorno $
assignment			:		/n end } retorno $
array						:		{ + - * / ^ < > >= <= ) /n end } retorno $
array2					:		]
array3					:		]
number  				:		{ + - * / ^ < > >= <= ) /n end } retorno $
boolean					:		{ + - * / ^ < > >= <= ) /n end } retorno $
enter						:		token_integer token_float true false id ! token_string array [ ( nil if else while for funcion retorno log leer importar desde /n end { } retorno $
n								:		token_integer token_float true false id ! token_string array [ ( nil if else while for funcion retorno log leer importar desde /n end { } retorno $
