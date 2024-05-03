#include <stdint.h>
#include <stddef.h>

#ifndef UTIL_HASH_H
#define UTIL_HASH_H

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Hashes a string using the crc32 algorithm
 *
 * @param data The string to hash
 * @param size The size of the string
 *
 * @return The crc32 hash of the string
 */
uint32_t crc32(const char *data, const size_t size);
#ifdef __cplusplus
}
#endif

#endif
