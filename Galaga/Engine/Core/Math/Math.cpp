#include "Math.h"
#include <random>

namespace Math
{
	int Random(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	float Random(float min, float max)
	{
		float alpha = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return min + (max - min) * alpha;
	}

	bool RandomBool()
	{
		return rand() % 2;
	}

	float Lerp(float a, float b, float t)
	{
		float deltaB = b - a;
		float deltaT = t - a;

		return deltaT / deltaB;
	}
}
