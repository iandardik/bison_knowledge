#include "recipe.h"
#include <algorithm>

Recipe::Recipe()
	: m_ingredients()
{}

Recipe::Recipe(const std::multiset<NounKey>& ingredients)
	: m_ingredients(ingredients)
{}

void Recipe::AddIngredient(const NounKey& i) {
	if ( i != m_name ) {
		m_ingredients.insert(i);
	}
	else {
		//TODO throw exception
	}
}

bool Recipe::ContainsIngredient(const NounKey& i) const {
	return m_ingredients.find(i) != m_ingredients.end();
}

std::multiset< NounKey > Recipe::GetIngredients() const {
	return m_ingredients;
}

size_t Recipe::NumIngredients() const {
	return m_ingredients.size();
}

bool Recipe::operator==(const Recipe& other) const {
	// self reference
	if ( this == &other ) {
		return true;
	}

	// if the ingredients are the same then the recipes are the same
	return this->m_ingredients == other.m_ingredients;
}

bool Recipe::operator!=(const Recipe& other) const {
	return !this->operator==(other);
}

bool Recipe::operator>(const Recipe& other) const {
	return this->m_ingredients > other.m_ingredients;
}

bool Recipe::operator<(const Recipe& other) const {
	return this->m_ingredients < other.m_ingredients;
}

std::string Recipe::ToString() const {
	std::string output("[");
	for (std::multiset< NounKey >::const_iterator i = m_ingredients.begin(); i != m_ingredients.end(); ++i) {
		output += *i;
		std::multiset< NounKey >::const_iterator iLookahead = i;
		++iLookahead;
		if ( iLookahead != m_ingredients.end() ) {
			output += ",";
		}
	}
	output += "]";
	return output;
}

std::set<Recipe> Recipe::ReplaceIngredientWithRecipe(const Recipe& recipe, const NounKey& ingredient, const Recipe& ingredientRecipe) {
	std::set<Recipe> newRecipes;

	const std::multiset<NounKey> replacementIngredients = ingredientRecipe.GetIngredients();

	std::multiset<NounKey> ingredients = recipe.GetIngredients();
	std::multiset<NounKey>::const_iterator targetIngrItr = ingredients.begin(); // assigning value only to initialize
	while ( (targetIngrItr = ingredients.find(ingredient)) != ingredients.end() ) {
		ingredients.erase(targetIngrItr);
		std::copy( replacementIngredients.begin(), replacementIngredients.end(), std::inserter(ingredients,ingredients.end()) );
		newRecipes.insert( Recipe(ingredients) );
	}

	return newRecipes;
}

