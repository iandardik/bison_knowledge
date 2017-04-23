
%{
#include <iostream>
#include "recipe.h"
#include "parser.tab.h"
#define YY_DECL extern "C" int yylex()
%}

%option noyywrap

%%

[ \t]                 ;
\n											{ return ENDL; }
"the" 									{ return THE; }
"THE" 									{ return THE; }
"is"										{ return IS; }
"IS"										{ return IS; }
"and"										{ return AND; }
"AND"										{ return AND; }
"plus"									{ return PLUS; }
"PLUS"									{ return PLUS; }
[a-zA-Z0-9]+  					{ yylval.val = strdup(yytext); return STRING; }
.                       { printf("Unknown token!\n"); yyterminate(); }

%%
