#include <iostream>
#include "parser.tab.h"
#include "database.h"
#include "noun.h"
#include "helpers.h"

extern Database* db;

int main(int argc, char* argv[]) {
	db = new Database();
	Noun::m_db = db;

	yyparse();
}
