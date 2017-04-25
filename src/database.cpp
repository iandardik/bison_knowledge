#include "database.h"
#include "noun.h"

Noun& Database::AddNoun(const NounKey& name) {
	return (m_db[name] = Noun());
}

bool Database::Exists(const NounKey& k) const {
	return m_db.find(k) != m_db.end();
}

Noun& Database::operator[](const NounKey& k) {
	return m_db[k];
}

std::vector<NounKey> Database::FindNounsWithIngredientInCache(const NounKey& ingr) {
	std::vector<NounKey> nounsFound;

	for (DatabaseMap_t::const_iterator i = m_db.begin(); i != m_db.end(); ++i) {
		const NounKey& key = i->first;
		const Noun& noun = i->second;
		if ( noun.HasIngredientInCache(ingr) ) {
			nounsFound.push_back( key );
		}
	}

	return nounsFound;
}

bool Database::FindNounsWithRecipeInCache(const Recipe& r, std::vector<NounKey>& matchingNouns) {
	for (DatabaseMap_t::const_iterator i = m_db.begin(); i != m_db.end(); ++i) {
		const NounKey& k = i->first;
		const Noun& n = i->second;
		if ( n.HasRecipeInCache(r) ) {
			matchingNouns.push_back(k);
		}
	}
	return matchingNouns.size() > 0;
}

std::set<Recipe> Database::FindCachedRecipesForNoun(const NounKey& n) {
	return m_db[n].GetRecipes();
}
