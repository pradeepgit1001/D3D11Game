#include <DX3D/Core/Logger.h>
#include <iostream>

/**
 * @brief Construct a Logger.
 *
 * Sets the active logging level and prints a small header to the console.
 *
 * @param logLevel Minimum level that will be emitted by log()
 */
dx3d::Logger::Logger(LogLevel logLevel): m_logLevel(logLevel)
{
	std::clog << "LOGGER CONSTRUCTOR" << "\n";
	std::clog << "Pradeep | C++ 3d" << "\n";
	std::clog << "----------------" << "\n";
}

/**
 * @brief Emit a log message if its severity is enabled.
 *
 * The function converts the LogLevel to a string and writes the message to
 * std::clog if the requested level is less than or equal to the configured
 * m_logLevel.
 *
 * @param level Severity of the message
 * @param message Null-terminated message string
 */
void dx3d::Logger::log(LogLevel level, const char* message)
{
	auto logLevelToString = [](LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Info: return "Info";
			case LogLevel::Warning: return "Warning";
			case LogLevel::Error: return "Error";
			default: return "Unknown";
			}
		};

	if (level > m_logLevel) return;
	std::clog << "DX3D " << logLevelToString(level) << "]: " << message << "\n";
}

/**
 * @brief Logger destructor.
 *
 * Writes a shutdown message to the console. No owned resources to free.
 */
dx3d::Logger::~Logger()
{
	std::clog << "logger destructor" << "\n";
}
