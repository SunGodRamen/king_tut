#include "log.h"

// EEPROM address to store the log level
#define LOG_LEVEL_EEPROM_ADDR 0

log_level_t current_log_level = LOG_LEVEL_ERROR;

void set_log_level(log_level_t level) {
    #ifdef CONSOLE_ENABLE
    dprintf("Setting log level to %d\n", level);
    #endif
    current_log_level = level;
    eeprom_update_byte((uint8_t *)LOG_LEVEL_EEPROM_ADDR, level);
}

log_level_t get_log_level(void) {
    return (log_level_t)eeprom_read_byte((uint8_t *)LOG_LEVEL_EEPROM_ADDR);
}

void log_init(void) {
    log_level_t stored_log_level = get_log_level();

    if (stored_log_level == LOG_LEVEL_ERROR || stored_log_level == LOG_LEVEL_INFO || stored_log_level == LOG_LEVEL_DEBUG) {
        current_log_level = stored_log_level;
    } else {
        // If there is no valid value stored in EEPROM, set the log level to LOG_LEVEL_ERROR
        current_log_level = LOG_LEVEL_ERROR;
        // Update the EEPROM with the default log level (LOG_LEVEL_ERROR)
        set_log_level(LOG_LEVEL_ERROR);
    }
}

// Helper function to check the log level
static bool should_log(log_level_t level) {
    #ifdef CONSOLE_ENABLE
    return current_log_level <= level;
    #else
    return false;
    #endif
}

void write_log_format(log_level_t level, const char* format, ...) {
    if (should_log(level)) {
        char buffer[BUFFER_SIZE];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        dprintf("%s", buffer);
    }
}
