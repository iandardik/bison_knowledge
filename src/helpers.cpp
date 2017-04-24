#include "helpers.h"
#include "recipe.h"

std::set< std::multiset<NounKey> > NonNullPowerSet( const std::multiset<NounKey>& ingr ) {
	std::set< std::multiset<NounKey> > ps = PowerSet(ingr);
	ps.erase( std::multiset<NounKey>() );
	return ps;
}

std::set< std::multiset<NounKey> > PowerSet( const std::multiset<NounKey>& ingr ) {
	// base case
	if ( ingr.size() == 0 ) {
		std::set< std::multiset<NounKey> > rv;
		rv.insert( std::multiset<NounKey>() );
		return rv;
	}

	// recursive step
	std::multiset<NounKey> recIngredients( ingr );
	NounKey otherIngredient = *recIngredients.begin();
	recIngredients.erase( recIngredients.begin() );
	std::set< std::multiset<NounKey> > recursiveResult = PowerSet(recIngredients);

	std::set< std::multiset<NounKey> > rvPS;
	for (std::set< std::multiset<NounKey> >::const_iterator i = recursiveResult.begin(); i != recursiveResult.end(); ++i) {
		const std::multiset<NounKey>& rrElem = *i;
		std::multiset<NounKey> withOtherIngredient( rrElem );
		withOtherIngredient.insert( otherIngredient );

		rvPS.insert(rrElem);
		rvPS.insert(withOtherIngredient);
	}
	
	return rvPS;
}

template<typename T>
std::multiset<T> SetMinus( const std::multiset<T>& a, const std::multiset<T>& b ) {
	std::multiset<T> rv(a);
	for (typename std::multiset<T>::const_iterator i = b.begin(); i != b.end(); ++i) {
		rv.erase(*i);
	}
	return rv;
}
template std::multiset<NounKey> SetMinus( const std::multiset<NounKey>&, const std::multiset<NounKey>& );
