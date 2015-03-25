#ifndef __COMM_LOGS_H__
#define __COMM_LOGS_H__

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    kDbgNone = 0,
    kDbgEvent,
    kDbgDebug,
    kDbgWarning,
    kDbgError,
    kDbgCritial,
    kDbgMax
}DbgLevel;

#define BASEFILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void LogPring(int level,
                const char *module,
                const char *file,
                int line,
                const char *format, ...);

#define Log(fmt,arg...) \
        LogPring(kDbgDebug,NULL,BASEFILE,__LINE__,fmt,##arg)

#define Evt(fmt,arg...) \
        LogPring(kDbgEvent,NULL,BASEFILE,__LINE__,fmt,##arg)

#define Wrn(fmt,arg...) \
        LogPring(kDbgWarning,NULL, BASEFILE,__LINE__,fmt,##arg)

#define Err(fmt,arg...) \
        LogPring(kDbgError,NULL, BASEFILE,__LINE__,fmt,##arg)

#define Crit(fmt,arg...) \
        LogPring(kDbgCritial,NULL, BASEFILE,__LINE__,fmt,##arg)

#ifdef __cplusplus
}
#endif

#endif//__COMM_LOGS_H__
