//
//  ASLogging.h
//
//  Created by Avraham Shukron on 12/9/2013.
//

#define LOG_LEVEL_ERROR 100     // Used for errors. Always printed.
#define LOG_LEVEL_WARNING 90    // Used for events that can lead to error.
#define LOG_LEVEL_NOTICE 80     // Used for events that the user should notice.
#define LOG_LEVEL_INFO 70       // Used for normal events of interest.
#define LOG_LEVEL_DEBUG 50      // Used for debug information.
#define LOG_LEVEL_VERBOSE 0     // Print all things!

#ifdef __OPTIMIZE__
/*
 * For optimized builds (e.g created by building with "Release" configuration)
 * the logging threshold is high to boost performance.
 */
#define ASLoggingThreshold LOG_LEVEL_WARNING
#else
/*
 *  Yours to play.
 *  You might want to change the value during development to see more logs.
 *  Usually DEBUG should be enough.
 */
#define ASLoggingThreshold LOG_LEVEL_DEBUG
#endif

#define _ASFileName [[NSString stringWithUTF8String:__FILE__] lastPathComponent]
#define _ASLineNumber __LINE__
#define _ASMethodName __func__

/*
 * The printing is done only the the message level is >= ASLoggingThreshold.
 * In practice the codition will not even evaluate because it is comparing two
 * consts that are known at compile time, so the compiler can optimize this code
 * and determine at compile time if it should be compiled or not.
 */
#define ASControlledLog(level, ...)\
if (level >= ASLoggingThreshold) {NSLog(__VA_ARGS__);}

/*
 *  A formatted call to ASControlledLog
 */
#define ASFormattedLog(level, tag, format, ...)\
ASControlledLog(level, @"[%@ Line:%d]\n%@: %@\n\n", _ASFileName, _ASLineNumber,\
                tag, [NSString stringWithFormat:(format), ##__VA_ARGS__])

/*
 * Utility to print messages that describe an erranous event. It is recommended
 * to use this macro rather that using ASLog() directly.
 */
#if ASLoggingThreshold <= LOG_LEVEL_ERROR
#define ASLogError(...) ASFormattedLog(LOG_LEVEL_ERROR, @"ERROR", __VA_ARGS__)
#else
#define ASLogError(...) 
#endif

/*
 * Utility to print messages that warn the user about a potentially dangerous
 * situation. It is recommended to use this macro rather that using ASLog()
 * directly.
 */
#if ASLoggingThreshold <= LOG_LEVEL_WARNING
#define ASLogWarning(...) ASFormattedLog(LOG_LEVEL_WARNING, @"WARNING", __VA_ARGS__)
#else
#define ASLogWarning(...) 
#endif

/*
 * Utility to print messages that are worth noticing. 
 * It is recommended to use this macro rather that using ASLog() directly.
 */
#if ASLoggingThreshold <= LOG_LEVEL_NOTICE
#define ASLogNotice(...) ASFormattedLog(LOG_LEVEL_NOTICE, @"NOTICE", __VA_ARGS__)
#else
#define ASLogNotice(...)
#endif

/*
 * Utility to print messages that provide a useful information in regular 
 * operation.
 * It is recommended to use this macro rather that using ASLog() directly.
 */
#if ASLoggingThreshold <= LOG_LEVEL_INFO
#define ASLogInfo(...) ASFormattedLog(LOG_LEVEL_INFO, @"INFO", __VA_ARGS__)
#else
#define ASLogInfo(...)
#endif

/*
 * Utility to print messages that are used during debuging. It is recommended to
 * use this macro rather that using ASLog() directly.
 */
#if ASLoggingThreshold <= LOG_LEVEL_DEBUG
#define ASLogDebug(...) ASFormattedLog(LOG_LEVEL_DEBUG, @"DEBUG", __VA_ARGS__)
#else
#define ASLogDebug(...)
#endif

/*
 * Utility to print messages that are not really important.
 * It is recommended to use this macro rather that using ASLog() directly.
 */
#if ASLoggingThreshold <= LOG_LEVEL_VERBOSE
#define ASLogVerbose(...) ASFormattedLog(LOG_LEVEL_VERBOSE, @"VERBOSE", __VA_ARGS__)
#else
#define ASLogVerbose(...) 
#endif