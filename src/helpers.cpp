#include "helpers.h"

std::set< std::set<NounKey> > NonNullPowerSet( const std::set<NounKey>& ingr ) {
	std::set< std::set<NounKey> > ps = PowerSet(ingr);
	ps.erase( std::set<NounKey>() );
	return ps;
}

std::set< std::set<NounKey> > PowerSet( const std::set<NounKey>& ingr ) {
	// base case
	if ( ingr.size() == 0 ) {
		std::set< std::set<NounKey> > rv;
		rv.insert( std::set<NounKey>() );
		return rv;
	}

	// recursive step
	std::set<NounKey> recIngredients( ingr );
	NounKey otherIngredient = *recIngredients.begin();
	recIngredients.erase( recIngredients.begin() );
	std::set< std::set<NounKey> > recursiveResult = PowerSet(recIngredients);

	for (std::set< std::set<NounKey> >::const_iterator i = recursiveResult.begin(); i != recursiveResult.end(); ++i) {
		const std::set<NounKey>& rrElem = *i;
		std::set<NounKey> withOtherIngredient( rrElem );
		withOtherIngredient.insert( otherIngredient );
		recursiveResult.insert( withOtherIngredient );
	}
	
	return recursiveResult;
}

template<typename T>
std::set<T> SetMinus( const std::set<T>& a, const std::set<T>& b ) {
	std::set<T> rv(a);
	for (typename std::set<T>::const_iterator i = b.begin(); i != b.end(); ++i) {
		rv.erase(*i);
	}
	return rv;
}
template std::set<NounKey> SetMinus( const std::set<NounKey>&, const std::set<NounKey>& );
