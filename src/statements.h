#ifndef _H_STATEMENTS
#define _H_STATEMENTS

#include "noun.h"
#include "database.h"

namespace Statements {
	void AddRecipe(Database* db, const NounKey& n, const Recipe* r) {
		if ( !db->Exists(n) ) {
			db->AddNoun(n);
		}
		(*db)[n].AddRecipe(*r);
	}

	bool IsValidRecipe(Database* db, const NounKey& n, const Recipe* r) {
		if ( db->Exists(n) ) {
			return (*db)[n].HasRecipe(*r);
		}
		return false;
	}
}

#endif /* _H_STATEMENTS */
