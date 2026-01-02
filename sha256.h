// sha256.h
#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stddef.h>

void sha256(const uint8_t *data, size_t len, uint8_t hash[32]);

#endif
