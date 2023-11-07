#ifndef ALPHANUMERIC_HASH_H
#define ALPHANUMERIC_HASH_H

#include <stdbool.h>
#include <stdint.h>
#include "timer.h"
#include "util.h"
#include <string.h>
#include "quantum.h"
#include "../lib/keymap_ascii.h"

bool alphanumeric_hash_active(void);
bool alphanumeric_hash_timed_out(void);
bool alphanumeric_hash_add(uint16_t keycode);
void alphanumeric_hash_end(void);
void alphanumeric_hash_reset_timer(void);
void alphanumeric_hash_start(void);
void alphanumeric_hash_task(void);

#endif //ALPHANUMERIC_HASH_H