#ifndef __PATH__
#define __PATH__

class CPath
{
public:
	CPath();
	virtual ~CPath() {}

	static bool					init();

	virtual void				debugDraw() {}

	bool						update(float dt);

	void						runSplineLogicEx(cocos2d::Vec3& vRef);
public:

	float						m_fTime;    
	float						m_fTimeAcc;

	std::vector<cocos2d::Vec3>	m_PointCon;
};

#endif