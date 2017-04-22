#include <iostream>
#include "parser.tab.h"
#include "database.h"

using namespace std;

extern Database* db;

int main(int argc, char* argv[]) {
	db = new Database();

	yyparse();
}
