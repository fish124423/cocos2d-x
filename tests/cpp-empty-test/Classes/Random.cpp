
#include <ctime>
#include <cstdlib>
using namespace std;

#include "Random.h"
Random::Random()
{
	m_isInit = false;
	srand(time(nullptr));
}

Random::~Random()
{
}

Random* Random::sharedRandom()
{
	static Random s_random;
	return &s_random;
}

int Random::randInt(void)
{
	return randInt32();
}

int Random::randInt(int min, int max)
{
	if (min == max)
	{
		return min;
	}
	return (randInt32() % (max - min)) + min;
}

float Random::randFloat(void)
{
	int iValue = rand();
	return (float)iValue / RAND_MAX;
}

int Random::randInt32()
{
	/*
		http://www.cnblogs.com/ngnetboy/archive/2012/11/23/2784078.html
		linux下的RAND_MAX值为2147483647（二进制32位）
		windows下的RAND_MAX值为32767（二进制16位）
		*/
	if (RAND_MAX == 0x7fff) // win32
	{
		return (rand() << 16) | rand();
	}
	else
	{
		return rand();
	}
}

RandomArray::RandomArray()
{
}
void RandomArray::setRandomArray(int total)
{
	if (!m_RandomArray.size())
	{
		for (int i = 0; i < total; i++)
			m_RandomArray.push_back(i);
	}
}

int RandomArray::getFromRandomArray()
{
	int i = Random::sharedRandom()->randInt() % m_RandomArray.size();
	int temp = m_RandomArray.at(i);

	vector<int>::iterator iter = m_RandomArray.begin() + i;
	iter = m_RandomArray.erase(iter);

	return temp;
}

void RandomArray::clearRandomArray()
{
	m_RandomArray.clear();
}