#include "recipe.h"

Recipe::Recipe()
	: m_ingredients()
{}

Recipe::Recipe(const std::set<NounKey>& ingredients)
	: m_ingredients(ingredients)
{}

void Recipe::AddIngredient(const NounKey& i) {
	m_ingredients.insert(i);
}

bool Recipe::ContainsIngredient(const NounKey& i) const {
	return m_ingredients.find(i) != m_ingredients.end();
}

std::set< NounKey > Recipe::GetIngredients() const {
	return m_ingredients;
}

std::string Recipe::ToString() const {
	std::string output("[");
	for (std::set< NounKey >::const_iterator i = m_ingredients.begin(); i != m_ingredients.end(); ++i) {
		output += *i;
		std::set< NounKey >::const_iterator iLookahead = i;
		++iLookahead;
		if ( iLookahead != m_ingredients.end() ) {
			output += ",";
		}
	}
	output += "]";
	return output;
}

bool Recipe::operator==(const Recipe& other) const {
	// self reference
	if ( this == &other ) {
		return true;
	}

	// if the ingredients are the same then the recipes are the same
	return this->m_ingredients == other.m_ingredients;
}
