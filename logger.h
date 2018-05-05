#ifndef LOGGER_H
#define LOGGER_H

#define _GNU_SOURCE

#include <stdio.h>
#include <syslog.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_WARNING
#endif

#ifndef _DISABLE_LOGGER
#define _DISABLE_LOGGER 0
#endif

#define TO_S(M) #M
#define STR(M) TO_S(M)

#ifndef _LOG_NO_STD
#ifdef _LOG_STDOUT
#define LOG_STD(LEVEL, f_str, ...) fprintf(stdout, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__)
#endif // _LOG_STDOUT
#ifndef _LOG_STDOUT
#define LOG_STD(LEVEL, f_str, ...) fprintf(stderr, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__)
#endif // _LOG_STDOUT
#else
#define LOG_STD(LEVEL, f_str, ...)
#endif // _LOG_NO_STD

#ifdef _SYS_LOG
#define LOG_SYS(LEVEL, f_str, ...) syslog(3, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__)
#else
#define LOG_SYS(LEVEL, f_str, ...)
#endif // _SYS_LOG

#ifdef _LOG_RUNTIME_ENVIRONMENT
extern FILE* user_file;
#define LOG_UMSG(LEVEL, f_str, ...) fprintf(user_file, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__)
int logger_read_configuration(struct logger_conf *config, const char *file_name);
int logger_init(struct logger_conf *configuraiton);
int logger_close(void);
int logger_write_configuration(struct logger_conf *config, const char *file_name);
#else
#define LOG_UMSG(LEVEL, f_str, ...)
#endif // _LOG_RUNTIME_ENVIRONMENT

#define LOG_MSG(LEVEL, f_str, ...)                                                   \
    do { \
        LOG_STD(LEVEL, f_str, ##__VA_ARGS__); \
        LOG_SYS(LEVEL, f_str, ##__VA_ARGS__); \
        LOG_UMSG(LEVEL, f_str, ##__VA_ARGS__); \
    } while(0)


#if LOG_LEVEL >= LOG_EMERG && !_DISABLE_LOGGER
#define LOGF_EMERG(f_str, ...) LOG_MSG("emerg", f_str, ##__VA_ARGS__)
#else
#define LOGF_EMERG(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_ALERT && !_DISABLE_LOGGER
#define LOGF_ALERT(f_str, ...) LOG_MSG("alert", f_str, ##__VA_ARGS__)
#else
#define LOGF_ALERT(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_CRIT && !_DISABLE_LOGGER
#define LOGF_CRIT(f_str, ...) LOG_MSG("crit", f_str, ##__VA_ARGS__)
#else
#define LOGF_CRIT(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_ERR && !_DISABLE_LOGGER
#define LOGF_ERR(f_str, ...) LOG_MSG("err", f_str, ##__VA_ARGS__)
#else
#define LOGF_ERR(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_WARNING && !_DISABLE_LOGGER
#define LOGF_WARINING(f_str, ...) LOG_MSG("warning", f_str, ##__VA_ARGS__)
#else
#define LOGF_WARINING(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_NOTICE && !_DISABLE_LOGGER
#define LOGF_NOTICE(f_str, ...) LOG_MSG("notice", f_str, ##__VA_ARGS__)
#else
#define LOGF_NOTICE(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_INFO && !_DISABLE_LOGGER
#define LOGF_INFO(f_str, ...) LOG_MSG("info", f_str, ##__VA_ARGS__)
#else
#define LOGF_INFO(f_str, ...)
#endif



#endif // LOGGER_H
