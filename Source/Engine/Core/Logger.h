#pragma once



#include <string>
#include <cassert>
#include <fstream>

#define INFO_LOG { neu::g_logger.Log(neu::LogLevel::Info, __FILE__, __LINE__); }
#define WARNING_LOG { neu::g_logger.Log(neu::LogLevel::Warning, __FILE__, __LINE__); }
#define ERROR_LOG { neu::g_logger.Log(neu::LogLevel::Error, __FILE__, __LINE__); }
#define ASSERT_LOG { neu::g_logger.Log(neu::LogLevel::Assert, __FILE__, __LINE__); }

namespace neu
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger
	{
	public:
		Logger(LogLevel loglevel, std::ostream* ostream) : 
			m_ostream{ ostream },
			m_logLevel{ loglevel }
		{}

		bool Log(LogLevel logLevel, const std::string& filename, int line);

	private:
		LogLevel m_logLevel;

		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;
}