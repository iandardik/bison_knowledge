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

// the power set minus the null set
std::set< std::set<NounKey> > NonNullPowerSet( const std::set<NounKey>& ingr );
std::set< std::set<NounKey> > PowerSet( const std::set<NounKey>& ingr );

template<typename T>
std::set<T> SetMinus( const std::set<T>& a, const std::set<T>& b );

#endif /* _H_HELPERS */
