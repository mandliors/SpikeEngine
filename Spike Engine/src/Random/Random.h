#pragma once

#include <random>
#include <ctime>
#include <algorithm>

namespace Spike {

	class Random
	{
	public:
		Random() = delete;

		static int Range(int min, int max /*inclusive, inclusive*/);
		static int Float(float min, float max /*inclusive, inclusive*/);
		
		template<typename Iter>
		static void Shuffle(Iter begin, const Iter end)
		{
			m_Generator.seed(time(0));
			std::shuffle(begin, end, m_Generator);
		}
		template<typename T>
		static void Shuffle(T* container)
		{
			Shuffle(std::begin(*container), std::end(*container));
		}

	private:
		static std::mt19937 m_Generator;
	};
}