#ifndef MODULE_WLOG_INCLUDE_WLOG_WLOG_H_
#define MODULE_WLOG_INCLUDE_WLOG_WLOG_H_

#define SPDLOG_HEADER_ONLY
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#define MY_LOG_NAME            "My_Log_Name"
#define MY_LOG_STDOUT_SINK_FMT "[%^%l%$]<%t %P>(%@,%!) %v"
#define MY_LOG_FILE_SINK_FMT   "[%Y-%m-%d %H:%M:%S.%e] <%t %P> [%^%l%$] (%@,%!) %v"

#define Trace_Log( ... )    SPDLOG_LOGGER_CALL( spdlog::get( MY_LOG_NAME ), spdlog::level::trace, __VA_ARGS__ )
#define Debug_Log( ... )    SPDLOG_LOGGER_CALL( spdlog::get( MY_LOG_NAME ), spdlog::level::debug, __VA_ARGS__ )
#define Info_Log( ... )     SPDLOG_LOGGER_CALL( spdlog::get( MY_LOG_NAME ), spdlog::level::info, __VA_ARGS__ )
#define Warn_Log( ... )     SPDLOG_LOGGER_CALL( spdlog::get( MY_LOG_NAME ), spdlog::level::warn, __VA_ARGS__ )
#define Error_Log( ... )    SPDLOG_LOGGER_CALL( spdlog::get( MY_LOG_NAME ), spdlog::level::err, __VA_ARGS__ )
#define Critical_Log( ... ) SPDLOG_LOGGER_CALL( spdlog::get( MY_LOG_NAME ), spdlog::level::critical, __VA_ARGS__ )

#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/details/thread_pool-inl.h>
#include <spdlog/details/thread_pool.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

void InitLogger( const std::string LogFileRootPath,
                 const std::string LogStdoutSinkFmt = MY_LOG_STDOUT_SINK_FMT,
                 const std::string LogFileSinkFmt   = MY_LOG_FILE_SINK_FMT );
// TODO :封装成类
// todo :完善
#endif // MODULE_WLOG_INCLUDE_WLOG_WLOG_H_

/*
Pattern flags
Pattern flags are in the form of %flag and resembles the strftime function:

flag	meaning	example
%v	The actual text to log	"some user text"
%t	Thread id	"1232"
%P	Process id	"3456"
%n	Logger's name	"some logger name"
%l	The log level of the message	"debug", "info", etc
%L	Short log level of the message	"D", "I", etc
%a	Abbreviated weekday name	"Thu"
%A	Full weekday name	"Thursday"
%b	Abbreviated month name	"Aug"
%B	Full month name	"August"
%c	Date and time representation	"Thu Aug 23 15:35:46 2014"
%C	Year in 2 digits	"14"
%Y	Year in 4 digits	"2014"
%D or %x	Short MM/DD/YY date	"08/23/14"
%m	Month 01-12	"11"
%d	Day of month 01-31	"29"
%H	Hours in 24 format 00-23	"23"
%I	Hours in 12 format 01-12	"11"
%M	Minutes 00-59	"59"
%S	Seconds 00-59	"58"
%e	Millisecond part of the current second 000-999	"678"
%f	Microsecond part of the current second 000000-999999	"056789"
%F	Nanosecond part of the current second 000000000-999999999	"256789123"
%p	AM/PM	"AM"
%r	12 hour clock	"02:55:02 PM"
%R	24-hour HH:MM time, equivalent to %H:%M	"23:55"
%T or %X	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S	"23:55:59"
%z	ISO 8601 offset from UTC in timezone ([+/-]HH:MM)	"+02:00"
%E	Seconds since the epoch	"1528834770"
%%	The % sign	"%"
%+	spdlog's default format	"[2014-10-31 23:46:59.678] [mylogger] [info] Some
message"
%^	start color range (can be used only once)	"[mylogger] [info(green)] Some
message"
%$	end color range (for example %^[+++]%$ %v) (can be used only once)	[+++]
Some message
%@	Source file and line (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc. instead of
spdlog::trace(...)) Same as %g:%# /some/dir/my_file.cpp:123 %s	Basename of the
source file (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	my_file.cpp %g	Full
or relative path of the source file as appears in the __FILE__ macro (use
SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	/some/dir/my_file.cpp
%#	Source line (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc.)	123
%!	Source function (use SPDLOG_TRACE(..), SPDLOG_INFO(...) etc. see tweakme for
pretty-print)	my_func %o	Elapsed time in milliseconds since previous message
456 %i	Elapsed time in microseconds since previous message	456 %u	Elapsed time
in nanoseconds since previous message	11456 %O	Elapsed time in seconds
since previous message	4 Aligning Each pattern flag can be aligned by
prepending a width number(up to 64).

Use-(left align) or = (center align) to control the align side:

align	meaning	example	result
%<width><flag>	Right align	%8l	"    info"
%-<width><flag>	Left align	%-8l	"info    "
%=<width><flag>	Center align	%=8l	"  info  "
Optionally add ! to truncate the result if its size exceeds the specified width:

align	meaning	example	result
%<width>!<flag>	Right align or truncate	%3!l	"inf"
%-<width>!<flag>	Left align or truncate	%-2!l	"in"
%=<width>!<flag>	Center align or truncate	%=1!l	"i"
Note: To truncate function names use '!!'. For example %10!! will limit function
names to 10 chars.
*/