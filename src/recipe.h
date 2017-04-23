#ifndef _H_RECIPE
#define _H_RECIPE

#include <set>
#include <string>

typedef std::string Ingredient;

class Recipe {
public:
	void AddIngredient(const Ingredient& i);
	bool ContainsIngredient(const Ingredient& i) const;
	bool operator==(const Recipe& other) const;

private:
	std::set< Ingredient > m_ingredients;
};

#endif /* _H_RECIPE */
