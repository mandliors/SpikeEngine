#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>

namespace Spike {

	class Debug
	{
	public:
		Debug() = delete;
		~Debug() = default;

		static enum class LOG_LEVEL
		{
			__LOG_LEVEL_ENGINE = 0, LOG_LEVEL_INFO, LOG_LEVEL_WARNING, LOG_LEVEL_ERROR
		};
		template<typename T, typename... Args>
		static void __ENGINE_LOG(T message, const Args&... rest)
		{
			if (s_LogLevel <= LOG_LEVEL::__LOG_LEVEL_ENGINE)
			{
				SetConsoleTextAttribute(s_hConsole, 23);
				time_t now = time(0);
				tm time;
				localtime_s(&time, &now);
				std::cout << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "] " << "INFO: " << message;
				__PRINT(rest...);
			}
		}
		template<typename T, typename... Args>
		static void Log(T message, const Args&... rest)
		{
			if (s_LogLevel <= LOG_LEVEL::LOG_LEVEL_INFO)
			{
				SetConsoleTextAttribute(s_hConsole, 7);
				time_t now = time(0);
				tm time;
				localtime_s(&time, &now);
				std::cout << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "] " << "INFO: " << message;
				__PRINT(rest...);
			}
		}
		template<typename T, typename... Args>
		static void Info(T message, const Args&... rest)
		{
			if (s_LogLevel <= LOG_LEVEL::LOG_LEVEL_INFO)
			{
				SetConsoleTextAttribute(s_hConsole, 7);
				time_t now = time(0);
				tm time;
				localtime_s(&time, &now);
				std::cout << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "] " << "INFO: " << message;
				__PRINT(rest...);
			}
		}
		template<typename T, typename... Args>
		static void Grat(T message, const Args&... rest)
		{
			if (s_LogLevel <= LOG_LEVEL::LOG_LEVEL_INFO)
			{
				SetConsoleTextAttribute(s_hConsole, 2);
				time_t now = time(0);
				tm time;
				localtime_s(&time, &now);
				std::cout << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "] " << "GRAT: " << message;
				__PRINT(rest...);
			}
		}
		template<typename T, typename... Args>
		static void Warn(T message, const Args&... rest)
		{
			if (s_LogLevel <= LOG_LEVEL::LOG_LEVEL_WARNING)
			{
				SetConsoleTextAttribute(s_hConsole, 6);
				time_t now = time(0);
				tm time;
				localtime_s(&time, &now);
				std::cout << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "] " << "WARNING: " << message;
				__PRINT(rest...);
			}
		}
		template<typename T, typename... Args>
		static void Error(T message, const Args&... rest)
		{
			if (s_LogLevel <= LOG_LEVEL::LOG_LEVEL_ERROR)
			{
				SetConsoleTextAttribute(s_hConsole, 4);
				time_t now = time(0);
				tm time;
				localtime_s(&time, &now);
				std::cout << "[" << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "] " << "ERROR: " << message;
				__PRINT(rest...);
			}
		}
		static void SetLogLevel(LOG_LEVEL level);
	private:
		static HANDLE s_hConsole;
		static LOG_LEVEL s_LogLevel;

		static void __PRINT()
		{
			std::cout << std::endl;
		}
		template<typename T, typename... Values>
		static void __PRINT(T message, const Values&... rest)
		{
			std::cout << message;
			__PRINT(rest...);
		}
	};
}