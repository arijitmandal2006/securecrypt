// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define HASH_SIZE 32

void print_hex(const char *label, const uint8_t *data, size_t len);
void hex_string_to_bytes(const char *hex, uint8_t *out, size_t out_len);
void secure_memzero(void *p, size_t n);

// NEW: Open a GUI file manager window and return the path
void get_file_path_from_dialog(char *buffer, size_t size);

#endif