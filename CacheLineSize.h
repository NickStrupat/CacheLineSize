#ifndef CACHELINESIZE_H_INCLUDED
#define CACHELINESIZE_H_INCLUDED

// Author: Nick Strupat
// Date: October 29, 2010
// Returns the cache line size (in bytes) of the processor, or 0 on failure

#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
size_t CacheLineSize();
#ifdef __cplusplus
}
#endif

#endif
