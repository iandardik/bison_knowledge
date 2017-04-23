#ifndef _H_STATEMENTS
#define _H_STATEMENTS

#include "noun.h"
#include "database.h"

namespace Statements {
	void AddNounWithAttribute(Database* db, const NounKey& n, const Attribute& a) {
		if ( !db->Exists(n) ) {
			db->AddNoun(n);
		}
		(*db)[n].AddAttribute(a);
	}

	bool DoesNounHaveAttribute(Database* db, const NounKey& n, const Attribute& a) {
		if ( db->Exists(n) ) {
			return (*db)[n].HasAttribute(a);
		}
		return false;
	}
}

#endif /* _H_STATEMENTS */
