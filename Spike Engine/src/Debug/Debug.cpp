#include "Debug.h"

namespace Spike {

	HANDLE Debug::s_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Debug::LOG_LEVEL Debug::s_LogLevel = LOG_LEVEL::LOG_LEVEL_INFO;

	void Debug::SetLogLevel(Debug::LOG_LEVEL level)
	{
		s_LogLevel = level;
	}

}