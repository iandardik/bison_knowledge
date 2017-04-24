#ifndef _H_HELPERS
#define _H_HELPERS

#include <algorithm>
#include <string>
#include <set>
#include <iostream>

// let's throw this in a types.h instead...
//typedef std::string Ingredient;
typedef std::string NounKey;

#define ARRAY_EXISTS( container, value ) \
	std::find( (container).begin(), (container).end(), (value) ) != (container).end()
#define ARRAY_MISSING( container, value ) \
	std::find( (container).begin(), (container).end(), (value) ) == (container).end()

// the power set minus the null set
std::set< std::multiset<NounKey> > NonNullPowerSet( const std::multiset<NounKey>& ingr );
std::set< std::multiset<NounKey> > PowerSet( const std::multiset<NounKey>& ingr );

template<typename T>
std::multiset<T> SetMinus( const std::multiset<T>& a, const std::multiset<T>& b );

#endif /* _H_HELPERS */
