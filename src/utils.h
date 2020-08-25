#ifndef _IRON_UTILS_H_
#define _IRON_UTILS_H_

#include <stdint.h>
#include <stdio.h>

#define LOG(...) printf(__VA_ARGS__)

static inline uint32_t
bin_to_uint32(const uint8_t *bin)
{
  return (uint32_t)bin[0] << 24 |
         (uint32_t)bin[1] << 16 |
         (uint32_t)bin[2] << 8  |
         (uint32_t)bin[3];
}

static inline uint16_t
bin_to_uint16(const uint8_t *bin)
{
  return (uint16_t)bin[0] << 8 |
         (uint16_t)bin[1];
}

#endif