#include "comm-logs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <syslog.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <assert.h>

#define gettid() syscall(__NR_gettid)

#define DEFAULT_MODULE_NAME     "Comm"

#define NORMAL   "\033[0m"
#define COLOR(x) "\033[" #x ";1m"
#define BOLD     COLOR(1)
#define F_RED    COLOR(31)
#define F_GREEN  COLOR(32)
#define F_YELLOW COLOR(33)
#define F_BLUE   COLOR(34)
#define B_RED    COLOR(41)

#if defined(ANDROID)
#include <jni.h>
#include <android/log.h>

#define TAG         "CommServer"
#define LOGD(...)   __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#endif

#if defined(UNITTEST)
static int global_verbose = kDbgMax;
#elif defined(ANDROID)
static int global_verbose = kDbgEvent;
#else
static int global_verbose = kDbgEvent;
#endif

void LogPring(int level,
              const char *module,
              const char *file,
              int line,
              const char *format, ...)
{
    if (!format)
        return;

    if (level < global_verbose)
        return;

    if (level == kDbgNone || level > kDbgCritial)
        return;
#if defined(ANDROID)
    char msg[512];

    struct timeval  tv;
    gettimeofday(&tv, NULL);

    struct tm *timeinfo;
    time_t t = tv.tv_sec;
    timeinfo = localtime(&t);
    char buf[40];
    strftime(buf,sizeof(buf),"%m/%d,%H:%M:%S",timeinfo);

    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    LOGD("[%s][%s:%d] %s\n", buf, file, line, msg);
#else
    static const char *lv[] = {NULL, F_BLUE, F_GREEN, F_YELLOW, F_RED, B_RED};
    static const char *type[] = {NULL, "Evt", "Info", "Warn", "Err", "Crit"};

    va_list va;
    const char *prefix = NULL;

    va_start (va, format);
    if (!prefix)
        prefix = DEFAULT_MODULE_NAME;

    struct timeval  tv;
    gettimeofday(&tv, NULL);

    struct tm *timeinfo;
    time_t t = tv.tv_sec;
    timeinfo = localtime(&t);
    char buf[40];
    strftime(buf,sizeof(buf),"%m/%d,%H:%M:%S",timeinfo);

    fprintf (stdout, "[%.5ld][%s][%.3d:%-20s] %s%s" NORMAL ": ",
                    gettid(),
                    buf, 
                    line, 
                    file, 
                    lv[level], 
                    type[level]);

    vfprintf (stdout, format, va);
    fprintf (stdout, "\n");
    va_end (va);
#endif
}
