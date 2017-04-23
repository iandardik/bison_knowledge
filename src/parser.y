
%{
	#include <cstdio>
	#include <iostream>
	#include "database.h"
	#include "statements.h"
	#include "recipe.h"

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
	class Recipe* recipe;
}

%token THE IS AND PLUS ENDL
%token <val> STRING
%type <val> noun ingredient
%type <recipe> recipe ingredients

%start statements

%%

statements:
			statement												{}
		| statements statement						{}
		;

statement:
			noun IS recipe ENDL							{ Statements::AddRecipe(db,$1,$3); cout << "OK" << endl; }
		| THE noun IS recipe ENDL					{ Statements::AddRecipe(db,$2,$4); cout << "OK" << endl; }
		| IS noun recipe ENDL							{ cout << (Statements::IsValidRecipe(db,$2,$3) ? "Yes" : "No") << endl; }
		| IS THE noun recipe ENDL					{ cout << (Statements::IsValidRecipe(db,$3,$4) ? "Yes" : "No") << endl; }
		;

recipe:
			ingredients											{ $$ = $1; }
		;

ingredients:
			ingredient											{ $$ = new Recipe(); $$->AddIngredient($1); }
		| ingredients AND ingredient			{ $$->AddIngredient($3); }
		| ingredients PLUS ingredient			{ $$->AddIngredient($3); }
		;

ingredient:
			STRING													{ $$ = $1; }
		;

noun:
			STRING 													{ $$ = $1; }
		;

%%

