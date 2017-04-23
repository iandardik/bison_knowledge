#include "noun.h"
#include "helpers.h"
#include "database.h"

Database* Noun::m_db = 0;

void Noun::AddRecipe(const Recipe& r) {
	m_recipes.push_back(r);
}

bool Noun::HasRecipe(const Recipe& r) {
	/*
	if ( HasRecipeInCache(r) ) {
		return true;
	}
	*/

	// update the cache and try again
	UpdateCacheForRecipe(r);
	return HasRecipeInCache(r);
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

// we need to change the strategy here a bit.  instead of updating the cache, we should be updating the recipe list
// to reduce the number of ingredients until we get a cache hit
void Noun::UpdateCacheForRecipe(const Recipe& recipe) {
	if ( HasRecipeInCache(recipe) ) {
		return;
	}

	const std::set< std::set<NounKey> > potentialNewRecipes = NonNullPowerSet( recipe.GetIngredients() );

	for (std::set< std::set<NounKey> >::const_iterator i = potentialNewRecipes.begin(); i != potentialNewRecipes.end(); ++i) {
		const std::set<NounKey>& potentialNewRecipe = *i;
		const std::set<NounKey>& remainingIngredients = SetMinus( recipe.GetIngredients(), potentialNewRecipe );

		// TODO change to m_db->FindNounsWithRecipe() (i.e. not just in the cache)
		std::vector<NounKey> matchingNouns;
		if ( m_db->FindNounsWithRecipeInCache( Recipe(potentialNewRecipe), matchingNouns ) ) {
			for (int j = 0; j < matchingNouns.size(); ++j) {
				const NounKey& newIngredient = matchingNouns[j];
				//std::cout << "Found intermediate ingredient: " << newIngredient << std::endl;
				std::set<NounKey> newIngredientList(remainingIngredients);
				newIngredientList.insert(newIngredient);
				Recipe newRecipe(newIngredientList);
				//AddRecipe(newRecipe);
				AddRecipe(recipe);
				
				//UpdateCacheForRecipe(newRecipe);
				//std::cout << "Added new recipe: " << newRecipe.ToString() << std::endl;
			}
		}
	}
}

bool Noun::HasRecipeInCache(const Recipe& recipe) const {
	return ARRAY_EXISTS( m_recipes, recipe );
}
