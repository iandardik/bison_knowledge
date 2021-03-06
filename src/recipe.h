#ifndef _H_RECIPE
#define _H_RECIPE

#include <set>
#include <string>
#include "helpers.h"

class Recipe {
public:
	//TODO require a name
	Recipe();
	Recipe(const std::multiset<NounKey>& ingredients);

	void AddIngredient(const NounKey& i);
	bool ContainsIngredient(const NounKey& i) const;
	std::multiset< NounKey > GetIngredients() const;
	size_t NumIngredients() const;

	bool operator==(const Recipe& other) const;
	bool operator!=(const Recipe& other) const;
	bool operator>(const Recipe& other) const;
	bool operator<(const Recipe& other) const;

	std::string ToString() const;

	static std::set<Recipe> ReplaceIngredientWithRecipe( const Recipe& recipe, const NounKey& ingredient, const Recipe& ingredientRecipe );

private:
	NounKey m_name;
	std::multiset< NounKey > m_ingredients;
};

#endif /* _H_RECIPE */
