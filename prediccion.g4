program					:		/n token_integer token_float true false id ! token_string array [ ( nil if while for funcion log leer importar desde $
statements			:   /n {
                |   /n
statements2 		:   token_integer token_float true false id ! token_string array [ ( nil if while for funcion log leer importar desde
                |   /n end } retorno $
statements3			:   /n
                |   /n end } retorno $
statement				:   token_integer token_float true false id ! token_string array [ ( nil
                |   if while for funcion log leer importar desde
element					:   token_integer token_float true false id ! token_string array [ ( nil
                |   id
element1				:   token_integer token_float
                |   true false
                |   id
                |   !
                |   id
                |   token_integer token_float true false id ! token_string array [ ( nil
element2				:   token_integer token_float true false id ! token_string array [ ( nil
                |   token_string
                |   [
                |   token_string [ (
                |   nil
routine					:   if while for funcion log leer importar desde
                |   while
                |   for
                |   funcion
                |   log
                |   leer
                |   importar desde
genoperation		:   token_string [ (
                |   (
genoperation1	  :   token_integer token_float true false id ! token_string array [ ( nil
                |   token_integer token_float true false id ! token_string array [ ( nil
fulloperator    :   ==
                |   !=
                |   &&
                |   ||
genoperator		  :   +
                |   -
                |   *
                |   /
                |   ^
                |   <
                |   >
                |   >=
                |   <=
espoperation		:   token_string [
                |   (
espoperation1	  :   +
                |   *
espoperation2	  :   token_string [
                |   id
espoperator		  :   token_string
                |   [
_for						:   for
forparam				:   token_string [
                |   token_string [ (
                |   id
                |   id
_while					:   while
_if							:   if
_else						:   else /n {
                |   /n end } retorno $
condition				:   token_integer token_float true false id ! token_string array [ ( nil
                |   (
condition1			:   token_integer token_float true false id ! token_string array [ ( nil
                |   )
log							:   log
leer						:   leer
importar				:   importar
                |   desde
importar1				:   id
importar2				:   .
                |   importar /n end } retorno $
functioncall		:   id
cparameters		  :   token_integer token_float true false id ! token_string array [ ( nil
                |   )
cparameters1		:   token_integer token_float true false id ! token_string array [ ( nil
cparameters2		:   ,
                |   )
function				:   funcion
parameters			:   id
                |   )
parameters1			:   id
parameters2			:   ,
                |   )
functionstm		  :   /n
functionstm1		:   retorno
                |   end
returnstm			  :   token_integer token_float true false id ! token_string array [ ( nil
                |   /n
negation				:   !
assignment			:   id
array						:   [
array2					:   token_integer token_float true false id ! token_string array [ ( nil
array3					:   ,
                |   ]
number  				:   token_integer
                |   token_float
boolean					:   true
                |   false
enter						:   /n
n								:   /n
                |   token_integer token_float true false id ! token_string array [ ( nil if else while for funcion retorno log leer importar desde /n end { } retorno $
