// crypto_aes.h
#ifndef CRYPTO_AES_H
#define CRYPTO_AES_H

#include <stdint.h>

// Encrypts a single 16-byte block
void aes_encrypt_block(uint8_t *block, const uint8_t *key);

// Decrypts a single 16-byte block
void aes_decrypt_block(uint8_t *block, const uint8_t *key);

#endif