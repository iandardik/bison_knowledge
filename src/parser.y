
%{
	#include <cstdio>
	#include <iostream>
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern "C" int yylex();
	extern "C" int yyparse();
	extern "C" FILE *yyin;
	 
	//void yyerror(const char *s);
  void yyerror(const char *s) { std::cout << "Error: " << s << std::endl; }
%}

%union {
	char* val;
}

%token THE IS
%token <val> STRING
%type <val> noun value

%start statement

%%

statement:
		THE noun IS value	{ cout << "map[" << $2 << "]= " << $4 << endl; }
		;

noun:
		STRING 						{ $$ = $1; }
		;

value:
		STRING 						{ $$ = $1; }
		;

%%

int main(int argc, char* argv[]) {
	//yylex();
	yyparse();
}
