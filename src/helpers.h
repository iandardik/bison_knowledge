#ifndef _H_HELPERS
#define _H_HELPERS

#include <algorithm>

#define ARRAY_EXISTS( container, value ) \
	std::find( (container).begin(), (container).end(), (value) ) != (container).end()

#endif /* _H_HELPERS */
