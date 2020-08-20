#include "Random.h"

namespace Spike {

	std::mt19937 Random::m_Generator = std::mt19937();

	int Random::Range(int min, int max /*inclusive, inclusive*/)
	{
		m_Generator.seed(std::time(0));
		std::uniform_int_distribution<int> random(min, max);
		return random(m_Generator);
	}

	int Random::Float(float min, float max /*inclusive, inclusive*/)
	{
		m_Generator.seed(std::time(0));
		std::uniform_real_distribution<float> random(min, max);
		return random(m_Generator);
	}

}