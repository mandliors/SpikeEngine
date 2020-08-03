#pragma once

#include <assert.h>

#ifdef SPIKE_DEBUG
	#define SPIKE_ASSERT(condition, message) \
		if (!condition) \
		{ \
			std::cerr << "Assertion '" #condition "' failed in " << __FILE__ << " line " << __LINE__ << ": " << message << std::endl; \
				std::terminate(); \
		}
#else
	#define SPIKE_ASSERT(condition, message)
#endif