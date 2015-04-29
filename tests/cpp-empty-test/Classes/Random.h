#ifndef __Random_H__
#define __Random_H__

#include <vector>
#include<stdlib.h>
using namespace std;

class Random
{
protected:
    Random();
public:
    ~Random();
    static Random* sharedRandom();

    int randInt();

    // return [min, max)
    int randInt(int min, int max);

    //[0,1)
    float randFloat();

private:
    // 32 bit random number function [10/21/2013 seed]
    int randInt32();
private:
    bool m_isInit;
    vector<int> m_RandomArray;
};

class RandomArray
{
public:
    RandomArray();
    ~RandomArray() { m_RandomArray.clear(); };
    void setRandomArray(int total);
    void clearRandomArray();
    int getFromRandomArray();
private:
    vector<int> m_RandomArray;
};

#endif // __Random_H__
