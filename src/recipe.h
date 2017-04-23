#ifndef _H_RECIPE
#define _H_RECIPE

#include <set>
#include <string>
#include "helpers.h"

class Recipe {
public:
	Recipe();
	Recipe(const std::set<NounKey>& ingredients);

	void AddIngredient(const NounKey& i);
	bool ContainsIngredient(const NounKey& i) const;
	std::set< NounKey > GetIngredients() const;
	std::string ToString() const;
	bool operator==(const Recipe& other) const;

private:
	std::set< NounKey > m_ingredients;
};

#endif /* _H_RECIPE */
