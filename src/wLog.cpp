#include <ctime>
#include <iostream>
#include <wLog/wLog.h>

void InitLogger( const std::string LogFileRootPath,
                 const std::string LogStdoutSinkFmt,
                 const std::string LogFileSinkFmt )
{
	try
	{
		std::vector<spdlog::sink_ptr> sinks;

		auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		stdout_sink->set_level( spdlog::level::trace );
		stdout_sink->set_pattern( LogStdoutSinkFmt );
		sinks.push_back( stdout_sink );

		time_t      now   = time( 0 );
		tm*         ltime = localtime( &now );
		std::string today = LogFileRootPath + std::to_string( ltime->tm_year + 1900 ) + "-" +
		                    std::to_string( ltime->tm_mon ) + "-" + std::to_string( ltime->tm_mday ) + ".log";

		auto r_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>( today, 1024 * 1024 * 10, 10 );
		r_file_sink->set_level( spdlog::level::debug );
		r_file_sink->set_pattern( LogFileSinkFmt );
		sinks.push_back( r_file_sink );

		auto My_Log = std::make_shared<spdlog::logger>( MY_LOG_NAME, begin( sinks ), end( sinks ) );
		My_Log->set_level( spdlog::level::trace );
		spdlog::register_logger( My_Log );
	}
	catch( const spdlog::spdlog_ex& ex )
	{
		std::cout << ( ex.what() );
	}
}
