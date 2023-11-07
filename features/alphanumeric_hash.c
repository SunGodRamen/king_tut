#include "alphanumeric_hash.h"

#ifndef ALPHANUMERIC_HASHING_TIMEOUT
#    define ALPHANUMERIC_HASHING_TIMEOUT 500
#endif

#define NUM_ALPHANUMERIC_CHARS 41
const char mapping[] = "E@GR$90!1#UL7PBVC5^MFZHYTS368DNKIQ4XOWAJ2";

#define ALPHANUMERIC_OUTPUT_LEN 16

// Flags and variables for alphanumeric hash generation
bool alphanumeric_hashing = false;
uint16_t alphanumeric_hashing_time = 0;
uint8_t alphanumeric_hash_index = 0;
uint32_t alphanumeric_hash_digits = 0;

// Function to map a digit to a character based on the mapping array
char map_digit_to_char(int digit) {
    char character;

    if (digit >= 0 && digit < NUM_ALPHANUMERIC_CHARS) {
        character = mapping[digit];
    } else {
        // Handle out of range digits
        character = '?'; // You can choose any character for out of range digits
    }

    return character;
}

// Function to convert a hash to a sequence of alphanumeric characters
void hash_to_sequence(uint32_t hash, char *sequence, int sequenceLength) {
    for (int i = 0; i < sequenceLength; i++) {
        // Take modulo against NUM_ALPHANUMERIC_CHARS to determine the character
        int digit = hash % NUM_ALPHANUMERIC_CHARS;
        sequence[i] = map_digit_to_char(digit);
        hash /= NUM_ALPHANUMERIC_CHARS;
    }
    sequence[sequenceLength] = '\0'; // Null-terminate the string
}

// Function to start the alphanumeric hash generation process
void alphanumeric_hash_start(void) {
    if (alphanumeric_hashing) {
        return;
    }
    alphanumeric_hashing = true;
    alphanumeric_hashing_time = timer_read();
    alphanumeric_hash_index = 0;
    alphanumeric_hash_digits = 0;
}

// Function to finish the alphanumeric hash generation and send the result as keycodes
void alphanumeric_hash_end(void) {
    alphanumeric_hashing = false;
    char alphanumeric[ALPHANUMERIC_OUTPUT_LEN + 1];

    hash_to_sequence(alphanumeric_hash_digits, alphanumeric, ALPHANUMERIC_OUTPUT_LEN);

    // Use the keymap_ascii library to send the alphanumeric string as keycodes
    send_string_as_keycodes(alphanumeric);
}

// Function to check if alphanumeric hash generation is active
bool alphanumeric_hash_active(void) {
    return alphanumeric_hashing;
}

// Function to check if alphanumeric hash generation has timed out
bool alphanumeric_hash_timed_out(void) {
#if defined(ALPHANUMERIC_HASH_NO_TIMEOUT)
    return alphanumeric_hash_index > 0 && timer_elapsed(alphanumeric_hashing_time) > ALPHANUMERIC_HASHING_TIMEOUT;
#else
    return timer_elapsed(alphanumeric_hashing_time) > ALPHANUMERIC_HASHING_TIMEOUT;
#endif
}

// Function to handle the alphanumeric hash generation process
void alphanumeric_hash_task(void) {
    if (alphanumeric_hash_active() && alphanumeric_hash_timed_out()) {
        alphanumeric_hash_end();
    }
}

// Function to reset the timer for alphanumeric hash generation
void alphanumeric_hash_reset_timer(void) {
    alphanumeric_hashing_time = timer_read();
}

// Function to perform alphanumeric hash generation
uint32_t alphanumeric_hashing_function(uint16_t keycode, uint32_t hash) {
    // Modify the hash function to make use of a different prime number
    keycode = keycode * 5;
    hash ^= ((keycode << 5) | (keycode >> 13));
    hash *= 2654435761U;  // You can experiment with different prime numbers
    uprintf("Alphanumeric Hash: %u\n", hash);
    return hash;
}

// Function to add a keycode to the alphanumeric hash
bool alphanumeric_hash_add(uint16_t keycode) {
#if defined(ALPHANUMERIC_HASH_NO_TIMEOUT)
    if (alphanumeric_hash_index == 0) {
        alphanumeric_hash_reset_timer();
    }
#endif

    // Add the keycode to the hash
    alphanumeric_hash_digits = alphanumeric_hashing_function(keycode, alphanumeric_hash_digits);
    alphanumeric_hash_index++;

    return true;
}
