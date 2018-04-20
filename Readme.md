# Logger for c language

This repository provides a simple logger for C language.

The `logger.h` header file provides simple compile-time logger utility
which could be used for logging messages syslog compatible logging levels.

The example code of usage can be found in the `example.c` file.

## The logging interface

The code will implement following macros for logging

```c
LOGF_EMERG("fmt_str", va_args...);
LOGF_ALERT("fmt_str", va_args...);
LOGF_CRIT("fmt_str", va_args...);
LOGF_ERR("fmt_str", va_args...);
LOGF_WARNING("fmt_str", va_args...);
LOGF_INFO("fmt_str", va_args...);
LOGF_DEBUG("fmt_str", va_args...);
```

All of those marcos are reporting the formatted string and its arguments with specified severity in following format

```
[${SEVERITY}][${FILE}:${LINE}] formatted message\n
```

Example:

```
[INFO][main.c:23] Connection accepted
[WARNING}[main.c:53] Connection reset by peer
```

### Compile time configuration

The logging facility can be configured in compile-time for basic logging.

There are three places, where the logger can write the output:

* `stderr` Standard error stream, which is default
* `stdout` Standard output stream, which can be switched
*  `syslog(3)`

The configuration of output can be done by following macros

```c
_LOG_STDOUT //will write to stdout instead of stderr
_LOG_NO_STD //will write neither to stdout nor to stderr
_LOG_SYSLOG // will write to syslog, which is independent on the s{out,err} configuration
```

Also the severity can be set by macro `LOG_LEVEL` which can be set to following values

```c
LOG_EMERG
LOG_ALERT
LOG_CRIT
LOG_ERR
LOG_WARNING
LOG_INFO
LOG_DEBUG
```

The log level macro will allow messages with same or greater severity -> where severity of emerg is as follows
`LOG_EMERG >= LOG_ALERT >= LOG_CRIT >= LOG_ERR >= LOG_WARNING >= LOG_INFO >= LOG_DEBUG`

> Note: the higher the severity is, lower is the numerical constant of selected

If `LOG_LEVEL` is not set, then `LOG_WARNING` is applied.

> Note: If the syslog logging is enabled, the programmer should open syslog in his code by himself, the library should not do it
> if it's used only as header file.

#### Example compile-time configuration

```bash
gcc my_main.c -D_LOG_STDOUT -D_LOG_SYSLOG -DLOG_LEVEL=LOG_DEBUG
```

### Runtime configuration

For the logger to be suitable for more general usage, the runtime configuration can be applied.
The runtime configuration can be enabled by macro `_LOG_RUNTIME_ENVIRONMENT`.

This configuration will require to have some object file and several functions for configuration, clean up
and execution.

#### General functions:

```c
int logger_read_configuration(struct logger_conf *config, const char *file_name);
int logger_init(struct logger_conf *configuraiton);
int logger_close(void);
int logger_write_configuration(struct logger_conf *config, const char *file_name);
```

The `struct logger_conf` does not yet have a interface, but it should enable user to specify file, that file 
that could be used for logging, or enable all previous sterams for output. Also the struct should specify, if
the logger will be used in multi threaded application.

If the multithreaded application will be used, the logger will use library __pthread__ `pthreads(7)` mutualy exclude
the threads when they are trying to write to it, so the output will be synchronized and no race-conditions will happen.
All of those functions will need to be implemented in file `logger.c` which then can be linked by user to his application.


__Notice!__ the `logger.h` must be usable without `logger.c` in case of compile-time configuration.
