#include "database.h"

void Database::AddNoun(const std::string& n) {
	m_db[n] = "";
}

void Database::AddNoun(const std::string& n, const std::string& v) {
	m_db[n] = v;
}

bool Database::LookUp(const std::string& n, const std::string& v) {

	// does the key exist?
	map_t::const_iterator iElem = m_db.find(n);
	if ( iElem == m_db.end() ) {
		return false;
	}

	// is the value of the key equal to the specified value?
	return iElem->second == v;
}
