
%{
	#include <cstdio>
	#include <iostream>
	#include "database.h"
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern "C" int yylex();
	//extern "C" int yyparse();
	extern "C" FILE *yyin;
	 
	//void yyerror(const char *s);
  void yyerror(const char *s) { std::cout << "Error: " << s << std::endl; }

	Database* db;
%}

%union {
	char* val;
}

%token THE IS
%token <val> STRING
%type <val> noun value

%start statements

%%

statements:
		statement									{}
		| statements statement		{}
		;

statement:
		noun IS value							{ db->AddNoun( $1, $3 ); }
		| THE noun IS value				{ db->AddNoun( $2, $4 ); }
		| IS noun value						{ cout << (db->LookUp( $2, $3 ) ? "Yes" : "No") << endl; }
		| IS THE noun value				{ cout << (db->LookUp( $3, $4 ) ? "Yes" : "No") << endl; }
		;

noun:
		STRING 										{ $$ = $1; }
		;

value:
		STRING 										{ $$ = $1; }
		;

%%

