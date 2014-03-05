#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "util.h"

inline string_and_length_t* string_and_length(char* string, size_t length) {
  string_and_length_t* sl = malloc(sizeof(string_and_length_t));
  sl->value = string;
  sl->length = length;
  return sl;
}

inline bool get_bit(uint8_t* buffer, size_t total_bit_index) {
  uint8_t* at_byte = buffer + (total_bit_index / 8);
  size_t bit_index = total_bit_index % 8;

  int b = *at_byte;
  int shifted = b >> (7 - bit_index);
  int res = shifted & 1;
  return res;
}

inline uint8_t get_bits8(uint8_t* buf, size_t offset, size_t num_bytes, uint8_t mask) {
  uint8_t* curr = buf + offset;
  uint8_t val = 0;
  for (; curr < buf + offset + num_bytes; curr++) {
    val = (val << 8) | *curr;
  }
  return val & mask;
}

inline uint16_t get_bits16(uint8_t* buf, size_t offset, size_t num_bytes, uint16_t mask) {
  uint8_t* curr = buf + offset;
  uint16_t val = 0;
  for (; curr < buf + offset + num_bytes; curr++) {
    val = (val << 8) | *curr;
  }
  return val & mask;
}

inline uint32_t get_bits32(uint8_t* buf, size_t offset, size_t num_bytes, uint32_t mask) {
  uint8_t* curr = buf + offset;
  uint32_t val = 0;
  for (; curr < buf + offset + num_bytes; curr++) {
    val = (val << 8) | *curr;
  }
  return val & mask;
}

static const char *DAY_NAMES[] =
  { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
static const char *MONTH_NAMES[] =
  { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

char* date_rfc1123() {
    const int RFC1123_TIME_LEN = 29;
    time_t t;
    struct tm* tm;
    char * buf = malloc(RFC1123_TIME_LEN+1);

    time(&t);
    tm = gmtime(&t);

    strftime(buf, RFC1123_TIME_LEN+1, "---, %d --- %Y %H:%M:%S GMT", tm);
    memcpy(buf, DAY_NAMES[tm->tm_wday], 3);
    memcpy(buf+8, MONTH_NAMES[tm->tm_mon], 3);

    return buf;
}

#define LOG_WITH_LEVEL(level) \
  va_list ap; \
  va_start(ap, format); \
  size_t needed = vsnprintf(NULL, 0, format, ap); \
  va_end(ap); \
  char* buffer = malloc(sizeof(char) * (needed + 1)); \
  va_start(ap, format); \
  vsnprintf(buffer, needed, format, ap); \
  va_end(ap); \
  fprintf(stderr, "%s\t%s\n", level, buffer);

void log_fatal(char* format, ...) {
#ifdef LOG_FATAL
  LOG_WITH_LEVEL("FATAL")
#endif
}

void log_warning(char* format, ...) {
#ifdef LOG_WARN
  LOG_WITH_LEVEL("WARN")
#endif
}

void log_error(char* format, ...) {
#ifdef LOG_ERROR
  LOG_WITH_LEVEL("ERROR")
#endif
}

void log_info(char* format, ...) {
#ifdef LOG_INFO
  LOG_WITH_LEVEL("INFO")
#endif
}

void log_debug(char* format, ...) {
#ifdef LOG_DEBUG
  LOG_WITH_LEVEL("DEBUG")
#endif
}
