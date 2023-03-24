#include "srt_log.hpp"
#include "srt_to_rtmp.hpp"
#include <string>
#include <stdint.h>
#include <stdarg.h>

LOGGER_LEVEL s_log_level = SRT_LOGGER_TRACE_LEVEL;
bool s_log_srt_to_rtmp = false;
static char* srt_log_buffer = new char[LOGGER_BUFFER_SIZE];

void snprintbuffer(char* buffer, size_t size, const char* fmt, ...) {
    va_list ap;
 
    va_start(ap, fmt);
    vsnprintf(buffer, size, fmt, ap);
    va_end(ap);

    return;
}

void set_srt_log_level(LOGGER_LEVEL level) {
    s_log_level = level;
}

void set_srt_log_srt_to_rtmp(bool active) {
    s_log_srt_to_rtmp = active;
}

LOGGER_LEVEL get_srt_log_level() {
    return s_log_level;
}

char* get_srt_log_buffer() {
    return srt_log_buffer;
}

void srt_log_output(LOGGER_LEVEL level, const char* buffer) {
    std::string log_content(buffer);
    if (s_log_srt_to_rtmp) {
        srt2rtmp::get_instance()->insert_log_message(level, log_content);
    }
    return;
}
