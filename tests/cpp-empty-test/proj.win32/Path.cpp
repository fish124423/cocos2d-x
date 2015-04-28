#include "cocos2d.h"

#include <vector>

#include "Path.h"

const static int s_SplineStep = 4096;

static cocos2d::Vec4* s_splineTable = nullptr;

void initSplineTable2()
{
	s_splineTable = new cocos2d::Vec4[s_SplineStep];

	float t;
	for (int step = 0; step < s_SplineStep; step++)
	{
		t = float(step) / s_SplineStep;
		cocos2d::Vec4 v4(0.5, 0.5*t, 0.5*t*t, 0.5*t*t*t);
		s_splineTable[step] = v4;
	}
}

CPath::CPath():
m_fTimeAcc(0.f)
{

}

bool CPath::init()
{
	if (nullptr == s_splineTable)
		initSplineTable2();

	return true;
}

bool CPath::update(float dt)
{
	m_fTimeAcc += dt;
	return true;
}

void CPath::runSplineLogicEx(cocos2d::Vec3& vRef)
{
	float fPercentage = m_fTimeAcc / m_fTime;

	int nSections = m_PointCon.size() - 3;
	m_PointCon[0] = m_vInitPos;
	int currPt = std::min((int)(floor(fPercentage*(float)nSections)), nSections - 1);

	float   t = fPercentage * (float)nSections - (float)currPt;
	float   fstep = t*(s_SplineStep - 1);
	int     nStep = (int)fstep;
	float   fVal = fstep - nStep - 0.5f;
	if (fVal > 0.0001f)
	{
		++nStep;
	}

	cocos2d::Vec3& a = m_PointCon[currPt];
	cocos2d::Vec3& b = m_PointCon[currPt + 1];
	cocos2d::Vec3& c = m_PointCon[currPt + 2];
	cocos2d::Vec3& d = m_PointCon[currPt + 3];

	// 计算出当前点坐标
	vRef = (-a + 3 * b - 3 * c + d)*s_splineTable[nStep].w + (2 * a - 5 * b + 4 * c - d)*s_splineTable[nStep].z + (-a + c)*s_splineTable[nStep].y + b;
}