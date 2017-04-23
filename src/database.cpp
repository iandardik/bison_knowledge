#include "database.h"

Noun& Database::AddNoun(const NounKey& name) {
	return (m_db[name] = Noun());
}

bool Database::Exists(const NounKey& k) const {
	return m_db.find(k) != m_db.end();
}

Noun& Database::operator[](const NounKey& k) {
	return m_db[k];
}
