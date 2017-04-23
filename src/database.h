#ifndef _H_DATABASE
#define _H_DATABASE

#include <string>
#include <map>
#include "noun.h"

typedef std::string NounKey;
typedef std::map< NounKey, Noun > DatabaseMap_t;

class Database {
public:
	Noun& AddNoun(const NounKey& name);
	bool Exists(const NounKey& k) const;
	Noun& operator[](const NounKey& k);

private:
	DatabaseMap_t m_db;
};

#endif /* _H_DATABASE */
