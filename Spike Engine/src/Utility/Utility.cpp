#include "Utility.h"

namespace Spike {
	namespace Utility {

		#pragma region Timer
		Timer::Timer(const std::string& name)
			: m_Name(name) { }
		void Timer::Start()
		{
			m_StartTime = std::chrono::high_resolution_clock::now();
		}
		void Timer::Stop()
		{
			auto m_EndTime = std::chrono::high_resolution_clock::now();
		}
		void Timer::Print()
		{
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_EndTime).time_since_epoch().count();

			auto duration = end - start;
			double ms = duration * 0.001;

			if (m_Name != "")
				std::cout << "[Timer] " << m_Name << ": " << duration << "us (" << ms << "ms)" << std::endl;
			else
				std::cout << "[Timer]: " << duration << "us (" << ms << "ms)" << std::endl;
		}
		#pragma endregion

		#pragma region ScopedTimer
		ScopedTimer::ScopedTimer(const std::string& name)
			: m_Name(name), m_StartTime(std::chrono::high_resolution_clock::now()) { }
		ScopedTimer::~ScopedTimer()
		{
			auto endTime = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

			auto duration = end - start;
			double ms = duration * 0.001;

			if (m_Name != "")
				std::cout << "[ScopedTimer] " << m_Name << ": " << duration << "us (" << ms << "ms)" << std::endl;
			else
				std::cout << "[ScopedTimer]: " << duration << "us (" << ms << "ms)" << std::endl;
		}
		#pragma endregion

		#pragma region Functions
		bool OverlapPoint(const Vector2& point, const Vector2& position, const Vector2& size)
		{
			if (point.X < position.X || point.X > position.X + size.X) return false;
			if (point.Y < position.Y || point.Y > position.Y + size.Y) return false;
			return true;
		}
		#pragma endregion
	}
}