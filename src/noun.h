#ifndef _H_NOUN
#define _H_NOUN

#include <string>
#include <vector>
#include "recipe.h"

class Noun {
public:
	void AddRecipe(const Recipe& r);
	bool HasRecipe(const Recipe& r) const;

	// will find the first recipe possible and populate r with
	// the result.  returns true if at least one recipe can be found,
	// false otherwise.  
	bool FindRecipe(const Ingredient& i, Recipe& r) const;

private:
	std::vector< Recipe > m_recipes;
};

#endif /* _H_NOUN */
