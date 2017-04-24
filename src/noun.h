#ifndef _H_NOUN
#define _H_NOUN

#include <string>
#include <vector>
#include "helpers.h"
#include "recipe.h"

class Database;

//TODO make this a set.  this requires us to make Recipe comparable
//typedef std::set< Recipe > NounRecipeContainer_t;
typedef std::vector< Recipe > NounRecipeContainer_t;

class Noun {
public:
	void AddRecipe(const Recipe& r);
	bool HasRecipe(const Recipe& r);

	bool HasRecipeInCache(const Recipe& r) const;
	bool HasIngredientInCache(const NounKey& i) const;

	// will find the first recipe possible and populate r with
	// the result.  returns true if at least one recipe can be found,
	// false otherwise.  
	bool FindRecipe(const NounKey& i, Recipe& r) const;

	static Database* m_db;

private:
	bool SearchDBForRecipe(const Recipe& r);

	NounRecipeContainer_t m_recipes;
};

#endif /* _H_NOUN */
