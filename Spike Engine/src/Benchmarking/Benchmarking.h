#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace Spike { 
	namespace Benchmarking {

		class Timer
		{
		public:
			Timer(const std::string& name = "");
			~Timer() = default;
			void Start();
			void Stop();
			void Print();
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
			std::string m_Name;
		};

		class ScopedTimer
		{
		public:
			ScopedTimer(const std::string& name = "");
			~ScopedTimer();
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
			std::string m_Name;
		};
	}
}