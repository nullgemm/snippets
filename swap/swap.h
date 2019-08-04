#ifndef H_SWAP
#define H_SWAP

#include <stdint.h>

inline uint32_t swap_u32(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    return (val << 16) | (val >> 16);
}

inline uint16_t swap_u16(uint16_t val)
{
    return (val << 8) | (val >> 8);
}

#endif
