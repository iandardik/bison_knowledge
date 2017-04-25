#include "noun.h"
#include "helpers.h"
#include "database.h"

Database* Noun::m_db = 0;

void Noun::AddRecipe(const Recipe& r) {
	m_recipes.insert(r);
}

bool Noun::HasRecipe(const Recipe& r) {
	if ( HasRecipeInCache(r) ) {
		return true;
	}

	// update the cache and try again
	ExpandIngredientsInCache();
	return SearchDBForRecipe(r);
	//return HasRecipeInCache(r);
}

bool Noun::HasIngredientInCache(const NounKey& ingr) const {
	// check each recipe in the cache to see if it uses the specified ingredient
	for (const Recipe& recipe : m_recipes) {
		if ( recipe.ContainsIngredient(ingr) ) {
			return true;
		}
	}
	return false;
}

NounRecipeContainer_t Noun::GetRecipesInCache() const {
	return m_recipes;
}

// for the time being we'll do a simple look up.  in the future we'll consider
// the internal list as merely a cache, and we'll be able to apply some logic
// to do some extra searching for additional recipes if we can't find any
// recipes with the specified intredient.  
bool Noun::FindRecipe(const NounKey& ingr, Recipe& r) const {
	for (const Recipe& myRecipe : m_recipes) {
		if ( myRecipe.ContainsIngredient(ingr) ) {
			r = myRecipe;
			return true;
		}
	}
	return false;
}

bool Noun::SearchDBForRecipe(const Recipe& recipe) {
	if ( HasRecipeInCache(recipe) ) {
		return true;
	}
	if ( recipe.NumIngredients() <= 1 && !HasRecipeInCache(recipe) ) {
		return false;
	}

	for (const Recipe& recipeVariation : ExpandIngredientSet(recipe) ) {
		//std::cout << "recipe variation: " << recipeVariation.ToString() << std::endl;
		if ( HasRecipeInCache(recipeVariation) ) {
			AddRecipe(recipe);
			return true;
		}
		
		/*
		if ( ReduceIngredientSet(recipeVariation) ) {
			AddRecipe(recipe); // i think i sprinkle these around a bit too liberally
			return true;
		}
		*/
	}
	/*
	std::cout << std::endl;
	std::cout << "Cache:" << std::endl;
	for ( const Recipe& r : m_recipes ) {
		std::cout << "\t" << r.ToString() << std::endl;
	}
	std::cout << std::endl;
	*/

	return false;
}

// find all equivalent recipes that are currently cached by expanding the ingredient list
std::set<Recipe> Noun::ExpandIngredientSet(const Recipe& recipe) {
	std::set<Recipe> rvRecipes;
	rvRecipes.insert(recipe);

	// keep a map of each ingredient to recipes for that ingredient
	std::map< NounKey, std::set<Recipe> > mNounToRecipe;

	// fill the map with the ingredients
	// for each ingredient we have, see we have a recipe for it in the DB
	const std::multiset<NounKey>& rawIngredients = recipe.GetIngredients();
	for ( const NounKey& rawIngredient : rawIngredients ) {
		if ( mNounToRecipe.find(rawIngredient) == mNounToRecipe.end() ) {
			// search the DB for a recipe for each ingredient
			mNounToRecipe[rawIngredient] = m_db->FindRecipesForNoun(rawIngredient);
		}
	}

	// for each raw ingredient, replace it with any and all recipes for that ingredient.  we now have a
	// new recipe for the original ingredient that we add to rvRecipes.  
	for ( const NounKey& ingredient : rawIngredients ) {
		//std::cout << "Trying to expand: " << ingredient << std::endl;
		for ( const Recipe& ingrRecipe : mNounToRecipe[ingredient] ) {
			//std::cout << ingredient << ": " << ingrRecipe.ToString() << std::endl;

			std::set<Recipe> curRvRecipes(rvRecipes);
			for ( const Recipe& curRvRecipe : curRvRecipes ) {
				const std::set<Recipe> newRecipes = Recipe::ReplaceIngredientWithRecipe( curRvRecipe, ingredient, ingrRecipe );
				std::copy( newRecipes.begin(), newRecipes.end(), std::inserter(rvRecipes,rvRecipes.end()) );
			}
		}
	}

	return rvRecipes;
}

// find all equivalent recipes that are currently cached by reducing the ingredient list
// this function works by reducing the size of the ingredient list until we find a matching recipe
bool Noun::ReduceIngredientSet(const Recipe& recipe) {
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
	return m_recipes.find(recipe) != m_recipes.end();
}

void Noun::ExpandIngredientsInCache() {
	for ( const Recipe& recipe : m_recipes ) {
		for ( const Recipe& recipeVariant : ExpandIngredientSet(recipe) ) {
			AddRecipe(recipeVariant);
		}
	}
}
