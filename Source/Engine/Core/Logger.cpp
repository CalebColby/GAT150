#include "Logger.h"
#include "FileIO.h"

#include <iostream>

namespace neu
{
	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case neu::LogLevel::Info:
			*m_ostream << "INFORMATION: ";
			break;
		case neu::LogLevel::Warning:
			*m_ostream << "WARNING: ";
			break;
		case neu::LogLevel::Error:
			*m_ostream << "ERROR: ";
			break;
		case neu::LogLevel::Assert:
			*m_ostream << "ASSERT: ";
			break;
		default:
			break;
		}

		*m_ostream << getFileName(filename) << "{" << line << "}\n";

		return true;;
	}

	Logger g_logger(LogLevel::Info, &std::cout);
}