#include "hash.h"

uint32_t hashing_function(uint16_t keycode, uint8_t index, uint32_t hash) {
    // Combine the keycode and index into the hash
    hash = ((hash << 5) | (hash >> 27)) ^ keycode;
    return hash;
}