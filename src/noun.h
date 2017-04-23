#ifndef _H_NOUN
#define _H_NOUN

#include <string>
#include <vector>

typedef std::string Attribute;
typedef std::string Ingredient;
typedef std::vector< Ingredient > Recipe;

class Noun {
public:
	void AddAttribute(const Attribute& a);
	std::vector< Attribute > GetAttributes() const;
	bool HasAttribute(const Attribute& a) const;

	void AddRecipe(const Recipe& r);
	std::vector< Recipe > GetRecipes() const;

	// will find the first recipe possible and populate r with
	// the result.  returns true if at least one recipe can be found,
	// false otherwise.  
	bool FindRecipe(const Ingredient& i, Recipe& r) const;

private:
	std::vector< Attribute > m_attributes;
	std::vector< Recipe > m_recipes;
};

#endif /* _H_NOUN */
