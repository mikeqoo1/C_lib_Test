#pragma once
#include "zlog.h"
#include <stddef.h>
zlog_category_t *logger;

#define ESC_START "\033["
#define ESC_END "\033[0m"
#define COLOR_FATAL "31;40;5m"
#define COLOR_ALERT "31;40;1m"
#define COLOR_CRIT "31;40;1m"
#define COLOR_ERROR "35;40;1m"
#define COLOR_WARN "33;40;1m"
#define COLOR_NOTICE "34;40;1m"
#define COLOR_INFO "32;40;1m"
#define COLOR_DEBUG "36;40;1m"
#define COLOR_TRACE "37;40;1m"

#define LOG_FATAL(fmt, ...)                                                                             \
    zlog(logger, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__,         \
         ZLOG_LEVEL_FATAL, ESC_START COLOR_FATAL __VA_ARGS__)

#define LOG_ERROR(fmt, ...)                                                                        \
    zlog(logger, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__,         \
         ZLOG_LEVEL_ERROR, ESC_START COLOR_ERROR __VA_ARGS__)

#define LOG_WARN(fmt, ...)                                                                         \
    zlog(logger, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__,         \
         ZLOG_LEVEL_WARN, ESC_START COLOR_WARN __VA_ARGS__)

#define LOG_NOTICE(fmt, ...)                                                                       \
    zlog(logger, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__,         \
         ZLOG_LEVEL_NOTICE, ESC_START COLOR_NOTICE __VA_ARGS__)

#define LOG_INFO(fmt, ...)                                                                         \
    zlog(logger, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__,         \
         ZLOG_LEVEL_INFO, ESC_START COLOR_INFO __VA_ARGS__)

#define LOG_DEBUG(fmt, ...)                                                                        \
    zlog(logger, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__,         \
         ZLOG_LEVEL_DEBUG, ESC_START COLOR_DEBUG __VA_ARGS__)

int log_init();

int init_zlog_category();

zlog_category_t *getLogger(int);
