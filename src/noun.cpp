#include "noun.h"
#include "helpers.h"

void Noun::AddRecipe(const Recipe& r) {
	m_recipes.push_back(r);
}

bool Noun::HasRecipe(const Recipe& r) const {
	return ARRAY_EXISTS( m_recipes, r );
}

// for the time being we'll do a simple look up.  in the future we'll consider
// the internal list as merely a cache, and we'll be able to apply some logic
// to do some extra searching for additional recipes if we can't find any
// recipes with the specified intredient.  
bool Noun::FindRecipe(const Ingredient& ingr, Recipe& r) const {
	for (int i = 0; i < m_recipes.size(); ++i) {
		const Recipe& myRecipe = m_recipes[i];
		if ( myRecipe.ContainsIngredient(ingr) ) {
			r = myRecipe;
			return true;
		}
	}
	return false;
}
