#include "noun.h"
#include "helpers.h"
#include "database.h"

Database* Noun::m_db = 0;

void Noun::AddRecipe(const Recipe& r) {
	if ( ARRAY_MISSING( m_recipes, r ) ) {
		m_recipes.push_back(r);
	}
}

bool Noun::HasRecipe(const Recipe& r) {
	if ( HasRecipeInCache(r) ) {
		return true;
	}

	// update the cache and try again
	return SearchDBForRecipe(r);
	//return HasRecipeInCache(r);
}

bool Noun::HasIngredientInCache(const NounKey& ingr) const {
	// check each recipe in the cache to see if it uses the specified ingredient
	for (int i = 0; i < m_recipes.size(); ++i) {
		const Recipe& recipe = m_recipes[i];
		if ( recipe.ContainsIngredient(ingr) ) {
			return true;
		}
	}
	return false;
}

// for the time being we'll do a simple look up.  in the future we'll consider
// the internal list as merely a cache, and we'll be able to apply some logic
// to do some extra searching for additional recipes if we can't find any
// recipes with the specified intredient.  
bool Noun::FindRecipe(const NounKey& ingr, Recipe& r) const {
	for (int i = 0; i < m_recipes.size(); ++i) {
		const Recipe& myRecipe = m_recipes[i];
		if ( myRecipe.ContainsIngredient(ingr) ) {
			r = myRecipe;
			return true;
		}
	}
	return false;
}

// this function works by reducing the size of the ingredient list until we find a matching recipe
bool Noun::SearchDBForRecipe(const Recipe& recipe) {
	if ( HasRecipeInCache(recipe) ) {
		return true;
	}
	if ( recipe.NumIngredients() <= 1 && !HasRecipeInCache(recipe) ) {
		return false;
	}

	const std::set< std::multiset<NounKey> > potentialNewRecipes = NonNullPowerSet( recipe.GetIngredients() );

	for (std::set< std::multiset<NounKey> >::const_iterator i = potentialNewRecipes.begin(); i != potentialNewRecipes.end(); ++i) {
		const std::multiset<NounKey>& potentialNewRecipe = *i;
		const std::multiset<NounKey>& remainingIngredients = SetMinus( recipe.GetIngredients(), potentialNewRecipe );

		// TODO change to m_db->FindNounsWithRecipe() (i.e. not just in the cache)
		std::vector<NounKey> matchingNouns;
		if ( m_db->FindNounsWithRecipeInCache( Recipe(potentialNewRecipe), matchingNouns ) ) {

			for (int j = 0; j < matchingNouns.size(); ++j) {
				const NounKey& newIngredient = matchingNouns[j];
				std::multiset<NounKey> newIngredientList(remainingIngredients);
				newIngredientList.insert(newIngredient);
				Recipe newRecipe(newIngredientList);

				if ( HasRecipeInCache(newRecipe) ) {
					AddRecipe(recipe);
					return true;
				}
				else {
					if ( SearchDBForRecipe(newRecipe) ) {
						AddRecipe(recipe); // might not need this
						return true;
					}
				}
			}

		}
	}

	return false;
}

bool Noun::HasRecipeInCache(const Recipe& recipe) const {
	return ARRAY_EXISTS( m_recipes, recipe );
}
