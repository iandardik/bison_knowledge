#include "recipe.h"

Recipe::Recipe()
	: m_ingredients()
{}

Recipe::Recipe(const std::multiset<NounKey>& ingredients)
	: m_ingredients(ingredients)
{}

void Recipe::AddIngredient(const NounKey& i) {
	m_ingredients.insert(i);
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
