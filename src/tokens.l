
%{
#include <iostream>
#include "parser.tab.h"
#define YY_DECL extern "C" int yylex()
%}

%option noyywrap

%%

[ \t\n]                 ;
"the" 									{ return THE; }
"THE" 									{ return THE; }
"is"										{ return IS; }
"IS"										{ return IS; }
[a-zA-Z0-9]+  					{ yylval.val = strdup(yytext); return STRING; }
.                       { printf("Unknown token!\n"); yyterminate(); }

%%
