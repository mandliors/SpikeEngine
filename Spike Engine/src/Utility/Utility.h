#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "Math/Vector2.h"

namespace Spike {
	namespace Utility {

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

		bool OverlapPoint(const Vector2& point, const Vector2& position, const Vector2& size);
	}
}