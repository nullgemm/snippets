#ifndef H_ABS
#define H_ABS

#include <stdint.h>

inline int64_t abs64(int64_t val)
{
	return (val > 0) ? val : -val;
}

inline int32_t abs32(int32_t val)
{
	return (val > 0) ? val : -val;
}

inline int16_t abs16(int16_t val)
{
	return (val > 0) ? val : -val;
}

inline int8_t abs8(int8_t val)
{
	return (val > 0) ? val : -val;
}

#endif
