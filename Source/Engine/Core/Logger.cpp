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
			*this << "INFORMATION: ";
			break;
		case neu::LogLevel::Warning:
			*this << "WARNING: ";
			break;
		case neu::LogLevel::Error:
			*this << "ERROR: ";
			break;
		case neu::LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << "): ";

		return true;;
	}

	Logger g_logger(LogLevel::Info, &std::cout, "log.txt");
}