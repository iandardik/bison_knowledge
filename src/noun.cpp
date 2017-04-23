#include "noun.h"
#include <algorithm>

void Noun::AddAttribute(const Attribute& a) {
	m_attributes.push_back(a);
}

std::vector< Attribute > Noun::GetAttributes() const {
	return m_attributes;
}

bool Noun::HasAttribute(const Attribute& a) const {
	return std::find( m_attributes.begin(), m_attributes.end(), a ) != m_attributes.end();
}

void Noun::AddRecipe(const Recipe& r) {
	m_recipes.push_back(r);
}

std::vector< Recipe > Noun::GetRecipes() const {
	return m_recipes;
}

// for the time being we'll do a simple look up.  in the future we'll consider
// the internal list as merely a cache, and we'll be able to apply some logic
// to do some extra searching for additional recipes if we can't find any
// recipes with the specified intredient.  
bool Noun::FindRecipe(const Ingredient& ingr, Recipe& r) const {
	for (int i = 0; i < m_recipes.size(); ++i) {
		const Recipe& myRecipe = m_recipes[i];
		if ( std::find( myRecipe.begin(), myRecipe.end(), ingr ) != myRecipe.end() ) {
			r = myRecipe;
			return true;
		}
	}
	return false;
}
