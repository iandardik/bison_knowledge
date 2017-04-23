#include "recipe.h"

void Recipe::AddIngredient(const Ingredient& i) {
	m_ingredients.insert(i);
}

bool Recipe::ContainsIngredient(const Ingredient& i) const {
	return m_ingredients.find(i) != m_ingredients.end();
}

bool Recipe::operator==(const Recipe& other) const {
	// self reference
	if ( this == &other ) {
		return true;
	}

	// if the ingredients are the same then the recipes are the same
	return this->m_ingredients == other.m_ingredients;
}
