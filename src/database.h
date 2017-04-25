#ifndef _H_DATABASE
#define _H_DATABASE

#include <string>
#include <map>
#include <vector>
#include "helpers.h"

class Noun;
class Recipe;

//typedef std::string NounKey;
typedef std::map< NounKey, Noun > DatabaseMap_t;

class Database {
public:
	Noun& AddNoun(const NounKey& name);
	bool Exists(const NounKey& k) const;
	Noun& operator[](const NounKey& k);

	std::vector<NounKey> FindNounsWithIngredientInCache(const NounKey& i);
	bool FindNounsWithRecipeInCache(const Recipe& r, std::vector<NounKey>& matchingNouns);
	std::set<Recipe> FindCachedRecipesForNoun(const NounKey& n);

private:
	DatabaseMap_t m_db;
};

#endif /* _H_DATABASE */
