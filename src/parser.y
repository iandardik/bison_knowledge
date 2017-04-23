
%{
	#include <cstdio>
	#include <iostream>
	#include "database.h"
	#include "statements.h"
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
%type <val> noun adjective

%start statements

%%

statements:
			statement										{}
		| statements statement				{}
		;

statement:
			noun IS adjective						{ Statements::AddNounWithAttribute(db,$1,$3); }
		| THE noun IS adjective				{ Statements::AddNounWithAttribute(db,$2,$4); }
		| IS noun adjective						{ cout << (Statements::DoesNounHaveAttribute(db,$2,$3) ? "Yes" : "No") << endl; }
		| IS THE noun adjective				{ cout << (Statements::DoesNounHaveAttribute(db,$3,$4) ? "Yes" : "No") << endl; }
		;

noun:
			STRING 											{ $$ = $1; }
		;

adjective:
			STRING 											{ $$ = $1; }
		;

%%

