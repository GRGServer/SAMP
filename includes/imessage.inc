/* 
    Bombo translate functions
*/

#if defined _TRANSLATE_FUNCS
	#endinput
#endif

#define _TRANSLATE_FUNCS

native init_ifile(filename[]);
native close_ifile();
native imessage(out_text[], name[], language[], size=sizeof out_text);

