#ifndef LOGGER_H
#define LOGGER_H

#define _GNU_SOURCE

#include <stdio.h>
#include <syslog.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_EMERG
#endif

#ifndef _DISABLE_LOGGER
#define _DISABLE_LOGGER 0
#endif

#define TO_S(M) #M
#define STR(M) TO_S(M)

#define LOG_MSG(LEVEL, f_str, ...)                                                   \
    do {                                                                        \
        fprintf(stderr, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__); \
    } while(0)


#if LOG_LEVEL >= LOG_EMERG && !_DISABLE_LOGGER 
#define LOGF_EMERG(f_str, ...) LOG_MSG("emerg", f_str, ##__VA_ARGS__)
#else
#define LOGF_EMERG(f_str, ...) 
#endif

#if LOG_LEVEL >= LOG_INFO && !_DISABLE_LOGGER
#define LOGF_INFO(f_str, ...) LOG_MSG("info", f_str, ##__VA_ARGS__)
#else
#define LOGF_INFO(f_str, ...) 
#endif

#endif
