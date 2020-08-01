#ifndef PC2_CHAOS_H
#define PC2_CHAOS_H

#include <stdint.h>
#include <stddef.h>

#define PC2_CHAOS_MAX 10000

void pc2_chaos_set_seed(uint8_t* hash_as_seed, size_t len);
uint32_t pc2_chaos_get_random();

#endif // PC2_CHAOS_H
